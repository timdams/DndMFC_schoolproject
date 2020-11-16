// PlayerInfo.cpp: implementation of the CPlayerInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DnD.h"
#include "PlayerInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CPlayerInfo,CObject,1)

CPlayerInfo::CPlayerInfo()
{

}


CPlayerInfo::~CPlayerInfo()
{

}

void CPlayerInfo::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
		if(ar.IsStoring())
		{
			ar << Age;
			ar << Alignment;
			ar << CharacterName;
			ar << Charisma;
			ar << Class;
			ar << Constitution;
			ar << Deity;
			ar << Description;
			ar << Dexterity;
			ar << Familiar ;
			ar << Gender ;
			ar << head;
			ar << Intelligence;
			ar << Race;
			ar << Strength;
			ar << Wisdom;
		}
		else
		{
			ar >>Age;
			ar >>Alignment;
			ar >>CharacterName;
			ar >>Charisma;
			ar >>Class;
			ar >>Constitution;
			ar >>Deity;
			ar >>Description;
			ar >>Dexterity;
			ar >>Familiar ;
			ar >>Gender ;
			ar >>head;
			ar >>Intelligence;
			ar >>Race;
			ar >>Strength;
			ar >>Wisdom;
			//ook in copy constructor aanpassen!!!
		}
}


CPlayerInfo::CPlayerInfo(const CPlayerInfo& obj2)
{
	Age=obj2.Age;
	Alignment=obj2.Alignment;
	CharacterName=obj2.CharacterName;
	Charisma=obj2.Charisma;
	Class=obj2.Class;
	Constitution=obj2.Constitution;
	Deity=obj2.Deity;
	Description=obj2.Description;
	Dexterity=obj2.Dexterity;
	Familiar=obj2.Familiar;
	Gender=obj2.Gender;
	head=obj2.head;
	Intelligence=obj2.Intelligence;
	Race=obj2.Race;
	Strength=obj2.Strength;
	Wisdom=obj2.Wisdom;
}
CPlayerInfo& CPlayerInfo::operator=(const CPlayerInfo& obj2)
{
	Age=obj2.Age;
	Alignment=obj2.Alignment;
	CharacterName=obj2.CharacterName;
	Charisma=obj2.Charisma;
	Class=obj2.Class;
	Constitution=obj2.Constitution;
	Deity=obj2.Deity;
	Description=obj2.Description;
	Dexterity=obj2.Dexterity;
	Familiar=obj2.Familiar;
	Gender=obj2.Gender;
	head=obj2.head;
	Intelligence=obj2.Intelligence;
	Race=obj2.Race;
	Strength=obj2.Strength;
	Wisdom=obj2.Wisdom;
	return *this;
}
