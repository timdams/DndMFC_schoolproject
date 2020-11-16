#if !defined(AFX_STATSDIALOG_H__29361A73_0950_461A_AE46_2783EC5E5CEC__INCLUDED_)
#define AFX_STATSDIALOG_H__29361A73_0950_461A_AE46_2783EC5E5CEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StatsDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStatsDialog dialog
#include "AniDialog.h"
#include "PictureEx.h"

class CStatsDialog : public CAniDialog
{
// Construction
public:
	CStatsDialog(CPoint pt, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStatsDialog)
	enum { IDD = IDD_STATSDIALOG };
	CPictureEx	m_Gif2;
	CPictureEx	m_Gif1;
	CString	m_Username;
	CString	m_Charname;
	CString	m_Armor;
	CString	m_Strength;
	CString	m_Dexterity;
	CString	m_Constitution;
	CString	m_Intelligence;
	CString	m_Wisdom;
	CString	m_Charisma;
	CString	m_Items;
	bool b_kick;
	bool b_ban;
	bool b_update;
	CStringArray Statnames;
	CStringArray Statvalues;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStatsDialog)
	afx_msg void OnDoChanges();
	virtual BOOL OnInitDialog();
	afx_msg void OnKick();
	virtual void OnOK();
	afx_msg void OnBan();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATSDIALOG_H__29361A73_0950_461A_AE46_2783EC5E5CEC__INCLUDED_)
