#if !defined(AFX_SERIESREGIONTOOL_H__C286FC72_93AD_4B47_89C2_DB6BAC8BF27B__INCLUDED_)
#define AFX_SERIESREGIONTOOL_H__C286FC72_93AD_4B47_89C2_DB6BAC8BF27B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CGradient;
class CBrush1;
class CPen1;

/////////////////////////////////////////////////////////////////////////////
// CSeriesRegionTool wrapper class

class CSeriesRegionTool : public COleDispatchDriver
{
public:
	CSeriesRegionTool() {}		// Calls COleDispatchDriver default constructor
	CSeriesRegionTool(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CSeriesRegionTool(const CSeriesRegionTool& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	VARIANT GetSeries();
	void SetSeries(const VARIANT& newValue);
	BOOL GetDrawBehind();
	void SetDrawBehind(BOOL bNewValue);
	CGradient GetGradient();
	double GetLowerBound();
	void SetLowerBound(double newValue);
	double GetOrigin();
	void SetOrigin(double newValue);
	long GetTransparency();
	void SetTransparency(long nNewValue);
	double GetUpperBound();
	void SetUpperBound(double newValue);
	BOOL GetAutoBounds();
	void SetAutoBounds(BOOL bNewValue);
	BOOL GetUseOrigin();
	void SetUseOrigin(BOOL bNewValue);
	CBrush1 GetBrush();
	unsigned long GetColor();
	void SetColor(unsigned long newValue);
	CPen1 GetPen();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERIESREGIONTOOL_H__C286FC72_93AD_4B47_89C2_DB6BAC8BF27B__INCLUDED_)
