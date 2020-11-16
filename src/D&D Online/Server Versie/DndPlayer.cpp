// DndPlayer.cpp : implementation file
//

#include "stdafx.h"
#include "DnD.h"
#include "DndPlayer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDndPlayer dialog


CDndPlayer::CDndPlayer(CWnd* pParent /*=NULL*/)
	: CDialog(CDndPlayer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDndPlayer)
	//}}AFX_DATA_INIT
}

void CDndPlayer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDndPlayer)
	DDX_Control(pDX, IDC_COMBOCHARS, m_combochars);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDndPlayer, CDialog)
	//{{AFX_MSG_MAP(CDndPlayer)
	ON_BN_CLICKED(IDC_CHOOSEHEAD, OnChoosehead)
	ON_WM_HSCROLL()
	ON_CBN_CLOSEUP(IDC_COMBOCHARS, OnCloseupCombochars)
	ON_CBN_SELCHANGE(IDC_COMBOCHARS, OnSelchangeCombochars)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDndPlayer message handlers

void CDndPlayer::OnChoosehead() 
{
	// TODO: Add your control notification handler code here
	CDndHeadMenu dlg;
	CString file;
	HBITMAP bmp;
	
	if(dlg.DoModal()==IDOK)
	{	
		CStatic* pHead= (CStatic*)GetDlgItem(IDC_HEAD);
		file.Format("Heads\\head%i.bmp",dlg.chosenhead);
		bmp=(HBITMAP)LoadImage(NULL,file,IMAGE_BITMAP,0,0,
							LR_DEFAULTSIZE|LR_LOADFROMFILE);
		pHead->SetBitmap(bmp);
		head=dlg.chosenhead;
	}
	else
	AfxMessageBox("No head  chosen");
}

void CDndPlayer::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

BOOL CDndPlayer::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
//	CStatic* pHead;
	m_combochars.Clear();
	for(int i=0;i<existingchars.GetSize();i++)
		m_combochars.AddString(existingchars.GetAt(i).CharacterName);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDndPlayer::LoadImages()
{



}

void CDndPlayer::OnCloseupCombochars() 
{
	// TODO: Add your control notification handler code here


}

void CDndPlayer::OnSelchangeCombochars() 
{
	// TODO: Add your control notification handler code here
	HBITMAP bmp;
	CString file;
	head=m_combochars.GetCurSel();
	UpdateData(TRUE);
	//char info

	CStatic* pName= (CStatic*)GetDlgItem(IDC_STATNAME);
	CStatic* pClass= (CStatic*)GetDlgItem(IDC_STATCLASS);

//	pName->SetWindowText("Name: "+existingchars.GetAt(m_combochars.GetCurSel()));
	pClass->SetWindowText("Class: undefined");


	
	//foto
	CStatic* pHead= (CStatic*)GetDlgItem(IDC_HEAD);
	file.Format("Heads\\head%i.bmp",m_combochars.GetCurSel()+10);
	bmp=(HBITMAP)LoadImage(NULL,file,IMAGE_BITMAP,0,0,
							LR_DEFAULTSIZE|LR_LOADFROMFILE);
	pHead->SetBitmap(bmp);
	
}
