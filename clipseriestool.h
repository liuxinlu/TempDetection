#if !defined(AFX_CLIPSERIESTOOL_H__FF551A1E_B8C8_4F89_BD19_9148F613EC71__INCLUDED_)
#define AFX_CLIPSERIESTOOL_H__FF551A1E_B8C8_4F89_BD19_9148F613EC71__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CClipSeriesTool wrapper class

class CClipSeriesTool : public COleDispatchDriver
{
public:
	CClipSeriesTool() {}		// Calls COleDispatchDriver default constructor
	CClipSeriesTool(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CClipSeriesTool(const CClipSeriesTool& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	VARIANT GetSeries();
	void SetSeries(const VARIANT& newValue);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIPSERIESTOOL_H__FF551A1E_B8C8_4F89_BD19_9148F613EC71__INCLUDED_)
