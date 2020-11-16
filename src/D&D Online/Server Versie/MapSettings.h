#if !defined(AFX_MAPSETTINGS_H__8AB5EF40_C373_43E9_9E6B_9A369593A40E__INCLUDED_)
#define AFX_MAPSETTINGS_H__8AB5EF40_C373_43E9_9E6B_9A369593A40E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MapSettings.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MapSettings dialog

class MapSettings : public CDialog
{
// Construction
public:
	bool clear;
	int prevblocksize;
	MapSettings(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MapSettings)
	enum { IDD = IDD_MAPSETDLG };
	UINT	m_blocksize;
	BOOL	m_dispgrid;
	BOOL	m_hires;
	BOOL	m_debugcleanup;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MapSettings)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MapSettings)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClearbutton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPSETTINGS_H__8AB5EF40_C373_43E9_9E6B_9A369593A40E__INCLUDED_)
