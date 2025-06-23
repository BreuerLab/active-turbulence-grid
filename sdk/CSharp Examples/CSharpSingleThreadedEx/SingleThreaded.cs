using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using sFndCLIWrapper;

namespace CSharpSingleThreadedEx
{
    class SingleThreaded
    {
        static void ExitProgram(int errCode)
        {
            Console.WriteLine("Press enter to continue.");
            Console.ReadLine();
            Environment.Exit(errCode);
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Single-threaded Example starting. Press Enter to continue.");
            Console.ReadLine();

            int portCount = 0;
            List<String> comHubPorts = new List<String>();

            //Create the SysManager object. This object will coordinate actions among various ports
            // and within nodes. In this example we use this object to setup and open our port.
            cliSysMgr myMgr = new cliSysMgr();                           //Create System Manager myMgr

            //This will try to open the port. If there is an error/exception during the port opening,
            //the code will jump to the catch loop where detailed information regarding the error will be displayed;
            //otherwise the catch loop is skipped over
            try
            {

                myMgr.FindComHubPorts(comHubPorts);
                Console.WriteLine("Found {0} SC Hubs", comHubPorts.Count);

                for (portCount = 0; portCount < comHubPorts.Count && portCount < 3; portCount++)
                {

                    myMgr.ComPortHub((uint)portCount, comHubPorts[portCount], cliSysMgr._netRates.MN_BAUD_12X);    //define the first SC Hub port (port 0) to be associated 
                                                                                    // with COM portnum (as seen in device manager)
                }

                if (portCount > 0)
                {
                    //printf("\n I will now open port \t%i \n \n", portnum);
                    myMgr.PortsOpen(portCount);             //Open the port

                    for (int i = 0; i < portCount; i++)
                    {
                        cliIPort myPort = myMgr.Ports(i);

                        Console.WriteLine(" Port[{0}]: state={1}, nodes={2}", myPort.NetNumber(), myPort.OpenState(), myPort.NodeCount());
                        myPort.Dispose();
                    }
                }
                else
                {
                    Console.WriteLine("Unable to locate SC hub port");

                    ExitProgram(-1); //pause so the user can see the error message; waits for user to press a key
                                     //This terminates the main program
                }

                // Create a list of axes - there will be one Axis per node
                List<Axis> listOfAxes = new List<Axis>();

                // Assume that the nodes are of the right type and that this app has full control
                bool nodeTypesGood = true, accessLvlsGood = true;

                for (int iPort = 0; iPort < portCount; iPort++)
                {
                    // Get a reference to the port and nodes, to make accessing them easier
                    cliIPort myPort = myMgr.Ports(iPort);
                    cliINode[] myNodes = new cliINode[myPort.NodeCount()];

                    for (int iNode = 0; iNode < myPort.NodeCount(); iNode++)
                    {
                        // Get a reference to the node, to make accessing it easier
                        myNodes[iNode] = myPort.Nodes(iNode);

                        // Make sure we are talking to a ClearPath SC (advanced or basic model will work)
                        if (myNodes[iNode].Info.NodeType() != cliIInfo._nodeTypes.CLEARPATH_SC_ADV
                            && myNodes[iNode].Info.NodeType() != cliIInfo._nodeTypes.CLEARPATH_SC)
                        {
                            Console.WriteLine("---> ERROR: Uh-oh! Node {0} is not a ClearPath-SC Motor", iNode);
                            nodeTypesGood = false;
                        }

                        if (nodeTypesGood)
                        {
                            // Create an axis for this node
                            listOfAxes.Add(new Axis(myMgr, myNodes[iNode]));

                            // Make sure we have full access
                            if (!myNodes[iNode].Setup.AccessLevelIsFull())
                            {
                                Console.WriteLine("---> ERROR: Oh snap! Access level is not good for node {0}", iNode);
                                accessLvlsGood = false;
                            }
                        }
                    }
                    // This will dispose of the reference to the port. This frees up memory (similar to C++'s delete)
                    // NOTE: All Teknic CLI classes implement the IDisposable pattern and should be properly disposed of when no longer in use.
                    myPort.Dispose();
                }

                // If we have full access to the nodes and they are all ClearPath-SC nodes, 
                // then continue with the example
                if (nodeTypesGood && accessLvlsGood)
                {
                    for (UInt16 iAxis = 0; iAxis < listOfAxes.Count; iAxis++)
                    {
                        // Tell each axis to do its thing
                        listOfAxes[iAxis].AxisMain();
                    }
                }
                else
                {
                    // If something is wrong with the nodes, tell the user about it
                    if (!nodeTypesGood)
                    {
                        Console.WriteLine("\n\tFAILURE: Please attach only ClearPath-SC nodes.\n\n");
                        ExitProgram(-5);
                    }
                    else if (!accessLvlsGood)
                    {
                        Console.WriteLine("\n\tFAILURE: Please get full access on all your nodes.\n\n");
                        ExitProgram(-6);
                    }
                }
                // Delete the list of axes that were created
                for (int iAxis = 0; iAxis < listOfAxes.Count; iAxis++)
                {
                    listOfAxes[iAxis].DestroyAxis();
                }

                // Close down the ports
                myMgr.PortsClose();
            }
            catch (System.Exception) {
                Console.WriteLine("Caught error:");
                ExitProgram(-3);
            }
            myMgr.Dispose();

            // Good-bye
            ExitProgram(1);
        }
    }
}
