#if !defined(AFX_DARVASSERIES_H__F47425A0_83C6_4414_9D56_5117DC19916D__INCLUDED_)
#define AFX_DARVASSERIES_H__F47425A0_83C6_4414_9D56_5117DC19916D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CPointer;
class CValueList;
class CPen1;
class CGradient;
class CBrush1;
class CTeeRect;

/////////////////////////////////////////////////////////////////////////////
// CDarvasSeries wrapper class

class CDarvasSeries : public COleDispatchDriver
{
public:
	CDarvasSeries() {}		// Calls COleDispatchDriver default constructor
	CDarvasSeries(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CDarvasSeries(const CDarvasSeries& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CPointer GetPointer();
	BOOL GetDark3D();
	void SetDark3D(BOOL bNewValue);
	long GetTransparency();
	void SetTransparency(long nNewValue);
	BOOL GetFastPoint();
	void SetFastPoint(BOOL bNewValue);
	long GetTreatNulls();
	void SetTreatNulls(long nNewValue);
	long GetCandleStyle();
	void SetCandleStyle(long nNewValue);
	long GetCandleWidth();
	void SetCandleWidth(long nNewValue);
	CValueList GetCloseValues();
	CValueList GetDateValues();
	unsigned long GetDownCloseColor();
	void SetDownCloseColor(unsigned long newValue);
	CValueList GetHighValues();
	CValueList GetLowValues();
	CValueList GetOpenValues();
	BOOL GetShowCloseTick();
	void SetShowCloseTick(BOOL bNewValue);
	BOOL GetShowOpenTick();
	void SetShowOpenTick(BOOL bNewValue);
	unsigned long GetUpCloseColor();
	void SetUpCloseColor(unsigned long newValue);
	long AddCandle(double DateValue, double OpenValue, double HighValue, double LowValue, double CloseValue);
	CPen1 GetHighLowPen();
	long GetColorStyle();
	void SetColorStyle(long nNewValue);
	CGradient GetUpCloseGradient();
	CGradient GetDownCloseGradient();
	CBrush1 GetBoxBrush();
	CPen1 GetBoxPen();
	long GetNumBoxes();
	long ClickedBox(long X, long Y);
	CTeeRect GetBoxesRect(long Index);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DARVASSERIES_H__F47425A0_83C6_4414_9D56_5117DC19916D__INCLUDED_)
