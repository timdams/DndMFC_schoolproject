// ChatOptions.cpp : implementation file
//

#include "stdafx.h"
#include "DnD.h"
#include "ChatOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChatOptions dialog


CChatOptions::CChatOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CChatOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChatOptions)
	m_sketchres = 0;
	//}}AFX_DATA_INIT
}


void CChatOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChatOptions)
	DDX_Control(pDX, IDC_SPINRES, m_spinres);
	DDX_Text(pDX, IDC_RES, m_sketchres);
	DDV_MinMaxUInt(pDX, m_sketchres, 1, 3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChatOptions, CDialog)
	//{{AFX_MSG_MAP(CChatOptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatOptions message handlers

BOOL CChatOptions::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_spinres.SetRange(1,3);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChatOptions::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);	
	CDialog::OnOK();
}
