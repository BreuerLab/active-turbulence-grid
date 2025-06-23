using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using sFndCLIWrapper;

namespace CSharpSingleThreadedEx
{
    class Axis
    {
        const int RAS_CODE = 3;
        const int TRQ_PCT = 100;
        const int ACC_LIM_RPM_PER_SEC = 8000;
        const int VEL_LIM_RPM = 2000;
        uint TRACKING_LIM;

        cliINode m_node;    // The ClearPath-SC for this axis
        cliSysMgr m_sysMgr;

        // Filename for the stored config file
        string m_configFile;

        // State machine information
        enum StateEnum
        {
            STATE_IDLE,
            STATE_SEND_MOVE,
            STATE_WAIT_FOR_MOVE_DONE,
            STATE_EXITED  
        };
        StateEnum m_state;
        StateEnum m_lastState;

        // Move information
        UInt32 m_moveCount;
        Int32 m_positionWrapCount;
        Int32 m_moveTimeoutMs;

        bool m_quitting;

        // Enable the node and get it ready to go
        void Enable()
        {
            if (m_node != null)
            {
                // Clear alerts and node stops
                m_node.Status.AlertsClear();
                m_node.Motion.NodeStop(cliNodeStopCodes.STOP_TYPE_ABRUPT);
                m_node.Motion.NodeStop(cliNodeStopCodes.STOP_TYPE_CLR_ALL);

                // Enable the node
                m_node.EnableReq(true);
                // If the node is not currently ready, wait for it to get there
                DateTime timeout;
                timeout = DateTime.Now.AddSeconds(3);
                // Basic mode - Poll until disabled
                while (!m_node.Status.IsReady())
                {
                    if (DateTime.Now.Ticks > timeout.Ticks)
                    {
                        Console.WriteLine("Error: Timed out waiting for enable");
                        return;
                    }
                };

                //If node is set up to home, start homing
                if (m_node.Motion.Homing.HomingValid())
                {
                    m_node.Motion.Homing.Initiate();
                    Console.WriteLine("Homing...");
                    timeout = DateTime.Now.AddSeconds(10);
                    // Basic mode - Poll until disabled
                    while (!m_node.Motion.Homing.WasHomed())
                    {
                        if (DateTime.Now.Ticks > timeout.Ticks)
                        {
                            Console.WriteLine("Error: Timed out waiting for homing");
                            return;
                        }
                    };
                    Console.WriteLine("Completed");
                }
            }
        }

        // Initialize accLim, velLim, etc
        void InitMotionParams()
        {
            // Set the user units to RPM and RPM/s
            m_node.VelUnit(cliINode._velUnits.RPM);
            m_node.AccUnit(cliINode._accUnits.RPM_PER_SEC);

            // Set the motion's limits
            m_node.Motion.VelLimit.Value(VEL_LIM_RPM);
            m_node.Motion.AccLimit.Value(ACC_LIM_RPM_PER_SEC);
            m_node.Motion.JrkLimit.Value(RAS_CODE);
            m_node.Limits.PosnTrackingLimit.Value(TRACKING_LIM);
            m_node.Limits.TrqGlobal.Value(TRQ_PCT);

            // Set the dwell used by the motor when applicable
            m_node.Motion.DwellMs.Value(5);
        }

        // Edit the current motion parameters
        void ChangeMotionParams(double newVelLimit, double newAccelLimit, UInt32 newJrkLimit, UInt32 newTrackingLimit, Int32 newTrqGlobal)
        {
            // Set the motion's limits
            m_node.Motion.VelLimit.Value(newVelLimit);
            m_node.Motion.AccLimit.Value(newAccelLimit);
            m_node.Motion.JrkLimit.Value(newJrkLimit);
            m_node.Limits.PosnTrackingLimit.Value(newTrackingLimit);
            m_node.Limits.TrqGlobal.Value(newTrqGlobal);
        }

        // Initiate a move
        void PosnMove(Int32 targetPosn, bool isAbsolute = false, bool addDwell = false)
        {
            // Save the move's calculated time for timeout handling
            m_moveTimeoutMs = (Int32)m_node.Motion.MovePosnDurationMsec(targetPosn, isAbsolute);
            m_moveTimeoutMs += 20;

            // Check for number-space wrapping. With successive moves, the position may
            // pass the 32-bit number cap (+ or -). The check below looks for that and
            // updates our counter to be used with GetPosition
            if (!isAbsolute)
            {
                if (GetPosition(false) + targetPosn > Int32.MaxValue)
                {
                    m_positionWrapCount++;
                }
                else if (GetPosition(false) + targetPosn < Int32.MinValue)
                {
                    m_positionWrapCount--;
                }
            }

            // Issue the move to the node
            m_node.Motion.MovePosnStart(targetPosn, isAbsolute, addDwell);
        }
        void VelMove(double targetVel)
        {
            // Issue the move to the node
            m_node.Motion.MoveVelStart(targetVel);

            // Move at the set velocity for half a second
            m_sysMgr.Delay(500);

            // Issue a node stop, forcing any movement (like a 
            // velocity move) to stop. There are several 
            // different types of node stops
            m_node.Motion.NodeStop(cliNodeStopCodes.STOP_TYPE_ABRUPT);
            //m_node->Motion.NodeStop(STOP_TYPE_RAMP);

            // Configure the timeout for the node stop to settle
            m_moveTimeoutMs = 100;
        }

        // Wait for attention that move has completed
        bool WaitForMove(Int32 timeoutMs, bool secondCall = false)
        {
            if (m_node == null)
            {
                return false;
            }

            // Wait for the proper calculated move time
            DateTime timeout = DateTime.Now;
            timeout = timeout.AddMilliseconds(timeoutMs);

            m_node.Status.RT.Refresh();
            // Basic mode - Poll until move done
            while (!Convert.ToBoolean(m_node.Status.RT.Value().cpm.MoveDone))
            {
                m_node.Status.RT.Refresh();
                if (DateTime.Now.Ticks > timeout.Ticks)
                {
                    Console.WriteLine("Error: Timed out during move");
                    return false;
                }

                // Catch specific errors that can occur during a move
                if (Convert.ToBoolean(m_node.Status.RT.Value().cpm.Disabled))
                {
                    Console.WriteLine("  ERROR: [{0}] disabled during move", m_node.Info.Ex.Addr);
                    return false;
                }
                if (Convert.ToBoolean(m_node.Status.RT.Value().cpm.NotReady))
                {
                    Console.WriteLine("  ERROR: [{0}] went NotReady during move", m_node.Info.Ex.Addr);
                    return false;
                }
            }

            return Convert.ToBoolean(m_node.Status.RT.Value().cpm.MoveDone);
        }

        // Alert handlers
        void CheckForAlerts()
        {
            // Refresh our relevant registers
            m_node.Status.Alerts.Refresh();
            m_node.Status.RT.Refresh();

            //Check for alerts
            if (Convert.ToBoolean(m_node.Status.RT.Value().cpm.AlertPresent))
            {
                string alertList = m_node.Status.Alerts.Value().StateStr();
                Console.WriteLine("Node {0} has alerts! Alert: {1}", m_node.Info.Ex.Addr, alertList);
                m_quitting = true;
            }
        }

        // HW Brake Setup
        void SetBrakeControl(uint brakeNum, cliIBrakeControl._BrakeControls brakeMode)
        {
            m_node.Port.BrakeControl.BrakeSetting(brakeNum, brakeMode);
        }

        // Return scaled position
        Int64 GetPosition(bool includeWraps = true)
        {
            // Create a variable to return and refresh the position
            Int64 scaledPosn;
            m_node.Motion.PosnCommanded.Refresh();

            // If there have been no number wraps, just return the position
            scaledPosn = (Int64)m_node.Motion.PosnCommanded.Value();

            if (includeWraps)
            {
                scaledPosn += (Int64)m_positionWrapCount << 32;
            }
            
            return scaledPosn;
        }

        //Public Members

        // Constructor/Destructor
        public Axis(cliSysMgr sysMgr, cliINode node)
        {
            m_node = node;
            TRACKING_LIM = m_node.Info.PositioningResolution.Value() / 4;
            m_sysMgr = sysMgr;
            m_moveCount = 0;
            m_positionWrapCount = 0;
            m_quitting = false;

            string tempPath = System.IO.Path.GetTempPath();
            m_configFile = tempPath + m_node.Info.Ex.Addr + m_node.Info.SerialNumber.Value();
            
            if (m_node.Setup.AccessLevelIsFull())
            {
                m_node.Setup.ConfigSave(m_configFile);
            }
        }

        public void DestroyAxis()
        {
            // Print out the move statistics one last time
            PrintStats();

            // If we don't have full access, there's nothing to do here
            if (!m_node.Setup.AccessLevelIsFull())
            {
                return;
            }
            
            // Disable the node and wait for it to disable
            m_node.EnableReq(false);
            
            // Poll the status register to confirm the node's disable
            DateTime timeout;
            timeout = DateTime.Now.AddSeconds(3);
            m_node.Status.RT.Refresh();
            while (Convert.ToBoolean(m_node.Status.RT.Value().cpm.Enabled))
            {
                if (DateTime.Now.Ticks > timeout.Ticks)
                {
                    Console.WriteLine("Error: Timed out waiting for disable");
                    return;
                }
                m_node.Status.RT.Refresh();
            };

            // Restore the original config file
            m_node.Setup.ConfigLoad(m_configFile, false);

            // Dispose of the node reference
            m_node.Dispose();
        }

        // Print the current stats (number of moves performed and
        // current commanded position)
        public void PrintStats(bool onInit = false)
        {
            // Refresh the measures position register
            m_node.Motion.PosnCommanded.Refresh();
            if (onInit)
            {
                Console.WriteLine("  [{0}]:\t\t**at startup**\t\t{1}", m_node.Info.Ex.Addr, GetPosition());
            }
            else
            {
                Console.WriteLine("  [{0}]:\t\t{1}\t\t{2}",
                    m_node.Info.Ex.Addr, m_moveCount, GetPosition());
            }
        }

        // Time to quit
        public void Quit()
        {
            m_quitting = true;
        }

        // The state machine
        public void AxisMain()
        {
            bool moveDone;

            // If we don't have nodes, exit
            if (m_node == null)
            {
                Console.WriteLine("No node, exiting");
                return;
            }

            try
            {
                // Get the node ready to go
                Enable();
                // Initialize the motion values
                InitMotionParams();
            }
            catch (System.Exception) {
                Console.WriteLine("Setup error");
            }

            if (!m_quitting)
            {
                // If your node has appropriate hardware (hardstop/home switch) 
                // and is configured in ClearView, uncomment the line below to 
                // initiate homing
                //theNode.Motion.Homing.Initiate();

                // Set the hardware brake to allow motion
                m_node.Port.BrakeControl.BrakeSetting(0, cliIBrakeControl._BrakeControls.BRAKE_ALLOW_MOTION);

                // Zero out the commanded position
                m_node.Motion.PosnCommanded.Refresh();
                double posn = m_node.Motion.PosnCommanded.Value();
                m_node.Motion.AddToPosition(-posn);
                m_node.Motion.PosnCommanded.Refresh();
                PrintStats(true);
            }

            m_state = StateEnum.STATE_IDLE;

            // Start the machine cycling
            while (!m_quitting)
            {
                try
                {
                    // Save last state for debugging purposes
                    m_lastState = m_state;

                    // Check for alerts
                    CheckForAlerts();

                    switch (m_state)
                    {
                        case StateEnum.STATE_IDLE:
                            // Update idle state
                            // Quitting?
                            if (m_quitting)
                                continue;
                            m_state = StateEnum.STATE_SEND_MOVE;
                            break;
                        case StateEnum.STATE_SEND_MOVE:
                            // Initiate the motion
                            if (m_moveCount % 2 == 0)
                            {
                                PosnMove(5000);
                            }
                            else
                            {
                                //Set new motion parameters before the next move
                                ChangeMotionParams(1500, 7500, 4, m_node.Info.PositioningResolution.Value() / 4, 95);

                                VelMove(50);
                            }

                            // Reset our motion parameters.  The parameters for the 
                            // next move could be entered instead to get a head start
                            InitMotionParams();

                            m_state = StateEnum.STATE_WAIT_FOR_MOVE_DONE;
                            break;
                        case StateEnum.STATE_WAIT_FOR_MOVE_DONE:
                            //Check if the move is done yet
                            moveDone = WaitForMove(m_moveTimeoutMs + 5);
                            if (!moveDone)
                            {
                                Console.WriteLine("ERROR: [{0}] timed out waiting for move done", m_node.Info.Ex.Addr);
                                return;
                            }
                            else
                            {
                                m_moveCount++;
                                m_state = StateEnum.STATE_IDLE;
                            }
                            if (m_moveCount == 4)
                            {
                                // Stop once we've properly demonstrated movement
                                Quit();
                            }
                            PrintStats();
                            if (m_quitting)
                                continue;
                            break;
                        default:
                            Console.WriteLine("Error, Illegal state");
                            return;
                    }
                } // Try block
                catch (System.Exception) {
                    Console.WriteLine("Link error");
                    ResetToIdle();
                    continue;
                }
                }

                m_state = StateEnum.STATE_EXITED;
                ResetToIdle();
                Console.WriteLine("[{0}] Quitting node...", m_node.Info.UserID.Value());
                return;
            }

        // Return a reference to our node
        public cliINode MyNode()
        {
            return m_node;
        }

        // Reset sequencer to "idle" state
        public void ResetToIdle()
        {
            if (m_state != StateEnum.STATE_IDLE)
            {
                m_state = m_lastState = StateEnum.STATE_IDLE;
            }
        }
    }
}
