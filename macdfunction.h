#if !defined(AFX_MACDFUNCTION_H__D5E3F3B9_5B23_49BB_8F37_0897D726384A__INCLUDED_)
#define AFX_MACDFUNCTION_H__D5E3F3B9_5B23_49BB_8F37_0897D726384A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CSeries;

/////////////////////////////////////////////////////////////////////////////
// CMACDFunction wrapper class

class CMACDFunction : public COleDispatchDriver
{
public:
	CMACDFunction() {}		// Calls COleDispatchDriver default constructor
	CMACDFunction(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMACDFunction(const CMACDFunction& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	double GetPeriod2();
	void SetPeriod2(double newValue);
	CSeries GetMACDExp();
	CSeries GetHistogram();
	long GetPeriod3();
	void SetPeriod3(long nNewValue);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MACDFUNCTION_H__D5E3F3B9_5B23_49BB_8F37_0897D726384A__INCLUDED_)