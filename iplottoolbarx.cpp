// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "iplottoolbarx.h"


/////////////////////////////////////////////////////////////////////////////
// CiPlotToolBarX properties

/////////////////////////////////////////////////////////////////////////////
// CiPlotToolBarX operations

CString CiPlotToolBarX::GetName()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CiPlotToolBarX::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL CiPlotToolBarX::GetVisible()
{
	BOOL result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CiPlotToolBarX::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

double CiPlotToolBarX::GetStartPercent()
{
	double result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CiPlotToolBarX::SetStartPercent(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double CiPlotToolBarX::GetStopPercent()
{
	double result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CiPlotToolBarX::SetStopPercent(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL CiPlotToolBarX::GetShowCopyButton()
{
	BOOL result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CiPlotToolBarX::SetShowCopyButton(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CiPlotToolBarX::GetShowSaveButton()
{
	BOOL result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CiPlotToolBarX::SetShowSaveButton(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CiPlotToolBarX::GetShowPrintButton()
{
	BOOL result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CiPlotToolBarX::SetShowPrintButton(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CiPlotToolBarX::GetShowEditButton()
{
	BOOL result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CiPlotToolBarX::SetShowEditButton(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CiPlotToolBarX::GetZOrder()
{
	long result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CiPlotToolBarX::SetZOrder(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CiPlotToolBarX::GetHorizontal()
{
	BOOL result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CiPlotToolBarX::SetHorizontal(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CiPlotToolBarX::GetShowResumeButton()
{
	BOOL result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CiPlotToolBarX::SetShowResumeButton(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CiPlotToolBarX::GetShowPauseButton()
{
	BOOL result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CiPlotToolBarX::SetShowPauseButton(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CiPlotToolBarX::GetShowAxesModeButtons()
{
	BOOL result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CiPlotToolBarX::SetShowAxesModeButtons(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CiPlotToolBarX::GetShowZoomInOutButtons()
{
	BOOL result;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CiPlotToolBarX::SetShowZoomInOutButtons(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CiPlotToolBarX::GetShowZoomBoxButton()
{
	BOOL result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CiPlotToolBarX::SetShowZoomBoxButton(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CiPlotToolBarX::GetShowCursorButton()
{
	BOOL result;
	InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CiPlotToolBarX::SetShowCursorButton(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void CiPlotToolBarX::TurnOffCursor()
{
	InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL CiPlotToolBarX::GetZoomBoxActive()
{
	BOOL result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CiPlotToolBarX::GetCursorActive()
{
	BOOL result;
	InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CiPlotToolBarX::DoButtonClickResume()
{
	InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CiPlotToolBarX::DoButtonClickPause()
{
	InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CiPlotToolBarX::DoButtonClickScrollAxesMode()
{
	InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CiPlotToolBarX::DoButtonClickZoomAxesMode()
{
	InvokeHelper(0x17, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CiPlotToolBarX::DoButtonClickZoomBox()
{
	InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CiPlotToolBarX::DoButtonClickZoomOut()
{
	InvokeHelper(0x19, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CiPlotToolBarX::DoButtonClickZoomIn()
{
	InvokeHelper(0x1a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CiPlotToolBarX::DoButtonClickCursor()
{
	InvokeHelper(0x1b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CiPlotToolBarX::DoButtonClickEdit()
{
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CiPlotToolBarX::DoButtonClickCopy()
{
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CiPlotToolBarX::DoButtonClickSave()
{
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CiPlotToolBarX::DoButtonClickPrint()
{
	InvokeHelper(0x1f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL CiPlotToolBarX::GetEnabled()
{
	BOOL result;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CiPlotToolBarX::SetEnabled(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x20, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CiPlotToolBarX::GetPopupEnabled()
{
	BOOL result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CiPlotToolBarX::SetPopupEnabled(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x21, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

double CiPlotToolBarX::GetZoomInOutFactor()
{
	double result;
	InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CiPlotToolBarX::SetZoomInOutFactor(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x22, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long CiPlotToolBarX::GetWidth()
{
	long result;
	InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CiPlotToolBarX::GetHeight()
{
	long result;
	InvokeHelper(0x24, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CiPlotToolBarX::GetShowSelectButton()
{
	BOOL result;
	InvokeHelper(0x25, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CiPlotToolBarX::SetShowSelectButton(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x25, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void CiPlotToolBarX::DoButtonClickSelect()
{
	InvokeHelper(0x26, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL CiPlotToolBarX::GetSelectActive()
{
	BOOL result;
	InvokeHelper(0x27, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long CiPlotToolBarX::GetLayer()
{
	long result;
	InvokeHelper(0x28, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CiPlotToolBarX::SetLayer(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x28, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CiPlotToolBarX::GetFlatButtons()
{
	BOOL result;
	InvokeHelper(0x29, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CiPlotToolBarX::SetFlatButtons(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x29, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CiPlotToolBarX::GetSmallButtons()
{
	BOOL result;
	InvokeHelper(0x2a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CiPlotToolBarX::SetSmallButtons(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x2a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CiPlotToolBarX::GetFlatBorder()
{
	BOOL result;
	InvokeHelper(0x2b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CiPlotToolBarX::SetFlatBorder(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x2b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CiPlotToolBarX::GetUserSelected()
{
	BOOL result;
	InvokeHelper(0x2c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CiPlotToolBarX::SetUserSelected(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x2c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CiPlotToolBarX::GetShowPreviewButton()
{
	BOOL result;
	InvokeHelper(0x2d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CiPlotToolBarX::SetShowPreviewButton(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x2d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void CiPlotToolBarX::DoButtonClickPreview()
{
	InvokeHelper(0x2e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL CiPlotToolBarX::HitTest(long X, long Y)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x320, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		X, Y);
	return result;
}

void CiPlotToolBarX::DoEditMenuItemClick()
{
	InvokeHelper(0x2f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL CiPlotToolBarX::GetUserCanEdit()
{
	BOOL result;
	InvokeHelper(0x30, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CiPlotToolBarX::SetUserCanEdit(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x30, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CiPlotToolBarX::GetCanFocus()
{
	BOOL result;
	InvokeHelper(0x31, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CiPlotToolBarX::SetCanFocus(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x31, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}
