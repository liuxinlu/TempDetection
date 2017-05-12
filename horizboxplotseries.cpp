// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "horizboxplotseries.h"

// Dispatch interfaces referenced by this interface
#include "Pointer.h"
#include "pen.h"


/////////////////////////////////////////////////////////////////////////////
// CHorizBoxPlotSeries properties

/////////////////////////////////////////////////////////////////////////////
// CHorizBoxPlotSeries operations

CPointer CHorizBoxPlotSeries::GetPointer()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CPointer(pDispatch);
}

BOOL CHorizBoxPlotSeries::GetDark3D()
{
	BOOL result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CHorizBoxPlotSeries::SetDark3D(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CHorizBoxPlotSeries::GetTransparency()
{
	long result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CHorizBoxPlotSeries::SetTransparency(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CHorizBoxPlotSeries::GetFastPoint()
{
	BOOL result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CHorizBoxPlotSeries::SetFastPoint(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xca, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CHorizBoxPlotSeries::GetTreatNulls()
{
	long result;
	InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CHorizBoxPlotSeries::SetTreatNulls(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xcb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CPointer CHorizBoxPlotSeries::GetExtrOut()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CPointer(pDispatch);
}

CPen1 CHorizBoxPlotSeries::GetMedianPen()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CPen1(pDispatch);
}

CPointer CHorizBoxPlotSeries::GetMildOut()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CPointer(pDispatch);
}

double CHorizBoxPlotSeries::GetPosition()
{
	double result;
	InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CHorizBoxPlotSeries::SetPosition(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double CHorizBoxPlotSeries::GetWhiskerLength()
{
	double result;
	InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CHorizBoxPlotSeries::SetWhiskerLength(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CPen1 CHorizBoxPlotSeries::GetWhiskerPen()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CPen1(pDispatch);
}

CPointer CHorizBoxPlotSeries::GetBox()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CPointer(pDispatch);
}

double CHorizBoxPlotSeries::GetMedian()
{
	double result;
	InvokeHelper(0x191, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CHorizBoxPlotSeries::SetMedian(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x191, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double CHorizBoxPlotSeries::GetQuartile1()
{
	double result;
	InvokeHelper(0x192, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CHorizBoxPlotSeries::SetQuartile1(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x192, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double CHorizBoxPlotSeries::GetQuartile3()
{
	double result;
	InvokeHelper(0x193, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CHorizBoxPlotSeries::SetQuartile3(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x193, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double CHorizBoxPlotSeries::GetInnerFence1()
{
	double result;
	InvokeHelper(0x194, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CHorizBoxPlotSeries::SetInnerFence1(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x194, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double CHorizBoxPlotSeries::GetInnerFence3()
{
	double result;
	InvokeHelper(0x195, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CHorizBoxPlotSeries::SetInnerFence3(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x195, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double CHorizBoxPlotSeries::GetOuterFence1()
{
	double result;
	InvokeHelper(0x196, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CHorizBoxPlotSeries::SetOuterFence1(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x196, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double CHorizBoxPlotSeries::GetOuterFence3()
{
	double result;
	InvokeHelper(0x197, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CHorizBoxPlotSeries::SetOuterFence3(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x197, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double CHorizBoxPlotSeries::GetAdjacentPoint1()
{
	double result;
	InvokeHelper(0x198, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CHorizBoxPlotSeries::SetAdjacentPoint1(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x198, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double CHorizBoxPlotSeries::GetAdjacentPoint3()
{
	double result;
	InvokeHelper(0x199, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CHorizBoxPlotSeries::SetAdjacentPoint3(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x199, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL CHorizBoxPlotSeries::GetUseCustomValues()
{
	BOOL result;
	InvokeHelper(0x19a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CHorizBoxPlotSeries::SetUseCustomValues(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x19a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

double CHorizBoxPlotSeries::MaxYValue()
{
	double result;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
	return result;
}

double CHorizBoxPlotSeries::MinYValue()
{
	double result;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
	return result;
}
