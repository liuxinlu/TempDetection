// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "glposition.h"


/////////////////////////////////////////////////////////////////////////////
// CGLPosition properties

/////////////////////////////////////////////////////////////////////////////
// CGLPosition operations

double CGLPosition::GetX()
{
	double result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CGLPosition::SetX(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double CGLPosition::GetY()
{
	double result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CGLPosition::SetY(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0xca, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double CGLPosition::GetZ()
{
	double result;
	InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CGLPosition::SetZ(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0xcb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}
