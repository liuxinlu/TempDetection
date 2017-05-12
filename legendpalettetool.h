#if !defined(AFX_LEGENDPALETTETOOL_H__54A73B65_0785_4B00_880F_F1185ECC8854__INCLUDED_)
#define AFX_LEGENDPALETTETOOL_H__54A73B65_0785_4B00_880F_F1185ECC8854__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CChartHiddenPen;
class CPen1;
class CGradient;
class CTeeShadow;

/////////////////////////////////////////////////////////////////////////////
// CLegendPaletteTool wrapper class

class CLegendPaletteTool : public COleDispatchDriver
{
public:
	CLegendPaletteTool() {}		// Calls COleDispatchDriver default constructor
	CLegendPaletteTool(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CLegendPaletteTool(const CLegendPaletteTool& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	VARIANT GetSeries();
	void SetSeries(const VARIANT& newValue);
	CChartHiddenPen GetBorder();
	long GetHeight();
	void SetHeight(long nNewValue);
	BOOL GetInverted();
	void SetInverted(BOOL bNewValue);
	long GetLeft();
	void SetLeft(long nNewValue);
	BOOL GetSmooth();
	void SetSmooth(BOOL bNewValue);
	long GetTop();
	void SetTop(long nNewValue);
	BOOL GetTransparent();
	void SetTransparent(BOOL bNewValue);
	BOOL GetVertical();
	void SetVertical(BOOL bNewValue);
	long GetWidth();
	void SetWidth(long nNewValue);
	long GetAxis();
	void SetAxis(long nNewValue);
	long GetPositionUnits();
	void SetPositionUnits(long nNewValue);
	CPen1 GetPen();
	unsigned long GetColor();
	void SetColor(unsigned long newValue);
	CGradient GetGradient();
	CTeeShadow GetShadow();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEGENDPALETTETOOL_H__54A73B65_0785_4B00_880F_F1185ECC8854__INCLUDED_)