#if !defined(AFX_CHATVIEW_H__5583A977_020E_11D7_832F_0050BA26DFA6__INCLUDED_)
#define AFX_CHATVIEW_H__5583A977_020E_11D7_832F_0050BA26DFA6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChatView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChatView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include "DnDDoc.h"
#include "ColorListBox.h"
class CChatView : public CFormView
{
protected:
	CChatView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CChatView)

// Form Data
public:
	//{{AFX_DATA(CChatView)
	enum { IDD = IDD_CHATVIEW };
	CStatic	m_head8;
	CStatic	m_head7;
	CStatic	m_head6;
	CStatic	m_head5;
	CStatic	m_head3;
	CStatic	m_head4;
	CStatic	m_head2;
	CStatic	m_head1;
	CComboBox	m_comcombo;
	CColorListBox	m_userbox;
	CColorListBox	m_chatbox;
	CString	m_commando;
	CString	m_sendstringchat;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	CPoint LastPopup;
	int IsHead(CPoint point);


	void SetStats(CString m_Charname,CStringArray& Statnames,CStringArray& Statvalues);
	int lines;
	void ClickedHead(int k);
	HBITMAP headbmp[160];
	void LoadImages();
	CDnDDoc* GetDocument();
	 bool firstpaint;

	void AddToListbox(CString str, int type);
	CStatic* pHead[MAXNUMCLIENTS];
	CDnDDoc* pDoc;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	virtual ~CChatView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CChatView)
	afx_msg void OnButtonSend(bool m_bUserTyped);
	afx_msg void OnCloseupCommandbox();
	afx_msg void OnHead1();
	afx_msg void OnHead2();
	afx_msg void OnHead3();
	afx_msg void OnHead4();
	afx_msg void OnHead5();
	afx_msg void OnHead6();
	afx_msg void OnHead7();
	afx_msg void OnHead8();
	afx_msg void OnPopupWhisper();
	afx_msg void OnPopupPlayerstats();
	afx_msg void OnUpdatePopupPlayerstats(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePopupBan(CCmdUI* pCmdUI);
	afx_msg void OnPopupBan();
	afx_msg void OnPopupKick();
	afx_msg void OnUpdatePopupKick(CCmdUI* pCmdUI);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnBtnsend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATVIEW_H__5583A977_020E_11D7_832F_0050BA26DFA6__INCLUDED_)
