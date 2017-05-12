#if !defined(AFX_POINTFIGURESERIES_H__E26BFAC6_7EA0_44BD_9113_813E73DDF30D__INCLUDED_)
#define AFX_POINTFIGURESERIES_H__E26BFAC6_7EA0_44BD_9113_813E73DDF30D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CValueList;
class CPointer;

/////////////////////////////////////////////////////////////////////////////
// CPointFigureSeries wrapper class

class CPointFigureSeries : public COleDispatchDriver
{
public:
	CPointFigureSeries() {}		// Calls COleDispatchDriver default constructor
	CPointFigureSeries(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CPointFigureSeries(const CPointFigureSeries& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CValueList GetCloseValues();
	CValueList GetDateValues();
	CValueList GetHighValues();
	CValueList GetLowValues();
	CValueList GetOpenValues();
	long AddOHLC(double DateValue, double OpenValue, double HighValue, double LowValue, double CloseValue);
	double GetBoxSize();
	void SetBoxSize(double newValue);
	double GetReversalAmount();
	void SetReversalAmount(double newValue);
	CPointer GetDownSymbol();
	CPointer GetUpSymbol();
	long GetInversionColumn(long Index);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POINTFIGURESERIES_H__E26BFAC6_7EA0_44BD_9113_813E73DDF30D__INCLUDED_)
