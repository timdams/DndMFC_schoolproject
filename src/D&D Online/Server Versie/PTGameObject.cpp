// PTGameObject.cpp: implementation of the CPTGameObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PTGameObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CPTGameObject,CObject,1)

CPTGameObject::CPTGameObject()
{
 m_nOnSketch=FALSE;
 m_nObjType=-1;
 m_nFlags=-1;
}

CPTGameObject::~CPTGameObject()
{

}

CPTGameObject::CPTGameObject(const CPTGameObject& obj2)
{
		inside_color=obj2.inside_color;
	outside_color=obj2.outside_color;
	m_nOnSketch=obj2.m_nOnSketch;
	m_nFlags=obj2.m_nFlags;
	m_nObjType=obj2.m_nObjType;
	m_ptPos1=obj2.m_ptPos1;
	m_ptPos2=obj2.m_ptPos2;
//	m_ptPos3=obj2.m_ptPos3;
}
CPTGameObject& CPTGameObject::operator=(const CPTGameObject& obj2)
{
	inside_color=obj2.inside_color;
	outside_color=obj2.outside_color;
	m_nOnSketch=obj2.m_nOnSketch;
	m_nFlags=obj2.m_nFlags;
	m_nObjType=obj2.m_nObjType;
	m_ptPos1=obj2.m_ptPos1;
	m_ptPos2=obj2.m_ptPos2;
//	m_ptPos3=obj2.m_ptPos3;
	return *this;
}

void CPTGameObject::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
		if(ar.IsStoring())
		{
			ar << m_nObjType;
			if(m_nObjType==LINE || m_nObjType==CIRCLE)
			{
				ar << inside_color;
				ar << outside_color;
				ar << m_ptPos2;
			}
			ar << m_nOnSketch;
			ar << m_nFlags;
			
			ar << m_ptPos1;
			
		//	ar << m_ptPos3;
		}
		else
		{
			ar >> m_nObjType;
			if(m_nObjType==LINE || m_nObjType==CIRCLE)
			{
				ar >> inside_color;
				ar >> outside_color;
				ar >> m_ptPos2;
			}
			ar >> m_nOnSketch;
			ar >> m_nFlags;
			
			ar >> m_ptPos1;
			
		//	ar >> m_ptPos3;
		}
}