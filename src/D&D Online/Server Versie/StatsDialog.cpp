// StatsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DnD.h"
#include "StatsDialog.h"
#include "DnDDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatsDialog dialog


CStatsDialog::CStatsDialog(CPoint pt, CWnd* pParent /*=NULL*/)
	: CAniDialog(pt, CStatsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStatsDialog)
	m_Username = _T("");
	m_Charname = _T("");
	m_Armor = _T("");
	m_Strength = _T("");
	m_Dexterity = _T("");
	m_Constitution = _T("");
	m_Intelligence = _T("");
	m_Wisdom = _T("");
	m_Charisma = _T("");
	m_Items = _T("");
	//}}AFX_DATA_INIT
}


void CStatsDialog::DoDataExchange(CDataExchange* pDX)
{
	CAniDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatsDialog)
	DDX_Control(pDX, IDC_GIF2, m_Gif2);
	DDX_Control(pDX, IDC_GIF1, m_Gif1);
	DDX_Text(pDX, IDC_USERNAME, m_Username);
	DDX_Text(pDX, IDC_CHARNAME, m_Charname);
	DDX_Text(pDX, IDC_ARMOR, m_Armor);
	DDX_Text(pDX, IDC_STRENGTH, m_Strength);
	DDX_Text(pDX, IDC_DEXTERITY, m_Dexterity);
	DDX_Text(pDX, IDC_CONSTITUTION, m_Constitution);
	DDX_Text(pDX, IDC_INTELLIGENCE, m_Intelligence);
	DDX_Text(pDX, IDC_WISDOM, m_Wisdom);
	DDX_Text(pDX, IDC_CHARISMA, m_Charisma);
	DDX_Text(pDX, IDC_ITEMS, m_Items);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStatsDialog, CAniDialog)
	//{{AFX_MSG_MAP(CStatsDialog)
	ON_BN_CLICKED(IDDOCHANGES, OnDoChanges)
	ON_BN_CLICKED(IDKICK, OnKick)
	ON_BN_CLICKED(IDBAN, OnBan)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatsDialog message handlers

void CStatsDialog::OnDoChanges() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	Statnames.Add("STRENGTH");
	Statvalues.Add(m_Strength);
	Statnames.Add("DEXTERITY");
	Statvalues.Add(m_Dexterity);
	Statnames.Add("CONSTITUTION");
	Statvalues.Add(m_Constitution);
	Statnames.Add("INTELLIGENCE");
	Statvalues.Add(m_Intelligence);
	Statnames.Add("WISDOM");
	Statvalues.Add(m_Wisdom);
	Statnames.Add("CHARISMA");
	Statvalues.Add(m_Charisma);

	b_update=true;
}

BOOL CStatsDialog::OnInitDialog() 
{
	CAniDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (m_Gif1.Load(_T("sTorch.gif")))
	   m_Gif1.Draw();
	if (m_Gif2.Load(_T("sTorch.gif")))
	   m_Gif2.Draw();

	b_kick=false;
	b_ban=false;
	b_update=false;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStatsDialog::OnKick() 
{
	// TODO: Add your control notification handler code here
	if(IDYES==AfxMessageBox("Are you sure you want to kick this player?",MB_YESNO))
	{
		b_kick=true;
		OnOK();
	}
	
}

void CStatsDialog::OnBan() 
{
	// TODO: Add your control notification handler code here
	if(IDYES==AfxMessageBox("Are you sure you want to ban this player?",MB_YESNO))
	{
		b_ban=true;
		OnOK();
	}
	
}

void CStatsDialog::OnOK() 
{
	// TODO: Add extra validation here
	
	CAniDialog::OnOK();
}
