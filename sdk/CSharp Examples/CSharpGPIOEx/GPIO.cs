using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using sFndCLIWrapper;

namespace CSharpGPIOEx
{
    class GPIO
    {

        static void ExitProgram(int errCode)
        {
            Console.WriteLine("Press enter to continue.");
            Console.ReadLine();
            Environment.Exit(errCode);
        }

        static void Main(string[] args)
        {
            Console.WriteLine("GPIO Example starting. Press Enter to continue.");
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
                Console.WriteLine("Port {0}: state={1}, nodes={2}", myPort.NetNumber(), myPort.OpenState(), myPort.NodeCount());

                // Set GPO to ON for the first brake control, 
                myPort.BrakeControl.BrakeSetting(0, cliIBrakeControl._BrakeControls.GPO_ON);
                // Can set GPO to OFF for the second brake control using the method below
                //myPort.BrakeControl.BrakeSetting(1, cliIBrakeControl._BrakeControls.GPO_OFF);

                for (uint iBrake = 0; iBrake < 2; iBrake++)
                {
                    // Print out brake mode for the first brake
                    uint controlMode = (uint)myPort.BrakeControl.BrakeSetting(iBrake);
                    if (controlMode == 3)
                    {
                        Console.WriteLine("Port[{0}] Brake {1} control mode: GPO ON", myPort.NetNumber(), iBrake);
                    }
                    else if (controlMode == 4)
                    {
                        Console.WriteLine("Port[{0}] Brake {1} control mode: GPO OFF", myPort.NetNumber(), iBrake);
                    }
                    else
                    {
                        Console.WriteLine("Port[{0}] Brake {1} control mode: GPO not set", myPort.NetNumber(), iBrake);
                    }
                    // keep the console output readable
                    Console.WriteLine("");
                }

                for (int n = 0; n < myPort.NodeCount(); n++)
                {
                    // Create a shortcut reference for a node
                    cliINode theNode = myPort.Nodes(n);
                    // Checking Inputs to each Node
                    if (Convert.ToBoolean(theNode.Status.RT.Value().cpm.InA))
                    {
                        Console.WriteLine("Node {0} Input A is asserted.", n);
                    }
                    else
                    {
                        Console.WriteLine("Node {0} Input A is not asserted.", n);
                    }
                    if (Convert.ToBoolean(theNode.Status.RT.Value().cpm.InB))
                    {
                        Console.WriteLine("Node {0} Input B is asserted.", n);
                    }
                    else
                    {
                        Console.WriteLine("Node {0} Input B is not asserted.", n);
                    }

                    // This will dispose of the reference to the node. This frees up memory (similar to C++'s delete)
                    // NOTE: All Teknic CLI classes implement the IDisposable pattern and should be properly disposed of when no longer in use.
                    theNode.Dispose();
                }
                myPort.Dispose();
            }
            Console.WriteLine("\nShutting down network.");

            // Close down the ports
            myMgr.PortsClose();
            myMgr.Dispose();

            ExitProgram(1);
        }
    }
}
