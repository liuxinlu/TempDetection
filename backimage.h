#if !defined(AFX_BACKIMAGE_H__276233F8_23BB_4B14_BDF4_0FB3A4320F22__INCLUDED_)
#define AFX_BACKIMAGE_H__276233F8_23BB_4B14_BDF4_0FB3A4320F22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CFilterItems;

/////////////////////////////////////////////////////////////////////////////
// CBackImage wrapper class

class CBackImage : public COleDispatchDriver
{
public:
	CBackImage() {}		// Calls COleDispatchDriver default constructor
	CBackImage(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CBackImage(const CBackImage& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CFilterItems GetFilters();
	void LoadImage(LPCTSTR FileName);
	void AssignImage(long ImageHandle);
	void ClearImage();
	BOOL ShowFiltersEditor();
	long GetHandle();
	void SaveToFile(LPCTSTR FileName);
	BOOL GetInside();
	void SetInside(BOOL bNewValue);
	long GetLeft();
	void SetLeft(long nNewValue);
	long GetTop();
	void SetTop(long nNewValue);
	long GetMode();
	void SetMode(long nNewValue);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BACKIMAGE_H__276233F8_23BB_4B14_BDF4_0FB3A4320F22__INCLUDED_)