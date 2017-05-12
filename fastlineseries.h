#if !defined(AFX_FASTLINESERIES_H__A87B9DD1_DD80_4E30_AC50_466D7DE6AAF1__INCLUDED_)
#define AFX_FASTLINESERIES_H__A87B9DD1_DD80_4E30_AC50_466D7DE6AAF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CPen1;

/////////////////////////////////////////////////////////////////////////////
// CFastLineSeries wrapper class

class CFastLineSeries : public COleDispatchDriver
{
public:
	CFastLineSeries() {}		// Calls COleDispatchDriver default constructor
	CFastLineSeries(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CFastLineSeries(const CFastLineSeries& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CPen1 GetLinePen();
	long AddRealTime(double X, double Y, LPCTSTR SomeLabel, unsigned long SomeColor);
	BOOL GetDrawAllPoints();
	void SetDrawAllPoints(BOOL bNewValue);
	BOOL GetAutoSizeVertAxis();
	void SetAutoSizeVertAxis(BOOL bNewValue);
	BOOL GetStairs();
	void SetStairs(BOOL bNewValue);
	BOOL GetInvertedStairs();
	void SetInvertedStairs(BOOL bNewValue);
	BOOL GetIgnoreNulls();
	void SetIgnoreNulls(BOOL bNewValue);
	BOOL GetFastPen();
	void SetFastPen(BOOL bNewValue);
	BOOL GetAutoRepaint();
	void SetAutoRepaint(BOOL bNewValue);
	long GetTreatNulls();
	void SetTreatNulls(long nNewValue);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FASTLINESERIES_H__A87B9DD1_DD80_4E30_AC50_466D7DE6AAF1__INCLUDED_)