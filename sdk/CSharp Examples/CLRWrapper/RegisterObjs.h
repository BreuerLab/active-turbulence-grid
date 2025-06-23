#pragma once

#include "pubSysCls.h"	
#include "FieldObjs.h"

using namespace sFnd;

namespace sFndCLIWrapper {
	public ref class cliAlertReg {
	private:
		alertReg* myReg;
		array<Uint32>^ m_Bits;
		cliCommonAlertFlds^ m_Common;
		cliIscAlertFlds^ m_DrvFld;
		cliCPMAlertFlds^ m_CPM;
	public:
		cliAlertReg::cliAlertReg();
		cliAlertReg::cliAlertReg(alertReg &reg);
		cliAlertReg::~cliAlertReg() { this->!cliAlertReg(); }
		cliAlertReg::!cliAlertReg();

		enum class _bitsTypes {
			LOW_ATTN,
			IN_REG,
			NON_ATTN
		};


		property cliCommonAlertFlds^ Common {
			cliCommonAlertFlds^ get() { return m_Common; }
			void set(cliCommonAlertFlds^ value) {
				m_Common = value;
				myReg->Common = value->Flds;
			}
		}
		property cliIscAlertFlds^ DrvFld {
			cliIscAlertFlds^ get() { return m_DrvFld; }
			void set(cliIscAlertFlds^ value) {
				m_DrvFld = value;
				myReg->DrvFld = *value->Flds;
			}
		}
		property cliCPMAlertFlds^ cpm {
			cliCPMAlertFlds^ get() { return m_CPM; }
			void set(cliCPMAlertFlds^ value) {
				m_CPM = value;
				myReg->cpm = value->Flds;
			}
		}

		System::String^ StateStr();
		void clear() { myReg->clear(); }
		bool isClear() { return myReg->isClear(); }
		bool isInAlert() { return myReg->isInAlert(); }
	};

	//*****************************************************************************
	// NAME                                                                       *
	//  cliMGNodeStopReg
	//
	// DESCRIPTION
	/*
	Universal Node Stop Action Register Definition

	This container type is used to describe the actions taken when a node
	stop is issued. The node stop system can affect multiple features within
	the node.

	The following items are affected by issuing a node stop.
	- Motion
	- Output or Drive Enable States
	- Status

	The motion portion of the node stop specified by the Style field
	specifies the action to be taken by the move generator. These include:
	- Immediate cancellation of the motion and any queued motion
	- Ramp the current velocity to zero at a pre-specified deceleration rate
	and cancel queued motion
	- Not to perform any action at all

	The EStop field controls what happens with subsequent motion requests. If
	non-zero, all motion requests will be rejected. This field is also referred
	to as the MotionLock field and the terms are interchangeable.

	For nodes that have a General Purpose Output feature, the
	Controlled field defines the action taken by the outputs. For
	ClearPath-SC this does nothing.

	The Disable field controls the node's servo state at the end of
	motion. If non-zero, the motor will disable and enter the dynamic brake
	mode.

	The Quiet field controls the posting of the Node Stop event to the
	status register.

	The EStop, Controlled and Disable states latch upon execution
	block their respective features from operating in the normal fashion.
	EStop in particular is a safety feature to prevent inadvertent motion
	to occur in your application until the originating reason has been cleared.

	To restore operations each of these features can be cleared by setting
	the Clear field to non-zero and setting the respective other field to
	non-zero and issuing a node stop. The STOP_TYPE_CLR_ALL enumeration
	provides a convenient way to clear all blocking actions.

	The commonly used node stops are available as enumerated constants
	defined in the cliNodeStopCodes enumeration.
	*/
	public ref class cliMGNodeStopReg {
	private:
		mgNodeStopReg* myReg;
		cliCPMNodeStopFlds^ m_CPM;
		cliISCNodeStopFlds^ m_ISC;
		cliNodeStopCodes m_Bits;
		cliNodeStopFlds^ m_Fld;
	public:
		cliMGNodeStopReg::cliMGNodeStopReg();
		cliMGNodeStopReg::cliMGNodeStopReg(mgNodeStopReg &myReg);
		cliMGNodeStopReg::~cliMGNodeStopReg() { this->!cliMGNodeStopReg(); }
		cliMGNodeStopReg::!cliMGNodeStopReg();

		/*
		Universal field view of the stop types.
		*/
		property cliNodeStopFlds^ Fld {
			cliNodeStopFlds^ get() { return m_Fld; }
			void set(cliNodeStopFlds^ newFld) {
				m_Fld = newFld;
				myReg->fld = newFld->Flds;
			}
		}
		/*
		ClearPath-SC field view of the stop types.
		*/
		property cliCPMNodeStopFlds^ CPM {
			cliCPMNodeStopFlds^ get() { return m_CPM; }
			void set(cliCPMNodeStopFlds^ newFld) {
				m_CPM = newFld;
				myReg->cpm = newFld->Flds;
			}
		}
		/*
		Meridian ISC field view of the stop types.
		*/
		property cliISCNodeStopFlds^ ISC {
			cliISCNodeStopFlds^ get() { return m_ISC; }
			void set(cliISCNodeStopFlds^ newFld) {
				m_ISC = newFld;
				myReg->isc = newFld->Flds;
			}
		}
		/*
		Bit-wide access to the Node Stop information.
		*/
		property cliNodeStopCodes Bits {
			cliNodeStopCodes get() { return m_Bits; }
			void set(cliNodeStopCodes newBits) {
				m_Bits = newBits;
				myReg->bits = (nodeStopCodes)newBits;
			}
		}
		/*
		Access for the underlying sFoundation type
		*/
		property mgNodeStopReg* Reg {
			mgNodeStopReg* get() { return myReg; }
		}
	};

	public ref class cliMNStatusReg {
	private:
		mnStatusReg* myReg;
		array<Uint16>^ m_Bits;
		Uint32^ m_AttnBits;
		cliCommonStatusFlds^ m_Common;
		cliIscStatusRegFlds^ m_Isc;
		cliCPMStatusRegFlds^ m_CPM;
	public:
		cliMNStatusReg::cliMNStatusReg();
		cliMNStatusReg::cliMNStatusReg(mnStatusReg &reg);
		cliMNStatusReg::~cliMNStatusReg() { this->!cliMNStatusReg(); }
		cliMNStatusReg::!cliMNStatusReg();
	public:
		enum class _bitsTypes {
			LOW_ATTN,
			IN_REG,
			NON_ATTN
		};

		property cliCommonStatusFlds^ Common {
			cliCommonStatusFlds^ get() { return m_Common; }
			void set(cliCommonStatusFlds^ value) {
				m_Common = value;
				myReg->Common = value->Flds;
			}
		}
		property cliIscStatusRegFlds^ isc {
			cliIscStatusRegFlds^ get() { return m_Isc; }
			void set(cliIscStatusRegFlds^ value) {
				m_Isc = value;
				myReg->isc = value->Flds;
			}
		}
		property cliCPMStatusRegFlds^ cpm {
			cliCPMStatusRegFlds^ get() { return m_CPM; }
			void set(cliCPMStatusRegFlds^ value) {
				m_CPM = value;
				myReg->cpm = value->Flds;
			}
		}
		/*
		Access for the underlying sFoundation type
		*/
		property mnStatusReg* Reg {
			mnStatusReg* get() { return myReg; }
		}

		void clear() { myReg->clear(); }
		bool isClear() { return myReg->isClear(); }
	};

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	// Attention Request/Status Register
	// 
	// NOTE: arrays of this items will involve 32-bit spacings
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	/*
		Attention Request Register and Source Container.

		This register is the representation of an Attention Packet.

		An AttentionReg.lBits equal to zero occurs when the function
		did not successfully get an attention.
	*/
	public ref class cliMNAttnReqReg {
	private:
		mnAttnReqReg* myReg;
	public:
		cliMNAttnReqReg::cliMNAttnReqReg() : myReg(new mnAttnReqReg()) {}
		cliMNAttnReqReg::cliMNAttnReqReg(mnAttnReqReg &reg) : myReg(new mnAttnReqReg(reg)) {}
		cliMNAttnReqReg::~cliMNAttnReqReg() { this->!cliMNAttnReqReg(); }
		cliMNAttnReqReg::!cliMNAttnReqReg();

		
		property Uint16 Multiaddr {
			Uint16 get() { return myReg->MultiAddr; }
			void set(Uint16 newVal) {
				
				myReg->MultiAddr = newVal;
			}
		}

		property cliMNStatusReg^ AttentionReg {
			cliMNStatusReg^ get() { return gcnew cliMNStatusReg(myReg->AttentionReg); }
			void set(cliMNStatusReg^ newVal) {
				myReg->AttentionReg = *newVal->Reg;
			}
		}
	};
}