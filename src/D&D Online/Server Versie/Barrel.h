// Barrel.h: interface for the CBarrel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BARREL_H__56DEBF8E_8DDE_4D00_AEA9_6DE8F736E3AD__INCLUDED_)
#define AFX_BARREL_H__56DEBF8E_8DDE_4D00_AEA9_6DE8F736E3AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBarrel : public CObject
{
public:
	CString data;
	UINT type;
	CBarrel();
	CBarrel(const CBarrel& obj2); //copy constructor

	CBarrel &operator=(const CBarrel& obj2);
	virtual ~CBarrel();

};

#endif // !defined(AFX_BARREL_H__56DEBF8E_8DDE_4D00_AEA9_6DE8F736E3AD__INCLUDED_)
