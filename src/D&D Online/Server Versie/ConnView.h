#if !defined(AFX_CONNVIEW_H__5583A976_020E_11D7_832F_0050BA26DFA6__INCLUDED_)
#define AFX_CONNVIEW_H__5583A976_020E_11D7_832F_0050BA26DFA6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConnView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConnView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include "DnDDoc.h"
#include "Mainfrm.h"
#include "ColorListBox.h"
#include "HyperLink.h";
class CConnView : public CFormView
{
protected:
	CConnView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CConnView)

// Form Data
public:
	//{{AFX_DATA(CConnView)
	enum { IDD = IDD_CONNVIEW };
	CHyperLink	m_link;
	CColorListBox	m_svrstatlist;
	UINT	m_nPort;
	BOOL	m_bTimeOut;
	CString	m_ipadapter;
	CString	m_ipadapter2;
	CString	m_connectedhosts;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	int lines;
	CString ConvertSocketError(int error);
	CDnDDoc* GetDocument();
	void AddToListbox(CString str, int type);
	CDnDDoc* pDoc;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConnView)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CConnView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CConnView)
	afx_msg void OnStartServer();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/*
#ifndef _DEBUG  // debug version in PTView.cpp
inline CDnDDoc* CConnView::GetDocument()
  { return (CDnDDoc*)m_pDocument; }
#endif*/
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONNVIEW_H__5583A976_020E_11D7_832F_0050BA26DFA6__INCLUDED_)
