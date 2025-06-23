using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using sFndCLIWrapper;

namespace CSharpHomingEx
{
    class Homing
    {

        const int CHANGE_NUMBER_SPACE = 2000;   //The change to the numberspace after homing (cnts)
        const int TIME_TILL_TIMEOUT = 10000;    //The timeout used for homing(ms)

        static void ExitProgram(int errCode)
        {
            Console.WriteLine("Press enter to continue.");
            Console.ReadLine();
            Environment.Exit(errCode);
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Homing Example starting. Press Enter to continue.");
            Console.ReadLine();

            //Create the SysManager object. This object will coordinate actions among various ports
            // and within nodes. In this example we use this object to setup and open our port.
            cliSysMgr myMgr = new cliSysMgr();
            List<String> comHubPorts = new List<String>();

            //This will try to open the port. If there is an error/exception during the port opening,
            //the code will jump to the catch loop where detailed information regarding the error will be displayed;
            //otherwise the catch loop is skipped over
            myMgr.FindComHubPorts(comHubPorts);
            int portCount = comHubPorts.Count;
            Console.WriteLine("Found {0} SC Hubs.", comHubPorts.Count);

            for (int i = 0; i < portCount && portCount < 3; i++)
            {
                myMgr.ComPortHub((uint)i, comHubPorts[i], cliSysMgr._netRates.MN_BAUD_12X);
            }

            if (portCount < 1)
            {
                Console.WriteLine("Unable to locate SC hub port.");
                ExitProgram(-1);
            }

            myMgr.PortsOpen(portCount);
            for (int i = 0; i < portCount; i++)
            {
                cliIPort myPort = myMgr.Ports(i);
                cliINode[] myNodes = new cliINode[myPort.NodeCount()];
                Console.WriteLine("Port {0}: state={1}, nodes={2}", myPort.NetNumber(), myPort.OpenState(), myPort.NodeCount());

                //Once the code gets past this point, it can be assumed that the Port has been opened without issue
                //Now we can get a reference to our port object which we will use to access the node objects
                for (int n = 0; n < myPort.NodeCount(); n++)
                {
                    // Create a shortcut reference for a node
                    myNodes[n] = myPort.Nodes(n);
                    myNodes[n].EnableReq(false);       //Ensure Node is disabled
                    myMgr.Delay(200);

                    Console.WriteLine("   Node[{0}]: type={1}", n, myNodes[n].Info.NodeType());
                    Console.WriteLine("            userID: {0}", myNodes[n].Info.UserID);
                    Console.WriteLine("        FW version: {0}", myNodes[n].Info.FirmwareVersion.Value());
                    Console.WriteLine("          Serial #: {0}", myNodes[n].Info.SerialNumber.Value());
                    Console.WriteLine("             Model: {0}", myNodes[n].Info.Model.Value());

                    // The following statements will attempt to enable the node.  First,
                    // any shutdowns or NodeStops are cleared, finally the node is enabled
                    myNodes[n].Status.AlertsClear();
                    myNodes[n].Motion.NodeStopClear();
                    myNodes[n].EnableReq(true);
                    Console.WriteLine("Node {0} enabled.", n);
                    double timeout = myMgr.TimeStampMsec() + TIME_TILL_TIMEOUT;     // Define a timeout in case the node is unable to enable
                                                                                    // This will loop checking on the Real time values of the node's Ready status
                    while (!myNodes[n].Motion.IsReady())
                    {
                        if (myMgr.TimeStampMsec() > timeout)
                        {
                            Console.WriteLine("Error: Timed out waiting for Node {0} to enable.", n);
                            ExitProgram(-1);
                        }
                    }

                    if (myNodes[n].Motion.Homing.HomingValid())
                    {
                        if (myNodes[n].Motion.Homing.WasHomed())
                        {
                            Console.WriteLine("Node {0} has already been homed, current position is: {1} ", n, myNodes[n].Motion.PosnMeasured.Value());
                            Console.WriteLine("Rehoming Node... \n");
                        }
                        else
                        {
                            Console.WriteLine("Node [{0}] has not been homed.  Homing Node now...", n);
                        }
                        // Now we will home the Node
                        myNodes[n].Motion.Homing.Initiate();

                        timeout = myMgr.TimeStampMsec() + TIME_TILL_TIMEOUT;    // Define a timeout in case the node is unable to enable
                                                                                // Basic mode - Poll until disabled
                        while (!myNodes[n].Motion.Homing.WasHomed())
                        {
                            if (myMgr.TimeStampMsec() > timeout)
                            {
                                Console.WriteLine("Node did not complete homing:  \n\t -Ensure Homing settings have been defined through ClearView. \n\t -Check for alerts/Shutdowns \n\t -Ensure timeout is longer than the longest possible homing move.");
                                ExitProgram(-1);
                            }
                        }
                        myNodes[n].Motion.PosnMeasured.Refresh();      // Refresh our current measured position
                        Console.WriteLine("Node completed homing, current position: {0} ", myNodes[n].Motion.PosnMeasured.Value());
                        Console.WriteLine("Soft limits now active");

                        Console.WriteLine("Adjusting Numberspace by {0}", CHANGE_NUMBER_SPACE);

                        myNodes[n].Motion.AddToPosition(CHANGE_NUMBER_SPACE);          // Now the node is no longer considered "homed, and soft limits are turned off

                        myNodes[n].Motion.Homing.SignalComplete();     // Reset the Node's "sense of home" soft limits (unchanged) are now active again

                        myNodes[n].Motion.PosnMeasured.Refresh();      // Refresh our current measured position
                        Console.WriteLine("Numberspace changed, current position: {0}", myNodes[n].Motion.PosnMeasured.Value());
                    }
                    else
                    {
                        Console.WriteLine("Node[{0}] has not had homing setup through ClearView.  The node will not be homed.", n);
                    }

                    // Disable the node
                    Console.WriteLine("Disabling Node.");
                    myNodes[n].EnableReq(false);

                    // This will dispose of the reference to the node. This frees up memory (similar to C++'s delete)
                    // NOTE: All Teknic CLI classes implement the IDisposable pattern and should be properly disposed of when no longer in use.
                    myNodes[n].Dispose();
                }
                myPort.Dispose();
            }
            myMgr.PortsClose();
            myMgr.Dispose();

            ExitProgram(1);
        }
    }
}
