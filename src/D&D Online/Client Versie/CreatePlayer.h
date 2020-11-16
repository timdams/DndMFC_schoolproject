#if !defined(AFX_CREATEPLAYER_H__B612F343_424B_11D7_8358_0050BA26DFA6__INCLUDED_)
#define AFX_CREATEPLAYER_H__B612F343_424B_11D7_8358_0050BA26DFA6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CreatePlayer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCreatePlayer dialog
#include "DndHeadMenu.h"
#include "PlayerInfo.h"
class CCreatePlayer : public CDialog
{
// Construction
public:
	int MaxHeadBitmaps;
	CString PortraitsPath;
	CString DescGenerator();
	CString NameGenerator(int randgetal);
	CStringArray ForbiddenNames;
	bool Generated;
	bool AssignCombatBonusses();
	bool AssignSaves();
	bool AssignHitPoints(int con);
	bool AssignRacialAbilities(int array[]);
	bool AssignAbilities(int array[]);
	void BubbleSort(int array[],int size);
	int GetAbilityModifier(int ability);
	int UCanGenerate;
	int DieRoll(int sides);
	int head;
	CPlayerInfo ThePlayer;
	CCreatePlayer(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCreatePlayer)
	enum { IDD = IDD_DLGCREATEPLAYER };
	CComboBox	m_deity;
	CComboBox	m_alignment;
	CComboBox	m_familiar;
	CComboBox	m_race;
	CComboBox	m_class;
	CComboBox	m_gender;
	CString	CharacterName;
	UINT	m_charisma;
	UINT	m_wisdom;
	UINT	m_strength;
	UINT	m_intelligence;
	UINT	m_dexterity;
	UINT	m_constitution;
	int		m_hitpoints;
	int		m_ac;
	int		m_will;
	int		m_reflex;
	int		m_fortitude;
	int		m_initiative;
	int		m_ranged;
	int		m_melee;
	int		m_age;
	CString	m_description;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreatePlayer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCreatePlayer)
	afx_msg void OnBtnportrait();
	afx_msg void OnGenstats();
	afx_msg void OnCloseupClass();
	afx_msg void OnCloseupRace();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeClass();
	afx_msg void OnSelchangeRace();
	afx_msg void OnChangeCharname();
	virtual void OnOK();
	afx_msg void OnGenrand();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREATEPLAYER_H__B612F343_424B_11D7_8358_0050BA26DFA6__INCLUDED_)
