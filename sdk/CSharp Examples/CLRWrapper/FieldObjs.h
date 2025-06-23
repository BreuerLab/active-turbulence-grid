#pragma once

#include "pubSysCls.h"	
#include "Enums.h"

using namespace sFnd;

namespace sFndCLIWrapper {
	public ref class cliCommonAlertFlds {
	private:
		commonAlertFlds &myFlds;
	public:
		cliCommonAlertFlds::cliCommonAlertFlds(commonAlertFlds &flds) : myFlds(flds) {};
		cliCommonAlertFlds::~cliCommonAlertFlds() { this->!cliCommonAlertFlds(); };
		cliCommonAlertFlds::!cliCommonAlertFlds() {};

		property UINT FwSelfTest {
			UINT get() { return myFlds.FwSelfTest; }
			void set(UINT newVal) { myFlds.FwSelfTest = newVal; }
		}
		property UINT FwNetBufferOverrun {
			UINT get() { return myFlds.FwNetBufferOverrun; }
			void set(UINT newVal) { myFlds.FwNetBufferOverrun = newVal; }
		}
		property UINT FwError0 {
			UINT get() { return myFlds.FwError0; }
			void set(UINT newVal) { myFlds.FwError0 = newVal; }
		}
		property UINT FwError1 {
			UINT get() { return myFlds.FwError1; }
			void set(UINT newVal) { myFlds.FwError1 = newVal; }
		}
		property UINT FwStackOverrun {
			UINT get() { return myFlds.FwStackOverrun; }
			void set(UINT newVal) { myFlds.FwStackOverrun = newVal; }
		}
		property UINT FwWatchdogRestarted {
			UINT get() { return myFlds.FwWatchdogRestarted; }
			void set(UINT newVal) { myFlds.FwWatchdogRestarted = newVal; }
		}
		property UINT FwInvalidConfiguration {
			UINT get() { return myFlds.FwInvalidConfiguration; }
			void set(UINT newVal) { myFlds.FwInvalidConfiguration = newVal; }
		}
		property UINT na7_10 {
			UINT get() { return myFlds.na7_10; }
			void set(UINT newVal) { myFlds.na7_10 = newVal; }
		}
		property UINT HwPowerProblem {
			UINT get() { return myFlds.HwPowerProblem; }
			void set(UINT newVal) { myFlds.HwPowerProblem = newVal; }
		}
		property UINT HwClockProblem {
			UINT get() { return myFlds.HwClockProblem; }
			void set(UINT newVal) { myFlds.HwClockProblem = newVal; }
		}
		property UINT HwEEPROMdead {
			UINT get() { return myFlds.HwEEPROMdead; }
			void set(UINT newVal) { myFlds.HwEEPROMdead = newVal; }
		}
		property UINT HwFlashCorrupt {
			UINT get() { return myFlds.HwFlashCorrupt; }
			void set(UINT newVal) { myFlds.HwFlashCorrupt = newVal; }
		}
		property UINT HwFlashChanged {
			UINT get() { return myFlds.HwFlashChanged; }
			void set(UINT newVal) { myFlds.HwFlashChanged = newVal; }
		}
		property UINT HwRAM {
			UINT get() { return myFlds.HwRAM; }
			void set(UINT newVal) { myFlds.HwRAM = newVal; }
		}
		property UINT HwADC {
			UINT get() { return myFlds.HwADC; }
			void set(UINT newVal) { myFlds.HwADC = newVal; }
		}
		property UINT HwADCsat {
			UINT get() { return myFlds.HwADCsat; }
			void set(UINT newVal) { myFlds.HwADCsat = newVal; }
		}
		property UINT na19_23 {
			UINT get() { return myFlds.na19_23; }
			void set(UINT newVal) { myFlds.na19_23 = newVal; }
		}
		property UINT NetVoltageLow {
			UINT get() { return myFlds.NetVoltageLow; }
			void set(UINT newVal) { myFlds.NetVoltageLow = newVal; }
		}
		property UINT NetWatchdog {
			UINT get() { return myFlds.NetWatchdog; }
			void set(UINT newVal) { myFlds.NetWatchdog = newVal; }
		}
		property UINT na26_27 {
			UINT get() { return myFlds.na26_27; }
			void set(UINT newVal) { myFlds.na26_27 = newVal; }
		}
		property UINT EStopped {
			UINT get() { return myFlds.EStopped; }
			void set(UINT newVal) { myFlds.EStopped = newVal; }
		}
		property UINT ConfigOutOfDate {
			UINT get() { return myFlds.ConfigOutOfDate; }
			void set(UINT newVal) { myFlds.ConfigOutOfDate = newVal; }
		}
		property UINT RunTimeErr {
			UINT get() { return myFlds.RunTimeErr; }
			void set(UINT newVal) { myFlds.RunTimeErr = newVal; }
		}
		property UINT na31 {
			UINT get() { return myFlds.na31; }
			void set(UINT newVal) { myFlds.na31 = newVal; }
		}
		/*
		Access for the underlying sFoundation type
		*/
		property commonAlertFlds Flds {
			commonAlertFlds get() { return myFlds; }
		}
	};

	public ref class cliCPMAlertFlds {
	private:
		cpmAlertFlds &myFlds;
		cliCommonAlertFlds^ m_Common;
	public:
		cliCPMAlertFlds::cliCPMAlertFlds(cpmAlertFlds &flds);
		cliCPMAlertFlds::~cliCPMAlertFlds() { this->!cliCPMAlertFlds(); }
		cliCPMAlertFlds::!cliCPMAlertFlds();

		property cliCommonAlertFlds^ Common { cliCommonAlertFlds^ get() { return m_Common; } }

		System::String^ StateStr(System::String^ buffer, uintptr_t size) {
			char charBuf[256];
			return (gcnew System::String(myFlds.StateStr(charBuf, sizeof(charBuf))));
		}

		property UINT JrkLimRequestBad {
			UINT get() { return myFlds.JrkLimRequestBad; }
			void set(UINT newVal) { myFlds.JrkLimRequestBad = newVal; }
		}
		property UINT MoveBufUnderrun {
			UINT get() { return myFlds.MoveBufUnderrun; }
			void set(UINT newVal) { myFlds.MoveBufUnderrun = newVal; }
		}
		property UINT JrkLimVelRequestBad {
			UINT get() { return myFlds.JrkLimVelRequestBad; }
			void set(UINT newVal) { myFlds.JrkLimVelRequestBad = newVal; }
		}
		property UINT MoveSpecAltered {
			UINT get() { return myFlds.MoveSpecAltered; }
			void set(UINT newVal) { myFlds.MoveSpecAltered = newVal; }
		}
		property UINT PhaseSensorFailed {
			UINT get() { return myFlds.PhaseSensorFailed; }
			void set(UINT newVal) { myFlds.PhaseSensorFailed = newVal; }
		}
		property UINT LimSwitchActivated {
			UINT get() { return myFlds.LimSwitchActivated; }
			void set(UINT newVal) { myFlds.LimSwitchActivated = newVal; }
		}
		property UINT SoftLimitExceeded {
			UINT get() { return myFlds.SoftLimitExceeded; }
			void set(UINT newVal) { myFlds.SoftLimitExceeded = newVal; }
		}
		property UINT ACPowerLost {
			UINT get() { return myFlds.ACPowerLost; }
			void set(UINT newVal) { myFlds.ACPowerLost = newVal; }
		}
		property UINT ACPhaseLost {
			UINT get() { return myFlds.ACPhaseLost; }
			void set(UINT newVal) { myFlds.ACPhaseLost = newVal; }
		}
		property UINT MtrTempLow {
			UINT get() { return myFlds.MtrTempLow; }
			void set(UINT newVal) { myFlds.MtrTempLow = newVal; }
		}
		property UINT MtrVectorBad {
			UINT get() { return myFlds.MtrVectorBad; }
			void set(UINT newVal) { myFlds.MtrVectorBad = newVal; }
		}
		property UINT MtrEncGlitch {
			UINT get() { return myFlds.MtrEncGlitch; }
			void set(UINT newVal) { myFlds.MtrEncGlitch = newVal; }
		}
		property UINT MtrEncOverspeed {
			UINT get() { return myFlds.MtrEncOverspeed; }
			void set(UINT newVal) { myFlds.MtrEncOverspeed = newVal; }
		}
		property UINT MtrPhaseOverload {
			UINT get() { return myFlds.MtrPhaseOverload; }
			void set(UINT newVal) { myFlds.MtrPhaseOverload = newVal; }
		}
		property UINT MtrBadSetupParams {
			UINT get() { return myFlds.MtrBadSetupParams; }
			void set(UINT newVal) { myFlds.MtrBadSetupParams = newVal; }
		}
		property UINT HardStopBrokeFree {
			UINT get() { return myFlds.HardStopBrokeFree; }
			void set(UINT newVal) { myFlds.HardStopBrokeFree = newVal; }
		}
		property UINT TrackingShutdown {
			UINT get() { return myFlds.TrackingShutdown; }
			void set(UINT newVal) { myFlds.TrackingShutdown = newVal; }
		}
		property UINT RMSOverload {
			UINT get() { return myFlds.RMSOverload; }
			void set(UINT newVal) { myFlds.RMSOverload = newVal; }
		}
		property UINT RMSOverloadShutdown {
			UINT get() { return myFlds.RMSOverloadShutdown; }
			void set(UINT newVal) { myFlds.RMSOverloadShutdown = newVal; }
		}
		property UINT BusVoltSat {
			UINT get() { return myFlds.BusVoltSat; }
			void set(UINT newVal) { myFlds.BusVoltSat = newVal; }
		}
		property UINT TrqSat {
			UINT get() { return myFlds.TrqSat; }
			void set(UINT newVal) { myFlds.TrqSat = newVal; }
		}
		property UINT NoCommSweepFailed {
			UINT get() { return myFlds.NoCommSweepFailed; }
			void set(UINT newVal) { myFlds.NoCommSweepFailed = newVal; }
		}
		property UINT NoCommSweepReversed {
			UINT get() { return myFlds.NoCommSweepReversed; }
			void set(UINT newVal) { myFlds.NoCommSweepReversed = newVal; }
		}
		property UINT NoCommFailed {
			UINT get() { return myFlds.NoCommFailed; }
			void set(UINT newVal) { myFlds.NoCommFailed = newVal; }
		}
		property UINT IndexCountZeroWarn {
			UINT get() { return myFlds.IndexCountZeroWarn; }
			void set(UINT newVal) { myFlds.IndexCountZeroWarn = newVal; }
		}
		property UINT DriveTempHigh {
			UINT get() { return myFlds.DriveTempHigh; }
			void set(UINT newVal) { myFlds.DriveTempHigh = newVal; }
		}
		property UINT StatorTempHigh {
			UINT get() { return myFlds.StatorTempHigh; }
			void set(UINT newVal) { myFlds.StatorTempHigh = newVal; }
		}
		property UINT BusOverCurrent {
			UINT get() { return myFlds.BusOverCurrent; }
			void set(UINT newVal) { myFlds.BusOverCurrent = newVal; }
		}
		property UINT BusOverVoltage {
			UINT get() { return myFlds.BusOverVoltage; }
			void set(UINT newVal) { myFlds.BusOverVoltage = newVal; }
		}
		property UINT BusVoltageLow {
			UINT get() { return myFlds.BusVoltageLow; }
			void set(UINT newVal) { myFlds.BusVoltageLow = newVal; }
		}
		property UINT BusRMSOverload {
			UINT get() { return myFlds.BusRMSOverload; }
			void set(UINT newVal) { myFlds.BusRMSOverload = newVal; }
		}
		property UINT MtrEncIndexMissing {
			UINT get() { return myFlds.MtrEncIndexMissing; }
			void set(UINT newVal) { myFlds.MtrEncIndexMissing = newVal; }
		}
		property UINT BusVoltageUnderOperatingV {
			UINT get() { return myFlds.BusVoltageUnderOperatingV; }
			void set(UINT newVal) { myFlds.BusVoltageUnderOperatingV = newVal; }
		}
		property UINT MtrEncIndexMisplaced {
			UINT get() { return myFlds.MtrEncIndexMisplaced; }
			void set(UINT newVal) { myFlds.MtrEncIndexMisplaced = newVal; }
		}
		property UINT StepsDuringPosnRecovery {
			UINT get() { return myFlds.StepsDuringPosnRecovery; }
			void set(UINT newVal) { myFlds.StepsDuringPosnRecovery = newVal; }
		}
		/*
		Access for the underlying sFoundation type
		*/
		property cpmAlertFlds Flds {
			cpmAlertFlds get() { return myFlds; }
		}
	};

	public ref class cliIscAlertFlds {
	private:
		iscAlertFlds* myFlds;
		cliCommonAlertFlds^ m_Common;
	public:
		cliIscAlertFlds::cliIscAlertFlds(iscAlertFlds &flds);
		cliIscAlertFlds::~cliIscAlertFlds() { this->!cliIscAlertFlds(); }
		cliIscAlertFlds::!cliIscAlertFlds();
	public:

		property cliCommonAlertFlds^ Common { cliCommonAlertFlds^ get() { return m_Common; } }

		property UINT FwBadDataAcqState {
			UINT get() { return myFlds->FwBadDataAcqState; }
			void set(UINT newVal) { myFlds->FwBadDataAcqState = newVal; }
		}
		property UINT FwMoveGenMisc {
			UINT get() { return myFlds->FwMoveGenMisc; }
			void set(UINT newVal) { myFlds->FwMoveGenMisc = newVal; }
		}
		property UINT FwMoveGenOffTarget {
			UINT get() { return myFlds->FwMoveGenOffTarget; }
			void set(UINT newVal) { myFlds->FwMoveGenOffTarget = newVal; }
		}
		property UINT FwMoveGenRange {
			UINT get() { return myFlds->FwMoveGenRange; }
			void set(UINT newVal) { myFlds->FwMoveGenRange = newVal; }
		}
		property UINT FwBadRASrequest {
			UINT get() { return myFlds->FwBadRASrequest; }
			void set(UINT newVal) { myFlds->FwBadRASrequest = newVal; }
		}
		property UINT FwMoveBufUnderrun {
			UINT get() { return myFlds->FwMoveBufUnderrun; }
			void set(UINT newVal) { myFlds->FwMoveBufUnderrun = newVal; }
		}
		property UINT FwBadRASVelrequest {
			UINT get() { return myFlds->FwBadRASVelrequest; }
			void set(UINT newVal) { myFlds->FwBadRASVelrequest = newVal; }
		}
		property UINT FwMoveSpecAltered {
			UINT get() { return myFlds->FwMoveSpecAltered; }
			void set(UINT newVal) { myFlds->FwMoveSpecAltered = newVal; }
		}
		property UINT HwPhaseSensor {
			UINT get() { return myFlds->HwPhaseSensor; }
			void set(UINT newVal) { myFlds->HwPhaseSensor = newVal; }
		}
		property UINT FwMoveGenHwLim {
			UINT get() { return myFlds->FwMoveGenHwLim; }
			void set(UINT newVal) { myFlds->FwMoveGenHwLim = newVal; }
		}
		property UINT FwMoveGenSwLim {
			UINT get() { return myFlds->FwMoveGenSwLim; }
			void set(UINT newVal) { myFlds->FwMoveGenSwLim = newVal; }
		}
		property UINT FwMoveBufOverrunLockdown {
			UINT get() { return myFlds->FwMoveBufOverrunLockdown; }
			void set(UINT newVal) { myFlds->FwMoveBufOverrunLockdown = newVal; }
		}
		property UINT Io5VSupplyOverload {
			UINT get() { return myFlds->Io5VSupplyOverload; }
			void set(UINT newVal) { myFlds->Io5VSupplyOverload = newVal; }
		}
		property UINT IoBrakeOverload {
			UINT get() { return myFlds->IoBrakeOverload; }
			void set(UINT newVal) { myFlds->IoBrakeOverload = newVal; }
		}
		property UINT IoGPO0overload {
			UINT get() { return myFlds->IoGPO0overload; }
			void set(UINT newVal) { myFlds->IoGPO0overload = newVal; }
		}
		property UINT IoGPO1overload {
			UINT get() { return myFlds->IoGPO1overload; }
			void set(UINT newVal) { myFlds->IoGPO1overload = newVal; }
		}
		property UINT IoGPOdetector {
			UINT get() { return myFlds->IoGPOdetector; }
			void set(UINT newVal) { myFlds->IoGPOdetector = newVal; }
		}
		property UINT IoGPOoverload {
			UINT get() { return myFlds->IoGPOoverload; }
			void set(UINT newVal) { myFlds->IoGPOoverload = newVal; }
		}
		property UINT IoInvalidInputs {
			UINT get() { return myFlds->IoInvalidInputs; }
			void set(UINT newVal) { myFlds->IoInvalidInputs = newVal; }
		}
		property UINT IoInvalidInputsLkdn {
			UINT get() { return myFlds->IoInvalidInputsLkdn; }
			void set(UINT newVal) { myFlds->IoInvalidInputsLkdn = newVal; }
		}
		property UINT ACPowerLost {
			UINT get() { return myFlds->ACPowerLost; }
			void set(UINT newVal) { myFlds->ACPowerLost = newVal; }
		}
		property UINT IEXlinkGlitch {
			UINT get() { return myFlds->IEXlinkGlitch; }
			void set(UINT newVal) { myFlds->IEXlinkGlitch = newVal; }
		}
		property UINT IEXlinkMultiGlitch {
			UINT get() { return myFlds->IEXlinkMultiGlitch; }
			void set(UINT newVal) { myFlds->IEXlinkMultiGlitch = newVal; }
		}
		property UINT na55 {
			UINT get() { return myFlds->na55; }
			void set(UINT newVal) { myFlds->na55 = newVal; }
		}
		property UINT MtrCommBadSeq {
			UINT get() { return myFlds->MtrCommBadSeq; }
			void set(UINT newVal) { myFlds->MtrCommBadSeq = newVal; }
		}
		property UINT MtrCommBadState {
			UINT get() { return myFlds->MtrCommBadState; }
			void set(UINT newVal) { myFlds->MtrCommBadState = newVal; }
		}
		property UINT MtrVector {
			UINT get() { return myFlds->MtrVector; }
			void set(UINT newVal) { myFlds->MtrVector = newVal; }
		}
		property UINT MtrVectorCrit {
			UINT get() { return myFlds->MtrVectorCrit; }
			void set(UINT newVal) { myFlds->MtrVectorCrit = newVal; }
		}
		property UINT MtrEncGlitch {
			UINT get() { return myFlds->MtrEncGlitch; }
			void set(UINT newVal) { myFlds->MtrEncGlitch = newVal; }
		}
		property UINT MtrEncOverspeed {
			UINT get() { return myFlds->MtrEncOverspeed; }
			void set(UINT newVal) { myFlds->MtrEncOverspeed = newVal; }
		}
		property UINT LdEncGlitch {
			UINT get() { return myFlds->LdEncGlitch; }
			void set(UINT newVal) { myFlds->LdEncGlitch = newVal; }
		}
		property UINT LdEncOverspeed {
			UINT get() { return myFlds->LdEncOverspeed; }
			void set(UINT newVal) { myFlds->LdEncOverspeed = newVal; }
		}
		property UINT MtrPhaseOverload {
			UINT get() { return myFlds->MtrPhaseOverload; }
			void set(UINT newVal) { myFlds->MtrPhaseOverload = newVal; }
		}
		property UINT MtrThermalOverload {
			UINT get() { return myFlds->MtrThermalOverload; }
			void set(UINT newVal) { myFlds->MtrThermalOverload = newVal; }
		}
		property UINT MtrBadSetupParams {
			UINT get() { return myFlds->MtrBadSetupParams; }
			void set(UINT newVal) { myFlds->MtrBadSetupParams = newVal; }
		}
		property UINT SvoHardStopRelease {
			UINT get() { return myFlds->SvoHardStopRelease; }
			void set(UINT newVal) { myFlds->SvoHardStopRelease = newVal; }
		}
		property UINT SvoTracking {
			UINT get() { return myFlds->SvoTracking; }
			void set(UINT newVal) { myFlds->SvoTracking = newVal; }
		}
		property UINT SvoTrackingCrit {
			UINT get() { return myFlds->SvoTrackingCrit; }
			void set(UINT newVal) { myFlds->SvoTrackingCrit = newVal; }
		}
		property UINT SvoRMSoverload {
			UINT get() { return myFlds->SvoRMSoverload; }
			void set(UINT newVal) { myFlds->SvoRMSoverload = newVal; }
		}
		property UINT SvoRMScritOverload {
			UINT get() { return myFlds->SvoRMScritOverload; }
			void set(UINT newVal) { myFlds->SvoRMScritOverload = newVal; }
		}
		property UINT SvoCoupling {
			UINT get() { return myFlds->SvoCoupling; }
			void set(UINT newVal) { myFlds->SvoCoupling = newVal; }
		}
		property UINT SvoStepNoise {
			UINT get() { return myFlds->SvoStepNoise; }
			void set(UINT newVal) { myFlds->SvoStepNoise = newVal; }
		}
		property UINT SvoVoltSat {
			UINT get() { return myFlds->SvoVoltSat; }
			void set(UINT newVal) { myFlds->SvoVoltSat = newVal; }
		}
		property UINT SvoTrqSat {
			UINT get() { return myFlds->SvoTrqSat; }
			void set(UINT newVal) { myFlds->SvoTrqSat = newVal; }
		}
		property UINT NoCommSweepFailed {
			UINT get() { return myFlds->NoCommSweepFailed; }
			void set(UINT newVal) { myFlds->NoCommSweepFailed = newVal; }
		}
		property UINT NoCommSweepReversed {
			UINT get() { return myFlds->NoCommSweepReversed; }
			void set(UINT newVal) { myFlds->NoCommSweepReversed = newVal; }
		}
		property UINT NoCommFailed {
			UINT get() { return myFlds->NoCommFailed; }
			void set(UINT newVal) { myFlds->NoCommFailed = newVal; }
		}
		property UINT IndexCountZeroWarn {
			UINT get() { return myFlds->IndexCountZeroWarn; }
			void set(UINT newVal) { myFlds->IndexCountZeroWarn = newVal; }
		}
		property UINT TempAmbient {
			UINT get() { return myFlds->TempAmbient; }
			void set(UINT newVal) { myFlds->TempAmbient = newVal; }
		}
		property UINT TempHeatsink {
			UINT get() { return myFlds->TempHeatsink; }
			void set(UINT newVal) { myFlds->TempHeatsink = newVal; }
		}
		property UINT BusOverCurrent {
			UINT get() { return myFlds->BusOverCurrent; }
			void set(UINT newVal) { myFlds->BusOverCurrent = newVal; }
		}
		property UINT BusOverVoltage {
			UINT get() { return myFlds->BusOverVoltage; }
			void set(UINT newVal) { myFlds->BusOverVoltage = newVal; }
		}
		property UINT BusVoltageLow {
			UINT get() { return myFlds->BusVoltageLow; }
			void set(UINT newVal) { myFlds->BusVoltageLow = newVal; }
		}
		property UINT BusRMSoverload {
			UINT get() { return myFlds->BusRMSoverload; }
			void set(UINT newVal) { myFlds->BusRMSoverload = newVal; }
		}
		property UINT FanSpeedLow {
			UINT get() { return myFlds->FanSpeedLow; }
			void set(UINT newVal) { myFlds->FanSpeedLow = newVal; }
		}
		property UINT MtrEncIndexMissing {
			UINT get() { return myFlds->MtrEncIndexMissing; }
			void set(UINT newVal) { myFlds->MtrEncIndexMissing = newVal; }
		}
		property UINT NoCommHwErr {
			UINT get() { return myFlds->NoCommHwErr; }
			void set(UINT newVal) { myFlds->NoCommHwErr = newVal; }
		}
		property UINT NoCommBusLow {
			UINT get() { return myFlds->NoCommBusLow; }
			void set(UINT newVal) { myFlds->NoCommBusLow = newVal; }
		}
		property UINT NoCommSetupErr {
			UINT get() { return myFlds->NoCommSetupErr; }
			void set(UINT newVal) { myFlds->NoCommSetupErr = newVal; }
		}
		property UINT HomeLimLockdown {
			UINT get() { return myFlds->HomeLimLockdown; }
			void set(UINT newVal) { myFlds->HomeLimLockdown = newVal; }
		}
		property UINT TravelLimLockdown {
			UINT get() { return myFlds->TravelLimLockdown; }
			void set(UINT newVal) { myFlds->TravelLimLockdown = newVal; }
		}
		property UINT MtrEncIndexMisplaced {
			UINT get() { return myFlds->MtrEncIndexMisplaced; }
			void set(UINT newVal) { myFlds->MtrEncIndexMisplaced = newVal; }
		}
		/*
		Access for the underlying sFoundation type
		*/
		property iscAlertFlds* Flds {
			iscAlertFlds* get() { return myFlds; }
		}
	};

	public ref class cliCPMStatusRegFlds {
	private:
		cpmStatusRegFlds &myFlds;
	public:
		cliCPMStatusRegFlds::cliCPMStatusRegFlds(cpmStatusRegFlds &flds) : myFlds(flds) {};
		cliCPMStatusRegFlds::~cliCPMStatusRegFlds() { this->!cliCPMStatusRegFlds(); };
		cliCPMStatusRegFlds::!cliCPMStatusRegFlds() {};

		enum class _velStates {
			VEL_STOPPED,
			VEL_POSITIVE,
			VEL_NEGATIVE,
			VEL_BOTH
		};
		enum class _shutdownStates {
			SHDN_STATE_IDLE = 0,
			SHDN_STATE_DELAY = 1,
			SHDN_STATE_RAMP = 2,
			SHDN_STATE_STOPPED = 3
		};

		property Uint16 Warning {
			Uint16 get() { return myFlds.Warning; }
			void set(Uint16 newVal) { myFlds.Warning = newVal; }
		}
		property Uint16 UserAlert {
			Uint16 get() { return myFlds.UserAlert; }
			void set(Uint16 newVal) { myFlds.UserAlert = newVal; }
		}
		property Uint16 NotReady {
			Uint16 get() { return myFlds.NotReady; }
			void set(Uint16 newVal) { myFlds.NotReady = newVal; }
		}
		property Uint16 MoveBufAvail {
			Uint16 get() { return myFlds.MoveBufAvail; }
			void set(Uint16 newVal) { myFlds.MoveBufAvail = newVal; }
		}
		property Uint16 Ready {
			Uint16 get() { return myFlds.Ready; }
			void set(Uint16 newVal) { myFlds.Ready = newVal; }
		}
		property Uint16 PowerEvent {
			Uint16 get() { return myFlds.PowerEvent; }
			void set(Uint16 newVal) { myFlds.PowerEvent = newVal; }
		}
		property Uint16 AlertPresent {
			Uint16 get() { return myFlds.AlertPresent; }
			void set(Uint16 newVal) { myFlds.AlertPresent = newVal; }
		}
		property Uint16 InPosLimit {
			Uint16 get() { return myFlds.InPosLimit; }
			void set(Uint16 newVal) { myFlds.InPosLimit = newVal; }
		}
		property Uint16 InNegLimit {
			Uint16 get() { return myFlds.InNegLimit; }
			void set(Uint16 newVal) { myFlds.InNegLimit = newVal; }
		}
		property Uint16 MotionBlocked {
			Uint16 get() { return myFlds.MotionBlocked; }
			void set(Uint16 newVal) { myFlds.MotionBlocked = newVal; }
		}
		property Uint16 WasHomed {
			Uint16 get() { return myFlds.WasHomed; }
			void set(Uint16 newVal) { myFlds.WasHomed = newVal; }
		}
		property Uint16 Homing {
			Uint16 get() { return myFlds.Homing; }
			void set(Uint16 newVal) { myFlds.Homing = newVal; }
		}
		property Uint16 GoingDisabled {
			Uint16 get() { return myFlds.GoingDisabled; }
			void set(Uint16 newVal) { myFlds.GoingDisabled = newVal; }
		}
		property Uint16 StatusEvent {
			Uint16 get() { return myFlds.StatusEvent; }
			void set(Uint16 newVal) { myFlds.StatusEvent = newVal; }
		}
		property Uint16 Enabled {
			Uint16 get() { return myFlds.Enabled; }
			void set(Uint16 newVal) { myFlds.Enabled = newVal; }
		}
		property Uint16 MoveCanceled {
			Uint16 get() { return myFlds.MoveCanceled; }
			void set(Uint16 newVal) { myFlds.MoveCanceled = newVal; }
		}
		property Uint16 MoveDone {
			Uint16 get() { return myFlds.MoveDone; }
			void set(Uint16 newVal) { myFlds.MoveDone = newVal; }
		}
		property Uint16 OutOfRange {
			Uint16 get() { return myFlds.OutOfRange; }
			void set(Uint16 newVal) { myFlds.OutOfRange = newVal; }
		}
		property Uint16 BFromEnd {
			Uint16 get() { return myFlds.BFromEnd; }
			void set(Uint16 newVal) { myFlds.BFromEnd = newVal; }
		}
		property Uint16 AbovePosn {
			Uint16 get() { return myFlds.AbovePosn; }
			void set(Uint16 newVal) { myFlds.AbovePosn = newVal; }
		}
		property Uint16 AtTargetVel {
			Uint16 get() { return myFlds.AtTargetVel; }
			void set(Uint16 newVal) { myFlds.AtTargetVel = newVal; }
		}
		property Uint16 InA {
			Uint16 get() { return myFlds.InA; }
			void set(Uint16 newVal) { myFlds.InA = newVal; }
		}
		property Uint16 InB {
			Uint16 get() { return myFlds.InB; }
			void set(Uint16 newVal) { myFlds.InB = newVal; }
		}
		property Uint16 InvInA {
			Uint16 get() { return myFlds.InvInA; }
			void set(Uint16 newVal) { myFlds.InvInA = newVal; }
		}
		property Uint16 InvInB {
			Uint16 get() { return myFlds.InvInB; }
			void set(Uint16 newVal) { myFlds.InvInB = newVal; }
		}
		property Uint16 AFromStart {
			Uint16 get() { return myFlds.AFromStart; }
			void set(Uint16 newVal) { myFlds.AFromStart = newVal; }
		}
		property Uint16 MoveCmdNeg {
			Uint16 get() { return myFlds.MoveCmdNeg; }
			void set(Uint16 newVal) { myFlds.MoveCmdNeg = newVal; }
		}
		property Uint16 Disabled {
			Uint16 get() { return myFlds.Disabled; }
			void set(Uint16 newVal) { myFlds.Disabled = newVal; }
		}
		property Uint16 TimerExpired {
			Uint16 get() { return myFlds.TimerExpired; }
			void set(Uint16 newVal) { myFlds.TimerExpired = newVal; }
		}
		property Uint16 InMotion {
			Uint16 get() { return myFlds.InMotion; }
			void set(Uint16 newVal) { myFlds.InMotion = newVal; }
		}
		property Uint16 InDisableStop {
			Uint16 get() { return myFlds.InDisableStop; }
			void set(Uint16 newVal) { myFlds.InDisableStop = newVal; }
		}
		property Uint16 InCtrlStop {
			Uint16 get() { return myFlds.InCtrlStop; }
			void set(Uint16 newVal) { myFlds.InCtrlStop = newVal; }
		}
		property Uint16 FanOn {
			Uint16 get() { return myFlds.FanOn; }
			void set(Uint16 newVal) { myFlds.FanOn = newVal; }
		}
		property Uint16 VectorSearch {
			Uint16 get() { return myFlds.VectorSearch; }
			void set(Uint16 newVal) { myFlds.VectorSearch = newVal; }
		}
		property Uint16 MoveCmdComplete {
			Uint16 get() { return myFlds.MoveCmdComplete; }
			void set(Uint16 newVal) { myFlds.MoveCmdComplete = newVal; }
		}
		property Uint16 InHardStop {
			Uint16 get() { return myFlds.InHardStop; }
			void set(Uint16 newVal) { myFlds.InHardStop = newVal; }
		}
		property Uint16 ShutdownState {
			Uint16 get() { return myFlds.ShutdownState; }
			void set(Uint16 newVal) { myFlds.ShutdownState = newVal; }
		}
		property Uint16 HwFailure {
			Uint16 get() { return myFlds.HwFailure; }
			void set(Uint16 newVal) { myFlds.HwFailure = newVal; }
		}
		property Uint16 TriggerArmed {
			Uint16 get() { return myFlds.TriggerArmed; }
			void set(Uint16 newVal) { myFlds.TriggerArmed = newVal; }
		}
		property Uint16 StepsActive {
			Uint16 get() { return myFlds.StepsActive; }
			void set(Uint16 newVal) { myFlds.StepsActive = newVal; }
		}
		property Uint16 IndexMtr {
			Uint16 get() { return myFlds.IndexMtr; }
			void set(Uint16 newVal) { myFlds.IndexMtr = newVal; }
		}
		property Uint16 SoftwareInputs {
			Uint16 get() { return myFlds.SoftwareInputs; }
			void set(Uint16 newVal) { myFlds.SoftwareInputs = newVal; }
		}
		/*
		Access for the underlying sFoundation type
		*/
		property cpmStatusRegFlds Flds {
			cpmStatusRegFlds get() { return myFlds; }
		}
	};

	public ref class cliLowAttnCommonFlds {
	private:
		lowAttnCommonFlds &myFlds;
	public:
		cliLowAttnCommonFlds::cliLowAttnCommonFlds(lowAttnCommonFlds &flds) : myFlds(flds) {};
		cliLowAttnCommonFlds::~cliLowAttnCommonFlds() { this->!cliLowAttnCommonFlds(); };
		cliLowAttnCommonFlds::!cliLowAttnCommonFlds() {};

		Uint16 Warning() { return myFlds.Warning; }
		Uint16 UserAlert() { return myFlds.UserAlert; }
		Uint16 NotReady() { return myFlds.NotReady; }
		/*
		Access for the underlying sFoundation type
		*/
		property lowAttnCommonFlds Flds {
			lowAttnCommonFlds get() { return myFlds; }
		}
	};

	public ref class cliPlaInCommonFlds {
	private:
		plaInCommonFlds &myFlds;
	public:
		cliPlaInCommonFlds::cliPlaInCommonFlds(plaInCommonFlds &flds) : myFlds(flds) {};
		cliPlaInCommonFlds::~cliPlaInCommonFlds() { this->!cliPlaInCommonFlds(); };
		cliPlaInCommonFlds::!cliPlaInCommonFlds() {};

		property Uint16 NodeStopped {
			Uint16 get() { return myFlds.NodeStopped; }
			void set(Uint16 newVal) { myFlds.NodeStopped = newVal; }
		}
		property Uint16 na0_15 {
			Uint16 get() { return myFlds.na0_15; }
			void set(Uint16 newVal) { myFlds.na0_15 = newVal; }
		}
		/*
		Access for the underlying sFoundation type
		*/
		property plaInCommonFlds Flds {
			plaInCommonFlds get() { return myFlds; }
		}
	};

	public ref class cliNonAttnCommonFlds {
	private:
		nonAttnCommonFlds &myFlds;
	public:
		cliNonAttnCommonFlds::cliNonAttnCommonFlds(nonAttnCommonFlds &flds) : myFlds(flds) {};
		cliNonAttnCommonFlds::~cliNonAttnCommonFlds() { this->!cliNonAttnCommonFlds(); };
		cliNonAttnCommonFlds::!cliNonAttnCommonFlds() {};

		property Uint16 InCtrlStop {
			Uint16 get() { return myFlds.InCtrlStop; }
			void set(Uint16 newVal) { myFlds.InCtrlStop = newVal; }
		}
		property Uint16 FanOn {
			Uint16 get() { return myFlds.FanOn; }
			void set(Uint16 newVal) { myFlds.FanOn = newVal; }
		}
		property Uint16 HwFailure {
			Uint16 get() { return myFlds.HwFailure; }
			void set(Uint16 newVal) { myFlds.HwFailure = newVal; }
		}
		/*
		Access for the underlying sFoundation type
		*/
		property nonAttnCommonFlds Flds {
			nonAttnCommonFlds get() { return myFlds; }
		}
	};

	public ref class cliCommonStatusFlds {
	private:
		commonStatusFlds &myFlds;
		cliLowAttnCommonFlds^ m_LowAttn;
		cliPlaInCommonFlds^ m_PlaIn;
		cliNonAttnCommonFlds^ m_NonAttn;
	public:
		cliCommonStatusFlds::cliCommonStatusFlds(commonStatusFlds &flds);
		cliCommonStatusFlds::~cliCommonStatusFlds() { this->!cliCommonStatusFlds(); }
		cliCommonStatusFlds::!cliCommonStatusFlds();

		property cliLowAttnCommonFlds^ LowAttn {
			cliLowAttnCommonFlds^ get() { return m_LowAttn; }
			void set(cliLowAttnCommonFlds^ newVal) {
				m_LowAttn = newVal;
				myFlds.LowAttn = newVal->Flds;
			}
		}
		property cliPlaInCommonFlds^ PlaIn {
			cliPlaInCommonFlds^ get() { return m_PlaIn; }
			void set(cliPlaInCommonFlds^ newVal) {
				m_PlaIn = newVal;
				myFlds.PlaIn = newVal->Flds;
			}
		}
		property cliNonAttnCommonFlds^ NonAttn {
			cliNonAttnCommonFlds^ get() { return m_NonAttn; }
			void set(cliNonAttnCommonFlds^ newVal) {
				m_NonAttn = newVal;
				myFlds.NonAttn = newVal->Flds;
			}
		}
		/*
		Access for the underlying sFoundation type
		*/
		property commonStatusFlds Flds {
			commonStatusFlds get() { return myFlds; }
		}
	};

	public ref class cliIscLowAttnFlds {
	private:
		iscLowAttnFlds &myFlds;
	public:
		cliIscLowAttnFlds::cliIscLowAttnFlds(iscLowAttnFlds &flds) : myFlds(flds) {};
		cliIscLowAttnFlds::~cliIscLowAttnFlds() { this->!cliIscLowAttnFlds(); };
		cliIscLowAttnFlds::!cliIscLowAttnFlds() {};

		property Uint16 Warning {
			Uint16 get() { return myFlds.Warning; }
			void set(Uint16 newVal) { myFlds.Warning = newVal; }
		}
		property Uint16 UserAlert {
			Uint16 get() { return myFlds.UserAlert; }
			void set(Uint16 newVal) { myFlds.UserAlert = newVal; }
		}
		property Uint16 NotReady {
			Uint16 get() { return myFlds.NotReady; }
			void set(Uint16 newVal) { myFlds.NotReady = newVal; }
		}
		property Uint16 MoveBufAvail {
			Uint16 get() { return myFlds.MoveBufAvail; }
			void set(Uint16 newVal) { myFlds.MoveBufAvail = newVal; }
		}
		property Uint16 IEXrise {
			Uint16 get() { return myFlds.IEXrise; }
			void set(Uint16 newVal) { myFlds.IEXrise = newVal; }
		}
		property Uint16 IEXfall {
			Uint16 get() { return myFlds.IEXfall; }
			void set(Uint16 newVal) { myFlds.IEXfall = newVal; }
		}
		property Uint16 IEXstatus {
			Uint16 get() { return myFlds.IEXstatus; }
			void set(Uint16 newVal) { myFlds.IEXstatus = newVal; }
		}
		property Uint16 MotionPending {
			Uint16 get() { return myFlds.MotionPending; }
			void set(Uint16 newVal) { myFlds.MotionPending = newVal; }
		}
		property Uint16 InPosLimit {
			Uint16 get() { return myFlds.InPosLimit; }
			void set(Uint16 newVal) { myFlds.InPosLimit = newVal; }
		}
		property Uint16 InNegLimit {
			Uint16 get() { return myFlds.InNegLimit; }
			void set(Uint16 newVal) { myFlds.InNegLimit = newVal; }
		}
		property Uint16 MotionBlocked {
			Uint16 get() { return myFlds.MotionBlocked; }
			void set(Uint16 newVal) { myFlds.MotionBlocked = newVal; }
		}
		property Uint16 TriggerPulse {
			Uint16 get() { return myFlds.TriggerPulse; }
			void set(Uint16 newVal) { myFlds.TriggerPulse = newVal; }
		}
		property Uint16 Homing {
			Uint16 get() { return myFlds.Homing; }
			void set(Uint16 newVal) { myFlds.Homing = newVal; }
		}
		property Uint16 GoingDisabled {
			Uint16 get() { return myFlds.GoingDisabled; }
			void set(Uint16 newVal) { myFlds.GoingDisabled = newVal; }
		}
		property Uint16 StatusEvent {
			Uint16 get() { return myFlds.StatusEvent; }
			void set(Uint16 newVal) { myFlds.StatusEvent = newVal; }
		}
		property Uint16 Enabled {
			Uint16 get() { return myFlds.Enabled; }
			void set(Uint16 newVal) { myFlds.Enabled = newVal; }
		}
		/*
		Access for the underlying sFoundation type
		*/
		property iscLowAttnFlds Flds {
			iscLowAttnFlds get() { return myFlds; }
		}
	};

	public ref class cliIscPlaInFlds {
	private:
		iscPlaInFlds &myFlds;
	public:
		cliIscPlaInFlds::cliIscPlaInFlds(iscPlaInFlds &flds) : myFlds(flds) {};
		cliIscPlaInFlds::~cliIscPlaInFlds() { this->!cliIscPlaInFlds(); };
		cliIscPlaInFlds::!cliIscPlaInFlds() {};

		property Uint16 NodeStopped {
			Uint16 get() { return myFlds.NodeStopped; }
			void set(Uint16 newVal) { myFlds.NodeStopped = newVal; }
		}
		property Uint16 MoveDone {
			Uint16 get() { return myFlds.MoveDone; }
			void set(Uint16 newVal) { myFlds.MoveDone = newVal; }
		}
		property Uint16 OutOfRange {
			Uint16 get() { return myFlds.OutOfRange; }
			void set(Uint16 newVal) { myFlds.OutOfRange = newVal; }
		}
		property Uint16 BFromEnd {
			Uint16 get() { return myFlds.BFromEnd; }
			void set(Uint16 newVal) { myFlds.BFromEnd = newVal; }
		}
		property Uint16 PlaOut0 {
			Uint16 get() { return myFlds.PlaOut0; }
			void set(Uint16 newVal) { myFlds.PlaOut0 = newVal; }
		}
		property Uint16 PlaOut1 {
			Uint16 get() { return myFlds.PlaOut1; }
			void set(Uint16 newVal) { myFlds.PlaOut1 = newVal; }
		}
		property Uint16 Gpi0 {
			Uint16 get() { return myFlds.Gpi0; }
			void set(Uint16 newVal) { myFlds.Gpi0 = newVal; }
		}
		property Uint16 Gpi1 {
			Uint16 get() { return myFlds.Gpi1; }
			void set(Uint16 newVal) { myFlds.Gpi1 = newVal; }
		}
		property Uint16 Gpi2_posLim {
			Uint16 get() { return myFlds.Gpi2_posLim; }
			void set(Uint16 newVal) { myFlds.Gpi2_posLim = newVal; }
		}
		property Uint16 Gpi3_negLim {
			Uint16 get() { return myFlds.Gpi3_negLim; }
			void set(Uint16 newVal) { myFlds.Gpi3_negLim = newVal; }
		}
		property Uint16 AtPosition {
			Uint16 get() { return myFlds.AtPosition; }
			void set(Uint16 newVal) { myFlds.AtPosition = newVal; }
		}
		property Uint16 MaskedIEX {
			Uint16 get() { return myFlds.MaskedIEX; }
			void set(Uint16 newVal) { myFlds.MaskedIEX = newVal; }
		}
		property Uint16 AFromStart {
			Uint16 get() { return myFlds.AFromStart; }
			void set(Uint16 newVal) { myFlds.AFromStart = newVal; }
		}
		property Uint16 MoveCmdNeg {
			Uint16 get() { return myFlds.MoveCmdNeg; }
			void set(Uint16 newVal) { myFlds.MoveCmdNeg = newVal; }
		}
		property Uint16 Disabled {
			Uint16 get() { return myFlds.Disabled; }
			void set(Uint16 newVal) { myFlds.Disabled = newVal; }
		}
		property Uint16 TimerExpired {
			Uint16 get() { return myFlds.TimerExpired; }
			void set(Uint16 newVal) { myFlds.TimerExpired = newVal; }
		}
		/*
		Access for the underlying sFoundation type
		*/
		property iscPlaInFlds Flds {
			iscPlaInFlds get() { return myFlds; }
		}
	};

	public ref class cliIscNonAttnFlds {
	private:
		iscNonAttnFlds &myFlds;
	public:
		cliIscNonAttnFlds::cliIscNonAttnFlds(iscNonAttnFlds &flds) : myFlds(flds) {};
		cliIscNonAttnFlds::~cliIscNonAttnFlds() { this->!cliIscNonAttnFlds(); };
		cliIscNonAttnFlds::!cliIscNonAttnFlds() {};

		property Uint16 InMotion {
			Uint16 get() { return myFlds.InMotion; }
			void set(Uint16 newVal) { myFlds.InMotion = newVal; }
		}
		property Uint16 StepsActive {
			Uint16 get() { return myFlds.StepsActive; }
			void set(Uint16 newVal) { myFlds.StepsActive = newVal; }
		}
		property Uint16 InCtrlStop {
			Uint16 get() { return myFlds.InCtrlStop; }
			void set(Uint16 newVal) { myFlds.InCtrlStop = newVal; }
		}
		property Uint16 FanOn {
			Uint16 get() { return myFlds.FanOn; }
			void set(Uint16 newVal) { myFlds.FanOn = newVal; }
		}
		property Uint16 VectorSearch {
			Uint16 get() { return myFlds.VectorSearch; }
			void set(Uint16 newVal) { myFlds.VectorSearch = newVal; }
		}
		property Uint16 MoveCmdComplete {
			Uint16 get() { return myFlds.MoveCmdComplete; }
			void set(Uint16 newVal) { myFlds.MoveCmdComplete = newVal; }
		}
		property Uint16 InHardStop {
			Uint16 get() { return myFlds.InHardStop; }
			void set(Uint16 newVal) { myFlds.InHardStop = newVal; }
		}
		property Uint16 ShutdownState {
			Uint16 get() { return myFlds.ShutdownState; }
			void set(Uint16 newVal) { myFlds.ShutdownState = newVal; }
		}
		property Uint16 HwFailure {
			Uint16 get() { return myFlds.HwFailure; }
			void set(Uint16 newVal) { myFlds.HwFailure = newVal; }
		}
		property Uint16 TriggerArmed {
			Uint16 get() { return myFlds.TriggerArmed; }
			void set(Uint16 newVal) { myFlds.TriggerArmed = newVal; }
		}
		property Uint16 IndexMtr {
			Uint16 get() { return myFlds.IndexMtr; }
			void set(Uint16 newVal) { myFlds.IndexMtr = newVal; }
		}
		property Uint16 IndexLd {
			Uint16 get() { return myFlds.IndexLd; }
			void set(Uint16 newVal) { myFlds.IndexLd = newVal; }
		}
		property Uint16 SoftwareInputs {
			Uint16 get() { return myFlds.SoftwareInputs; }
			void set(Uint16 newVal) { myFlds.SoftwareInputs = newVal; }
		}
		/*
		Access for the underlying sFoundation type
		*/
		property iscNonAttnFlds Flds {
			iscNonAttnFlds get() { return myFlds; }
		}
	};

	public ref class cliIscStatusRegFlds {
	private:
		iscStatusRegFlds &myFlds;
		cliIscLowAttnFlds^ m_LowAttn;
		cliIscPlaInFlds^ m_PlaIn;
		cliIscNonAttnFlds^ m_NonAttn;
	public:
		cliIscStatusRegFlds::cliIscStatusRegFlds(iscStatusRegFlds &flds);
		cliIscStatusRegFlds::~cliIscStatusRegFlds() { this->!cliIscStatusRegFlds(); }
		cliIscStatusRegFlds::!cliIscStatusRegFlds();

		property cliIscLowAttnFlds^ LowAttn {
			cliIscLowAttnFlds^ get() { return m_LowAttn; }
			void set(cliIscLowAttnFlds^ newVal) {
				m_LowAttn = newVal;
				myFlds.LowAttn = newVal->Flds;
			}
		}
		property cliIscPlaInFlds^ PlaIn {
			cliIscPlaInFlds^ get() { return m_PlaIn; }
			void set(cliIscPlaInFlds^ newVal) {
				m_PlaIn = newVal;
				myFlds.PLAin = newVal->Flds;
			}
		}
		property cliIscNonAttnFlds^ NonAttn {
			cliIscNonAttnFlds^ get() { return m_NonAttn; }
			void set(cliIscNonAttnFlds^ newVal) {
				m_NonAttn = newVal;
				myFlds.NonAttn = newVal->Flds;
			}
		}
		/*
		Access for the underlying sFoundation type
		*/
		property iscStatusRegFlds Flds {
			iscStatusRegFlds get() { return myFlds; }
		}
	};

	//*****************************************************************************
	// NAME                                                                       *
	//  cliCPMNodeStopFlds
	//
	// DESCRIPTION
	/*
	ClearPath-SC stop type definition.

	This bit encoded register is used to specify the actions a motor will take
	when a default or explicit node stop action occurs.
	*/
	public ref class cliCPMNodeStopFlds {
	private:
		cpmNodeStopFlds &myFlds;
	public:
		cliCPMNodeStopFlds::cliCPMNodeStopFlds(cpmNodeStopFlds &flds) : myFlds(flds) {};
		cliCPMNodeStopFlds::~cliCPMNodeStopFlds() { this->!cliCPMNodeStopFlds(); };
		cliCPMNodeStopFlds::!cliCPMNodeStopFlds() {};

		/*
		Move Generator Action to Take

		This is what the motion generator will do for all non-clearing actions.
		*/
		property cliMGStopStyles MotionAction {
			cliMGStopStyles get() { return (cliMGStopStyles)myFlds.MotionAction; }
			void set(cliMGStopStyles newStyle) { myFlds.MotionAction = (mgStopStyles)newStyle; }
		}
		// - - - - - - - - - - - -
		// Stop type modifiers
		// - - - - - - - - - - - -
		/*
		Clear modifier(s)

		This field is set in conjunction with the MotionLock or Disable
		fields to clear the latching condition preventing normal operations
		of these features.
		*/
		property Uint16 Clear {
			Uint16 get() { return myFlds.Clear; }
			void set(Uint16 newVal) { myFlds.Clear = newVal; }
		}
		/*
		Motion Lockout latch

		If this set, subsequent motion requests are rejected until this
		condition is cleared with the Clear modifier.
		*/
		property Uint16 MotionLock {
			Uint16 get() { return myFlds.MotionLock; }
			void set(Uint16 newVal) { myFlds.MotionLock = newVal; }
		}
		/*
		Suppress Node Stop Status

		The update of the Status Register is suppressed making this
		a stealth Node Stop.
		*/
		property Uint16 Quiet {
			Uint16 get() { return myFlds.Quiet; }
			void set(Uint16 newVal) { myFlds.Quiet = newVal; }
		}
		/*
		Force disable after Motion Action is complete

		The node will disable the servo after the motion action completes. This
		can be used with the AutoBrake feature to engage the brake.
		*/
		property Uint16 Disable {
			Uint16 get() { return myFlds.Disable; }
			void set(Uint16 newVal) { myFlds.Disable = newVal; }
		}
		/*
		Access for the underlying sFoundation type
		*/
		property cpmNodeStopFlds Flds {
			cpmNodeStopFlds get() { return myFlds; }
		}
	};

	//*****************************************************************************
	// NAME                                                                       *
	//  cliISCStopFlds
	//
	// DESCRIPTION
	/*
	Meridian ISC stop type definition.

	This bit encoded register is used to specify the actions a motor will take
	when a default or explicit node stop action occurs.
	*/
	public ref class cliISCNodeStopFlds {
	private:
		iscNodeStopFlds &myFlds;
	public:
		cliISCNodeStopFlds::cliISCNodeStopFlds(iscNodeStopFlds &flds) : myFlds(flds) {};
		cliISCNodeStopFlds::~cliISCNodeStopFlds() { this->!cliISCNodeStopFlds(); };
		cliISCNodeStopFlds::!cliISCNodeStopFlds() {};

		/*
		Move Generator response

		This is what the motion generator will do for all non-Clearing actions.
		*/
		property cliMGStopStyles MotionAction {
			cliMGStopStyles get() { return (cliMGStopStyles)myFlds.MotionAction; }
			void set(cliMGStopStyles newStyle) { myFlds.MotionAction = (mgStopStyles)newStyle; }
		}
		// - - - - - - - - - - - -
		// Stop type modifiers
		// - - - - - - - - - - - -
		/// Clear modifier(s)
		property Uint16 Clear {
			Uint16 get() { return myFlds.Clear; }
			void set(Uint16 newVal) { myFlds.Clear = newVal; }
		}
		/// Lockout subsequent motion and enter E-Stopped State
		property Uint16 MotionLock {
			Uint16 get() { return myFlds.MotionLock; }
			void set(Uint16 newVal) { myFlds.MotionLock = newVal; }
		}
		/// Suppress update of Status Register making this
		/// a stealth Node Stop.
		property Uint16 Quiet {
			Uint16 get() { return myFlds.Quiet; }
			void set(Uint16 newVal) { myFlds.Quiet = newVal; }
		}
		/// Force the Output Register to the Controlled
		/// Output Register
		property Uint16 IOControl {
			Uint16 get() { return myFlds.IOControl; }
			void set(Uint16 newVal) { myFlds.IOControl = newVal; }
		}
		/*
		Access for the underlying sFoundation type
		*/
		property iscNodeStopFlds Flds {
			iscNodeStopFlds get() { return myFlds; }
		}
	};

	/*
	Universal Node Stop Register Field Definitions.

	Not all models support all options.
	*/
	public ref class cliNodeStopFlds {
	private:
		mgNodeStopReg::_nodeStopFlds &myFlds;
	public:
		cliNodeStopFlds::cliNodeStopFlds(mgNodeStopReg::_nodeStopFlds &flds) : myFlds(flds) {};
		cliNodeStopFlds::~cliNodeStopFlds() { this->!cliNodeStopFlds(); };
		cliNodeStopFlds::!cliNodeStopFlds() {};

		/*
		Move Generator Action Taken.

		This is what the motion generator will do for all non-Clearing
		actions.
		*/
		property cliMGStopStyles Style {
			cliMGStopStyles get() { return (cliMGStopStyles)myFlds.Style; }
			void set(cliMGStopStyles newStyle) { myFlds.Style = (mgStopStyles)newStyle; }
		}
		// - - - - - - - - - - - -
		// Stop type modifiers
		// - - - - - - - - - - - -
		/*
		Clear latched modifier(s).

		This is used to restore operations after EStop,
		Controlled, or Disable node stop has been issued. Set this
		field with along with the modifier you wish to clear. The
		Style field is ignored when this is set.
		*/
		property Uint16 Clear {
			Uint16 get() { return myFlds.Clear; }
			void set(Uint16 newVal) { myFlds.Clear = newVal; }
		}
		/*
		Lockout subsequent motion.

		Prevent subsequent motion after node stop issued until the latch
		is cleared. This is sometimes called the E-Stop or MotionLock
		state. Clear this condition by issuing a node stop with this field
		set and the Clear field set.
		*/
		property Uint16 EStop {
			Uint16 get() { return myFlds.EStop; }
			void set(Uint16 newVal) { myFlds.EStop = newVal; }
		}
		/*
		Suppress update of Status Register.

		This makes this node stop a stealth Node Stop.
		*/
		property Uint16 Quiet {
			Uint16 get() { return myFlds.Quiet; }
			void set(Uint16 newVal) { myFlds.Quiet = newVal; }
		}
		/*
		Force drive to disable after the Motion Action completes.

		Clear this condition by issuing a node stop with this field
		set and the Clear field set.
		*/
		property Uint16 Disable {
			Uint16 get() { return myFlds.Disable; }
			void set(Uint16 newVal) { myFlds.Disable = newVal; }
		}
		/*
		Force the Output Register to the Controlled
		Output Register state.

		Prevent subsequent output register changes until cleared. Clear
		this condition by issuing a node stop with this field
		set and the Clear field set.

		This is Meridian-ISC only feature
		*/
		property Uint16 Controlled {
			Uint16 get() { return myFlds.Controlled; }
			void set(Uint16 newVal) { myFlds.Controlled = newVal; }
		}
		/*
		Access for the underlying sFoundation type
		*/
		property mgNodeStopReg::_nodeStopFlds Flds {
			mgNodeStopReg::_nodeStopFlds get() { return myFlds; }
		}
	};
}