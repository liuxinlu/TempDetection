#if !defined(AFX_WALLS_H__8251A375_7915_4ABA_9122_9498F8E9FDF0__INCLUDED_)
#define AFX_WALLS_H__8251A375_7915_4ABA_9122_9498F8E9FDF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CWall;

/////////////////////////////////////////////////////////////////////////////
// CWalls wrapper class

class CWalls : public COleDispatchDriver
{
public:
	CWalls() {}		// Calls COleDispatchDriver default constructor
	CWalls(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CWalls(const CWalls& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CWall GetBottom();
	CWall GetLeft();
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	unsigned long GetBackColor();
	void SetBackColor(unsigned long newValue);
	CWall GetBack();
	CWall GetRight();
	void SetSize(long nNewValue);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WALLS_H__8251A375_7915_4ABA_9122_9498F8E9FDF0__INCLUDED_)
