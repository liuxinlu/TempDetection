#if !defined(AFX_FRAMEDBORDER_H__D4413923_2779_4119_A704_CFE82906CCA3__INCLUDED_)
#define AFX_FRAMEDBORDER_H__D4413923_2779_4119_A704_CFE82906CCA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CBrush1;
class CFrameBrush;
class CTeeShadow;

/////////////////////////////////////////////////////////////////////////////
// CFramedBorder wrapper class

class CFramedBorder : public COleDispatchDriver
{
public:
	CFramedBorder() {}		// Calls COleDispatchDriver default constructor
	CFramedBorder(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CFramedBorder(const CFramedBorder& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CBrush1 GetBrush();
	BOOL GetCircled();
	void SetCircled(BOOL bNewValue);
	CFrameBrush GetInnerBrush();
	CFrameBrush GetMiddleBrush();
	CFrameBrush GetOuterBrush();
	CTeeShadow GetShadow();
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	long GetWidth();
	void SetWidth(long nNewValue);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRAMEDBORDER_H__D4413923_2779_4119_A704_CFE82906CCA3__INCLUDED_)
