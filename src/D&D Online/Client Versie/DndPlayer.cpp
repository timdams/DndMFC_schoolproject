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
	m_unusedcharname = _T("");
	//}}AFX_DATA_INIT
}

void CDndPlayer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDndPlayer)
	DDX_Control(pDX, IDC_COMBOCHARS, m_combochars);
	DDX_Text(pDX, IDC_EDITUNCHAR, m_unusedcharname);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDndPlayer, CDialog)
	//{{AFX_MSG_MAP(CDndPlayer)
	ON_BN_CLICKED(IDC_CHOOSEHEAD, OnChoosehead)
	ON_WM_HSCROLL()
	ON_CBN_CLOSEUP(IDC_COMBOCHARS, OnCloseupCombochars)
	ON_CBN_SELCHANGE(IDC_COMBOCHARS, OnSelchangeCombochars)
	ON_BN_CLICKED(IDC_NEWCHAR, OnNewchar)
	ON_BN_CLICKED(IDC_UNOWNED, OnUnownedCharacter)
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
	chosenchar=-3;
	// TODO: Add extra initialization here
//	CStatic* pHead;
	newChar=FALSE;
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
	CString temp;
	head=existingchars.GetAt(m_combochars.GetCurSel()).head;
	chosenchar=m_combochars.GetCurSel();
	//char info

	
	
	
	CStatic* pAge= (CStatic*)GetDlgItem(IDC_STATAGE);
	temp.Format("%i",existingchars.GetAt(m_combochars.GetCurSel()).Age);
	pAge->SetWindowText("Age: "+temp);

	CStatic* pAlignment= (CStatic*)GetDlgItem(IDC_STATALIGNMENT);
	pAlignment->SetWindowText("Alignment: "+existingchars.GetAt(m_combochars.GetCurSel()).Alignment);

	CStatic* pName= (CStatic*)GetDlgItem(IDC_STATNAME);
	pName->SetWindowText("Name: "+existingchars.GetAt(m_combochars.GetCurSel()).CharacterName);
	
	CStatic* pClass= (CStatic*)GetDlgItem(IDC_STATCLASS);
	pClass->SetWindowText("Class: "+existingchars.GetAt(m_combochars.GetCurSel()).Class);


	CStatic* pRace= (CStatic*)GetDlgItem(IDC_STATRACE);
	pRace->SetWindowText("Race: "+existingchars.GetAt(m_combochars.GetCurSel()).Race);

	CStatic* pDeity= (CStatic*)GetDlgItem(IDC_STATDEITY);
	pDeity->SetWindowText("Deity: "+existingchars.GetAt(m_combochars.GetCurSel()).Deity);

	CStatic* pDesc= (CStatic*)GetDlgItem(IDC_STATDESCRIPTION);
	pDesc->SetWindowText(existingchars.GetAt(m_combochars.GetCurSel()).Description);

	CStatic* pGender= (CStatic*)GetDlgItem(IDC_STATGENDER);
	pGender->SetWindowText("Gender: "+existingchars.GetAt(m_combochars.GetCurSel()).Gender);
	
	//stats
	CStatic* pStrength= (CStatic*)GetDlgItem(IDC_STATSTR);
	temp.Format("%i",existingchars.GetAt(m_combochars.GetCurSel()).Strength);
	pStrength->SetWindowText("Strength: "+temp);

	CStatic* pDex= (CStatic*)GetDlgItem(IDC_STATDEX);
	temp.Format("%i",existingchars.GetAt(m_combochars.GetCurSel()).Dexterity);
	pDex->SetWindowText("Dexterity: "+temp);
	
	CStatic* pConn= (CStatic*)GetDlgItem(IDC_STATCON);
	temp.Format("%i",existingchars.GetAt(m_combochars.GetCurSel()).Constitution);
	pConn->SetWindowText("Constitution: "+temp);

	CStatic* pWis= (CStatic*)GetDlgItem(IDC_STATWIS);
	temp.Format("%i",existingchars.GetAt(m_combochars.GetCurSel()).Wisdom);
	pWis->SetWindowText("Wisdom: "+temp);

	CStatic* pInt= (CStatic*)GetDlgItem(IDC_STATINT);
	temp.Format("%i",existingchars.GetAt(m_combochars.GetCurSel()).Intelligence);
	pInt->SetWindowText("Intelligence: "+temp);
	
	CStatic* pChar= (CStatic*)GetDlgItem(IDC_STATCHA);
	temp.Format("%i",existingchars.GetAt(m_combochars.GetCurSel()).Charisma);
	pChar->SetWindowText("Charisma: "+temp);
	//foto
	CStatic* pHead= (CStatic*)GetDlgItem(IDC_HEAD);
	file.Format("Heads\\head%i.bmp",head);
	bmp=(HBITMAP)LoadImage(NULL,file,IMAGE_BITMAP,0,0,
							LR_DEFAULTSIZE|LR_LOADFROMFILE);
	pHead->SetBitmap(bmp);
		UpdateData(TRUE);
}

void CDndPlayer::BubbleSort(int array[], int size)
{

}

void CDndPlayer::OnNewchar() 
{
	// TODO: Add your control notification handler code here
		newChar=TRUE;
		CDialog::OnOK();
}

void CDndPlayer::OnUnownedCharacter() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	chosenchar=-2;
	CDialog::OnOK();
}

void CDndPlayer::OnOK() 
{
	// TODO: Add extra validation here
	if (chosenchar==-3)
	{
		AfxMessageBox("No character chosen. Please do so before continuing");
			
	}
	else 
		CDialog::OnOK();
}
