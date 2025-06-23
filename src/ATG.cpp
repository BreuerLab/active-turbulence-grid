// Required include files
#include "mex.h"
#include "pubSysCls.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <cmath>

#define VERBOSE 0
#define HOMING  0

#define mex_Printff(...)                                                       \
  {                                                                            \
    mexPrintf(__VA_ARGS__);                                                    \
    mexEvalString("drawnow;");                                                 \
  }

using namespace sFnd;

#define ACC_LIM_RPM_PER_SEC 100000
#define VEL_LIM_RPM 700
#define TIME_TILL_TIMEOUT 10000

void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]) {
    size_t Speed;
    char* Command;
    std::vector<size_t> Channels;
    if (nrhs == 0) {
        mex_Printff("USAGE: preliminaryFunctions( Command, Channel, Speed )\n");
        return;
    }
    Command = mxArrayToString(prhs[0]);
    if (!mxIsDouble(prhs[1]) || mxIsComplex(prhs[1]) || mxGetNumberOfDimensions(prhs[1]) != 2) {
        mex_Printff("Second argument must be a 1D numeric array of channels\n");
        return;
    }
    size_t numChannels = mxGetNumberOfElements(prhs[1]);
    double* channelData = mxGetPr(prhs[1]);
    for (size_t i = 0; i < numChannels; ++i) {
        if (channelData[i] < 0 || floor(channelData[i]) != channelData[i]) {
            mex_Printff("Invalid channel index: %f. Must be non-negative integer.\n", channelData[i]);
            return;
        }
        Channels.push_back(static_cast<size_t>(channelData[i]));
    }
    if (nrhs < 3) {
        mex_Printff("Missing third argument (Speed or Angle)\n");
        return;
    }
    Speed = static_cast<size_t>(mxGetScalar(prhs[2]));
    mex_Printff("preliminaryFunctions: Command: %s; Channels: [", Command);
    for (size_t ch : Channels) mex_Printff("%zu ", ch);
    mex_Printff("]; Speed: %zu\n", Speed);

    size_t portCount = 0;
    std::vector<std::string> comHubPorts;
    SysManager* myMgr = SysManager::Instance();
    try {
        SysManager::FindComHubPorts(comHubPorts);
        for (portCount = 0; portCount < comHubPorts.size() && portCount < NET_CONTROLLER_MAX; portCount++) {
            myMgr->ComHubPort(portCount, comHubPorts[portCount].c_str());
        }
        if (portCount < 1) {
            mex_Printff("Unable to locate SC hub port\n");
            return;
        }
        myMgr->PortsOpen(portCount);

        std::vector<INode*> selectedNodes;
        for (size_t i = 0; i < portCount; i++) {
            IPort& myPort = myMgr->Ports(i);
            for (size_t iNode = 0; iNode < myPort.NodeCount(); iNode++) {
                INode& theNode = myPort.Nodes(iNode);
                theNode.EnableReq(false);
                myMgr->Delay(200);
                theNode.Status.AlertsClear();
                theNode.Motion.NodeStopClear();
                theNode.EnableReq(true);
                double timeout = myMgr->TimeStampMsec() + TIME_TILL_TIMEOUT;
                while (!theNode.Motion.IsReady()) {
                    if (myMgr->TimeStampMsec() > timeout) {
                        mex_Printff("Error: Timed out waiting for Node %d to enable\n", (int)iNode);
                        return;
                    }
                }
            }
            for (size_t ch : Channels) {
                selectedNodes.push_back(&myPort.Nodes(ch));
            }
        }

        if (strcmp(Command, "RUN") == 0) {
            for (INode* node : selectedNodes) node->Motion.MoveVelStart(Speed);
            double startTime = myMgr->TimeStampMsec();
            double timeout = startTime + 15000;
            while (myMgr->TimeStampMsec() < timeout) myMgr->Delay(100);
            for (INode* node : selectedNodes) node->Motion.MoveVelStart(0);
        }
        else if (strcmp(Command, "POSITION") == 0) {
            double angleDeg = mxGetScalar(prhs[2]);
            for (INode* node : selectedNodes) {
                size_t countsPerRev = static_cast<size_t>(node->Info.PositioningResolution.Value());
                int32_t targetCounts = static_cast<int32_t>((angleDeg / 360.0) * countsPerRev);
                node->Motion.MovePosnStart(targetCounts, true);
            }
            double timeout = myMgr->TimeStampMsec() + 10000;
            for (INode* node : selectedNodes) {
                while (!node->Motion.MoveIsDone()) {
                    if (myMgr->TimeStampMsec() > timeout) break;
                    myMgr->Delay(50);
                }
            }
        }
        else if (strcmp(Command, "SETHOME") == 0) {
            for (INode* node : selectedNodes) {
                double currentPos = node->Motion.PosnMeasured.Value();
                node->Motion.AddToPosition(-currentPos);
                node->Motion.Homing.SignalComplete();
            }
        }
        else if (strcmp(Command, "FLAP") == 0) {
            if (nrhs < 4) {
                mex_Printff("Usage: ClearView('FLAP', Channels[], AngleDegrees, SpeedRPM)\n");
                return;
            }
            double flapAngleDeg = mxGetScalar(prhs[2]);
            double flapSpeedRPM = mxGetScalar(prhs[3]);
            for (INode* node : selectedNodes) {
                size_t countsPerRev = static_cast<size_t>(node->Info.PositioningResolution.Value());
                int32_t flapOffset = static_cast<int32_t>((flapAngleDeg / 360.0) * countsPerRev);
                node->AccUnit(INode::RPM_PER_SEC);
                node->VelUnit(INode::RPM);
                node->Motion.AccLimit = ACC_LIM_RPM_PER_SEC;
                node->Motion.VelLimit = flapSpeedRPM;
                node->Motion.NodeStopClear();
            }
            double startTime = myMgr->TimeStampMsec();
            double flapDuration = 5000;
            double endTime = startTime + flapDuration;
            while (myMgr->TimeStampMsec() < endTime) {
                for (INode* node : selectedNodes) {
                    int32_t center = static_cast<int32_t>(node->Motion.PosnMeasured.Value());
                    int32_t flapOffset = static_cast<int32_t>((flapAngleDeg / 360.0) * node->Info.PositioningResolution.Value());
                    node->Motion.MovePosnStart(center + flapOffset, true);
                }
                for (INode* node : selectedNodes) while (!node->Motion.MoveIsDone()) myMgr->Delay(5);
                for (INode* node : selectedNodes) node->Motion.MovePosnStart(node->Motion.PosnMeasured.Value(), true);
                for (INode* node : selectedNodes) while (!node->Motion.MoveIsDone()) myMgr->Delay(5);
                for (INode* node : selectedNodes) {
                    int32_t center = static_cast<int32_t>(node->Motion.PosnMeasured.Value());
                    int32_t flapOffset = static_cast<int32_t>((flapAngleDeg / 360.0) * node->Info.PositioningResolution.Value());
                    node->Motion.MovePosnStart(center - flapOffset, true);
                }
                for (INode* node : selectedNodes) while (!node->Motion.MoveIsDone()) myMgr->Delay(5);
                for (INode* node : selectedNodes) node->Motion.MovePosnStart(node->Motion.PosnMeasured.Value(), true);
                for (INode* node : selectedNodes) while (!node->Motion.MoveIsDone()) myMgr->Delay(5);
            }
        }
    }
    catch (mnErr& theErr) {
        mex_Printff("Caught error: addr=%d, err=0x%08x\nmsg=%s\n", theErr.TheAddr, theErr.ErrorCode, theErr.ErrorMsg);
        return;
    }
    myMgr->PortsClose();
}
