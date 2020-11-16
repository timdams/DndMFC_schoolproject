// Profile.cpp: implementation of the CProfile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Profile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CProfile,CObject,1)

CProfile::CProfile()
{

}

CProfile::~CProfile()
{

}

CProfile::CProfile(const CProfile& obj2)
{
	ServerIP=obj2.ServerIP;
	ServerName=obj2.ServerName;
	UserName=obj2.UserName;
	UserPass=obj2.UserPass;

}
CProfile& CProfile::operator=(const CProfile& obj2)
{
	ServerIP=obj2.ServerIP;
	ServerName=obj2.ServerName;
	UserName=obj2.UserName;
	UserPass=obj2.UserPass;
	return *this;
}

void CProfile::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
		if(ar.IsStoring())
		{
			ar << ServerIP;
			ar << ServerName;
			ar << UserName;
			ar << UserPass;

		}
		else
		{
			ar >> ServerIP;
			ar >> ServerName;
			ar >> UserName;
			ar >> UserPass;
		}
}
