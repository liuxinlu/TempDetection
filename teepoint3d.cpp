// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "teepoint3d.h"


/////////////////////////////////////////////////////////////////////////////
// CTeePoint3D properties

/////////////////////////////////////////////////////////////////////////////
// CTeePoint3D operations

double CTeePoint3D::GetX()
{
	double result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CTeePoint3D::SetX(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double CTeePoint3D::GetY()
{
	double result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CTeePoint3D::SetY(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double CTeePoint3D::GetZ()
{
	double result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CTeePoint3D::SetZ(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}
