#if !defined(AFX_POINTARRAY_H__A1CC1A63_550C_40D2_8AEE_160F8CBE5DD6__INCLUDED_)
#define AFX_POINTARRAY_H__A1CC1A63_550C_40D2_8AEE_160F8CBE5DD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CTeePoint2D;

/////////////////////////////////////////////////////////////////////////////
// CPointArray wrapper class

class CPointArray : public COleDispatchDriver
{
public:
	CPointArray() {}		// Calls COleDispatchDriver default constructor
	CPointArray(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CPointArray(const CPointArray& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	CTeePoint2D GetItem(long Index);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POINTARRAY_H__A1CC1A63_550C_40D2_8AEE_160F8CBE5DD6__INCLUDED_)
