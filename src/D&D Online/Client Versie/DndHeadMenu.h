#if !defined(AFX_DNDHEADMENU_H__9A766E52_374D_11D7_834D_0050BA26DFA6__INCLUDED_)
#define AFX_DNDHEADMENU_H__9A766E52_374D_11D7_834D_0050BA26DFA6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DndHeadMenu.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDndHeadMenu dialog
#include "defines.h"
class CDndHeadMenu : public CDialog
{
// Construction
public:
	CString PortraitsPath;
	int MaxHeadBitmaps;
	CString Path;
	void OnChosen();
	int chosenhead;
	int headsten;
	void LoadImages();
	CDndHeadMenu(CWnd* pParent = NULL);   // standard constructor
	HBITMAP headbmp[160];

// Dialog Data
	//{{AFX_DATA(CDndHeadMenu)
	enum { IDD = IDD_DLGHEADCHOOSE };
	CButton	m_prevhead;
	CButton	m_nexthead;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDndHeadMenu)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDndHeadMenu)
	afx_msg void OnPaint();
	afx_msg void OnNexthead();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPrevhead();
	afx_msg void OnHead1();
	afx_msg void OnHead2();
	afx_msg void OnHead3();
	afx_msg void OnHead4();
	afx_msg void OnHead5();
	afx_msg void OnHead6();
	afx_msg void OnHead7();
	afx_msg void OnHead8();
	afx_msg void OnHead9();
	afx_msg void OnHead10();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DNDHEADMENU_H__9A766E52_374D_11D7_834D_0050BA26DFA6__INCLUDED_)
