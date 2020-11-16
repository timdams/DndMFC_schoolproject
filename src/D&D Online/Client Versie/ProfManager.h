#if !defined(AFX_PROFMANAGER_H__CAF605B5_9084_4DA7_B184_42E65CE9835F__INCLUDED_)
#define AFX_PROFMANAGER_H__CAF605B5_9084_4DA7_B184_42E65CE9835F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProfManager.h : header file
//
#include "AddProfile.h"
#include "Profile.h"
#include "AfxTempl.h"
/////////////////////////////////////////////////////////////////////////////
// CProfManager dialog


class CProfManager : public CDialog
{
// Construction
public:
	CString Path;
	UINT SaveChanges();
	UINT LoadChanges();
	CProfManager(CWnd* pParent = NULL);   // standard constructor
	DWORD GetDWORDIPAddress(CString strIPAddress);	
	CArray<CProfile, CProfile&> ProfileStack;
// Dialog Data
	//{{AFX_DATA(CProfManager)
	enum { IDD = IDD_PROFMANAGERDLG };
	CEdit	m_ctlfile;
	CButton	m_ctlbrowse;
	CStatic	m_ctlfilestat;
	CListBox	m_ctlProfiles;
	CString	m_strFile;
	BOOL	m_bpathcheck;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProfManager)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProfManager)
	afx_msg void OnSavechanges();
	afx_msg void OnAdd();
	afx_msg void OnChange();
	afx_msg void OnDelete();
	afx_msg void OnBrowsefile();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnChangepath();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROFMANAGER_H__CAF605B5_9084_4DA7_B184_42E65CE9835F__INCLUDED_)
