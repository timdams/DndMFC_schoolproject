// Profile.h: interface for the CProfile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_Profile_H__96FA6FE0_4727_11D6_B526_E4B4B57D131D__INCLUDED_)
#define AFX_Profile_H__96FA6FE0_4727_11D6_B526_E4B4B57D131D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CProfile : public CObject
{
DECLARE_SERIAL(CProfile)
public:

	
	CString ServerIP;
	CString UserName;
	CString UserPass;
	CString ServerName;

	CProfile& operator=(const CProfile& obj2);
	CProfile(const CProfile& obj2);

	CProfile();
	virtual ~CProfile();
	virtual void Serialize(CArchive& ar);
};

#endif // !defined(AFX_Profile_H__96FA6FE0_4727_11D6_B526_E4B4B57D131D__INCLUDED_)
