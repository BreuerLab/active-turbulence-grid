using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using sFndCLIWrapper;

namespace CSharpStatusAlertsEx
{
    class StatusAlerts
    {
        static void ExitProgram(int errCode)
        {
            Console.WriteLine("Press enter to continue.");
            Console.ReadLine();
            Environment.Exit(errCode);
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Status Alerts example starting. Press Enter to continue.");
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

                string alertList = "";
                Console.WriteLine("Checking for Alerts: ");

                //Once the code gets past this point, it can be assumed that the Port has been opened without issue
                //Now we can get a reference to our port object which we will use to access the node objects
                for (int n = 0; n < myPort.NodeCount(); n++)
                {
                    // Create a shortcut reference for a node
                    myNodes[n] = myPort.Nodes(n);

                    // Make sure our registers are up to date
                    myNodes[n].Status.RT.Refresh();
                    myNodes[n].Status.Alerts.Refresh();

                    Console.WriteLine("---------");
                    Console.WriteLine(" Checking node {0} for Alerts:", n);

                    // Check the status register's "AlertPresent" bit
                    // The bit is set true if there are alerts in the alert register
                    if (!Convert.ToBoolean(myNodes[n].Status.RT.Value().cpm.AlertPresent))
                    {
                        Console.WriteLine("   Node has no alerts!");
                    }
                    //Check to see if the node experienced torque saturation
                    if (myNodes[n].Status.HadTorqueSaturation())
                    {
                        Console.WriteLine("      Node has experienced torque saturation since last checking");
                    }
                    if (myNodes[n].Status.Alerts.Value().isInAlert())
                    {
                        // get a copy of the alert register bits and a text description of all bits set
                        alertList = myNodes[n].Status.Alerts.Value().StateStr();
                        Console.WriteLine("   Node has alerts! Alerts:\n{0}", alertList);

                        // can access specific alerts using the method below
                        if (Convert.ToBoolean(myNodes[n].Status.Alerts.Value().cpm.Common.EStopped))
                        {
                            Console.WriteLine("      Node is e-stopped: Clearing E-Stop");
                            myNodes[n].Motion.NodeStopClear();
                        }
                        if (Convert.ToBoolean(myNodes[n].Status.Alerts.Value().cpm.TrackingShutdown))
                        {
                            Console.WriteLine("      Node exceeded Tracking error limit");
                        }



                        // Check for more alerts and Clear Alerts
                        myNodes[n].Status.Alerts.Refresh();
                        if (myNodes[n].Status.Alerts.Value().isInAlert())
                        {
                            alertList = myNodes[n].Status.Alerts.Value().StateStr();
                            Console.WriteLine("      Node has non-estop alerts: {0}", alertList);
                            Console.WriteLine("      Clearing non-serious alerts");
                            myNodes[n].Status.AlertsClear();

                            // Are there still alerts?
                            myNodes[n].Status.Alerts.Refresh();
                            if (myNodes[n].Status.Alerts.Value().isInAlert())
                            {
                                alertList = myNodes[n].Status.Alerts.Value().StateStr();
                                Console.WriteLine("   Node has serious, non-clearing alerts: {0}", alertList);
                            }
                            else
                            {
                                Console.WriteLine("   Node {0}: all alerts have been cleared", myNodes[n].Info.Ex.Addr);
                            }
                        }
                        else
                        {
                            Console.WriteLine("   Node {0}: all alerts have been cleared", myNodes[n].Info.Ex.Addr);
                        }
                    }
                    // This will dispose of the reference to the node. This frees up memory (similar to C++'s delete)
                    // NOTE: All Teknic CLI classes implement the IDisposable pattern and should be properly disposed of when no longer in use.
                    myNodes[n].Dispose();
                }
                myPort.Dispose();
            }
            Console.WriteLine("\nShutting down network");

            // Close down the ports and dispose of the manager reference.
            myMgr.PortsClose();
            myMgr.Dispose();

            ExitProgram(1);
        }
    }
}
