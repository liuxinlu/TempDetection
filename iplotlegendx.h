#if !defined(AFX_IPLOTLEGENDX_H__FACAEB2A_C2BE_4604_86E6_6F0FB87796E3__INCLUDED_)
#define AFX_IPLOTLEGENDX_H__FACAEB2A_C2BE_4604_86E6_6F0FB87796E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class COleFont;

/////////////////////////////////////////////////////////////////////////////
// CiPlotLegendX wrapper class

class CiPlotLegendX : public COleDispatchDriver
{
public:
	CiPlotLegendX() {}		// Calls COleDispatchDriver default constructor
	CiPlotLegendX(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CiPlotLegendX(const CiPlotLegendX& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

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
	double GetMarginLeft();
	void SetMarginLeft(double newValue);
	double GetMarginTop();
	void SetMarginTop(double newValue);
	double GetMarginRight();
	void SetMarginRight(double newValue);
	double GetMarginBottom();
	void SetMarginBottom(double newValue);
	unsigned long GetBackGroundColor();
	void SetBackGroundColor(unsigned long newValue);
	BOOL GetBackGroundTransparent();
	void SetBackGroundTransparent(BOOL bNewValue);
	unsigned long GetSelectedItemBackGroundColor();
	void SetSelectedItemBackGroundColor(unsigned long newValue);
	COleFont GetSelectedItemFont();
	void SetSelectedItemFont(LPDISPATCH newValue);
	BOOL GetShowColumnXAxisTitle();
	void SetShowColumnXAxisTitle(BOOL bNewValue);
	BOOL GetShowColumnYAxisTitle();
	void SetShowColumnYAxisTitle(BOOL bNewValue);
	BOOL GetShowColumnMarker();
	void SetShowColumnMarker(BOOL bNewValue);
	BOOL GetShowColumnXValue();
	void SetShowColumnXValue(BOOL bNewValue);
	BOOL GetShowColumnYValue();
	void SetShowColumnYValue(BOOL bNewValue);
	COleFont GetFont();
	void SetFont(LPDISPATCH newValue);
	double GetColumnSpacing();
	void SetColumnSpacing(double newValue);
	double GetRowSpacing();
	void SetRowSpacing(double newValue);
	BOOL GetHorizontal();
	void SetHorizontal(BOOL bNewValue);
	long GetZOrder();
	void SetZOrder(long nNewValue);
	unsigned long GetFontColor();
	void SetFontColor(unsigned long newValue);
	unsigned long GetSelectedItemFontColor();
	void SetSelectedItemFontColor(unsigned long newValue);
	BOOL GetShowColumnLine();
	void SetShowColumnLine(BOOL bNewValue);
	BOOL GetColumnTitlesVisible();
	void SetColumnTitlesVisible(BOOL bNewValue);
	COleFont GetColumnTitlesFont();
	void SetColumnTitlesFont(LPDISPATCH newValue);
	unsigned long GetColumnTitlesFontColor();
	void SetColumnTitlesFontColor(unsigned long newValue);
	BOOL GetEnabled();
	void SetEnabled(BOOL bNewValue);
	BOOL GetPopupEnabled();
	void SetPopupEnabled(BOOL bNewValue);
	long GetWidth();
	long GetHeight();
	BOOL GetShowColumnYMax();
	void SetShowColumnYMax(BOOL bNewValue);
	BOOL GetShowColumnYMin();
	void SetShowColumnYMin(BOOL bNewValue);
	BOOL GetShowColumnYMean();
	void SetShowColumnYMean(BOOL bNewValue);
	double GetChannelNameMaxWidth();
	void SetChannelNameMaxWidth(double newValue);
	CString GetCaptionColumnTitle();
	void SetCaptionColumnTitle(LPCTSTR lpszNewValue);
	CString GetCaptionColumnXAxisTitle();
	void SetCaptionColumnXAxisTitle(LPCTSTR lpszNewValue);
	CString GetCaptionColumnYAxisTitle();
	void SetCaptionColumnYAxisTitle(LPCTSTR lpszNewValue);
	CString GetCaptionColumnXValue();
	void SetCaptionColumnXValue(LPCTSTR lpszNewValue);
	CString GetCaptionColumnYValue();
	void SetCaptionColumnYValue(LPCTSTR lpszNewValue);
	CString GetCaptionColumnYMax();
	void SetCaptionColumnYMax(LPCTSTR lpszNewValue);
	CString GetCaptionColumnYMin();
	void SetCaptionColumnYMin(LPCTSTR lpszNewValue);
	CString GetCaptionColumnYMean();
	void SetCaptionColumnYMean(LPCTSTR lpszNewValue);
	long GetWrapColDesiredCount();
	void SetWrapColDesiredCount(long nNewValue);
	BOOL GetWrapColAutoCountEnabled();
	void SetWrapColAutoCountEnabled(BOOL bNewValue);
	long GetWrapColAutoCountMax();
	void SetWrapColAutoCountMax(long nNewValue);
	double GetWrapColSpacingMin();
	void SetWrapColSpacingMin(double newValue);
	BOOL GetWrapColSpacingAuto();
	void SetWrapColSpacingAuto(BOOL bNewValue);
	long GetWrapRowDesiredCount();
	void SetWrapRowDesiredCount(long nNewValue);
	BOOL GetWrapRowAutoCountEnabled();
	void SetWrapRowAutoCountEnabled(BOOL bNewValue);
	long GetWrapRowAutoCountMax();
	void SetWrapRowAutoCountMax(long nNewValue);
	double GetWrapRowSpacingMin();
	void SetWrapRowSpacingMin(double newValue);
	BOOL GetWrapRowSpacingAuto();
	void SetWrapRowSpacingAuto(BOOL bNewValue);
	BOOL GetUserSelected();
	void SetUserSelected(BOOL bNewValue);
	long GetChannelNameColorStyle();
	void SetChannelNameColorStyle(long nNewValue);
	long GetViewStartIndex();
	void SetViewStartIndex(long nNewValue);
	long GetViewStopIndex();
	BOOL HitTest(long X, long Y);
	void DoEditMenuItemClick();
	long GetLineColumnWidth();
	void SetLineColumnWidth(long nNewValue);
	long GetLineColumnHeight();
	void SetLineColumnHeight(long nNewValue);
	BOOL GetUserCanEdit();
	void SetUserCanEdit(BOOL bNewValue);
	BOOL GetCanFocus();
	void SetCanFocus(BOOL bNewValue);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPLOTLEGENDX_H__FACAEB2A_C2BE_4604_86E6_6F0FB87796E3__INCLUDED_)
