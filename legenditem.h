#if !defined(AFX_LEGENDITEM_H__68AFFD28_BE64_4E64_BA4E_B5E6BBE0F4DF__INCLUDED_)
#define AFX_LEGENDITEM_H__68AFFD28_BE64_4E64_BA4E_B5E6BBE0F4DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CLegendItem wrapper class

class CLegendItem : public COleDispatchDriver
{
public:
	CLegendItem() {}		// Calls COleDispatchDriver default constructor
	CLegendItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CLegendItem(const CLegendItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	// method 'GetSymbolRect' not emitted because of invalid return type or parameter type
	// method 'SetSymbolRect' not emitted because of invalid return type or parameter type
	long GetAlign();
	long GetLeft();
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	long GetTop();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEGENDITEM_H__68AFFD28_BE64_4E64_BA4E_B5E6BBE0F4DF__INCLUDED_)
