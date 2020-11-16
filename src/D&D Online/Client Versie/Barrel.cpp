// Barrel.cpp: implementation of the CBarrel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DnD.h"
#include "Barrel.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBarrel::CBarrel()
{

}

CBarrel::~CBarrel()
{

}

CBarrel& CBarrel::operator =(const CBarrel& obj2)
{
	data=obj2.data;
	type=obj2.type;
	return *this;
}


CBarrel::CBarrel(const CBarrel& obj2)
{
	data=obj2.data;
	type=obj2.type;
}
