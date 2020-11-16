#if !defined(AFX_ADDPROFILE_H__F47D0974_E30F_4BDB_B891_9BD126657191__INCLUDED_)
#define AFX_ADDPROFILE_H__F47D0974_E30F_4BDB_B891_9BD126657191__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddProfile.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddProfile dialog

class CAddProfile : public CDialog
{
// Construction
public:
	CString ServerIP;
	CAddProfile(CWnd* pParent = NULL);   // standard constructor
	DWORD GetDWORDIPAddress(CString strIPAddress);	
// Dialog Data
	//{{AFX_DATA(CAddProfile)
	enum { IDD = IDD_ADDPROFILE };
	CIPAddressCtrl	m_ctIP;
	CString	m_pass;
	CString	m_profname;
	CString	m_username;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddProfile)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddProfile)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDPROFILE_H__F47D0974_E30F_4BDB_B891_9BD126657191__INCLUDED_)
