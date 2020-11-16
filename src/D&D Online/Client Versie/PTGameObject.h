// PTGameObject.h: interface for the CPTGameObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PTGAMEOBJECT_H__96FA6FE0_4727_11D6_B526_E4B4B57D131D__INCLUDED_)
#define AFX_PTGAMEOBJECT_H__96FA6FE0_4727_11D6_B526_E4B4B57D131D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "defines.h"

class CPTGameObject : public CObject
{
DECLARE_SERIAL(CPTGameObject)
public:
	
	//Place members that are often used together near each other in 
	//the structure declaration. This improves the chances of both items
	//being cached on the first cache miss.


	
	int m_nObjType; 
	int m_nOnSketch;
	CPoint m_ptPos1;
	int m_nFlags; 
	CPoint m_ptPos2;
//	CPoint m_ptPos3; //Unused (wanna go 3D? :p)
	COLORREF inside_color;		
	COLORREF outside_color;



	CPTGameObject& operator=(const CPTGameObject& obj2);
	CPTGameObject(const CPTGameObject& obj2);

	CPTGameObject();
	virtual ~CPTGameObject();
	virtual void Serialize(CArchive& ar);
};

#endif // !defined(AFX_PTGAMEOBJECT_H__96FA6FE0_4727_11D6_B526_E4B4B57D131D__INCLUDED_)
