#if !defined(AFX_DNDPLAYER_H__9A766E51_374D_11D7_834D_0050BA26DFA6__INCLUDED_)
#define AFX_DNDPLAYER_H__9A766E51_374D_11D7_834D_0050BA26DFA6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DndPlayer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDndPlayer dialog
#include "PlayerInfo.h"
#include "DndHeadMenu.h"
#include "AfxTempl.h"


class CDndPlayer : public CDialog
{
// Construction
public:
	bool newChar;
	void BubbleSort(int array[],int size);
	CArray<CPlayerInfo, CPlayerInfo&> existingchars;

	int chosenchar;
	int head;
	void LoadImages();
	CDndPlayer(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CDndPlayer)
	enum { IDD = IDD_DLGPLAYERSET };
	CComboBox	m_combochars;
	CString	m_unusedcharname;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDndPlayer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDndPlayer)
	afx_msg void OnChoosehead();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	afx_msg void OnCloseupCombochars();
	afx_msg void OnSelchangeCombochars();
	afx_msg void OnNewchar();
	afx_msg void OnUnownedCharacter();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DNDPLAYER_H__9A766E51_374D_11D7_834D_0050BA26DFA6__INCLUDED_)
