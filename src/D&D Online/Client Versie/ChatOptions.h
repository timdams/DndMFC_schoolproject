#if !defined(AFX_CHATOPTIONS_H__6345375F_5994_4603_8905_92028BD5A527__INCLUDED_)
#define AFX_CHATOPTIONS_H__6345375F_5994_4603_8905_92028BD5A527__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChatOptions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChatOptions dialog

class CChatOptions : public CDialog
{
// Construction
public:
	CChatOptions(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChatOptions)
	enum { IDD = IDD_CHATOPTIONSDLG };
	CSpinButtonCtrl	m_spinres;
	UINT	m_sketchres;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChatOptions)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATOPTIONS_H__6345375F_5994_4603_8905_92028BD5A527__INCLUDED_)
