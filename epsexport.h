#if !defined(AFX_EPSEXPORT_H__EA8D908D_DC61_40A6_A31D_D3D5B6C2E9F4__INCLUDED_)
#define AFX_EPSEXPORT_H__EA8D908D_DC61_40A6_A31D_D3D5B6C2E9F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CEPSExport wrapper class

class CEPSExport : public COleDispatchDriver
{
public:
	CEPSExport() {}		// Calls COleDispatchDriver default constructor
	CEPSExport(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CEPSExport(const CEPSExport& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetWidth();
	void SetWidth(long nNewValue);
	long GetHeight();
	void SetHeight(long nNewValue);
	void SaveToFile(LPCTSTR FileName);
	VARIANT SaveToStream();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EPSEXPORT_H__EA8D908D_DC61_40A6_A31D_D3D5B6C2E9F4__INCLUDED_)
