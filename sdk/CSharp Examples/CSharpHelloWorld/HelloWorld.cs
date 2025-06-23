using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using sFndCLIWrapper;

namespace CSharpHelloWorld
{
    class HelloWorld
    {
        static void ExitProgram(int errCode)
        {
            Console.WriteLine("Press enter to continue.");
            Console.ReadLine();
            Environment.Exit(errCode);
        }

        /*****************************************************************************
        *	Description:	This program is the bare minimum to open a port and identify the number of nodes
        *		on the port.
        *	
        *
        *		Return:		0 if the system was initialized properly.
        *					-1 if there was a problem accessing the port.
        *****************************************************************************/
        static void Main(string[] args)
        {
            //Create the SysManager object. This object will coordinate actions among various ports
            //and within nodes. In this example we use this object to setup and open our port.
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

                // This will dispose of the reference to the port. This frees up memory (similar to C++'s delete)
                // NOTE: All Teknic CLI classes implement the IDisposable pattern and should be properly disposed of when no longer in use.
                myPort.Dispose();
            }

            myMgr.PortsClose();
            myMgr.Dispose();

            ExitProgram(1);
        }
    }
}
