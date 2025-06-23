// CLRWrapper.h

#pragma once

#include <msclr/marshal.h>
#include "pubSysCls.h"
#include "ValueObjs.h"


using namespace sFnd;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;


namespace sFndCLIWrapper {

	ref class cliIAttnNode;
	ref class cliIAttnPort;
	ref class cliIBrakeControl;
	ref class cliIGrpShutdown;
	ref class cliIHoming;
	ref class cliIInfo;
	ref class cliIInfoAdv;
	ref class cliIInfoEx;
	ref class cliILimits;
	ref class cliILimitsAdv;
	ref class cliIMotion;
	ref class cliIMotionAdv;
	ref class cliIMotionAudit;
	ref class cliINode;
	ref class cliINodeAdv;
	ref class cliINodeEx;
	ref class cliIOuts;
	ref class cliIPort;
	ref class cliIPortAdv;
	ref class cliISetup;
	ref class cliISetupEx;
	ref class cliIStatus;
	ref class cliIStatusAdv;
	ref class cliSysMgr;

	ref class cliAuditData;
	ref class cliShutdownInfo;
	
	//*****************************************************************************
	// NAME																	      *
	// 	cliIAttnNode class
	/*

	Node Attention Feature Interface.

	A reference to this object allows your application to control which node
	status events will generate a <i>Network Attention</i> packet. These packets
	efficiently signal the host some noteworthy event, such as move done, has
	occurred. Using Attentions eliminates the overhead and latency involved with
	polling.

	This feature is only available on nodes that have the Advanced
	feature set.

	See cliCPMStatusRegFlds for a complete list of Node status events
	*/
	public ref class cliIAttnNode
	{
	private:
		IAttnNode &myAttnNode;
		cliValueStatus^ m_Mask;
		cliValueAlert^ m_WarnMask;
		cliValueAlert^ m_AlertMask;
		cliValueStatus^ m_StatusMask;
	public:
		// Constructor / destructor
		cliIAttnNode::cliIAttnNode(IAttnNode &val);
		cliIAttnNode::~cliIAttnNode() { this->!cliIAttnNode(); }
		cliIAttnNode::!cliIAttnNode();

		/*
		Attention Enabling Mask

		Setup which fields of the Status Attn/Rise Register cause the
		generation of an Attention Packet to the host. These packets are
		similar to a microprocessor interrupt.
		*/
		property cliValueStatus^ Mask { cliValueStatus^ get() { return m_Mask; } }
		/*
		Warnings to indicate in the Status Register

		Setup which fields of the Warning Register will set the
		cliCPMStatusRegFlds::Warning field in the Status Register.

		This can be used to send attentions on drive events such as torque
		saturations.
		*/
		property cliValueAlert^ WarnMask { cliValueAlert^ get() { return m_WarnMask; } }
		/*
		Selection of Alerts to include in the Status Register
		User Alert field.

		Setup which fields of the Alert Register will set the
		cliCPMStatusRegFlds::UserAlert field in the Status Register.
		*/
		property cliValueAlert^ AlertMask { cliValueAlert^ get() { return m_AlertMask; } }
		/*
		Selection of Status Events to include in the Status Register Status Event field.

		Setup which fields of the Status Register will set the
		cliCPMStatusRegFlds::StatusEvent field in the Status Register.

		Do not include the StatusEvent field in this mask to avoid
		latching this field in the status register.
		*/
		property cliValueStatus^ StatusMask { cliValueStatus^ get() { return m_StatusMask; } }

		/*
		Wait for any of the indicated attention fields to assert.

		Param[in] theAttn The set of attentions to wait on. Only the lower
		32-bits of the status register generate attentions.
		Param[in] timeoutMsec The maximum time to wait for these attentions.
		Param[in] autoClear If set, the bits underlying last attention register
		cooresponding to theAttn will be atomically cleared.
		Return A copy of the attentions that released this function. If the
		fields of this register is zero, the timeout occurred.

		When called, this function blocks until the desired attention occurs.
		The returned mnStatusReg is set with the fields of the last
		matching attention. This is helpful when waiting on multiple attentions
		to find out the actual attention signaled. The timeoutMS parameter
		allows you limit the amount of waiting time until the return. This is
		typically required to prevent your application from hanging up when
		something fails to deliver the expected event(s).
		*/
		cliMNStatusReg^ WaitForAttn(cliMNStatusReg^ theAttn, int timeoutMsec, bool autoClear) {
			return gcnew cliMNStatusReg(myAttnNode.WaitForAttn(*theAttn->Reg, timeoutMsec, autoClear));
		}
		/*
		Clear the indicated fields from the current attention state.

		Param[in] attnClr Set fields you wish to clear from the accumulating
		attentions.

		This member function is used to clear unwanted past Attentions that
		have been received by the host.
		*/
		void ClearAttn(cliMNStatusReg^ attnClr) { myAttnNode.ClearAttn(*attnClr->Reg); }
		/*
		Signal that an Attention Packet has arrived with the
		indicated attn fields set.

		Param[in] theAttn Detected attention information
		*/
		void SignalAttn(cliMNStatusReg^ theAttn) { myAttnNode.SignalAttn(*theAttn->Reg); }
	};
	//																			  *
	//*****************************************************************************

	//*****************************************************************************
	// NAME																	      *
	// 	cliIAttnPort class

	/*
		Serial Port Attention Feature Interface.

		This implements the feature object required to setup attentions and register
		an Attention handler callback function on this port.
	*/
	public ref class cliIAttnPort
	{
	private:
		IAttnPort &myAttnPort;
		
	public:
		// Constructor / destructor
		cliIAttnPort::cliIAttnPort(IAttnPort &val) : myAttnPort(val) {}
		cliIAttnPort::~cliIAttnPort() { this->!cliIAttnPort(); }
		cliIAttnPort::!cliIAttnPort() {}

		/*
			Return codes for cliIAttnPort::WaitForAttn.

			Use these return codes to interpret how the cliIAttnPort::WaitForAttn
			succeeded. Usually your application would perform some action
			when HAS_ATTN is returned.
		*/
		enum class _attnState {
			HAS_ATTN,
			TIMEOUT,
			DISABLED,
			TERMINATING
		};

		/*
			Control the posting of attentions

			Param[in] newState If set, sFoundation will process received
			Attention Requests.

			This does not turn off the generation of attentions by the node.
			Turn off Attention generation by clearing the cliIAttnNode::Mask for
			each node on the Port.  If attention posting is disabled, but attentions
			are still generated, an error will be generated.
		*/
		void Enable(bool newState) { myAttnPort.Enable(newState); }
		/*
			Return the global attention posting switch

			Return True if attentions can be posted.
		*/
		bool Enabled() { return myAttnPort.Enabled(); }
		/*
			Wait for an attention to arrive.

			This function will periodically return TIMEOUT to allow the 
			application to terminate when no attentions have been detected.

			Param[out] attnRecvd If the function returns cliIAttnPort::HAS_ATTN, this
			buffer will be filled in with detected event.
			Return attnState To determine processing of the attn buffer.
		*/
		_attnState WaitForAttn(mnAttnReqReg &attnRecvd) {
			return (_attnState)myAttnPort.WaitForAttn(attnRecvd);
		}
		/*
			Detect if handler is defined.

			Return true if a handler is installed.

			Use the cliIAttnPort::AttnHandler function to register a handler callback
			function.
		*/
		bool HasAttnHandler() { return myAttnPort.HasAttnHandler(); }
		/*
			Register an attention callback function.

			Param[in] theNewHandler The address of a handler function of type
			mnAttnCallback;

			To prevent system performance issues, the implemented callback
			function should not run for extended periods of time. The function is
			also restricted from running any network based command. This includes
			parameter accesses and node commands. This function should signal other threads to
			restart themselves or other lightweight signaling mechanisms.
		*/
		void AttnHandler(mnAttnCallback theNewHandler) { myAttnPort.AttnHandler(theNewHandler); }
		/*
			Invoke the attention handler if defined.

			Param[in]  detected attention

			This is an internal function and should not be used.
		*/
		void InvokeAttnHandler(const mnAttnReqReg &detected) {  myAttnPort.InvokeAttnHandler(detected); }
	};
	//																			  *
	//*****************************************************************************

	//*****************************************************************************
	// NAME																	      *
	// 	cliIBrakeControl class
	/*
		Brake Control Feature Interface.

		This class implements access to the brake control outputs of a SC-Hub Board.  If multiple SC-Hub boards are chained together on a single port,
		only the first SC-Hub board's outputs will be controllable.

		The Brake Control feature can be used to automatically control a brake whenever a node is disabled or shutdown, or they can be used as general purpose outputs.
		This object also allows the application to override the brake to turn the brake off even when the node is disabled, allowing
		the axis to move freely.  This class provides functions to turn the outputs on and off, as well as to check the current state of the outputs.

		Sometimes a brake can take time to engage so there is a Node Level [delay to disable](cliISetup::DelayToDisableMsecs) parameter
		which can be set to give the brake time to activate before the motor disables.

		When using BRAKE_AUTOCONTROL mode, Brake_0 will activate and deactivate based on the state of the node connected to the CP0 connector on the SC-Hub Board.
		Similarly, Brake_1 will correspond to CP1 on the SC-Hub Board.
	*/
	public ref class cliIBrakeControl
	{
	private:
		IBrakeControl &myBrakeControl;
	public:
		// Constructor / destructor
		cliIBrakeControl::cliIBrakeControl(IBrakeControl &val) : myBrakeControl(val) {}
		cliIBrakeControl::~cliIBrakeControl() { this->!cliIBrakeControl(); }
		cliIBrakeControl::!cliIBrakeControl() {}

		enum class _BrakeControls
		{
			BRAKE_AUTOCONTROL,
			BRAKE_PREVENT_MOTION,
			BRAKE_ALLOW_MOTION,
			GPO_ON,
			GPO_OFF
		};

		/*
			Setup how brake will function.

			This function configures the configures the brake output.

			Param[in] brakeNum Brake number to use [0..1] 0 corresponds to Brake_0 on a SC Hub, 1 corresponds to Brake_1.
			Param[in] brakeMode Brake mode to use.

			See  _BrakeControls for the complete list of modes
		*/
		void BrakeSetting(uintptr_t brakeNum, _BrakeControls brakeMode) {
			myBrakeControl.BrakeSetting((size_t)brakeNum, (BrakeControls)brakeMode);
		}
		/*
			Get the brake control state.

			Param[in] brakeNum Brake number to use [0..1] 0 corresponds to Brake_0 on a SC Hub, 1 corresponds to Brake_1.
		*/
		_BrakeControls BrakeSetting(uintptr_t brakeNum) {
			return (_BrakeControls)myBrakeControl.BrakeSetting((size_t)brakeNum);
		}
		/*
			Return the current brake state.

			Determine the curent state of the Brake.  A Brake is considered engaged when the brake is holding the axis.  This would correspond to zero current flow on a GPO.

			Param[in] brakeNum Brake number to use [0..1]; 0 corresponds to Brake_0 on a SC Hub, 1 corresponds to Brake_1.
			Return true if the brake is engaged.
		*/
		bool BrakeEngaged(uintptr_t brakeNum) { return myBrakeControl.BrakeEngaged((size_t)brakeNum); }
	};
	//																			  *
	//*****************************************************************************

	//*****************************************************************************
	// NAME																	      *
	// 	cliIGrpShutdown class
	/*
		Group Shutdown Feature Interface.

		This class implements access to the group shutdown feature which
		allows an electrical connection or a change in a node's status to initiate a Group Shutdown Node Stop.
		This Group Shutdown will automatically propagate and initiate a Node Stop on all nodes in the port.

		This class can configure how each node on the port will react to a Group Shutdown Node Stop, as well as whether
		certain fields in the Node's mnStatusdReg will issue a group shutdown.  For instance, once a node goes [not ready](cliCPMStatusRegFlds::NotReady)
		a group shutdown can be called.

		Once a group shutdown is triggered the shutdown is sent to each node on the port. A group shutdown
		is also automatically triggered upon the loss of power (negative edge) of the global stop input on the SC-Hub board.
	*/
	public ref class cliIGrpShutdown
	{
	private:
		IGrpShutdown &myGrpShutdown;
	public:
		// Constructor / destructor
		cliIGrpShutdown::cliIGrpShutdown(IGrpShutdown &val) : myGrpShutdown(val) {}
		cliIGrpShutdown::~cliIGrpShutdown() { this->!cliIGrpShutdown(); }
		cliIGrpShutdown::!cliIGrpShutdown() {}

		/*
			Setup the group shutdown for this node.

			This function is used to setup how a node will react to a group shutdown, as well as
			which items in the node's status register will trigger a group shutdown.

			Param[in] nodeIndex Node index. This corresponds to the location from
			the host on the network.
			Param[in] theInfo Settings to apply to this node.
		*/
		void ShutdownWhen(uintptr_t nodeIndex, cliShutdownInfo^ theInfo);
		/*
			Get the group shutdown settings for this node.

			Retrieve the current ShutdownInfo for this node, including the stop type, status mask,
			and whether the feature is enabled

			Param[in] nodeIndex Node index. This corresponds to the location from
			the host on the network.
			Param[out] theInfo Settings to apply to this node.

		*/
		cliShutdownInfo^ ShutdownWhenGet(uintptr_t nodeIndex);
		/*
			Initiate a group shutdown.
		*/
		void ShutdownInitiate() { myGrpShutdown.ShutdownInitiate(); }
	};
	//																			  *
	//*****************************************************************************



	//*****************************************************************************
	// NAME																	      *
	// 	cliIHoming class
	/*
		Homing Feature Interface.

		This class object implements access to Teknic's homing engine.  This object allows
		a user to initiate homing and test whether homing was complete. This object
		cannot configure homing parameters such as homing direction/speed.  Homing parameters
		must be set using the ClearView software, and this object only provides the ability
		to start homing and check whether the axis has homed.

		Homing is required to use soft limits and
		establish the node's number space for absolute type moves.
	*/
	public ref class cliIHoming
	{
	private:
		IHoming &myHoming;
	public:
		// Constructor / destructor
		cliIHoming::cliIHoming(IHoming &val) : myHoming(val) {}
		cliIHoming::~cliIHoming() { this->!cliIHoming(); }
		cliIHoming::!cliIHoming() {}

		/*
			Initiate the homing sequence.

			This function is called to initiate a homing sequence. ClearView
			should be used to setup how homing is performed.
		*/
		void Initiate() { myHoming.Initiate(); }
		/**
			Update status real-time and return the state of the homing active
			flag.

			Update [status real-time register](cliIStatus::RT) and return the state of the homing active
			flag.

			Return True if homing is occurring.
		*/
		bool IsHoming() { return myHoming.IsHoming(); }
		/**
			Update status real-time and return the state of the homing
			complete flag.

			Update [status real-time register](cliIStatus::RT) and return the state of the homing
			complete flag.  Homing complete will only assert after a successful homing sequence
			or if the user calls the SignalComplete() function indicating a successful manual homing.

			Return True if homing has completed.
		**/
		bool WasHomed() { return myHoming.WasHomed(); }
		/*
			Signal the completion of manual homing.

			This function is used to signal to the node that the homing sequence
			has completed. Typically the homing process automatically
			proceeds until completion. If a hard-stop or input cannot
			be used to terminate the homing sequence, this function can be
			used to signal the completion of a homing sequence.

			Calling this function will cause soft limits to activate.

			This function is used when the  automatic homing
			feature cannot be used to establish the absolute number space. For
			example when camera processing is used to establish a position.

			See cliIHoming::SignalInvalid To disable soft limits and allow another
			homing sequence to occur.
			See cliIMotion::AddToPosition to manually adjust the number space during manual homing
		*/
		void SignalComplete() { myHoming.SignalComplete(); }
		/*
			Signal the node that our absolute position space is invalid.

			This is	useful when using soft limits and manual homing procedure.

			After calling this function the soft limit feature, if enabled,
			is disabled.

			See cliIHoming::SignalComplete to reverse the affects of this function.

			See cliIMotion::AddToPosition to manually adjust the number space during manual homing
		*/
		void SignalInvalid() { myHoming.SignalInvalid(); }
		/*
			Check Homing settings to see if they are set-up properly

			Return True if homing has been set-up
		*/
		bool HomingValid() { return myHoming.HomingValid(); }
	};
	//																			  *
	//*****************************************************************************


	//*****************************************************************************
	// NAME																	      *
	// 	cliIInfo class
	/*
		Node Information Interface.

		This class object implements access to node information.

		This includes node management items such as:
		- Serial Number
		- Node Type
		- Firmware Version
		- User ID management
		- Configuration file loading and saving
	*/
	public ref class cliIInfo
	{
	private:
		IInfo &myInfo;
		cliValueUnsigned^ m_SerialNumber;
		cliValueString^ m_FirmwareVersion;
		cliValueUnsigned^ m_FirmwareVersionCode;
		cliValueString^ m_HardwareVersion;
		cliValueString^ m_Model;
		cliValueUnsigned^ m_PositioningResolution;
		cliValueString^ m_UserID;
		cliValueUnsigned^ m_UserRAM;
		cliIInfoEx^ m_Ex;
		cliIInfoAdv^ m_Adv;
	public:
		// Constructor / destructor
		cliIInfo::cliIInfo(IInfo &val);
		cliIInfo::~cliIInfo() { this->!cliIInfo(); }
		cliIInfo::!cliIInfo();

		enum class _nodeTypes {
			UNKNOWN,
			MERIDIAN_ISC,
			CLEARPATH_SC,
			CLEARPATH_SC_ADV
		};
		/*
			Get serial number of this node.

			Access the node serial number via the Value function.
		*/
		property cliValueUnsigned^ SerialNumber { cliValueUnsigned^ get() { return m_SerialNumber; } }
		/*
			Return a firmware version string.

			The string is in the format of "x.y.z checksum" for example, "1.0.2 E113".
		*/
		property cliValueString^ FirmwareVersion { cliValueString^ get() { return m_FirmwareVersion; } }
		/*
			Get the version number code.

			This is an unique value where the magnitude increases as newer firmware
			is released.
		*/
		property cliValueUnsigned^ FirmwareVersionCode { cliValueUnsigned^ get() { return m_FirmwareVersionCode; } }
		/*
			Get the hardware version code string.

			This reference allows access to the node's hardware version string.
		*/
		property cliValueString^ HardwareVersion { cliValueString^ get() { return m_HardwareVersion; } }
		/*
			Get the model string.

			This reference allows access to the model string for this node
		*/
		property cliValueString^ Model { cliValueString^ get() { return m_Model; } }
		/*
			Get the positioning resolution

			This function allows access to the node's positioning resolution.
			The returned value is the number of position counts per revolution.
		*/
		property cliValueUnsigned^ PositioningResolution { cliValueUnsigned^ get() { return m_PositioningResolution; } }
		/*
			Manage the UserID string for this node.

			This parameter is saved to and overwritten by loading configuration files, or resetting to factory defaults
		*/
		property cliValueString^ UserID { cliValueString^ get() { return m_UserID; } }
		/*
			Manage User Volatile Data.

			This feature is useful for your application to stash information in
			a node in case the host application crashes.

			This value is set to zero up power-up or restarting.
		*/
		property cliValueUnsigned^ UserRAM { cliValueUnsigned^ get() { return m_UserRAM; } }
		/*
			Expert Information Access.

			This object allow access to expert information.

			These include:
			- The network address
			- The node index for this node
			- Generic Parameter maintenance
		*/
		property cliIInfoEx^ Ex { cliIInfoEx^ get() { return m_Ex; } }
		/*
			Advanced model information access.

			This object will work with Advanced firmware nodes.

			There is no feature currently implemented here yet.
		*/
		property cliIInfoAdv^ Adv { cliIInfoAdv^ get() { return m_Adv; } }

		/*
			Return the enumerated type of this node.

			This function is used to determine the type and base capabilities
			of this node.
		*/
		_nodeTypes NodeType() { return (_nodeTypes)myInfo.NodeType(); }
		/*
			\brief Set the Current User Defined Non-volatile Data.

			Param [in] bank which bank of data to write to [0-3].
			Param [in] m_lastUserData The data to write into the Node.  MN_USER_NV_SIZE = 13 for ClearPath SC Nodes.


			This feature allows the storage of calibration or other data at a node
			location. This information will be retained without power and survives
			node restarts, and configuration file changes.  Up to 4 banks of 13 bytes are available

			Restoring the node to Factory Settings will clear this
			data.
		*/
		void UserData(uintptr_t bank, const byte m_lastUserData[MN_USER_NV_SIZE]) {
			myInfo.UserData((size_t)bank, m_lastUserData);
		}
		/*
			Get the Current User Defined Non-volatile Data.

			Param [in] bank which bank of data to access [0-3].

			This function allows access to the non-volatile storage areas.

			Restoring the node to Factory Settings will clear this
			data.
		*/
		std::vector<uint8_t> UserData(uintptr_t bank) { return myInfo.UserData((size_t)bank); }
	};
	//																			  *
	//*****************************************************************************

	//*****************************************************************************
	// NAME																	      *
	// 	cliIInfoAdv class
	/*
		Advanced Information Features Interface.

		This class object implements access to the advanced node information.

		There is currently no advanced information available.
	*/
	public ref class cliIInfoAdv
	{
	private:
		IInfoAdv &myInfoAdv;
	public:
		// Constructor / destructor
		cliIInfoAdv::cliIInfoAdv(IInfoAdv &val) : myInfoAdv(val) {}
		cliIInfoAdv::~cliIInfoAdv() { this->!cliIInfoAdv(); }
		cliIInfoAdv::!cliIInfoAdv() {}
	};
	//																			  *
	//*****************************************************************************

	//*****************************************************************************
	// NAME																	      *
	// 	cliIInfoEx class

	/*
		Expert Information Interface.

		This class object implements access to expert node information.
	*/
	public ref class cliIInfoEx
	{
	private:
		IInfoEx &myInfoEx;
		multiaddr^ m_Addr;
		nodeaddr^ m_NodeIndex;
	public:
		// Constructor / destructor
		cliIInfoEx::cliIInfoEx(IInfoEx &val);
		cliIInfoEx::~cliIInfoEx() { this->!cliIInfoEx(); }
		cliIInfoEx::!cliIInfoEx();

		/**
			Get our internal network address.

			Return The network address for this node.

			This information allows the retrieval of the internal network address.
		**/
		property multiaddr^ Addr { multiaddr^ get() { return (System::UInt16)m_Addr; } }
		/*
			Get this node's network location

			Return The node index for this port.

			This is the zero based index of the location of the node. The first
			node from the host starts the count.
		*/
		property nodeaddr^ NodeIndex { nodeaddr^ get() { return m_NodeIndex; } }

		/*
			Get a numeric parameter's current value

			Param[in] index The parameter number for a numeric parameter.
			Return Numeric value. The scaling and units depend on the requested
			parameter.

			This function should only be used under direction of Teknic support
			staff.
		*/
		double Parameter(nodeparam index) { return myInfoEx.Parameter(index); }
		/*
			Set a numeric parameter's new value

			Param[in] index The parameter number for a numeric parameter.
			Param[in] newValue The new value to write into this parameter.

			This function should only be used under direction of support
			staff.
		*/
		void Parameter(nodeparam index, double newValue) { myInfoEx.Parameter(index, newValue); }
	};
	//																			  *
	//*****************************************************************************

	//*****************************************************************************
	// NAME																	      *
	// 	cliILimits Class
	/*
		Torque and Position Limits Feature Interface.

		This class object implements the settings for torque limits and
		positional limits.
	*/
	public ref class cliILimits
	{
	private:
		ILimits &myLimits;
		cliValueDouble^ m_TrqGlobal;
		cliValueSigned^ m_SoftLimit1;
		cliValueSigned^ m_SoftLimit2;
		cliValueUnsigned^ m_PosnTrackingLimit;
		cliValueDouble^ m_MotorSpeedLimit;
		cliILimitsAdv^ m_Adv;
	public:
		// Constructor / destructor
		cliILimits::cliILimits(ILimits &val);
		cliILimits::~cliILimits() { this->!cliILimits(); }
		cliILimits::!cliILimits();

		/*
			Access the node's global torque limit.

			Access the node's global torque limit in the current user torque units.(cliINode::TrqUnit).
			Typically this value is set through the ClearView application and is not changed during the application.
		*/
		property cliValueDouble^ TrqGlobal { cliValueDouble^ get() { return m_TrqGlobal; } }
		/*
			Access the software limits 1.

			Typically these values are set through the ClearView application and are not changed during the application.

			Soft limits are only enabled when the absolute number space has been established via homing
		*/
		property cliValueSigned^ SoftLimit1 { cliValueSigned^ get() { return m_SoftLimit1; } }
		/*
			Access the software limits 2.

			Typically these values are set through the ClearView application and are not changed during the application.

			Soft limits are only enabled when the absolute number space has been established via homing
		*/
		property cliValueSigned^ SoftLimit2 { cliValueSigned^ get() { return m_SoftLimit2; } }
		/*
			Access the tracking limit shutdown point.

			This parameter is a safety limit should not be changed by the application
			during operation except is rare application specific circumstances.

			Tracking error(cliIMotion::PosnTracking) at or beyond this point will cause a safety shutdown to occur.
		*/
		property cliValueUnsigned^ PosnTrackingLimit { cliValueUnsigned^ get() { return m_PosnTrackingLimit; } }
		/*
			Access the motor speed limit.

			This value is returned in the current user velocity units.
		*/
		property cliValueDouble^ MotorSpeedLimit { cliValueDouble^ get() { return m_MotorSpeedLimit; } }
		/*
			Access the advanced limits object.

			Access to the advanced limit features for Advanced ClearPath-SC Nodes.
		*/
		property cliILimitsAdv^ Adv { cliILimitsAdv^ get() { return m_Adv; } }
	};
	//																			  *
	//*****************************************************************************


	//*****************************************************************************
	// NAME																	      *
	// 	cliILimitsAdv Class
	/*
		Advanced Limit Feature Interface.

		This class object implements the settings for directional torque limiting.
	*/
	public ref class cliILimitsAdv
	{
	private:
		ILimitsAdv &myLimitsAdv;
		cliValueDouble^ m_NegativeRelaxTCmsec;
		cliValueDouble^ m_NegativeTrq;
		cliValueDouble^ m_PositiveRelaxTCmsec;
		cliValueDouble^ m_PositiveTrq;
	public:
		// Constructor / destructor
		cliILimitsAdv::cliILimitsAdv(ILimitsAdv &val);
		cliILimitsAdv::~cliILimitsAdv() { this->!cliILimitsAdv(); }
		cliILimitsAdv::!cliILimitsAdv();

		/*
			Access the node's positive torque limit object.

			Access the node's positive torque limit parameter object using the current torque
			units. This parameter determines the positive torque limit used when positive torque limiting
			is started.

			See cliINode::TrqUnit To determine the unit
			See cliINode::TrqUnit(_trqUnits) To change the unit
			See cliValueDouble for manipulation examples
		*/
		property cliValueDouble^ PositiveTrq { cliValueDouble^ get() { return m_PositiveTrq; } }
		/*
			Access the node's positive torque limit time constant.

			Access the node's positive torque limit time constant parameter object. The value is
			specified in milliseconds.  This parameter controls how quickly the torque limit is changed
			after positive torque limiting has started.  A longer time constant will produce a smoother
			change in torque, a shorter time constant will produce a more sudden change.

			See cliValueDouble for manipulation examples
		*/
		property cliValueDouble^ PositiveRelaxTCmsec { cliValueDouble^ get() { return m_PositiveRelaxTCmsec; } }
		/*
			Access the node's negative torque limit.

			Access the node's negative torque limit parameter object in the current torque units.
			This parameter determines the negative torque limit used when negative torque limiting
			is started.

			See cliINode::TrqUnit To determine the unit
			See cliINode::TrqUnit(_trqUnits) To change the unit
			See cliValueDouble for manipulation examples
		*/
		property cliValueDouble^ NegativeTrq { cliValueDouble^ get() { return m_NegativeTrq; } }
		/*
			Access the node's negative torque limit time constant.

			Access the node's negative torque limit time constant parameter object. The value is
			specified in milliseconds.  This parameter controls how quickly the torque limit is changed
			after negative torque limiting has started.  A longer time constant will produce a smoother
			change in torque, a shorter time constant will produce a more sudden change.

			See cliValueDouble for manipulation examples
		*/
		property cliValueDouble^ NegativeRelaxTCmsec { cliValueDouble^ get() { return m_NegativeRelaxTCmsec; } }
		
		/*
			Control the positive torque limit feature.

			Control user initiate the positive torque limit feature when
			engage is true.  If engage is false positive torque limiting is
			turned off.

			If the node has been configured through Clearview to start limiting positive torque based off
			and input, or move done, etc. this request is ignored but remembered as the user's selection.
		*/
		void StartPosFoldback(bool engage) { myLimitsAdv.StartPosFoldback(engage); }
		/*
			Get current state of the positive torque limit.

			Return the status of the user initiated positive torque limiting.  True indicates the positive
			torque limit is active.  False indicates the positive torque limit is inactive.

			If the node has been configured through Clearview to start limiting positive torque based off
			and input, or move done, etc. this request returns the user's requested state, not the actual state.
		*/
		bool StartPosFoldback() { return myLimitsAdv.StartPosFoldback(); }
		/*
			\Control the negative torque limit feature.

			Control user initiate the negative torque limit feature when
			engage is true.

			If the node has been configured through Clearview to start limiting negative torque based off
			and input, or move done, etc. this request is ignored but remembered as the user's selection.
		*/
		void StartNegFoldback(bool engage) { myLimitsAdv.StartNegFoldback(engage); }
		/*
			Get current state of the negative torque limit.

			Return the status of the user initiated negative torque limiting.  True indicates the negative
			torque limit is active.  False indicates the negative torque limit is inactive.

			If the node has been configured through Clearview to start limiting negative torque based off
			and input, or move done, etc. this request returns the user's requested state, not the actual state.
		*/
		bool StartNegFoldback() { return myLimitsAdv.StartNegFoldback(); }
	};
	//																			  *
	//*****************************************************************************

	//*****************************************************************************
	// NAME																	      *
	// 	cliIMotion Class
	/*
		Motion Control Feature Interface.

		This class object allows setup, initiation and cancellation of motion.
	*/
	public ref class cliIMotion
	{
	private:
		IMotion &myMotion;
		cliValueDouble^ m_AccLimit;
		cliValueDouble^ m_VelLimit;
		cliValueUnsigned^ m_JrkLimit;
		cliValueDouble^ m_JrkLimitDelay;
		cliValueUnsigned^ m_DwellMs;
		cliValueDouble^ m_NodeStopDecelLim;
		cliValueDouble^ m_PosnMeasured;
		cliValueDouble^ m_PosnCommanded;
		cliValueDouble^ m_PosnTracking;
		cliValueDouble^ m_VelMeasured;
		cliValueDouble^ m_VelCommanded;
		cliValueDouble^ m_TrqMeasured;
		cliValueDouble^ m_TrqCommanded;
		cliIMotionAdv^ m_Adv;
		cliIHoming^ m_Homing;
	public:
		// Constructor / destructor
		cliIMotion::cliIMotion(IMotion &val);
		cliIMotion::~cliIMotion() { this->!cliIMotion(); }
		cliIMotion::!cliIMotion();

		/*
			Current Node Acceleration Limit

			Access the acceleration limit value for the next issued move. The value
			is specified using this node's user acceleration units. Changed values will
			apply to the next move.  The default units are RPM/sec

			See cliINode::AccUnit
		*/
		property cliValueDouble^ AccLimit {
			cliValueDouble^ get() { return m_AccLimit; }
			void set(cliValueDouble^ newValue) { m_AccLimit = newValue; }
		}
		/*
			Current Node Velocity Limit

			Access the current velocity limit value specified in the current velocity
			units. Changed values will apply to the next issued move.  The default units
			are RPM.

			See cliINode::VelUnit
		*/
		property cliValueDouble^ VelLimit {
			cliValueDouble^ get() { return m_VelLimit; }
			void set(cliValueDouble^ newValue) { m_VelLimit = newValue; }
		}
		/*
			Get the current jerk limit register.
		*/
		property cliValueUnsigned^ JrkLimit {
			cliValueUnsigned^ get() { return m_JrkLimit; }
			void set(cliValueUnsigned^ newValue) { m_JrkLimit = newValue; }
		}
		/*
			Get the current delay added by the jerk limit.
		*/
		property cliValueDouble^ JrkLimitDelay {
			cliValueDouble^ get() { return m_JrkLimitDelay; }
			void set(cliValueDouble^ newValue) { m_JrkLimitDelay = newValue; }
		}
		/*
			Post-motion dwell time in milliseconds.

			Access to the post move dwell time used in positional moves with a after-move dwell.

			See MovePosnStart() for more information on how to command a positional move with dwell
		*/
		property cliValueUnsigned^ DwellMs {
			cliValueUnsigned^ get() { return m_DwellMs; }
			void set(cliValueUnsigned^ newValue) { m_DwellMs = newValue; }
		}
		/*
			Access the stopping acceleration limits in step/sec^2.
		*/
		property cliValueDouble^ NodeStopDecelLim {
			cliValueDouble^ get() { return m_NodeStopDecelLim; }
			void set(cliValueDouble^ newValue) { m_NodeStopDecelLim = newValue; }
		}
		/*
			Access the current measured position.

			The resolution of this value will be the same as the positioning resolution of the motor (800cnts/rev for "Regular" 6400cnts/rev for "Enhanced").
			This means that for step+direction modes the position may be scaled differently from the step and direction input  based on the ratio of the input
			resolution set up through ClearView, and the motor's native positioning resolution.  For example, if you are using a "Regular" ClearPath-SC motor
			with a native positioning resolution of 800 cnts/rev, and you set the Input resolution to 200 steps/rev to drop in for a 200 cnt stepper motor, each
			step sent will change the position 4 cnts.
		*/
		property cliValueDouble^ PosnMeasured { cliValueDouble^ get() { return m_PosnMeasured; } }
		/*
			Access the current commanded position.

			The resolution of this value will be the same as the positioning resolution of the motor (800cnts/rev for "R" 6400cnts/rev for "E").
			This means that for step and direction modes, the position may be scaled differently from the step and direction input  based on the ratio of the input
			resolution set up through ClearView, and the motor's native positioning resolution.  For example, if you are using a "R" ClearPath-SC motor
			with a native positioning resolution of 800 cnts/rev, and you set the Input resolution to 200 steps/rev to drop in for a 200 cnt stepper motor, each
			step sent will change the position 4 cnts.
		*/
		property cliValueDouble^ PosnCommanded { cliValueDouble^ get() { return m_PosnCommanded; } }
		/*
			Access the current position tracking error.

			 Tracking error is defined as commanded position - measured position.

			The resolution of this value will be the same as the positioning resolution of the motor (800cnts/rev for "Regular" 6400cnts/rev for "Enhanced").
			This means that for step+direction modes the position may be scaled differently from the step and direction input  based on the ratio of the input
			resolution set up through ClearView, and the motor's native positioning resolution.  For example, if you are using a "Regular" ClearPath-SC motor
			with a native positioning resolution of 800 cnts/rev, and you set the Input resolution to 200 steps/rev to drop in for a 200 cnt stepper motor, each
			step sent will change the position 4 cnts.
		*/
		property cliValueDouble^ PosnTracking { cliValueDouble^ get() { return m_PosnTracking; } }
		/*
			Access the current measured velocity.

			The velocity is scaled to the current node's velocity unit.  
			The default units are RPM.

			See cliINode::VelUnit(_velUnits) To set velocity units.
		*/
		property cliValueDouble^ VelMeasured { cliValueDouble^ get() { return m_VelMeasured; } }
		/*
			Access the current commanded velocity. The velocity is scaled to the
			current node's velocity unit. The default units are RPM.

			See cliINode::VelUnit(_velUnits) To set velocity units.
		*/
		property cliValueDouble^ VelCommanded { cliValueDouble^ get() { return m_VelCommanded; } }
		/*
			Access the current measured torque. The torque is scaled to the
			current node's torque unit. The default units are percentage of maximum.

			See cliINode::TrqUnit(_trqUnits)
		*/
		property cliValueDouble^ TrqMeasured { cliValueDouble^ get() { return m_TrqMeasured; } }
		/*
			Access the current commanded torque. The torque is scaled to the
			current node's torque unit. The default units are percentage of maximum.

			See cliINode::TrqUnit(_trqUnits)
		*/
		property cliValueDouble^ TrqCommanded { cliValueDouble^ get() { return m_TrqCommanded; } }
		/*
			Access advanced features if available on the node's model.
		*/
		property cliIMotionAdv^ Adv { cliIMotionAdv^ get() { return m_Adv; } }
		/*
			Access to the homing feature.
		*/
		property cliIHoming^ Homing { cliIHoming^ get() { return m_Homing; } }
		
		/*
			Calculate the duration of a positional move.

			Param[in] target Target position. This is either the
			absolute position or relative to the current position
			depending on the targetIsAbsolute argument.
			Param[in] targetIsAbsolute The target is an absolute
			destination.

			Using the currently specified kinematic constraints, return the
			expected duration (in milliseconds) of the move from when it
			starts to when the move command completes.

			This function is useful for setting up timeouts or helping to schedule
			other events in your application.
		*/
		double MovePosnDurationMsec(int target, bool targetIsAbsolute) {
			return myMotion.MovePosnDurationMsec((int32_t)target, targetIsAbsolute);
		}
		/*
			Calculate the duration of a velocity move.

			Param [in] target Target velocity.

			Using the currently specified kinematic constraints, return the
			expected duration (in milliseconds) of the move's acceleration to the target velocity.

			This function is useful for setting up timeouts or helping to schedule
			other events in your application.
		*/
		double MoveVelDurationMsec(double target) { return myMotion.MoveVelDurationMsec(target); }

		/*
			Initiate a positional move.

			Param [in] target Target position. This is either the
			absolute position of relative to the current position
			depending on the targetIsAbsolute argument.
			Param [in] targetIsAbsolute the target is an absolute
			destination.
			Param [in] addPostMoveDwell delay the next move being issued
			by DwellMs after this move profile completes.
			Return Number of additional moves the node will accept.

			The move is kinematically limited by the current
			acceleration(AccLimit) and velocity(VelLimit) limits.

			Move requests are buffered and requests initiated during an active move will execute
			immediately after the active move completes. The return value
			will tell you the number of additional moves that may be queued(up to 16) when
			this request is processed.  You can also use the Status
			Register's _cpmStatusRegFlds::MoveBufAvail field, which will be
			deasserted when the buffer is full.
		*/
		uintptr_t MovePosnStart(int target, bool targetIsAbsolute, bool addPostMoveDwell) {
			return myMotion.MovePosnStart((int32_t)target, targetIsAbsolute, addPostMoveDwell);
		}
		/*
			Initiate a velocity move.

			Param [in] target Target velocity.
			Return Number of additional moves the node will accept.

			The move is kinematically limited by the current
			acceleration limit(cliIMotion::AccLimit).

			Move requests are buffered and requests initiated during a active move will execute
			immediately after the active move completes. The return value
			will tell you the number of additional moves that may be queued(up to 16) when
			this request is processed. You can also use the Status
			Register's _cpmStatusRegFlds::MoveBufAvail field, which will be
			deasserted when the buffer is full.
		*/
		uintptr_t MoveVelStart(double target) { return myMotion.MoveVelStart(target); }

		/*
			Update the status rise register and test and clear the move
			done field.

			Update the status rise register(cliIStatus::Rise)  and test and clear the node
			Move Done(clicpmStatusRegFlds::MoveDone) field.

			Return true if Move Done went true since last call.

			For performance reasons it may be superior to use the Status reference
			and perform a Refresh in a periodic place in your
			application and check the results via the Status object(cliValueStatus).
		*/
		bool MoveWentDone() { return myMotion.MoveWentDone(); }
		/*
			Update the real-time status register and test for move done.

			Refresh the real-time status register(cliIStatus::RT) and test for Move Done(cliCPMStatusRegFlds::MoveDone).
			This allows for a simple script-like interface.

			Return true if Move Done is true.

			\note For performance reasons it may be superior to use the real-time status register reference
			and perform a Refresh in a periodic place in your application and check the results via the Status object(cliValueStatus).
		*/
		bool MoveIsDone() { return myMotion.MoveIsDone(); }
		/*
			Update the status rise register and test and clear the
			At Target Velocity field.

			Update the status rise register(cliIStatus::Rise)  and test and clear the node
			At Target Velocity(cliCPMStatusRegFlds::AtTargetVel) field.

			Return true if At Target Velocity went true since last call.

			For performance reasons it may be superior to use the status rise register(cliIStatus::Rise) reference
			and perform a Refresh in a periodic place in your
			application and check the results via the Status object(cliValueStatus).
		*/
		bool VelocityReachedTarget() { return myMotion.VelocityReachedTarget(); }
		/*
			Update the real-time status register and test for At
			Target Velocity.

			Refresh the real-time status register(cliIStatus::RT) and test for At Target Velocity(cliCPMStatusRegFlds::AtTargetVel).
			This allows for a simple script-like interface.

			Return true if At Target Velocity(cliCPMStatusRegFlds::AtTargetVel) is true.

			For performance reasons it may be necessary to use the Status reference(cliIStatus::RT)
			and manually perform a Refresh in a periodic place if your application and check the results.
		**/
		bool VelocityAtTarget() { return myMotion.VelocityAtTarget(); }
		/*
			Update the status rise register and test and clear the node
			not ready field.

			Update the status rise register(cliIStatus::Rise) and test and clear the node
			Not Ready(cliCPMStatusRegFlds::NotReady) field.

			For performance reasons it may be superior to use the status rise register(cliIStatus::Rise)
			reference and perform a Refresh in a periodic place in your
			application and check the results via the Status object(cliValueStatus).
		*/
		bool WentNotReady() { return myMotion.WentNotReady(); }
		/*
			Update the real-time status register and test for Node ready.

			Refresh the real-time status register(cliIStatus::RT) and test for Node Ready(cliCPMStatusRegFlds::NotReady).
			This allows for a simple script-like interface.

			\return true if the Node is ready(cliCPMStatusRegFlds::NotReady) for motion command.

			For performance reasons it may be necessary to use the Status reference(cliIStatus::RT)
			and manually perform a Refresh in a periodic place if your application and check the results via the Status object.
		*/
		bool IsReady() { return myMotion.IsReady(); }
		/*
			Initiate a simple node stop at this node.

			Param[in] howToStop One of the commonly used Node Stop codes.

			This is the simplest way to command a nodestop.

			See cliIMotion::NodeStopClear To clear latching attributes

		*/
		void NodeStop(cliNodeStopCodes howToStop) { myMotion.NodeStop((nodeStopCodes)howToStop); }
		/*
			Initiate a node stop on all nodes on this port.

			Param[in] howToStop One of the commonly used Node Stop codes.

			This is the simplest way to broadcast a group node stop. This issues
			a stop of the specified type to all nodes on the initiating node's port.

			See cliIMotion::NodeStopClear To clear latching attributes

		*/
		void GroupNodeStop(cliNodeStopCodes howToStop) {
			myMotion.GroupNodeStop((nodeStopCodes)howToStop);
		}
		/*
			Clear all latching Node Stop modifiers.

			This function will clear the MotionLock, E-Stop, Controlled, Disabled,
			etc. latching conditions from the node. This will allow
			normal operations to continue, unless the motor is shutdown state.

			See cliIMotion::NodeStop(nodeStopCodes) For initiating Node Stops
		*/
		void NodeStopClear() {  myMotion.NodeStopClear(); }
		/*
			Adjust number space.

			Param[in] adjAmount The amount to adjust the number space.

			This function is used mostly with a manual homing process, or anytime an application need to adjust the number space. It allows
			the measured(PosnMeasured) and commanded(PosnCommanded) position to be shifted by the specified amount.

			If using Soft Position limits, this command will
			reset the motor's "Was Homed"(cliCPMStatusRegFlds::WasHomed) status causing the soft
			limit settings to be ignored.  To re-enable soft limits see the cliIHoming::SignalComplete function.

		*/
		void AddToPosition(double adjAmount) { myMotion.AddToPosition(adjAmount); }
	};
	//																			  *
	//*****************************************************************************

	//*****************************************************************************
	// NAME																	      *
	// 	cliIMotionAdv Class
	/*
		Advanced Motion Control Interface.

		This class object allows setup and initiation of advanced motion features only available
		in advance models of Clearpath SC.  These features include:

		- Head, and Tail Moves(HeadTailMoveSect)
		- Asymmetric moves(AsymetricalMoveSect)
		- Triggered Moves(CPMtriggerPage)
		- A after start(cliCPMStatusRegFlds::AFromStart)/ B after end events(cliCPMStatusRegFlds::BFromEnd)
	*/
	public ref class cliIMotionAdv
	{
	private:
		IMotionAdv &myMotionAdv;
		cliValueUnsigned^ m_AAfterStartDistance;
		cliValueUnsigned^ m_BeforeEndDistance;
		cliValueDouble^ m_DecelLimit;
		cliValueDouble^ m_HeadTailVelLimit;
		cliValueUnsigned^ m_HeadDistance;
		cliValueUnsigned^ m_TailDistance;
	public:
		// Constructor / destructor
		cliIMotionAdv::cliIMotionAdv(IMotionAdv &val);
		cliIMotionAdv::~cliIMotionAdv() { this->!cliIMotionAdv(); }
		cliIMotionAdv::!cliIMotionAdv();

		/*
			Access the A after Start event distance.

			The resolution of this value will be the same as the positioning resolution of the motor (800cnts/rev for "Regular" 6400cnts/rev for "Enhanced").

			cliCPMStatusRegFlds::AFromStart for the associated Status event
		**/
		property cliValueUnsigned^ AAfterStartDistance {
			cliValueUnsigned^ get() { return m_AAfterStartDistance; }
		}
		/*
			Access the B before End event distance in steps.

			The resolution of this value will be the same as the positioning resolution of the motor (800cnts/rev for "Regular" 6400cnts/rev for "Enhanced").

			cliCPMStatusRegFlds::BFromEnd for the associated Status event
		*/
		property cliValueUnsigned^ BeforeEndDistance {
			cliValueUnsigned^ get() { return m_BeforeEndDistance; }
		}
		/*
			Access the decceleration limit value for the next asymmetric move. The value
			is specified using this node's user acceleration units. Changed values will
			apply to the next move.  The default units are RPM/sec

			cliINode::AccUnit(enum _accUnits newUnits) Changing Acceleration Units
		*/
		property cliValueDouble^ DecelLimit {
			cliValueDouble^ get() { return m_DecelLimit; }
		}
		/*
			Access the velocity limit for the head-tail sections of the
			next issued head-tail move.

			Access the current head/tail velocity limit for the next head-tail move.
			The value is specified in the current velocity
			units. Changed values will apply to the next issued move.  The default units
			are RPM.

			See cliINode::VelUnit(enum _velUnits newUnits)
		*/
		property cliValueDouble^ HeadTailVelLimit {
			cliValueDouble^ get() { return m_HeadTailVelLimit; }
		}
		/*
			Access the head distance for the next issued head-tail move
			in steps.

			The resolution of this value will be the same as the positioning resolution of the motor (800cnts/rev for "Regular" 6400cnts/rev for "Enhanced").
		*/
		property cliValueUnsigned^ HeadDistance {
			cliValueUnsigned^ get() { return m_HeadDistance; }
		}
		/*
			Access the tail distance for the next issued head-tail
			move in steps.

			The resolution of this value will be the same as the positioning resolution of the motor (800cnts/rev for "Regular" 6400cnts/rev for "Enhanced").
		*/
		property cliValueUnsigned^ TailDistance {
			cliValueUnsigned^ get() { return m_TailDistance; }
		}

		/*
			Calculate the duration of a positional move.

			Param [in] targetPosn Target position. This is either the
			absolute position of relative to the current position
			depending on the targetIsAbsolute argument.
			Param [in] targetIsAbsolute the target is an absolute
			destination.
			Return duration (milliseconds)

			Using the currently specified kinematic constraints, return the
			expected duration (in milliseconds) of the move from when it
			starts to when the move command completes.

			This function is useful for setting up timeouts or helping to schedule
			other events in your application.

		*/
		double MovePosnDurationMsec(int targetPosn, bool targetIsAbsolute) {
			return myMotionAdv.MovePosnDurationMsec((int32_t)targetPosn, targetIsAbsolute);
		}
		/*
			Returns the duration of a head-tail positional move.

			Param [in] targetPosn Target position. This is either the
			absolute position of relative to the current position
			depending on the theType argument. The triggered
			type move will prevent execution of the motion until a
			trigger event is detected at the node.
			Param [in] targetIsAbsolute the target is an absolute
			destination.
			Param [in] hasHead Do not exceed the HeadTailVelLimit until
			after HeadDistance steps have been sent.
			Param [in] hasTail Do not exceed the HeadTailVelLimit during
			the last TailDistance steps of the move.
			Return motion duration (milliseconds)

			Using the currently specified kinematic constraints, return the
			expected duration (in milliseconds) of the move from when it
			starts to when the move command completes.

			This function is useful for setting up timeouts or helping to schedule
			other events in your application.
		*/
		double MovePosnHeadTailDurationMsec(int targetPosn, bool targetIsAbsolute, bool hasHead, bool hasTail) {
			return myMotionAdv.MovePosnHeadTailDurationMsec((int32_t)targetPosn, targetIsAbsolute, hasHead, hasTail);
		}
		/*
			\brief Returns the duration of an asymmetric positional move.

			Param [in] targetPosn Target position. This is either the
			absolute position of relative to the current position
			depending on the theType argument. The triggered
			type move will prevent execution of the motion until a
			trigger event is detected at the node.
			Param [in] targetIsAbsolute the target is an absolute
			destination.
			Return motion duration (milliseconds)

			Using the currently specified kinematic constraints, return the
			expected duration (in milliseconds) of the move from when it
			starts to when the move command completes.

			This function is useful for setting up timeouts or helping to schedule
			other events in your application.
		*/
		double MovePosnAsymDurationMsec(int targetPosn, bool targetIsAbsolute) {
			return myMotionAdv.MovePosnAsymDurationMsec((int32_t)targetPosn, targetIsAbsolute);
		}
		/*
			Returns the duration of a velocity move.

			Param [in] targetCountsPerSec Target velocity. (counts/sec)
			Return time to reach target velocity (milliseconds)

			Using the currently specified kinematic constraints, return the
			expected duration (in milliseconds) of the move's acceleration to the target velocity.

			This function is useful for setting up timeouts or helping to schedule
			other events in your application.
		*/
		double MoveVelDurationMsec(double targetCountsPerSec) {
			return myMotionAdv.MoveVelDurationMsec(targetCountsPerSec);
		}

		/*
			Initiate a trapezoid/triangle positional move.

			Param [in] targetPosn Target position. This is either the
			absolute position of relative to the current position
			depending on the theType argument. The triggered
			type move will prevent execution of the motion until a
			trigger event is detected at the node.
			Param [in] targetIsAbsolute the target is an absolute
			destination.
			Param [in] isTriggered The move awaits a trigger event
			to start the motion if true.
			Param [in] hasDwell The move will wait the dwell parameter
			amount of time before starting the next move.
			Return Number of additional moves the node will accept.

			The move is kinematically limited by the current
			acceleration(cliIMotion::AccLimit) and velocity(cliIMotion::VelLimit) limits.

			Move requests are buffered and requests initiated during an active move will execute
			immediately after the active move completes.  Triggered moves will wait for a trigger event before executing.
			The return value will tell you the number of additional moves that may be queued(up to 16) when
			this request is processed.  You can also use the Status
			Register's cliCPMStatusRegFlds::MoveBufAvail field, which will be
			deasserted when the buffer is full.

			See cliIPortAdv::TriggerMovesInGroup For starting these moves
			See cliIMotionAdv::TriggerMove For starting these moves
		*/
		uintptr_t MovePosnStart(int targetPosn, bool targetIsAbsolute, bool isTriggered, bool hasDwell) {
			return myMotionAdv.MovePosnStart((int32_t)targetPosn, targetIsAbsolute, isTriggered, hasDwell);
		}
		/*
			Initiate a head-tail positional move.

			Param [in] targetPosn The target position. This is either the
			absolute position of relative to the current position
			depending on the theType argument. The triggered
			type move will prevent execution of the motion until a
			trigger event is detected at the node.
			Param [in] targetIsAbsolute the target is an absolute
			destination.
			Param [in] isTriggered The move awaits a trigger event
			to start the motion if true.
			Param [in] hasHead Do not exceed the HeadTailVelLimit until
			after HeadDistance steps have been sent.
			Param [in] hasTail Do not exceed the HeadTailVelLimit during
			the last TailDistance steps of the move.
			Param [in] hasDwell delay the next move being issued
			by DwellMs after this move profile completes.
			Return Number of additional moves the node will accept.

			The move is kinematically limited by the current
			acceleration(cliIMotion::AccLimit), velocity(cliIMotion::VelLimit), 
			as well as Head(cliIMotionAdv::HeadDistance) and tailcliIMotionAdv::TailDistance) distances.

			Move requests are buffered and requests initiated during an active move will execute
			immediately after the active move completes.  Triggered moves will wait for a trigger event before executing.
			The return value will tell you the number of additional moves that may be queued(up to 16) when
			this request is processed.  You can also use the Status
			Register's cliCPMStatusRegFlds::MoveBufAvail field, which will be
			deasserted when the buffer is full.

			See cliIPortAdv::TriggerMovesInGroup For starting these moves
			See cliIMotionAdv::TriggerMove For starting these moves
		*/
		uintptr_t MovePosnHeadTailStart(int targetPosn, bool targetIsAbsolute, bool isTriggered, 
										bool hasHead, bool hasTail, bool hasDwell) {
			return myMotionAdv.MovePosnHeadTailStart((int32_t)targetPosn, targetIsAbsolute, isTriggered, 
														hasHead, hasTail, hasDwell);
		}
		/*
			Initiate a asymmetric positional move.

			Param [in] targetPosn Target position. This is either the
			absolute position of relative to the current position
			depending on the theType argument. The triggered
			type move will prevent execution of the motion until a
			trigger event is detected at the node.
			Param [in] targetIsAbsolute the target is an absolute
			destination.
			Param [in] isTriggered The move awaits a trigger event
			to start the motion if true.
			Param [in] hasDwell The move will wait the dwell parameter
			amount of time before starting the next move.
			Return Number of additional moves the node will accept.

			The move is kinematically limited by the current
			acceleration(cliIMotion::AccLimit), deceleration(cliIMotionAdv::DecelLimit), and velocity(cliIMotion::VelLimit).

			Move requests are buffered and requests initiated during an active move will execute
			immediately after the active move completes.  Triggered moves will wait for a trigger event before executing.
			The return value will tell you the number of additional moves that may be queued(up to 16) when
			this request is processed.  You can also use the Status
			Register's cliCPMStatusRegFlds::MoveBufAvail field, which will be
			deasserted when the buffer is full.

			See cliIPortAdv::TriggerMovesInGroup For starting these moves
			See cliIMotionAdv::TriggerMove For starting these moves
		*/
		uintptr_t MovePosnAsymStart(int targetPosn, bool targetIsAbsolute, bool isTriggered, bool hasDwell) {
			return myMotionAdv.MovePosnAsymStart((int32_t)targetPosn, targetIsAbsolute, isTriggered, hasDwell);
		}
		/*
			Initiate a velocity move.

			Param [in] targetPosn Target velocity. If the triggered
			argument is true, this move will wait for a trigger event
			to be detected at the node.
			Param [in] isTriggered The move awaits a trigger event
			to start the motion if true.
			Return Number of additional moves the node will accept.

			The move is kinematically limited by the current
			acceleration limit(cliIMotion::AccLimit).

			Move requests are buffered and requests initiated during an active move will execute
			immediately after the active move completes.  Triggered moves will wait for a trigger event before executing.
			The return value will tell you the number of additional moves that may be queued(up to 16) when
			this request is processed.  You can also use the Status
			Register's cliCPMStatusRegFlds::MoveBufAvail field, which will be
			deasserted when the buffer is full.
		*/
		uintptr_t MoveVelStart(double targetPosn, bool isTriggered) {
			return myMotionAdv.MoveVelStart(targetPosn, isTriggered);
		}

		/*
			Trigger a waiting move

			Call this function to release a waiting move.

			If there are no waiting moves or if the Node is currently executing a move, this command will be ignored.
		*/
		void TriggerMove() { myMotionAdv.TriggerMove(); }
		/*
			Trigger a group of waiting moves

			Call this function to release waiting moves in this trigger group.

			If there are no waiting moves, or if the node is currently executing a move this command will be ignored on that node.
		*/
		void TriggerMovesInMyGroup() { myMotionAdv.TriggerMovesInMyGroup(); }
		/*
			Get our current trigger group setting.

			Return This node's current group number

			If zero, there is no trigger group assigned and the group trigger
			will be ignored.
		*/
		uintptr_t TriggerGroup() { return myMotionAdv.TriggerGroup(); }
		/*
			Set our trigger group

			Param[in] groupNumber Set to non-zero to assign this
			node to a triggerable group. To remove from a group set to zero.

			The trigger group allows multiple nodes to start motion with low
			latency. For example a machine with multiple XYZ axes could assign
			groupNumber 1 to one set and 2 to another. Releasing one group with
			a cliIPortAdv::TriggerMovesInGroup(size_t) call, or by calling TriggerMovesInMyGroup on one of the Nodes.
		*/
		void TriggerGroup(uintptr_t groupNumber) { myMotionAdv.TriggerGroup((size_t)groupNumber); }
	};
	//																			  *
	//*****************************************************************************

	//*****************************************************************************
	// NAME																	      *
	// 	cliIMotionAudit class
	/*
		Motion Audit Feature Interface

		This class object implements access to the motion audit feature. This
		feature is used to watch a reference move and determine if the axis
		has problems that may require service.

		This is only available with Advanced feature set.
	*/
	public ref class cliIMotionAudit
	{
	private:
		IMotionAudit &myMotionAudit;
		cliAuditData^ m_Results;
	public:
		// Constructor / destructor
		cliIMotionAudit::cliIMotionAudit(IMotionAudit &val);
		cliIMotionAudit::~cliIMotionAudit() { this->!cliIMotionAudit(); }
		cliIMotionAudit::!cliIMotionAudit();

		/*
			Audit Monitoring Testpoints
		*/
		enum class _testPoints {
			//Watch Positional tracking errors.
			MON_POS_TRK = 6,
			//Watch measured torque.
			MON_TRQ_MEAS = 7,
			//Watch commanded torque.
			MON_TRQ_CMD = 8
		};

		/*
			Result from last Refresh.

			After calling the Refresh function, the results are stored here.

			This feature is only available on Advanced nodes.
		*/
		property cliAuditData^ Results { cliAuditData^ get() { return m_Results; } }

		/*
			Update the results.

			Calling this member function will retrieve the last collected audit
			information updating by calling IMotionAutit::Results function..

			This feature is only available on Advanced nodes.
		*/
		void Refresh() { myMotionAudit.Refresh(); }
		/*
			Setup monitoring test point

			Param[in] testPoint The node test point to monitor and collect
			statistics on.
			Param[in] fullScale The gain to apply for the selected channel. This
			should be carefully selected to match the expected values. If set too
			small, the values could be clipped in amplitude and if too large,
			quantization effects could affect the RMS and high frequency results.
			Param[in] filterTCmsec Low-pass filtering time constant specified
			in milliseconds.

			This function sets up the monitoring system test point. This test
			point collects high pass, low pass, maximum positive value, maximum
			negative value and RMS values during the collection interval.
		*/
		void SelectTestPoint(_testPoints testPoint, double fullScale, double filterTCmsec) {
			return myMotionAudit.SelectTestPoint((IMotionAudit::_testPoints)testPoint, fullScale, filterTCmsec);
		}
	};
	//																			  *
	//*****************************************************************************


	//*****************************************************************************
	// NAME																	      *
	// 	cliINode class
	/*
		Virtual Node Interface.

		This class defines a "super" node whose framework exposes the Node Level features
		available for your application by a series of public attribute references.
		There are common member functions for these feature objects to determine
		if the node supports the feature.

		This class also implements:
		- Velocity Units
		- Acceleration Units
		- Torque Units
		- Enable Requests

		See cliSysManager For the root object for interacting with
		ClearPath-SC motors.
		See cliSysManager::Ports To get references to the cliIPort objects created
		when cliSysManager::PortsOpen has successfully opened.
		See cliIPort::Nodes To get references to INode objects detected on a
		port.
	*/
	public ref class cliINode
	{
	private:
		INode &myNode;
		cliIPort^ m_Port;
		cliIInfo^ m_Info;
		cliIMotion^ m_Motion;
		cliIStatus^ m_Status;
		cliILimits^ m_Limits;
		cliIOuts^ m_Outs;
		cliISetup^ m_Setup;
		cliINodeEx^ m_Ex;
		cliINodeAdv^ m_Adv;
	public:
		// Constructor / destructor
		cliINode::cliINode(INode &node);
		cliINode::cliINode(const cliINode% node);
		cliINode::~cliINode() { this->!cliINode(); }
		cliINode::!cliINode();

		/*
			Units for Accelerations parameters and status.
		*/
		enum class _accUnits {
			RPM_PER_SEC,	///< Revolutions/Minute/Second 
			COUNTS_PER_SEC2	///< Counts/Second^2
		};
		/*
			Units for velocity parameters and status.
		*/
		enum class _velUnits {
			RPM,			///< Revolutions/Minute 
			COUNTS_PER_SEC	///< Counts/Second
		};
		/*
			Units for torque parameters and status.
		*/
		enum class _trqUnits {
			PCT_MAX,		///< Percentage of drive maximum
			AMPS			///< Drive delivery amps
		};

		/*
			Change the acceleration units

			Param[in] newUnits Change the acceleration units to newUnits.
		*/
		void AccUnit(_accUnits newUnits) { myNode.AccUnit((INode::_accUnits)newUnits); }
		/*
			Get the current acceleration units

			Return Current acceleration unit
		*/
		_accUnits AccUnit() { return (_accUnits)myNode.AccUnit(); }
		/*
			Change the velocity units

			Param[in] newUnits Set new velocity unit
		*/
		void VelUnit(_velUnits newUnits) { myNode.VelUnit((INode::_velUnits)newUnits); }
		/*
			Get the current velocity units

			Return Current velocity unit
		*/
		_velUnits VelUnit() { return (_velUnits)myNode.VelUnit(); }
		/*
			Change the torque units

			Param[in] newUnits New torque unit
		*/
		void TrqUnit(_trqUnits newUnits) { myNode.TrqUnit((INode::_trqUnits)newUnits); }
		/*
			Get the current torque units

			Return Current torque unit
		*/
		_trqUnits TrqUnit() { return (_trqUnits)myNode.TrqUnit(); }

		/*
			Get a reference to the port object this node is attached to.
		*/
		property cliIPort^ Port { cliIPort^ get() { return m_Port; } }
		/*
			This reference allows for access about generic information
			about a node.
		*/
		property cliIInfo^ Info { cliIInfo^ get() { return m_Info; } }
		/*
			Get a reference to the motion feature interface object
		*/
		property cliIMotion^ Motion { cliIMotion^ get() { return m_Motion; } }
		/*
			Get a reference to the status information object
		*/
		property cliIStatus^ Status { cliIStatus^ get() { return m_Status; } }
		/*
			Get a reference to the limits feature object
		*/
		property cliILimits^ Limits { cliILimits^ get() { return m_Limits; } }
		/*
			Get a reference to the outputs object
		*/
		property cliIOuts^ Outs { cliIOuts^ get() { return m_Outs; } }
		/*
			Get a reference to our Setup object
		*/
		property cliISetup^ Setup { cliISetup^ get() { return m_Setup; } }
		/*
			Get a reference to our expert features object
		*/
		property cliINodeEx^ Ex { cliINodeEx^ get() { return m_Ex; } }
		/*
			Get a reference to the advanced features object
		*/
		property cliINodeAdv^ Adv { cliINodeAdv^ get() { return m_Adv; } }

		/*
			Thread safe enable request
			Param[in] newState Change the state of the Enable Request.

			This function allows you to assert the user Enable Request.  If Enable Request
			is asserted the drive will enable unless an overriding disable nodeStop condition or a shutdown persists.
			If a shutdown or nodestop prevents the Node from enabling, then as soon as the condition is removed by
			clearing the Nodestop(cliIMotion::NodeStopClear) or clearing the alert(cliIStatus::AlertsClear)
			the Node will immediately enable(there is no need to re-send the enable request).
		*/
		void EnableReq(bool newState) { myNode.EnableReq(newState); }
		/*
			Get the current Enable Request state.

			This function will return the state of the user Enable Request.

			The Node may not be Enabled even if this request is asserted.  A NodeStop or Shutdown Alert(cliValueAlert)
			can prevent the enable request from executing.
		*/
		bool EnableReq() { return myNode.EnableReq(); }
	};
	//																			  *
	//*****************************************************************************

	//*****************************************************************************
	// NAME																	      *
	// 	cliINodeAdv class
	/*
		Advanced Node Features Interface.

		This implements the objects required to access any advanced features
		of a node.

		Provides access to the following advanced features:
		- Attention Generation
	*/
	public ref class cliINodeAdv
	{
	private:
		INodeAdv &myNodeAdv;
		cliIAttnNode^ m_Attn;
		cliIMotionAudit^ m_MotionAudit;
	public:
		// Constructor / destructor
		cliINodeAdv::cliINodeAdv(INodeAdv &val);
		cliINodeAdv::~cliINodeAdv() { this->!cliINodeAdv(); }
		cliINodeAdv::!cliINodeAdv();

		/*
			Attention Generation Feature Setup.

			Access the node's Attention Generation feature.
		*/
		property cliIAttnNode^ Attn { cliIAttnNode^ get() { return m_Attn; } }
		/*
			Motion Audit Feature Access

			This feature can be used to monitor an axis' operational
			characteristics and monitor for changes.
		*/
		property cliIMotionAudit^ MotionAudit { cliIMotionAudit^ get() { return m_MotionAudit; } }
	};
	//																			  *
	//*****************************************************************************

	//*****************************************************************************
	// NAME																	      *
	// 	cliINodeEx class
	/*
		Expert Node Features Interface.

		This implements the objects required to access any expert features
		of a node.
	*/
	public ref class cliINodeEx
	{
	private:
		INodeEx &myNodeEx;
	public:
		// Constructor / destructor
		cliINodeEx::cliINodeEx(INodeEx &val) : myNodeEx(val) {}
		cliINodeEx::~cliINodeEx() { this->!cliINodeEx(); }
		cliINodeEx::!cliINodeEx() {}
	};
	//																			  *
	//*****************************************************************************

	//*****************************************************************************
	// NAME																	      *
	// 	cliIOuts class
	/*
		Output Register Interface.

		This class manages the access to the output registers.

		This includes:
		- The User Output Register
		- Access to the actual output register state

		Functions are provided to allow thread safe modifications to the
		User Output Register.
	*/
	public ref class cliIOuts
	{
	private:
		IOuts &myOuts;
		cliValueOutReg^ m_User;
		cliValueOutReg^ m_Out;
	public:
		// Constructor / destructor
		cliIOuts::cliIOuts(IOuts &val);
		cliIOuts::~cliIOuts() { this->!cliIOuts(); }
		cliIOuts::!cliIOuts();

		/*
			Access the User Output Register.

			Access the User Output Register object. This is used to
			change application initiated actions.

			Use the Set and Clear functions to adjust this register when
			multiple threads may be changing this register.
		*/
		property cliValueOutReg^ User { cliValueOutReg^ get() { return m_User; } }
		/*
			Access the Operational Output Register.

			This read-only reference will allow access to the current
			Operational Output Register. This register is the internal
			register that engages the features attached to it.
		*/
		property cliValueOutReg^ Out { cliValueOutReg^ get() { return m_Out; } }

		/*
			Thread safe enable request
			Param[in] newState Change the state of the Enable Request.

			This function allows you to assert the user Enable Request.  If Enable Request
			is asserted the drive will enable unless an overriding disable nodeStop condition or a shutdown persists.
			If a shutdown or nodestop prevents the Node from enabling, then as soon as the condition is removed by
			clearing the Nodestop(cliIMotion::NodeStopClear) or clearing the alert(cliIStatus::AlertsClear)
			the Node will immediately enable(there is no need to re-send the enable request).
		*/
		void EnableReq(bool newState) { myOuts.EnableReq(newState); }
		/*
			Get the current Enable Request state.

			This function will return the state of the user Enable Request.

			The Node may not be Enabled even if this request is asserted.  A NodeStop or Shutdown Alert(cliValueAlert)
			can prevent the enable request from executing.
		*/
		bool EnableReq() { return myOuts.EnableReq(); }
	};
	//																			  *
	//*****************************************************************************

	//*****************************************************************************
	// NAME																	      *
	// cliIPort class
	/*
		Serial Port Interface.

		This class defines a "super" Port whose framework exposes the Port Level features
		available for your application by a series of public attribute references.
		There are common member functions for these feature objects to determine
		if the node supports the feature.

		This class also implements:
		- References to Node object on the Port
		- Functions to restart the Port, and determine if the Port is currently Open
		- A function to issue a Port wide Nodestop to every Node on this Port
		- A function to record the command history of all communication on this Port

		See cliSysManager For the root object for interacting with
		ClearPath-SC motors.
		See cliSysManager::Ports To get references to the cliIPort objects created
		when cliSysManager::PortsOpen has successfully opened.
	**/
	public ref class cliIPort
	{
	private:
		IPort &myPort;
		cliIGrpShutdown^ m_GrpShutdown;
		cliIBrakeControl^ m_BrakeControl;
		cliIPortAdv^ m_Adv;
	public:
		// Constructor / destructor
		cliIPort::cliIPort(IPort &port);
		cliIPort::~cliIPort() { this->!cliIPort(); }
		cliIPort::!cliIPort();

		// Type definitions
		enum class openStates {
			UNKNOWN,
			CLOSED,
			FLASHING,
			PORT_UNAVAILABLE,
			OPENED_SEARCHING,
			OPENED_ONLINE
		};

		/*
			Return a reference to the indexed node on this port

			Param[in] index Get a reference for the node. This is the zero based
			index, meaning zero is the first node. The first node is the node
			closest to the host serial port in the ring.
		*/
		cliINode^ cliIPort::Nodes(int index) { return gcnew cliINode(myPort.Nodes(index)); }
		/*
			Return the count of nodes active on this port

			Return Return the count of nodes present on this port.

			Use this function to find out how many active nodes are attached to
			this port. If the port if offline, this will be zero.
		*/
		Uint16 NodeCount() { return myPort.NodeCount(); }

		/*
			Group Shutdown Feature
		*/
		property cliIGrpShutdown^ GrpShutdown { cliIGrpShutdown^ get() { return m_GrpShutdown; } }
		/*
			Brake Control Feature of SC-Hub
		*/
		property cliIBrakeControl^ BrakeControl { cliIBrakeControl^ get() { return m_BrakeControl; } }
		/*
			Access to advanced features for the port.
		*/
		property cliIPortAdv^ Adv { cliIPortAdv^ get() { return m_Adv; } }

		/*
			Restart this nodes to its powered on state and re-connect

			This causes the nodes on this port to restart and re-establish
			contact with the detected node configuration.
		*/
		void RestartCold() { myPort.RestartCold(); }
		/*
			Get port state

			Return Current port operational state.

			Use this function to ascertain the operation state of this port.

			Ports operate independently from each other. In other words, a
			failure on connections on one port should not affect another port.
		*/
		openStates OpenState() { return (openStates)myPort.OpenState(); }
		/*
			Wait for the port to go online

			Param[in] timeoutMsec Time to wait for port to return or go online

			Return True if the port came back online.

			This function is useful after restarting the network after power is lost.
		*/
		bool WaitForOnline(int timeoutMsec) { return myPort.WaitForOnline((int32_t)timeoutMsec); }
		/*
			Create command trace file.

			This function creates a file which contains a detailed transaction log
			of the all the commands	send and data received by the host. It will
			remember the last 4096 commands and/or responses.

			Teknic support staff may ask for the file created via this function
			to determine where a programming error occurred.
		*/
		void CommandTraceSave(System::String^ filePath);
		/*
			Send a high-priority Node Stop command to all the nodes
			attached to this serial port. If stopType is
			STOP_TYPE_IGNORE, the nodes will use their default stop type instead
			of the specific type.

			Param [in] stopType Will force this stop type to all nodes on this port.

			This is a fast acting command that can be used to stop all motion on a
			port. If a modifier field is set, such as E-Stop, all motion will be
			blocked until this condition is cleared.

			See cliIMotion::NodeStop For initiating node stops at a single node.
		*/
		void NodeStop(int stopType) { myPort.NodeStop(stopType); }

		Uint16 NetNumber() { return myPort.NetNumber(); }
		void NetNumber(Uint16 index) { myPort.NetNumber(index); }
	};
	//																			  *
	//*****************************************************************************

	//*****************************************************************************
	// NAME																	      *
	// 	cliIPortAdv class
	/*
		Advanced Port Features Interface.

		This implements the objects required to access any advanced features
		at the port level.  Currently, this class provides a function to trigger groups of Nodes on this Port.
	*/
	public ref class cliIPortAdv
	{
	private:
		IPortAdv &myPortAdv;
		cliIAttnPort^ m_Attn;
	public:
		// Constructor / destructor
		cliIPortAdv::cliIPortAdv(IPortAdv &val);
		cliIPortAdv::~cliIPortAdv() { this->!cliIPortAdv(); }
		cliIPortAdv::!cliIPortAdv();

		/*
			Access the Attention Handling feature object

			This object allows access to the advanced Attention Request
			feature. This feature allows for non-polled asynchronous event
			handling.
		*/
		property cliIAttnPort^ Attn { cliIAttnPort^ get() { return m_Attn; } }

		/*
			Trigger a group of nodes to initiate their moves.

			Param[in] groupNumber Group to signal on the network attached to this
			port.

			If there are no waiting moves or nodes setup at this groupNumber,
			this command will be ignored with no actions taken.

			See cliIMotionAdv for configuring/loading triggered moves
			See cliIMotionAdv::TriggerGroup to set/get a Node's trigger Group
		*/
		void TriggerMovesInGroup(uintptr_t groupNumber) {
			myPortAdv.TriggerMovesInGroup((size_t)groupNumber);
		}
	};
	//																			  *
	//*****************************************************************************

	//*****************************************************************************
	// NAME																	      *
	// 	cliISetup class
	/*
		Node Setup Features Interface.

		This class accesses and manages node setup features. These include:
		- Loading Configuration files from your application
		- Saving Configuration files
	*/
	public ref class cliISetup
	{
	private:
		ISetup &mySetup;
		cliValueDouble^ m_DelayToDisableMsecs;
		cliISetupEx^ m_Ex;
	public:
		// Constructor / destructor
		cliISetup::cliISetup(ISetup &val);
		cliISetup::~cliISetup() { this->!cliISetup(); }
		cliISetup::!cliISetup();

		/*
			Manage the delay to actual disable.

			This allows an electrical brake to engage
			prior to the actual disable. The units are milliseconds.

			See cliIBrakeControl for more information on configuring, and controlling brakes
		*/
		property cliValueDouble^ DelayToDisableMsecs {
			cliValueDouble^ get() { return m_DelayToDisableMsecs; }
		}
		/*
			Expert setup features access.
		*/
		property cliISetupEx^ Ex { cliISetupEx^ get() { return m_Ex; } }

		/*
			Load configuration File.

			Param[in] filePath Pointer to C-String file path to the file
			to load.
			Param[in] doReset Set this to true to force the node to reset
			at the end of load.

			Load the configuration file specified by filePath to
			this node.
		*/
		void ConfigLoad(System::String^ filePath, bool doReset);
		/*
			Save the node's configuration.

			Param[in] filePath Pointer to C-String file path to save the
			configuration at.

			Save the node's configuration to the filePath specified.  This would typically be performed through ClearView right after tuning each axis.
		*/
		void ConfigSave(System::String^ filePath);
		/*
			Returns true if the node is in full access mode on this network.

			Returns true if the node is in full access mode on this network.
			The only time a node may not be in full access mode is if ClearView is connected through the USB hub on the motor
			and the user has taken Full Access through the USB diagnostic port via ClearView.
		*/
		bool AccessLevelIsFull() { return mySetup.AccessLevelIsFull(); }
	};
	//																			  *
	//*****************************************************************************


	//*****************************************************************************
	// NAME																	      *
	// 	cliISetupEx class
	/*
		Expert Setup Interface.

		This class allows access to the more advanced setup options for this node. Items accessed in this class may be overridden by ClearView or
		configuration file loads.
	*/
	public ref class cliISetupEx
	{
	private:
		ISetupEx &mySetupEx;
		cliValueDouble^ m_NetWatchdogMsec;
		cliValueAppConfigReg^ m_App;
		cliValueHwConfigReg^ m_HW;
	public:
		// Constructor / destructor
		cliISetupEx::cliISetupEx(ISetupEx &val);
		cliISetupEx::~cliISetupEx() { this->!cliISetupEx(); }
		cliISetupEx::!cliISetupEx();

		/*
			Network watchdog timer.

			This allows the adjustment of a network watchdog timer that will
			force a ramped Node Stop if the host stops communicating with
			the node. This is a safety feature and should not be changed except in
			rare application specific circumstances.

			The ramp stop acceleration is setup via the E-Stop deceleration rate in ClearView.
			This is found in the details dropdown menu in ClearView.

			Set this to zero to disable. Units are milliseconds.

			This setting can be saved into a config file(cliISetup::ConfigSave) and is overwritten when a config file is loaded(cliISetup::ConfigLoad).
		*/
		property cliValueDouble^ NetWatchdogMsec { cliValueDouble^ get() { return m_NetWatchdogMsec; } }
		/*
			Access application setup register.

			This register will not be changed for nearly all applications.
			This register is configured within the motor configuration file, and will not typically change during operation.
		*/
		property cliValueAppConfigReg^ App { cliValueAppConfigReg^ get() { return m_App; } }
		/*
			Access the hardware setup register.

			This register will not be changed for nearly all applications.
			This register is configured within the motor configuration file, and will not typically change during operation.
		*/
		property cliValueHwConfigReg^ HW { cliValueHwConfigReg^ get() { return m_HW; } }
	};
	//																			  *
	//*****************************************************************************

	//*****************************************************************************
	// NAME																	      *
	// 	cliIStatus class
	/*
		Node Status Features Interface.

		This Node Level class accesses and manages the node status information.  Node Status information is divided into
		two types of registers:
		- Status Registers
		- Alert/Shutdown Registers

		Status Registers contain current information about the node's dynamic state such as whether a node: is
		in motion, has gone move done, etc. The main Realtime Status Register is maintained by the node
		and is updated each sample-time to reflect the node's state.  To reduce latency and allow the capture of
		short transient events, the Realtime Status Register feeds a series of accumulating registers.
		These registers store transitional events until they are accessed by the application program. These are:

		- The deassertions are captured by the Status Fallen Register.
		- The assertions are captured by the Status Risen & Attention Source Register. This register is the source of the autonomous Attention Packets when enabled on "Advanced" motors.
		- The Status Accumulated Register is a bitwise OR accumulation of the Realtime Status Register. This register is useful for determining if an assertion has occurred since the last access.


		The Alert Register contains information regarding a shutdown the Node may have experienced during normal operation.
		Depending on the type of alert, the application may be able to recover and/or indentify the root cause of the failure.

		Access to these registers is provided through the cliValueAlert and cliValueStatus classes.

		See cliValueAlert for more information on accessing the Node's Alert Register
		See cliValueStatus for more information on accessing the Node's Status Register
		See cliCPMStatusRegFlds for a complete list of ClearPath-SC Status Fields
		See cliCPMAlertFlds for a complete list of ClearPath-SC Alerts
	*/
	public ref class cliIStatus
	{
	private:
		IStatus &myStatus;
		cliValueStatus^ m_RT;
		cliValueStatus^ m_Rise;
		cliValueStatus^ m_Fall;
		cliValueStatus^ m_Accum;
		cliValueAlert^ m_Warnings;
		cliValueAlert^ m_Alerts;
		cliValueDouble^ m_RMSLevel;
		cliValuePowerReg^ m_Power;
		cliIStatusAdv^ m_Adv;
	public:
		// Constructor / destructor
		cliIStatus::cliIStatus(IStatus &val);
		cliIStatus::~cliIStatus() { this->!cliIStatus(); }
		cliIStatus::!cliIStatus();

		/*
			Real Time Status Register Reference.

			The Real Time Status Register reference
		*/
		property cliValueStatus^ RT { cliValueStatus^ get() { return m_RT; } }
		/*
			Status Risen Register Reference.

			The Status Risen Register reference.
		*/
		property cliValueStatus^ Rise { cliValueStatus^ get() { return m_Rise; } }
		/*
			Status Fallen Register Reference.

			The Status Fallen Register reference.
		*/
		property cliValueStatus^ Fall { cliValueStatus^ get() { return m_Fall; } }
		/*
			Status Accumulated Register Reference.

			The Status Accumulated Register reference.
		*/
		property cliValueStatus^ Accum { cliValueStatus^ get() { return m_Accum; } }
		/*
			Warnings Accumulated Register Reference.

			Update and manage Warnings Accumulated Register.
		*/
		property cliValueAlert^ Warnings { cliValueAlert^ get() { return m_Warnings; } }
		/*
			Alerts/Shutdowns Registers Reference.

			The Alerts/Shutdowns Register reference.
		*/
		property cliValueAlert^ Alerts { cliValueAlert^ get() { return m_Alerts; } }
		/*
			RMS level Reference.

			A reference to the Node's RMS Level.
		*/
		property cliValueDouble^ RMSLevel { cliValueDouble^ get() { return m_RMSLevel; } }
		/*
			RMS level Reference.

			A reference to the Node's bus and backup power status.
		*/
		property cliValuePowerReg^ Power { cliValuePowerReg^ get() { return m_Power; } }
		/*
			Advanced status information.

			Access to extra status information only available in advanced ClearPath-SC nodes.
		*/
		property cliIStatusAdv^ Adv { cliIStatusAdv^ get() { return m_Adv; } }

		/*
			Clear non-serious alerts.

			Clear all non-serious alerts and allow node to enable if an
			Enable Request is still pending.
		*/
		void AlertsClear() { myStatus.AlertsClear(); }
		/*
			If true, the node is ready for motion.
			Return True if the node is ready for motion.

			This function is used to determine the availability of the move
			generator to begin operations.
		*/
		bool IsReady() { return myStatus.IsReady(); }
		/*
			If true, the node is ready for motion.
			Return True if the node is ready for motion.

			This function is used to determine if a Torque saturation event has
			occurred since the last query.

			The Warnings register is queried when this function is called
		*/
		bool HadTorqueSaturation() { return myStatus.HadTorqueSaturation(); }
	};
	//																			  *
	//*****************************************************************************


	//*****************************************************************************
	// NAME																	      *
	// 	cliIStatusAdv class
	/*
		\brief Advanced Status Features Interface.

		This class accesses and manages the advanced node status information.
		It provides	access to:
		- Capture Registers
	*/
	public ref class cliIStatusAdv
	{
	private:
		IStatusAdv &myStatusAdv;
		cliValueSigned^ m_CapturedHiResPosn;
		cliValueSigned^ m_CapturedPos;
	public:
		// Constructor / destructor
		cliIStatusAdv::cliIStatusAdv(IStatusAdv &val);
		cliIStatusAdv::~cliIStatusAdv() { this->!cliIStatusAdv(); }
		cliIStatusAdv::!cliIStatusAdv();

		/*
			Access the last captured high resolution position value.

			This input corresponds to a change of state of the Node's input A
		*/
		property cliValueSigned^ CapturedHiResPosn {
			cliValueSigned^ get() { return m_CapturedHiResPosn; }
		}
		/*
			Return the last at sample-rate position captured.

			This input corresponds to a change of state of the Node's input A
		*/
		property cliValueSigned^ CapturedPos {
			cliValueSigned^ get() { return m_CapturedPos; }
		}
	};
	//																			  *
	//*****************************************************************************

	//*****************************************************************************
	// NAME																	      *
	// 	cliSysManager class 
	/*
		sFoundation Top Level System Object.

		This class defines the manager object whose framework implements 
		system level functions including:
		- Functions to open, close, and restart ports in the system
		- A thread safe system dwell
		- The system timestamp
		- Direct access to ports and nodes within the system

		Only one instance of this object can be used in any application.

		See cliIPort to reference port level features
		See cliINode to reference node level features
	*/
	public ref class cliSysMgr
	{
	private:
		SysManager *myMgr;
	public:
		// Constructor / destructor
		cliSysMgr::cliSysMgr();
		cliSysMgr::~cliSysMgr() { this->!cliSysMgr(); }
		cliSysMgr::!cliSysMgr();
	public:

		/*
			Supported communication rates.

			Select one of these items to match the capabilities of the serial port
			attached to your network.
		*/
		enum class _netRates {
			MN_BAUD_1X = 9600,			///< 1x Net Speed
			MN_BAUD_12X = 115200,		///< 12x Net Speed
			MN_BAUD_24X = 230400,		///< 24x Net Speed
			MN_BAUD_48X = 460800,		///< 48x Net Speed
			MN_BAUD_96X = 921600,		///< 96x Net Speed
			MN_BAUD_108X = 1036800		///< 108x Net Speed
		};

		/*
			Search for ClearPath-SC COM Hubs on this machine

			Param[out] comHubPorts This will hold a vector of strings
			which can later be passed to ComHubPort to open the given port(s).
		*/
		void FindComHubPorts(List<System::String^> ^comHubPorts);
		/*
			Simplified setup for ClearPath-SC COM Hub

			Param[in] netNumber This is the index of the port to setup. The first
			port is numbered zero. The range of the netNumbers is from 0 to 2.
			Param[in] portNumber This is Windows oriented port number. i.e.
			COM1 would set portNumber = 1.
			Param[in] portRate This is set to the desired network rate to operate
			at. If using a SC-HUB, you can specify the speed as MN_BAUD_24X, else
			you should use MN_BAUD_12X for 115200 fields/second ports typically
			found on a PC motherboard.

			This function is used to define the relationship between the system's
			serial port number and the index number(netNumber) in your system.
		*/
		void ComPortHub(uintptr_t netNumber, int portNumber, _netRates portRate) {
			myMgr->ComHubPort((size_t)netNumber, portNumber, (netRates)portRate);
		}
		void ComPortHub(uintptr_t netNumber, System::String^ portPath, _netRates portRate);

		/*
			Get a reference to port's setup

			Param[in] netNumber The index into the port table. The first port is
			numbered zero. The valid range is [0...NET_CONTROLLER_MAX-1].

			Returns the current settings for the specified port.
		*/
		portSpec &PortSetup(uintptr_t netNumber) { return myMgr->PortSetup((size_t)netNumber); }
		/*
			Open ports to start operations.

			Param[in] portCount Number of ports specified

			Call this function to start network operations after the ports have
			been specified.

			Ports should be assigned from 0 without skipping
			any.

			See cliIPort::OpenState For information about starting success.
			See cliIPort::WaitForOnline To synchronize waiting for online state.
		*/
		void PortsOpen(uintptr_t portCount);
		void PortsOpen(int portCount); 
		/*
			Close all operations down and close the ports.

			This function will close the serial ports in the system and release
			all resources related to them.

			Any references to Ports, Nodes, or ValueXXXX parameters will no longer be valid after this function is called
		*/
		void PortsClose() { myMgr->PortsClose(); }
		
		/*
			Close and re-open ports with node restarts and perform system
			initialization.

			This function will send a reset node command to restart them
			to their powered-up state. The serial ports are re-inventoried for
			nodes and the SysManager refreshed for a new startup.

			Any references to Ports, Nodes, or ValueXXXX parameters will no longer be valid after this function is called

			See cliIPort::OpenState For information about starting success.
			See cliIPort::WaitForOnline To synchronize waiting for online state.
		*/
		void RestartCold() { myMgr->RestartCold(); }
		/*
			Close and re-open ports and perform system initialization.

			This function will close and re-open the serial ports are
			re-inventoried for nodes and the SysManager refreshed for a new startup.

			Any references to Ports, Nodes, or ValueXXXX parameters will no longer be valid after this function is called

			See cliIPort::OpenState For information about starting success.
			See cliIPort::WaitForOnline To synchronize waiting for online state.
		*/
		void RestartWarm() { myMgr->RestartWarm(); }
		/*
			Get a time-stamp.

			Return High precision time-stamp

			This time-stamp will have at least millisecond resolution. For the
			Windows platform this is actually microsecond resolution.

			This time stamp correlates to the time stamp in the Command Trace(cliIPort::CommandTraceSave) file.
		*/
		double TimeStampMsec() { return myMgr->TimeStampMsec(); }
		/*
			Format a std:string with a time-stamp string.

			Updates toUpdString with a time-stamp string that correlates to
			the Command Trace(cliIPort::CommandTraceSave) feature.

			Param[in,out] toUpdString Reference to string to update
			Returns toUpdString the incoming string reference
		*/
		System::String^ TimeStampMsecStr() {
			return gcnew System::String(myMgr->TimeStampMsecStr().c_str());
		}
		/*
			Suspend thread execution.

			Param [in] msec Delay in milliseconds.

			This calls the underlying operating system's thread suspension
			function to delay execution for this thread.
		*/
		void Delay(Uint32 msec) { myMgr->Delay((uint32_t)msec); }
		/*
			Get reference to our port object.

			Param[in] index The port index used when initializing the system.

			This function is used to get a reference to the cliIPort object associated
			with serial port. This would be the same as argument used with the
			cliSysManager::ComHubPort function.

			See cliSysManager::ComHubPort For setting up a serial port,
		*/
		cliIPort^ cliSysMgr::Ports(int index) { return gcnew cliIPort(myMgr->Ports(index)); }

		/*
			Convert multi-address to an cliINode reference.

			Param[in] theMultiAddr This a system's internal node address.

			The returned node reference may exist on any defined ports.

			A cliMNErr object is thrown if the requested address does not
			exist in your system or the port currently is offline.
		*/
		cliINode^ NodeGet(multiaddr theMultiAddr);
	};

	

	

	

	

	//C++ Structs as classes

	public ref class cliAuditData
	{
	private:
		mnAuditData &myAuditData;
		double^	m_LowPassRMS;
		double^	m_LowPassMaxPos;
		double^	m_LowPassMaxNeg;
		double^	m_HighPassRMS;
		double^	m_DurationMS;
		nodelong^ m_MaxTrackingPos;
		nodelong^ m_MaxTrackingNeg;
	public:
		// Constructor / destructor
		cliAuditData::cliAuditData(mnAuditData &val);
		cliAuditData::~cliAuditData() { this->!cliAuditData(); }
		cliAuditData::!cliAuditData();

		property double^ LowPassRMS {
			double^ get() { return m_LowPassRMS; }
			void set(double^ value) { m_LowPassRMS = value; }
		}
		property double^ LowPassMaxPos {
			double^ get() { return m_LowPassMaxPos; }
			void set(double^ value) { m_LowPassMaxPos = value; }
		}
		property double^ LowPassMaxNeg {
			double^ get() { return m_LowPassMaxNeg; }
			void set(double^ value) { m_LowPassMaxNeg = value; }
		}
		property double^ HighPassRMS {
			double^ get() { return m_HighPassRMS; }
			void set(double^ value) { m_HighPassRMS = value; }
		}
		property double^ DurationMS {
			double^ get() { return m_DurationMS; }
			void set(double^ value) { m_DurationMS = value; }
		}
		property nodelong^ MaxTrackingPos {
			nodelong^ get() { return m_MaxTrackingPos; }
			void set(nodelong^ value) { m_MaxTrackingPos = value; }
		}
		property nodelong^ MaxTrackingNeg {
			nodelong^ get() { return m_MaxTrackingNeg; }
			void set(nodelong^ value) { m_MaxTrackingNeg = value; }
		}
	};

	public ref class cliMNErr : System::Exception {
	private:
		mnErr &myErr;
		multiaddr^ m_TheAddr;
		System::String^ m_ErrorMsg;
	public:
		cliMNErr::cliMNErr(mnErr &val);
		cliMNErr::~cliMNErr() { this->!cliMNErr(); }
		cliMNErr::!cliMNErr();

		property multiaddr^ TheAddr { multiaddr^ get() { return m_TheAddr; } }
		property System::String^ ErrorMsg { System::String^ get() { return m_ErrorMsg; } }

		cliCNErrCode ErrorCode() { return (cliCNErrCode)myErr.ErrorCode; }
	};

	//*****************************************************************************
	// NAME	
	//	cliShutdownInfo
	/*
		Information to setup group shutdowns at a node.

		This is the main struct for the Auto-shutdown feature.  The struct consists of three parts:
		- Whether or not the node should respond to a Group Shutdown.
		- The Node Stop type for this node.
		- The Status Register mask for this Node which will trigger a Group shutdown.

		The following lines of code show an example of how to create a Shutdown info object.

		//First we create the status mask object consisting of which status events on the node will trigger a group shutdown.
		//In this case we are using "AlertPresent", "Disabled", and "Input A"

		cliMNStatusReg myShutdownStatusMask;					//Create Status mask
		myShutdownStatusMask.cpm.AlertPresent = 1;				//Set desired fields
		myShutdownStatusMask.cpm.Disabled = 1;
		myShutdownStatusMask.cpm.InA = 1;

		// Next we create the ShutdownInfo object we will use to configure the Node with
		cliShutdownInfo myShutdownInfo;							//Create ShutdownInfo Object
		myShutdownInfo.Enabled = true;							// This sets the node to respond to Group Shutdowns
		myShutdownInfo.TheStopType = STOP_TYPE_ABRUPT;			//Use an Abrupt Nodestop type for this node in response to a group shutdown
		myShutdownInfo.StatusMask = myShutdownStatusMask;		// Configure the node to issue a group shutdown automatically based on our status mask

		//Finally we use configure the Port's first Node (Node 0) with our shutdown object
		myport.GrpShutdown.ShutdownWhen(0,myShutdownInfo);
	*/
	public ref class cliShutdownInfo {
	private:
		ShutdownInfo* myInfo;
		cliMGNodeStopReg^ m_StopType;
		cliMNStatusReg^ m_StatusMask;
	public:
		cliShutdownInfo::cliShutdownInfo();
		cliShutdownInfo::cliShutdownInfo(ShutdownInfo* info);
		cliShutdownInfo::~cliShutdownInfo() { this->!cliShutdownInfo(); }
		cliShutdownInfo::!cliShutdownInfo();

		/*
			The kind of stop to assert when this feature fires off.
		*/
		property cliMGNodeStopReg^ TheStopType { 
			cliMGNodeStopReg^ get() { return m_StopType; } 
			void set(cliMGNodeStopReg^ newType) { 
				m_StopType = newType; 
				myInfo->theStopType = *newType->Reg;
			}
		}
		/*
			Items to trigger a Group Shutdown stop when the Node's status register rises on the unmasked
			bits of the StatusMask. Set the bits to non-zero to enable the
			detection of this event.
		*/
		property cliMNStatusReg^ StatusMask { 
			cliMNStatusReg^ get() { return m_StatusMask; }
			void set(cliMNStatusReg^ newReg) { 
				m_StatusMask = newReg; 
				myInfo->statusMask = *newReg->Reg;
			}
		}
		/*
			Enables checking at this node.  If this is set to false, the node will not shutdown during a group shutdown.
		*/
		property bool Enabled {
			bool get() { return (bool)myInfo->enabled; }
			void set(bool newVal) { myInfo->enabled = (nodebool)newVal; }
		}
		/*
			Access for the underlying sFoundation type
		*/
		property ShutdownInfo* Info {
			ShutdownInfo* get() { return myInfo; }
		}
	};
}