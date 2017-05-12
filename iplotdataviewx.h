#if !defined(AFX_IPLOTDATAVIEWX_H__8B89CE50_3D8F_4FEF_A574_D9A5383A1C9D__INCLUDED_)
#define AFX_IPLOTDATAVIEWX_H__8B89CE50_3D8F_4FEF_A574_D9A5383A1C9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CiPlotDataViewX wrapper class

class CiPlotDataViewX : public COleDispatchDriver
{
public:
	CiPlotDataViewX() {}		// Calls COleDispatchDriver default constructor
	CiPlotDataViewX(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CiPlotDataViewX(const CiPlotDataViewX& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	double GetStartPercent();
	void SetStartPercent(double newValue);
	double GetStopPercent();
	void SetStopPercent(double newValue);
	CString GetTitle();
	void SetTitle(LPCTSTR lpszNewValue);
	CString GetGridXAxisName();
	void SetGridXAxisName(LPCTSTR lpszNewValue);
	CString GetGridYAxisName();
	void SetGridYAxisName(LPCTSTR lpszNewValue);
	BOOL GetGridShow();
	void SetGridShow(BOOL bNewValue);
	unsigned long GetGridLineColor();
	void SetGridLineColor(unsigned long newValue);
	BOOL GetGridLineShowLeft();
	void SetGridLineShowLeft(BOOL bNewValue);
	BOOL GetGridLineShowRight();
	void SetGridLineShowRight(BOOL bNewValue);
	BOOL GetGridLineShowTop();
	void SetGridLineShowTop(BOOL bNewValue);
	BOOL GetGridLineShowBottom();
	void SetGridLineShowBottom(BOOL bNewValue);
	BOOL GetGridLineShowXMajors();
	void SetGridLineShowXMajors(BOOL bNewValue);
	BOOL GetGridLineShowXMinors();
	void SetGridLineShowXMinors(BOOL bNewValue);
	BOOL GetGridLineShowYMajors();
	void SetGridLineShowYMajors(BOOL bNewValue);
	BOOL GetGridLineShowYMinors();
	void SetGridLineShowYMinors(BOOL bNewValue);
	long GetGridLineMajorStyle();
	void SetGridLineMajorStyle(long nNewValue);
	long GetGridLineMinorStyle();
	void SetGridLineMinorStyle(long nNewValue);
	BOOL GetBackGroundTransparent();
	void SetBackGroundTransparent(BOOL bNewValue);
	unsigned long GetBackGroundColor();
	void SetBackGroundColor(unsigned long newValue);
	BOOL GetEnabled();
	void SetEnabled(BOOL bNewValue);
	BOOL GetPopupEnabled();
	void SetPopupEnabled(BOOL bNewValue);
	long GetWidth();
	long GetHeight();
	BOOL GetGridLineXMajorCustom();
	void SetGridLineXMajorCustom(BOOL bNewValue);
	unsigned long GetGridLineXMajorColor();
	void SetGridLineXMajorColor(unsigned long newValue);
	long GetGridLineXMajorWidth();
	void SetGridLineXMajorWidth(long nNewValue);
	long GetGridLineXMajorStyle();
	void SetGridLineXMajorStyle(long nNewValue);
	BOOL GetGridLineXMinorCustom();
	void SetGridLineXMinorCustom(BOOL bNewValue);
	unsigned long GetGridLineXMinorColor();
	void SetGridLineXMinorColor(unsigned long newValue);
	long GetGridLineXMinorWidth();
	void SetGridLineXMinorWidth(long nNewValue);
	long GetGridLineXMinorStyle();
	void SetGridLineXMinorStyle(long nNewValue);
	BOOL GetGridLineYMajorCustom();
	void SetGridLineYMajorCustom(BOOL bNewValue);
	unsigned long GetGridLineYMajorColor();
	void SetGridLineYMajorColor(unsigned long newValue);
	long GetGridLineYMajorWidth();
	void SetGridLineYMajorWidth(long nNewValue);
	long GetGridLineYMajorStyle();
	void SetGridLineYMajorStyle(long nNewValue);
	BOOL GetGridLineYMinorCustom();
	void SetGridLineYMinorCustom(BOOL bNewValue);
	unsigned long GetGridLineYMinorColor();
	void SetGridLineYMinorColor(unsigned long newValue);
	long GetGridLineYMinorWidth();
	void SetGridLineYMinorWidth(long nNewValue);
	long GetGridLineYMinorStyle();
	void SetGridLineYMinorStyle(long nNewValue);
	long GetLayer();
	void SetLayer(long nNewValue);
	double PixelsXToPositionPercent(long Value);
	double PixelsYToPositionPercent(long Value);
	long PositionPercentToPixelsX(double Value);
	long PositionPercentToPixelsY(double Value);
	BOOL GetUserSelected();
	void SetUserSelected(BOOL bNewValue);
	BOOL GetAxesControlEnabled();
	void SetAxesControlEnabled(BOOL bNewValue);
	long GetAxesControlWheelStyle();
	void SetAxesControlWheelStyle(long nNewValue);
	long GetAxesControlMouseStyle();
	void SetAxesControlMouseStyle(long nNewValue);
	BOOL HitTest(long X, long Y);
	void DoEditMenuItemClick();
	BOOL GetUserCanEdit();
	void SetUserCanEdit(BOOL bNewValue);
	BOOL GetCanFocus();
	void SetCanFocus(BOOL bNewValue);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPLOTDATAVIEWX_H__8B89CE50_3D8F_4FEF_A574_D9A5383A1C9D__INCLUDED_)