// PlayerInfo.h: interface for the CPlayerInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLAYERINFO_H__B612F342_424B_11D7_8358_0050BA26DFA6__INCLUDED_)
#define AFX_PLAYERINFO_H__B612F342_424B_11D7_8358_0050BA26DFA6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPlayerInfo : public CObject
{
DECLARE_SERIAL(CPlayerInfo)
public:
	int Charisma;
	int Age;
	CString Description;
	int Wisdom;
	int Intelligence;
	int Constitution;
	int Dexterity;
	CString Alignment;
	CString Deity;
	CString Familiar;
	CString Race;
	int Strength;
	int head;
	CString Class;
	CString Gender;
	CString CharacterName;
	CPlayerInfo();
	CPlayerInfo& operator=(const CPlayerInfo& obj2);
	CPlayerInfo(const CPlayerInfo& obj2);

	virtual ~CPlayerInfo();
	virtual void Serialize(CArchive& ar);

};

#endif // !defined(AFX_PLAYERINFO_H__B612F342_424B_11D7_8358_0050BA26DFA6__INCLUDED_)
