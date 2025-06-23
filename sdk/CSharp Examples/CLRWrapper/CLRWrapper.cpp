// This is the main DLL file.

#include "CLRWrapper.h"

using namespace sFndCLIWrapper;


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
// SysManager implementations
//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
cliSysMgr::cliSysMgr() : myMgr(SysManager::Instance()) {}
cliSysMgr::!cliSysMgr(){
	delete myMgr;
	myMgr = nullptr;
}

cliINode^ cliSysMgr::NodeGet(multiaddr theMultiAddr) {
	return gcnew cliINode(myMgr->NodeGet(theMultiAddr));
}

void cliSysMgr::FindComHubPorts(List<System::String^> ^comHubPorts) {
	std::vector<std::string> hubPorts;
	myMgr->FindComHubPorts(hubPorts);
	for (int i = 0; i < (int)hubPorts.size(); i++) {
		System::String^ name(gcnew System::String(hubPorts[i].c_str()));
		comHubPorts->Add(name);
		delete name;
	}
}

void cliSysMgr::ComPortHub(uintptr_t netNumber, System::String^ portPath, _netRates portRate) {
	msclr::interop::marshal_context oMarshalContext;
	const char* path = oMarshalContext.marshal_as<const char*>(portPath);
	myMgr->ComHubPort((size_t)netNumber, path, (netRates)portRate);
}

void cliSysMgr::PortsOpen(uintptr_t portCount) {
	try {
		myMgr->PortsOpen((size_t)portCount);
	}
	catch (...) {
		printf("ERROR: A problem occurred while trying to open the designated port(s). \n");
	}
}
void cliSysMgr::PortsOpen(int portCount) {
	try {
		myMgr->PortsOpen(portCount);
	}
	catch (...) {
		printf("ERROR: A problem occurred while trying to open the designated port(s). \n");
	}
}

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
// cliINode implementations
//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
cliINode::cliINode(INode &node) : myNode(node),
m_Port(gcnew cliIPort(myNode.Port)),
m_Info(gcnew cliIInfo(myNode.Info)),
m_Motion(gcnew cliIMotion(myNode.Motion)),
m_Status(gcnew cliIStatus(myNode.Status)),
m_Limits(gcnew cliILimits(myNode.Limits)),
m_Outs(gcnew cliIOuts(myNode.Outs)),
m_Setup(gcnew cliISetup(myNode.Setup)),
m_Ex(gcnew cliINodeEx(myNode.Ex)),
m_Adv(gcnew cliINodeAdv(myNode.Adv)) {}

cliINode::cliINode(const cliINode% node) : myNode(node.myNode),
m_Port(gcnew cliIPort(myNode.Port)),
m_Info(gcnew cliIInfo(myNode.Info)),
m_Motion(gcnew cliIMotion(myNode.Motion)),
m_Status(gcnew cliIStatus(myNode.Status)),
m_Limits(gcnew cliILimits(myNode.Limits)),
m_Outs(gcnew cliIOuts(myNode.Outs)),
m_Setup(gcnew cliISetup(myNode.Setup)),
m_Ex(gcnew cliINodeEx(myNode.Ex)),
m_Adv(gcnew cliINodeAdv(myNode.Adv)) {}

cliINode::!cliINode() {
	delete m_Port;
	delete m_Info;
	delete m_Motion;
	delete m_Status;
	delete m_Limits;
	delete m_Outs;
	delete m_Setup;
	delete m_Ex;
	delete m_Adv;
}

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
// cliIPort implementations
//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
cliIPort::cliIPort(IPort &port) : myPort(port),
m_GrpShutdown(gcnew cliIGrpShutdown(myPort.GrpShutdown)),
m_BrakeControl(gcnew cliIBrakeControl(myPort.BrakeControl)),
m_Adv(gcnew cliIPortAdv(myPort.Adv)) {}
cliIPort::!cliIPort() {
	delete m_GrpShutdown;
	delete m_BrakeControl;
	delete m_Adv;
}

void cliIPort::CommandTraceSave(System::String^ filePath) {
	msclr::interop::marshal_context oMarshalContext;
	const char* path = oMarshalContext.marshal_as<const char*>(filePath);
	myPort.CommandTraceSave(path);
}

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
// cliIMotion implementations
//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
cliIMotion::cliIMotion(IMotion &val) : myMotion(val),
m_AccLimit(gcnew cliValueDouble(myMotion.AccLimit)),
m_VelLimit(gcnew cliValueDouble(myMotion.VelLimit)),
m_JrkLimit(gcnew cliValueUnsigned(myMotion.JrkLimit)),
m_JrkLimitDelay(gcnew cliValueDouble(myMotion.JrkLimitDelay)),
m_DwellMs(gcnew cliValueUnsigned(myMotion.DwellMs)),
m_NodeStopDecelLim(gcnew cliValueDouble(myMotion.NodeStopDecelLim)),
m_PosnMeasured(gcnew cliValueDouble(myMotion.PosnMeasured)),
m_PosnCommanded(gcnew cliValueDouble(myMotion.PosnCommanded)),
m_PosnTracking(gcnew cliValueDouble(myMotion.PosnTracking)),
m_VelMeasured(gcnew cliValueDouble(myMotion.VelMeasured)),
m_VelCommanded(gcnew cliValueDouble(myMotion.VelCommanded)),
m_TrqMeasured(gcnew cliValueDouble(myMotion.TrqMeasured)),
m_TrqCommanded(gcnew cliValueDouble(myMotion.TrqCommanded)),
m_Adv(gcnew cliIMotionAdv(myMotion.Adv)),
m_Homing(gcnew cliIHoming(myMotion.Homing)) {}

cliIMotion::!cliIMotion() {
	delete m_AccLimit;
	delete m_VelLimit;
	delete m_JrkLimit;
	delete m_JrkLimitDelay;
	delete m_DwellMs;
	delete m_NodeStopDecelLim;
	delete m_PosnMeasured;
	delete m_PosnCommanded;
	delete m_PosnTracking;
	delete m_VelMeasured;
	delete m_VelCommanded;
	delete m_TrqMeasured;
	delete m_TrqCommanded;
	delete m_Adv;
	delete m_Homing;
}

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
// cliIMotionAudit implementations
//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
cliIMotionAudit::cliIMotionAudit(IMotionAudit &val) : myMotionAudit(val),
m_Results(gcnew cliAuditData(myMotionAudit.Results)) {}
cliIMotionAudit::!cliIMotionAudit() {
	delete m_Results;
}

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
// cliIPortAdv implementations
//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
cliIPortAdv::cliIPortAdv(IPortAdv &val) : myPortAdv(val),
m_Attn(gcnew cliIAttnPort(myPortAdv.Attn)){}
cliIPortAdv::!cliIPortAdv() {
	delete m_Attn;
}

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
// cliIGrpShutdown implementations
//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
void cliIGrpShutdown::ShutdownWhen(uintptr_t nodeIndex, cliShutdownInfo^ theInfo) {
	myGrpShutdown.ShutdownWhen((size_t)nodeIndex, *theInfo->Info);
}
cliShutdownInfo^ cliIGrpShutdown::ShutdownWhenGet(uintptr_t nodeIndex) {
	ShutdownInfo info;
	myGrpShutdown.ShutdownWhenGet((size_t)nodeIndex, info);
	return gcnew cliShutdownInfo(&info);
}

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
// cliIInfo implementations
//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
cliIInfo::cliIInfo(IInfo &val) : myInfo(val),
m_Adv(gcnew cliIInfoAdv(myInfo.Adv)),
m_Ex(gcnew cliIInfoEx(myInfo.Ex)),
m_SerialNumber(gcnew cliValueUnsigned(myInfo.SerialNumber)),
m_FirmwareVersion(gcnew cliValueString(myInfo.FirmwareVersion)),
m_FirmwareVersionCode(gcnew cliValueUnsigned(myInfo.FirmwareVersionCode)),
m_HardwareVersion(gcnew cliValueString(myInfo.HardwareVersion)),
m_Model(gcnew cliValueString(myInfo.Model)),
m_PositioningResolution(gcnew cliValueUnsigned(myInfo.PositioningResolution)),
m_UserID(gcnew cliValueString(myInfo.UserID)),
m_UserRAM(gcnew cliValueUnsigned(myInfo.UserRAM)) {}
cliIInfo::!cliIInfo() {
	delete m_Adv;
	delete m_Ex;
	delete m_SerialNumber;
	delete m_FirmwareVersion;
	delete m_FirmwareVersionCode;
	delete m_HardwareVersion;
	delete m_Model;
	delete m_PositioningResolution;
	delete m_UserID;
	delete m_UserRAM;
}

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
// cliIStatus implementations
//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
cliIStatus::cliIStatus(IStatus &val) : myStatus(val),
m_RT(gcnew cliValueStatus(myStatus.RT)),
m_Rise(gcnew cliValueStatus(myStatus.Rise)),
m_Fall(gcnew cliValueStatus(myStatus.Fall)),
m_Accum(gcnew cliValueStatus(myStatus.Accum)),
m_Warnings(gcnew cliValueAlert(myStatus.Warnings)),
m_Alerts(gcnew cliValueAlert(myStatus.Alerts)),
m_RMSLevel(gcnew cliValueDouble(myStatus.RMSlevel)),
m_Power(gcnew cliValuePowerReg(myStatus.Power)),
m_Adv(gcnew cliIStatusAdv(myStatus.Adv)) {}
cliIStatus::!cliIStatus() {
	delete m_RT;
	delete m_Rise;
	delete m_Fall;
	delete m_Accum;
	delete m_Warnings;
	delete m_Alerts;
	delete m_RMSLevel;
	delete m_Power;
	delete m_Adv;
}

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
// cliILimits implementations
//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
cliILimits::cliILimits(ILimits &val) : myLimits(val),
m_TrqGlobal(gcnew cliValueDouble(myLimits.TrqGlobal)),
m_SoftLimit1(gcnew cliValueSigned(myLimits.SoftLimit1)),
m_SoftLimit2(gcnew cliValueSigned(myLimits.SoftLimit2)),
m_PosnTrackingLimit(gcnew cliValueUnsigned(myLimits.PosnTrackingLimit)),
m_MotorSpeedLimit(gcnew cliValueDouble(myLimits.MotorSpeedLimit)),
m_Adv(gcnew cliILimitsAdv(myLimits.Adv)) {}
cliILimits::!cliILimits() {
	delete m_TrqGlobal;
	delete m_SoftLimit1;
	delete m_SoftLimit2;
	delete m_PosnTrackingLimit;
	delete m_MotorSpeedLimit;
	delete m_Adv;
}

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
// cliIOuts implementations
//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
cliIOuts::cliIOuts(IOuts &val) : myOuts(val),
m_User(gcnew cliValueOutReg(myOuts.User)),
m_Out(gcnew cliValueOutReg(myOuts.Out)) {}
cliIOuts::!cliIOuts() {
	delete m_User;
	delete m_Out;
}

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
// cliISetup implementations
//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
cliISetup::cliISetup(ISetup &val) : mySetup(val),
m_DelayToDisableMsecs(gcnew cliValueDouble(mySetup.DelayToDisableMsecs)),
m_Ex(gcnew cliISetupEx(mySetup.Ex)) {}
cliISetup::!cliISetup() {
	delete m_DelayToDisableMsecs;
	delete m_Ex;
}
void cliISetup::ConfigLoad(System::String^ filePath, bool doReset) {
	System::IntPtr path = Marshal::StringToHGlobalAnsi(filePath);
	mySetup.ConfigLoad((const char*)(void*)path, doReset);
	Marshal::FreeHGlobal(path);
}
void cliISetup::ConfigSave(System::String^ filePath) {
	System::IntPtr path = Marshal::StringToHGlobalAnsi(filePath);
	mySetup.ConfigSave((const char*)(void*)path);
	Marshal::FreeHGlobal(path);
}

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
// cliINodeAdv implementations
//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
cliINodeAdv::cliINodeAdv(INodeAdv &val) : myNodeAdv(val),
m_Attn(gcnew cliIAttnNode(myNodeAdv.Attn)),
m_MotionAudit(gcnew cliIMotionAudit(myNodeAdv.MotionAudit)) {}
cliINodeAdv::!cliINodeAdv() {
	delete m_Attn;
	delete m_MotionAudit;
}

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
// cliIMotionAdv implementations
//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
cliIMotionAdv::cliIMotionAdv(IMotionAdv &val) : myMotionAdv(val),
m_AAfterStartDistance(gcnew cliValueUnsigned(myMotionAdv.AfterStartDistance)),
m_BeforeEndDistance(gcnew cliValueUnsigned(myMotionAdv.BeforeEndDistance)),
m_DecelLimit(gcnew cliValueDouble(myMotionAdv.DecelLimit)),
m_HeadTailVelLimit(gcnew cliValueDouble(myMotionAdv.HeadTailVelLimit)),
m_HeadDistance(gcnew cliValueUnsigned(myMotionAdv.HeadDistance)),
m_TailDistance(gcnew cliValueUnsigned(myMotionAdv.TailDistance)) {}
cliIMotionAdv::!cliIMotionAdv() {
	delete m_AAfterStartDistance;
	delete m_BeforeEndDistance;
	delete m_DecelLimit;
	delete m_HeadTailVelLimit;
	delete m_HeadDistance;
	delete m_TailDistance;
}

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
// cliIStatusAdv implementations
//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
cliIStatusAdv::cliIStatusAdv(IStatusAdv &val) : myStatusAdv(val),
m_CapturedHiResPosn(gcnew cliValueSigned(myStatusAdv.CapturedHiResPosn)),
m_CapturedPos(gcnew cliValueSigned(myStatusAdv.CapturedPos)) {}
cliIStatusAdv::!cliIStatusAdv() {
	delete m_CapturedHiResPosn;
	delete m_CapturedPos;
}

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
// cliIAttnNode implementations
//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
cliIAttnNode::cliIAttnNode(IAttnNode &val) : myAttnNode(val),
m_AlertMask(gcnew cliValueAlert(myAttnNode.AlertMask)),
m_Mask(gcnew cliValueStatus(myAttnNode.Mask)),
m_StatusMask(gcnew cliValueStatus(myAttnNode.StatusMask)),
m_WarnMask(gcnew cliValueAlert(myAttnNode.WarnMask)) {}
cliIAttnNode::!cliIAttnNode() {
	delete m_AlertMask;
	delete m_Mask;
	delete m_StatusMask;
	delete m_WarnMask;
}

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
// cliILimitsAdv implementations
//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
cliILimitsAdv::cliILimitsAdv(ILimitsAdv &val) : myLimitsAdv(val),
m_NegativeRelaxTCmsec(gcnew cliValueDouble(myLimitsAdv.NegativeRelaxTCmsec)),
m_NegativeTrq(gcnew cliValueDouble(myLimitsAdv.NegativeTrq)),
m_PositiveRelaxTCmsec(gcnew cliValueDouble(myLimitsAdv.PositiveRelaxTCmsec)),
m_PositiveTrq(gcnew cliValueDouble(myLimitsAdv.PositiveTrq)) {}
cliILimitsAdv::!cliILimitsAdv() {
	delete m_NegativeRelaxTCmsec;
	delete m_NegativeTrq;
	delete m_PositiveRelaxTCmsec;
	delete m_PositiveTrq;
}

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
// cliIAuditData implementations
//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
cliAuditData::cliAuditData(mnAuditData &val) : myAuditData(val),
m_LowPassRMS(gcnew double(myAuditData.LowPassRMS)),
m_LowPassMaxPos(gcnew double(myAuditData.LowPassMaxPos)),
m_LowPassMaxNeg(gcnew double(myAuditData.LowPassMaxNeg)),
m_HighPassRMS(gcnew double(myAuditData.HighPassRMS)),
m_DurationMS(gcnew double(myAuditData.DurationMS)),
m_MaxTrackingPos(gcnew nodelong(myAuditData.MaxTrackingPos)),
m_MaxTrackingNeg(gcnew nodelong(myAuditData.MaxTrackingNeg)) {}
cliAuditData::!cliAuditData() {
	delete m_LowPassRMS;
	delete m_LowPassMaxPos;
	delete m_LowPassMaxNeg;
	delete m_HighPassRMS;
	delete m_DurationMS;
	delete m_MaxTrackingPos;
	delete m_MaxTrackingNeg;
}

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
// cliISetupEx implementations
//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
cliISetupEx::cliISetupEx(ISetupEx &val) : mySetupEx(val),
m_NetWatchdogMsec(gcnew cliValueDouble(mySetupEx.NetWatchdogMsec)),
m_App(gcnew cliValueAppConfigReg(mySetupEx.App)),
m_HW(gcnew cliValueHwConfigReg(mySetupEx.HW)) {}
cliISetupEx::!cliISetupEx() {
	delete m_NetWatchdogMsec;
	delete m_App;
	delete m_HW;
}

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
// cliIInfoEx implementations
//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
cliIInfoEx::cliIInfoEx(IInfoEx &val) : myInfoEx(val),
m_Addr(gcnew multiaddr(myInfoEx.Addr())),
m_NodeIndex(gcnew nodeaddr(myInfoEx.NodeIndex())) {}
cliIInfoEx::!cliIInfoEx() {
	delete m_Addr;
	delete m_NodeIndex;
}

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
// cliMNErr implementations
//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
cliMNErr::cliMNErr(mnErr &val) : myErr(val),
m_TheAddr(gcnew multiaddr(myErr.TheAddr)),
m_ErrorMsg(gcnew System::String(myErr.ErrorMsg)) {}
cliMNErr::!cliMNErr() {
	delete m_TheAddr;
	delete m_ErrorMsg;
}

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
// cliCommonStatusFlds implementations
//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
cliCommonStatusFlds::cliCommonStatusFlds(commonStatusFlds &flds) : myFlds(flds),
m_LowAttn(gcnew cliLowAttnCommonFlds(myFlds.LowAttn)),
m_PlaIn(gcnew cliPlaInCommonFlds(myFlds.PlaIn)),
m_NonAttn(gcnew cliNonAttnCommonFlds(myFlds.NonAttn)) {}
cliCommonStatusFlds::!cliCommonStatusFlds() {
	delete m_LowAttn;
	delete m_PlaIn;
	delete m_NonAttn;
}

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
// cliIscStatusRegFlds implementations
//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
cliIscStatusRegFlds::cliIscStatusRegFlds(iscStatusRegFlds &flds) : myFlds(flds),
m_LowAttn(gcnew cliIscLowAttnFlds(myFlds.LowAttn)),
m_PlaIn(gcnew cliIscPlaInFlds(myFlds.PLAin)),
m_NonAttn(gcnew cliIscNonAttnFlds(myFlds.NonAttn)) {}
cliIscStatusRegFlds::!cliIscStatusRegFlds() {
	delete m_LowAttn;
	delete m_PlaIn;
	delete m_NonAttn;
}

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
// cliMNStatusReg implementations
//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
cliMNStatusReg::cliMNStatusReg() : myReg(new mnStatusReg()),
m_AttnBits(gcnew Uint32(myReg->attnBits)),
m_Common(gcnew cliCommonStatusFlds(myReg->Common)),
m_Isc(gcnew cliIscStatusRegFlds(myReg->isc)),
m_CPM(gcnew cliCPMStatusRegFlds(myReg->cpm)) {
	m_Bits = gcnew array<Uint16>(3);
	m_Bits[0] = myReg->bits[0];
	m_Bits[1] = myReg->bits[1];
	m_Bits[2] = myReg->bits[2];
}
cliMNStatusReg::cliMNStatusReg(mnStatusReg &reg) : myReg(new mnStatusReg(reg)),
m_AttnBits(gcnew Uint32(myReg->attnBits)),
m_Common(gcnew cliCommonStatusFlds(myReg->Common)),
m_Isc(gcnew cliIscStatusRegFlds(myReg->isc)),
m_CPM(gcnew cliCPMStatusRegFlds(myReg->cpm)) {
	m_Bits = gcnew array<Uint16>(3);
	m_Bits[0] = myReg->bits[0];
	m_Bits[1] = myReg->bits[1];
	m_Bits[2] = myReg->bits[2];
}
cliMNStatusReg::!cliMNStatusReg() {
	delete[] m_Bits;
	delete m_AttnBits;
	delete m_Common;
	delete m_Isc;
	delete m_CPM;
	delete myReg;
	myReg = nullptr;
}

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
// cliMNAttnReqReg implementations
//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
cliMNAttnReqReg::!cliMNAttnReqReg() {
	delete myReg;
	myReg = nullptr;
}

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
// cliAlertReg implementations
//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
cliAlertReg::cliAlertReg() : myReg(new alertReg()),
m_Common(gcnew cliCommonAlertFlds(myReg->Common)),
m_DrvFld(gcnew cliIscAlertFlds(myReg->DrvFld)),
m_CPM(gcnew cliCPMAlertFlds(myReg->cpm)) {
	m_Bits = gcnew array<Uint32>(3);
	m_Bits[0] = myReg->bits[0];
	m_Bits[1] = myReg->bits[1];
	m_Bits[2] = myReg->bits[2];
}
cliAlertReg::cliAlertReg(alertReg &reg) : myReg(new alertReg(reg)),
m_Common(gcnew cliCommonAlertFlds(myReg->Common)),
m_DrvFld(gcnew cliIscAlertFlds(myReg->DrvFld)),
m_CPM(gcnew cliCPMAlertFlds(myReg->cpm)) {
	m_Bits = gcnew array<Uint32>(3);
	m_Bits[0] = myReg->bits[0];
	m_Bits[1] = myReg->bits[1];
	m_Bits[2] = myReg->bits[2];
}
cliAlertReg::!cliAlertReg() {
	delete[] m_Bits;
	delete m_Common;
	delete m_DrvFld;
	delete m_CPM;
	delete myReg;
	myReg = nullptr;
}
System::String^ cliAlertReg::StateStr() {
	char charBuf[256];
	return (gcnew System::String(myReg->StateStr(charBuf, sizeof(charBuf))));
}

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
// cliIscAlertFlds implementations
//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
cliIscAlertFlds::cliIscAlertFlds(iscAlertFlds &flds) : myFlds(new iscAlertFlds(flds)),
m_Common(gcnew cliCommonAlertFlds(myFlds->Common)) {}
cliIscAlertFlds::!cliIscAlertFlds() {
	delete m_Common;
	delete myFlds;
	myFlds = nullptr;
}

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
// cliCPMAlertFlds implementations
//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
cliCPMAlertFlds::cliCPMAlertFlds(cpmAlertFlds &flds) : myFlds(flds),
m_Common(gcnew cliCommonAlertFlds(myFlds.Common)) {}
cliCPMAlertFlds::!cliCPMAlertFlds() {
	delete m_Common;
}

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
// cliMGNodeStopReg implementations
//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
cliMGNodeStopReg::cliMGNodeStopReg() : myReg(new mgNodeStopReg()),
m_CPM(gcnew cliCPMNodeStopFlds(myReg->cpm)),
m_ISC(gcnew cliISCNodeStopFlds(myReg->isc)),
m_Bits((cliNodeStopCodes)myReg->bits),
m_Fld(gcnew cliNodeStopFlds(myReg->fld)) {}
cliMGNodeStopReg::cliMGNodeStopReg(mgNodeStopReg &reg) : myReg(new mgNodeStopReg(reg)),
m_CPM(gcnew cliCPMNodeStopFlds(myReg->cpm)),
m_ISC(gcnew cliISCNodeStopFlds(myReg->isc)),
m_Bits((cliNodeStopCodes)myReg->bits),
m_Fld(gcnew cliNodeStopFlds(myReg->fld)) {}
cliMGNodeStopReg::!cliMGNodeStopReg() {
	delete m_CPM;
	delete m_ISC;
	delete m_Fld;
	delete myReg;
	myReg = nullptr;
}

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
// cliShutdownInfo implementations
//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 
cliShutdownInfo::cliShutdownInfo() : myInfo(new ShutdownInfo()),
m_StatusMask(gcnew cliMNStatusReg(myInfo->statusMask)),
m_StopType(gcnew cliMGNodeStopReg(myInfo->theStopType)) {}
cliShutdownInfo::cliShutdownInfo(ShutdownInfo* info) : myInfo(info),
m_StatusMask(gcnew cliMNStatusReg(myInfo->statusMask)),
m_StopType(gcnew cliMGNodeStopReg(myInfo->theStopType)) {}
cliShutdownInfo::!cliShutdownInfo() {
	delete m_StatusMask;
	delete m_StopType;
	delete myInfo;
	myInfo = nullptr;
}
