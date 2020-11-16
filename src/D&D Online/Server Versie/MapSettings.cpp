// MapSettings.cpp : implementation file
//

#include "stdafx.h"
#include "DnD.h"
#include "MapSettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MapSettings dialog


MapSettings::MapSettings(CWnd* pParent /*=NULL*/)
	: CDialog(MapSettings::IDD, pParent)
{
	//{{AFX_DATA_INIT(MapSettings)
	m_blocksize = 0;
	m_dispgrid = FALSE;
	m_hires = FALSE;
	m_debugcleanup = FALSE;
	//}}AFX_DATA_INIT
}


void MapSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MapSettings)
	DDX_Text(pDX, IDC_BLOCKS, m_blocksize);
	DDV_MinMaxUInt(pDX, m_blocksize, 5, 100);
	DDX_Check(pDX, IDC_DISPGRID, m_dispgrid);
	DDX_Check(pDX, IDC_CHECKHIRES, m_hires);
	DDX_Check(pDX, IDC_CHECKCP, m_debugcleanup);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MapSettings, CDialog)
	//{{AFX_MSG_MAP(MapSettings)
	ON_BN_CLICKED(IDC_CLEARBUTTON, OnClearbutton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MapSettings message handlers

BOOL MapSettings::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	prevblocksize=m_blocksize;
	clear=FALSE;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void MapSettings::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	if(prevblocksize!=m_blocksize || clear)
	{
		if(IDYES==AfxMessageBox("Continuing will result in a new/empty map. Are you sure?",MB_YESNO))
		
		CDialog::OnOK();
		else
		{
			m_blocksize=prevblocksize;
			clear=FALSE;
			UpdateData(TRUE);
		}
	}
	else
		CDialog::OnOK();
}	

void MapSettings::OnClearbutton() 
{
	// TODO: Add your control notification handler code here
		clear=TRUE;
}
