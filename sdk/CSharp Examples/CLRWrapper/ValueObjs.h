#pragma once

#include "pubSysCls.h"	
#include "RegisterObjs.h"

using namespace sFnd;

//Value Classes
namespace sFndCLIWrapper {
	public ref class cliValueAlert
	{
	private:
		ValueAlert* myVal;
	public:
		// Constructor / destructor
		cliValueAlert::cliValueAlert(ValueAlert &val) : myVal(new ValueAlert(val)) {}
		cliValueAlert::~cliValueAlert() { this->!cliValueAlert(); }
		cliValueAlert::!cliValueAlert() {
			delete myVal;
			myVal = nullptr;
		}
	public:

		// ValueAlert wrapper functions
		void Refresh() { myVal->Refresh(); }
		bool Exists() { return myVal->Exists(); }
		void AutoRefresh(bool newState) { myVal->AutoRefresh(newState); }
		bool AutoRefresh() { return myVal->AutoRefresh(); }
		bool IsVolatile() { return myVal->IsVolatile(); }

		alertReg &operator=(alertReg &newValue) { return myVal->operator=(newValue); }
		operator alertReg() { return myVal->Value(); }

		void Value(const alertReg &newValue) { myVal->Value(newValue); }
		cliAlertReg^ Value() { return gcnew cliAlertReg(myVal->Value()); }
		void Clear() { myVal->Clear(); }
		cliAlertReg^ Last() { return gcnew cliAlertReg(myVal->Last()); }
		bool TestAndClear(const alertReg &mask, alertReg &result) {
			return myVal->TestAndClear(mask, result);
		}
	};

	public ref class cliValueAppConfigReg
	{
	private:
		ValueAppConfigReg* myVal;
	public:
		// Constructor / destructor
		cliValueAppConfigReg::cliValueAppConfigReg(ValueAppConfigReg &val) :
			myVal(new ValueAppConfigReg(val)) {}
		cliValueAppConfigReg::~cliValueAppConfigReg() { this->!cliValueAppConfigReg(); }
		cliValueAppConfigReg::!cliValueAppConfigReg() {
			delete myVal;
			myVal = nullptr;
		}

		// ValueStatus wrapper functions
		void Refresh() { myVal->Refresh(); }
		bool Exists() { return myVal->Exists(); }
		void AutoRefresh(bool newState) { myVal->AutoRefresh(newState); }
		bool AutoRefresh() { return myVal->AutoRefresh(); }
		bool IsVolatile() { return myVal->IsVolatile(); }

		operator double() { return (double)myVal->Value().bits; }
		operator int32_t() { return (int32_t)myVal->Value().bits; }
		operator uint32_t() { return (uint32_t)myVal->Value().bits; }
		operator mnAppConfigReg() { return myVal->Value(); }
		mnAppConfigReg &operator=(mnAppConfigReg &newValue) { return myVal->operator=(newValue); }
		mnAppConfigReg Value() { return myVal->Value(); }

		void Value(const mnAppConfigReg &newValue) { myVal->Value(newValue); }
		void Clear(const mnAppConfigReg &mask) { myVal->Clear(mask); }
		mnAppConfigReg Last() { return myVal->Last(); }
		void Set(const mnAppConfigReg &mask) { myVal->Set(mask); }
	};

	public ref class cliValueDouble
	{
	private:
		ValueDouble* myVal;
	public:
		// Constructor / destructor
		cliValueDouble::cliValueDouble(ValueDouble &val) : myVal(new ValueDouble(val)) {}
		cliValueDouble::~cliValueDouble() { this->!cliValueDouble(); }
		cliValueDouble::!cliValueDouble() {
			delete myVal;
			myVal = nullptr;
		}

		// ValueDouble wrapper functions
		void Refresh() { myVal->Refresh(); }
		bool Exists() { return myVal->Exists(); }
		void AutoRefresh(bool newState) { myVal->AutoRefresh(newState); }
		bool AutoRefresh() { return myVal->AutoRefresh(); }
		bool IsVolatile() { return myVal->IsVolatile(); }

		double operator=(double newValue) { return myVal->operator=(newValue); }
		operator double() { return myVal->operator double(); }
		operator int() { return myVal->operator int32_t(); }
		operator Uint32() { return myVal->operator uint32_t(); }

		void Value(int newValue, bool makeNonVolatile) {
			myVal->Value((int32_t)newValue, makeNonVolatile);
		}
		void Value(int newValue) { myVal->Value((int32_t)newValue); }
		void Value(double newValue, bool makeNonVolatile) { myVal->Value(newValue, makeNonVolatile); }
		void Value(double newValue) { myVal->Value(newValue); }
		double Value(bool getNonVolatile) { return myVal->Value(getNonVolatile); }
		double Value() { return myVal->Value(); }
	};

	public ref class cliValueHwConfigReg
	{
	private:
		ValueHwConfigReg* myVal;
	public:
		// Constructor / destructor
		cliValueHwConfigReg::cliValueHwConfigReg(ValueHwConfigReg &val) : myVal(new ValueHwConfigReg(val)) {}
		cliValueHwConfigReg::~cliValueHwConfigReg() { this->!cliValueHwConfigReg(); }
		cliValueHwConfigReg::!cliValueHwConfigReg() {
			delete myVal;
			myVal = nullptr;
		}

		// ValueStatus wrapper functions
		void Refresh() { myVal->Refresh(); }
		bool Exists() { return myVal->Exists(); }
		void AutoRefresh(bool newState) { myVal->AutoRefresh(newState); }
		bool AutoRefresh() { return myVal->AutoRefresh(); }
		bool IsVolatile() { return myVal->IsVolatile(); }

		operator double() { return (double)myVal->Value().bits; }
		operator int32_t() { return (int32_t)myVal->Value().bits; }
		operator uint32_t() { return (uint32_t)myVal->Value().bits; }
		operator mnHwConfigReg() { return myVal->Value(); }
		mnHwConfigReg &operator=(mnHwConfigReg &newValue) { return myVal->operator=(newValue); }

		mnHwConfigReg Value() { return myVal->Value(); }
		void Value(const mnHwConfigReg &newValue) { myVal->Value(newValue); }
		void Clear(const mnHwConfigReg &mask) { myVal->Clear(mask); }
		mnHwConfigReg Last() { return myVal->Last(); }
		void Set(const mnHwConfigReg &mask) { myVal->Set(mask); }
	};

	public ref class cliValueOutReg
	{
	private:
		ValueOutReg* myVal;
	public:
		// Constructor / destructor
		cliValueOutReg::cliValueOutReg(ValueOutReg &val) : myVal(new ValueOutReg(val)) {}
		cliValueOutReg::~cliValueOutReg() { this->!cliValueOutReg(); }
		cliValueOutReg::!cliValueOutReg() {
			delete myVal;
			myVal = nullptr;
		}

		// ValueStatus wrapper functions
		void Refresh() { myVal->Refresh(); }
		bool Exists() { return myVal->Exists(); }
		void AutoRefresh(bool newState) { myVal->AutoRefresh(newState); }
		bool AutoRefresh() { return myVal->AutoRefresh(); }
		bool IsVolatile() { return myVal->IsVolatile(); }

		operator mnOutReg() { return myVal->Value(); }
		operator double() { return (double)myVal->Value().bits; }
		operator int32_t() { return (int32_t)myVal->Value().bits; }
		operator uint32_t() { return (uint32_t)myVal->Value().bits; }
		mnOutReg &operator=(mnOutReg &newValue) { return myVal->operator=(newValue); }

		mnOutReg Value() { return myVal->Value(); }
		void Value(const mnOutReg &newValue) { myVal->Value(newValue); }
		void Clear(const mnOutReg &mask) { myVal->Clear(mask); }
		mnOutReg Last() { return myVal->Last(); }
		void Set(const mnOutReg &mask) { myVal->Set(mask); }
	};

	public ref class cliValuePowerReg
	{
	private:
		ValuePowerReg* myVal;
	public:
		// Constructor / destructor
		cliValuePowerReg::cliValuePowerReg(ValuePowerReg &val) : myVal(new ValuePowerReg(val)) {}
		cliValuePowerReg::~cliValuePowerReg() { this->!cliValuePowerReg(); }
		cliValuePowerReg::!cliValuePowerReg() {
			delete myVal;
			myVal = nullptr;
		}

		// ValueStatus wrapper functions
		void Refresh() { myVal->Refresh(); }
		bool Exists() { return myVal->Exists(); }
		void AutoRefresh(bool newState) { myVal->AutoRefresh(newState); }
		bool AutoRefresh() { return myVal->AutoRefresh(); }
		bool IsVolatile() { return myVal->IsVolatile(); }

		operator mnPowerReg() { return myVal->Value(); }

		mnPowerReg Value() { return myVal->Value(); }
		void Clear() { myVal->Clear(); }
		mnPowerReg Last() { return myVal->Last(); }
		bool TestAndClear(const mnPowerReg &mask, mnPowerReg &result) {
			return myVal->TestAndClear(mask, result);
		}
	};

	public ref class cliValueSigned
	{
	private:
		ValueSigned* myVal;
	public:
		// Constructor / destructor
		cliValueSigned::cliValueSigned(ValueSigned &val) : myVal(new ValueSigned(val)) {}
		cliValueSigned::~cliValueSigned() { this->!cliValueSigned(); }
		cliValueSigned::!cliValueSigned() {
			delete myVal;
			myVal = nullptr;
		}

		// ValueDouble wrapper functions
		void Refresh() { myVal->Refresh(); }
		bool Exists() { return myVal->Exists(); }
		void AutoRefresh(bool newState) { myVal->AutoRefresh(newState); }
		bool AutoRefresh() { return myVal->AutoRefresh(); }
		bool IsVolatile() { return myVal->IsVolatile(); }
		void Value(int32_t newValue, bool makeNonVolatile) { myVal->Value(newValue, makeNonVolatile); }
		void Value(int32_t newValue) { myVal->Value(newValue); }
		int32_t Value(bool getNonVolatile) { return myVal->Value(getNonVolatile); }
		int32_t Value() { return myVal->Value(); }

		int32_t operator=(int32_t newValue) { return myVal->operator=(newValue); }
		operator double() { return myVal->operator double(); }
		operator int32_t() { return myVal->operator int32_t(); }
		operator uint32_t() { return myVal->operator uint32_t(); }

		int32_t operator|(int32_t arg) { return(myVal->operator int32_t() | arg); }
		int32_t operator&(int32_t arg) { return(myVal->operator int32_t() & arg); }
		int32_t operator^(int32_t arg) { return(myVal->operator int32_t() ^ arg); }
		int32_t operator+(int32_t arg) { return(myVal->operator int32_t() + arg); }
		int32_t operator-(int32_t arg) { return(myVal->operator int32_t() - arg); }
		int32_t operator*(int32_t arg) { return(myVal->operator int32_t() * arg); }
		int32_t operator/(int32_t arg) { return(myVal->operator int32_t() / arg); }

		int32_t operator|=(int32_t arg) { return myVal->operator=(myVal->operator|(arg)); }
		int32_t operator&=(int32_t arg) { return myVal->operator=(myVal->operator&(arg)); }
		int32_t operator^=(int32_t arg) { return myVal->operator=(myVal->operator^(arg)); }
		int32_t operator+=(int32_t arg) { return myVal->operator=(myVal->operator+(arg)); }
		int32_t operator-=(int32_t arg) { return myVal->operator=(myVal->operator-(arg)); }
		int32_t operator*=(int32_t arg) { return myVal->operator=(myVal->operator*(arg)); }
		int32_t operator/=(int32_t arg) { return myVal->operator=(myVal->operator/(arg)); }

		int32_t operator|(uint32_t arg) { return(myVal->operator int32_t() | arg); }
		int32_t operator&(uint32_t arg) { return(myVal->operator int32_t() & arg); }
		int32_t operator^(uint32_t arg) { return(myVal->operator int32_t() ^ arg); }
		int32_t operator+(uint32_t arg) { return(myVal->operator int32_t() + arg); }
		int32_t operator-(uint32_t arg) { return(myVal->operator int32_t() - arg); }
		int32_t operator*(uint32_t arg) { return(myVal->operator int32_t() * arg); }
		int32_t operator/(uint32_t arg) { return(myVal->operator int32_t() / arg); }

		int32_t operator|=(uint32_t arg) { return myVal->operator=(myVal->operator|(arg)); }
		int32_t operator&=(uint32_t arg) { return myVal->operator=(myVal->operator&(arg)); }
		int32_t operator^=(uint32_t arg) { return myVal->operator=(myVal->operator^(arg)); }
		int32_t operator+=(uint32_t arg) { return myVal->operator=(myVal->operator+(arg)); }
		int32_t operator-=(uint32_t arg) { return myVal->operator=(myVal->operator-(arg)); }
		int32_t operator*=(uint32_t arg) { return myVal->operator=(myVal->operator*(arg)); }
		int32_t operator/=(uint32_t arg) { return myVal->operator=(myVal->operator/(arg)); }

		double operator+(double arg) { return(myVal->operator int32_t() + arg); }
		double operator-(double arg) { return(myVal->operator int32_t() - arg); }
		double operator*(double arg) { return(myVal->operator int32_t() * arg); }
		double operator/(double arg) { return(myVal->operator int32_t() / arg); }

		int32_t operator+=(double arg) { return myVal->operator=(static_cast<int32_t>(myVal->operator+(arg))); }
		int32_t operator-=(double arg) { return myVal->operator=(static_cast<int32_t>(myVal->operator-(arg))); }
		int32_t operator*=(double arg) { return myVal->operator=(static_cast<int32_t>(myVal->operator*(arg))); }
		int32_t operator/=(double arg) { return myVal->operator=(static_cast<int32_t>(myVal->operator/(arg))); }
	};

	public ref class cliValueStatus
	{
	private:
		ValueStatus* myVal;
	public:
		// Constructor / destructor
		cliValueStatus::cliValueStatus(ValueStatus &val) : myVal(new ValueStatus(val)) {}
		cliValueStatus::~cliValueStatus() { this->!cliValueStatus(); }
		cliValueStatus::!cliValueStatus() {
			delete myVal;
			myVal = nullptr;
		}

		// ValueStatus wrapper functions
		void Refresh() { myVal->Refresh(); }
		bool Exists() { return myVal->Exists(); }
		void AutoRefresh(bool newState) { myVal->AutoRefresh(newState); }
		bool AutoRefresh() { return myVal->AutoRefresh(); }
		bool IsVolatile() { return myVal->IsVolatile(); }

		mnStatusReg &operator=(mnStatusReg &newValue) { return myVal->operator=(newValue); }
		operator mnStatusReg() { return myVal->Value(); }

		void Value(const mnStatusReg &newValue) { myVal->Value(newValue); }
		void Value(cliMNStatusReg^ newValue) { myVal->Value(*newValue->Reg); }
		cliMNStatusReg^ Value() { return gcnew cliMNStatusReg(myVal->Value()); }
		void Clear() { myVal->Clear(); }
		cliMNStatusReg^ Last() { return gcnew cliMNStatusReg(myVal->Last()); }
		bool TestAndClear(const mnStatusReg &mask) { return myVal->TestAndClear(mask); }
		bool TestAndClear(const mnStatusReg &mask, mnStatusReg &result) {
			return myVal->TestAndClear(mask, result);
		}
	};

	public ref class cliValueString
	{
	private:
		ValueString &myVal;
	public:
		// Constructor / destructor
		cliValueString::cliValueString(ValueString &val) : myVal(val) {}
		cliValueString::~cliValueString() { this->!cliValueString(); }
		cliValueString::!cliValueString() {}

		// Valuestring wrapper functions
		void Refresh() { myVal.Refresh(); }
		bool Exists() { return myVal.Exists(); }
		void AutoRefresh(bool newState) { myVal.AutoRefresh(newState); }
		bool AutoRefresh() { return myVal.AutoRefresh(); }
		bool IsVolatile() { return myVal.IsVolatile(); }

		const char* operator=(const char* newValue) { return myVal.operator=(newValue); }
		operator const char*() { return myVal.operator const char*(); }

		void Value(const char* newValue) { myVal.Value(newValue); }
		System::String^ Value() { return gcnew System::String(myVal.Value()); }
	};

	public ref class cliValueUnsigned
	{
	private:
		ValueUnsigned* myVal;
	public:
		// Constructor / destructor
		cliValueUnsigned::cliValueUnsigned(ValueUnsigned &val) : myVal(new ValueUnsigned(val)) {}
		cliValueUnsigned::~cliValueUnsigned() { this->!cliValueUnsigned(); }
		cliValueUnsigned::!cliValueUnsigned() {
			delete myVal;
			myVal = nullptr;
		}

		// ValueDouble wrapper functions
		void Refresh() { myVal->Refresh(); }
		bool Exists() { return myVal->Exists(); }
		void AutoRefresh(bool newState) { myVal->AutoRefresh(newState); }
		bool AutoRefresh() { return myVal->AutoRefresh(); }
		bool IsVolatile() { return myVal->IsVolatile(); }

		void Value(uint32_t newValue, bool makeNonVolatile) { myVal->Value(newValue, makeNonVolatile); }
		void Value(uint32_t newValue) { myVal->Value(newValue); }
		uint32_t Value(bool getNonVolatile) { return myVal->Value(getNonVolatile); }
		uint32_t Value() { return myVal->Value(); }

		operator double() { return myVal->operator double(); }
		operator uint32_t() { return myVal->operator uint32_t(); }
		uint32_t operator=(uint32_t newValue) { return myVal->operator=(newValue); }
		uint32_t operator|(int32_t arg) { return(myVal->operator uint32_t() | arg); }
		uint32_t operator&(int32_t arg) { return(myVal->operator uint32_t() & arg); }
		uint32_t operator^(int32_t arg) { return(myVal->operator uint32_t() ^ arg); }
		uint32_t operator+(int32_t arg) { return(myVal->operator uint32_t() + arg); }
		uint32_t operator-(int32_t arg) { return(myVal->operator uint32_t() - arg); }
		uint32_t operator*(int32_t arg) { return(myVal->operator uint32_t() * arg); }
		uint32_t operator/(int32_t arg) { return(myVal->operator uint32_t() / arg); }

		uint32_t operator|=(int32_t arg) { return myVal->operator=(myVal->operator|(arg)); }
		uint32_t operator&=(int32_t arg) { return myVal->operator=(myVal->operator&(arg)); }
		uint32_t operator^=(int32_t arg) { return myVal->operator=(myVal->operator^(arg)); }
		uint32_t operator+=(int32_t arg) { return myVal->operator=(myVal->operator+(arg)); }
		uint32_t operator-=(int32_t arg) { return myVal->operator=(myVal->operator-(arg)); }
		uint32_t operator*=(int32_t arg) { return myVal->operator=(myVal->operator*(arg)); }
		uint32_t operator/=(int32_t arg) { return myVal->operator=(myVal->operator/(arg)); }

		uint32_t operator|(uint32_t arg) { return(myVal->operator uint32_t() | arg); }
		uint32_t operator&(uint32_t arg) { return(myVal->operator uint32_t() & arg); }
		uint32_t operator^(uint32_t arg) { return(myVal->operator uint32_t() ^ arg); }
		uint32_t operator+(uint32_t arg) { return(myVal->operator uint32_t() + arg); }
		uint32_t operator-(uint32_t arg) { return(myVal->operator uint32_t() - arg); }
		uint32_t operator*(uint32_t arg) { return(myVal->operator uint32_t() * arg); }
		uint32_t operator/(uint32_t arg) { return(myVal->operator uint32_t() / arg); }

		uint32_t operator|=(uint32_t arg) { return myVal->operator=(myVal->operator|(arg)); }
		uint32_t operator&=(uint32_t arg) { return myVal->operator=(myVal->operator&(arg)); }
		uint32_t operator^=(uint32_t arg) { return myVal->operator=(myVal->operator^(arg)); }
		uint32_t operator+=(uint32_t arg) { return myVal->operator=(myVal->operator+(arg)); }
		uint32_t operator-=(uint32_t arg) { return myVal->operator=(myVal->operator-(arg)); }
		uint32_t operator*=(uint32_t arg) { return myVal->operator=(myVal->operator*(arg)); }
		uint32_t operator/=(uint32_t arg) { return myVal->operator=(myVal->operator/(arg)); }

		double operator+(double arg) { return(myVal->operator uint32_t() + arg); }
		double operator-(double arg) { return(myVal->operator uint32_t() - arg); }
		double operator*(double arg) { return(myVal->operator uint32_t() * arg); }
		double operator/(double arg) { return(myVal->operator uint32_t() / arg); }

		uint32_t operator+=(double arg) { return myVal->operator=(static_cast<uint32_t>(myVal->operator+(arg))); }
		uint32_t operator-=(double arg) { return myVal->operator=(static_cast<uint32_t>(myVal->operator-(arg))); }
		uint32_t operator*=(double arg) { return myVal->operator=(static_cast<uint32_t>(myVal->operator*(arg))); }
		uint32_t operator/=(double arg) { return myVal->operator=(static_cast<uint32_t>(myVal->operator/(arg))); }
	};

}