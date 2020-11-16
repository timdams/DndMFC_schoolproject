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

#include "ColorListBox.h"
#include "DnDDoc.h"
#include "ProfManager.h"
#include "Profile.h"

class CConnView : public CFormView
{
protected:
	CConnView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CConnView)

// Form Data
public:
	//{{AFX_DATA(CConnView)
	enum { IDD = IDD_CONNVIEW };
	CComboBox	m_userprof;
	CComboBox	m_combprof;
	CIPAddressCtrl	m_cIP;
	CColorListBox	m_ConnList;
	int		m_nPort;
	CString	m_sEditUsername;
	CString	m_sEditPass;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	CString m_strFile;
	bool bCustomProfilePath;
	UINT LoadProfiles();
	int lines;
	void AddToListbox(CString str,int type);
	CArray<CProfile, CProfile&> ProfileStack;
	void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	void CloseConnect();
	CString ConvertSocketError(int error);
	CDnDDoc* GetDocument();
	CDnDDoc* pDoc;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConnView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
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
	afx_msg void OnButtonConnect();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDebugbtn();
	afx_msg void OnPlayerset();
	afx_msg void OnSelchangeConnprofile();
	afx_msg void OnSelchangeUserprofile();
	afx_msg void OnProfmanager();
	afx_msg void OnDebugbtn2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONNVIEW_H__5583A976_020E_11D7_832F_0050BA26DFA6__INCLUDED_)
