#if !defined(AFX_SURFACENEARESTTOOL_H__499D9303_8A27_4A97_A301_362E0847AD95__INCLUDED_)
#define AFX_SURFACENEARESTTOOL_H__499D9303_8A27_4A97_A301_362E0847AD95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CSurfaceNearestTool wrapper class

class CSurfaceNearestTool : public COleDispatchDriver
{
public:
	CSurfaceNearestTool() {}		// Calls COleDispatchDriver default constructor
	CSurfaceNearestTool(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CSurfaceNearestTool(const CSurfaceNearestTool& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	VARIANT GetSeries();
	void SetSeries(const VARIANT& newValue);
	unsigned long GetCellColor();
	void SetCellColor(unsigned long newValue);
	unsigned long GetColumnColor();
	void SetColumnColor(unsigned long newValue);
	unsigned long GetRowColor();
	void SetRowColor(unsigned long newValue);
	long GetSelectedCell();
	void SetSelectedCell(long nNewValue);
	long GetRow();
	long GetCol();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SURFACENEARESTTOOL_H__499D9303_8A27_4A97_A301_362E0847AD95__INCLUDED_)
