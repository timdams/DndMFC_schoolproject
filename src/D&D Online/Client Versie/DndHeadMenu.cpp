// DndHeadMenu.cpp : implementation file
//

#include "stdafx.h"
#include "DnD.h"
#include "DndHeadMenu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDndHeadMenu dialog


CDndHeadMenu::CDndHeadMenu(CWnd* pParent /*=NULL*/)
	: CDialog(CDndHeadMenu::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDndHeadMenu)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDndHeadMenu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDndHeadMenu)
	DDX_Control(pDX, IDC_PREVHEAD, m_prevhead);
	DDX_Control(pDX, IDC_NEXTHEAD, m_nexthead);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDndHeadMenu, CDialog)
	//{{AFX_MSG_MAP(CDndHeadMenu)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_NEXTHEAD, OnNexthead)
	ON_WM_CTLCOLOR()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_PREVHEAD, OnPrevhead)
	ON_BN_CLICKED(IDC_HEAD1, OnHead1)
	ON_BN_CLICKED(IDC_HEAD2, OnHead2)
	ON_BN_CLICKED(IDC_HEAD3, OnHead3)
	ON_BN_CLICKED(IDC_HEAD4, OnHead4)
	ON_BN_CLICKED(IDC_HEAD5, OnHead5)
	ON_BN_CLICKED(IDC_HEAD6, OnHead6)
	ON_BN_CLICKED(IDC_HEAD7, OnHead7)
	ON_BN_CLICKED(IDC_HEAD8, OnHead8)
	ON_BN_CLICKED(IDC_HEAD9, OnHead9)
	ON_BN_CLICKED(IDC_HEAD10, OnHead10)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDndHeadMenu message handlers

void CDndHeadMenu::LoadImages()
{
	CString filepath;
	
	for(int k=0;k<MaxHeadBitmaps;k++)
	{
		filepath.Format(PortraitsPath+"\\head%i.bmp",k+1);
		
		headbmp[k]=(HBITMAP)LoadImage(NULL,filepath,IMAGE_BITMAP,0,0,
								LR_DEFAULTSIZE|LR_LOADFROMFILE);
			if(!headbmp[k])
			{
			headbmp[k]=(HBITMAP)LoadImage(NULL,PortraitsPath+"\\default.bmp",IMAGE_BITMAP,0,0,
								LR_DEFAULTSIZE|LR_LOADFROMFILE);
			
			}
	}
	
}

void CDndHeadMenu::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here

	// Do not call CDialog::OnPaint() for painting messages
}

void CDndHeadMenu::OnNexthead() 
{
	// TODO: Add your control notification handler code here
	CStatic* pHead[10];
	HBITMAP def;
	CString filepath;
	filepath.Format(PortraitsPath+ "\\default.bmp");

	def=(HBITMAP)LoadImage(NULL,filepath,IMAGE_BITMAP,0,0,
								LR_DEFAULTSIZE|LR_LOADFROMFILE);
	int heads=10;
	headsten++;

	m_prevhead.EnableWindow(TRUE);
	
	if(MaxHeadBitmaps-10*headsten<10)
	{
		heads=MaxHeadBitmaps-10*headsten;
		m_nexthead.EnableWindow(FALSE);
	
	}
		
	for(int l=0;l<10;l++)
	{
		pHead[l]= (CStatic*)GetDlgItem(IDC_HEAD1+l);
		pHead[l]->SetBitmap(def);

	}

	
	for(int k=0;k<heads;k++)
	{
	
		pHead[k]->SetBitmap(headbmp[k+headsten*10]);
	
	//	pHead[l]->EnableWindow(TRUE);
			
	}


}

BOOL CDndHeadMenu::OnInitDialog() 
{
	CDialog::OnInitDialog();
	chosenhead=0;
	int aant=10;
	// TODO: Add extra initialization here
	headsten=0;
	int i=0;
	
	CStatic* pHead[10];

//	MaxHeadBitmaps=0;
/*	char FileName[MAX_PATH];
	GetModuleFileName(AfxGetInstanceHandle(),FileName,MAX_PATH);
	Path=(CString)FileName;
	Path=Path.Left(Path.ReverseFind('\\') );
*/
/*
	CFileFind finder;
	CString FirstPath =Path+"\\Heads\\"+ "head0.bmp";
	bool bWorking = finder.FindFile(FirstPath);
	while (bWorking)
	{
		MaxHeadBitmaps++;
		FirstPath.Format(Path+"\\Heads\\head%i.bmp",MaxHeadBitmaps+1);
		bWorking = finder.FindFile(FirstPath);
      
	}
	if(MaxHeadBitmaps==0)
		AfxMessageBox("No bitmaps found in \\Heads  ! Continue at own risk!"); */
	LoadImages();
	if(MaxHeadBitmaps<=10)
		aant=MaxHeadBitmaps;
	for(int k=0;k<aant;k++)
	{
		pHead[k]= (CStatic*)GetDlgItem(IDC_HEAD1+k);
		pHead[k]->SetBitmap(headbmp[k]);
	}
	if (MaxHeadBitmaps>10)
	{
		m_nexthead.EnableWindow(TRUE);
		m_prevhead.EnableWindow(FALSE);
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CDndHeadMenu::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here

	// TODO: Return a different brush if the default is not desired
	return hbr;
}

int CDndHeadMenu::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here

	return 0;
}

void CDndHeadMenu::OnPrevhead() 
{
	// TODO: Add your control notification handler code here
	CStatic* pHead[10];
	HBITMAP def;
	CString filepath;
	filepath.Format(PortraitsPath+"\\default.bmp");

	def=(HBITMAP)LoadImage(NULL,filepath,IMAGE_BITMAP,0,0,
								LR_DEFAULTSIZE|LR_LOADFROMFILE);
	int heads=10;
	headsten--;

	m_nexthead.EnableWindow(TRUE);
	for(int l=0;l<10;l++)
	{
		pHead[l]= (CStatic*)GetDlgItem(IDC_HEAD1+l);
		pHead[l]->SetBitmap(def);

	}
	if(headsten==0)
	{
		
		m_prevhead.EnableWindow(FALSE);

	}
	for(int k=0;k<heads;k++)
	{
		pHead[k]->SetBitmap(headbmp[k+headsten*10]);
		//pHead[l]->EnableWindow(TRUE);
	}
}

void CDndHeadMenu::OnHead1() 
{
	// TODO: Add your control notification handler code here
	chosenhead=headsten*10+1;
	OnChosen();
}

void CDndHeadMenu::OnHead2() 
{
	// TODO: Add your control notification handler code here
	chosenhead=headsten*10+2;
	OnChosen();
}

void CDndHeadMenu::OnHead3() 
{
	// TODO: Add your control notification handler code here
	chosenhead=headsten*10+3;
	OnChosen();
}

void CDndHeadMenu::OnHead4() 
{
	// TODO: Add your control notification handler code here
	chosenhead=headsten*10+4;
	OnChosen();	
}

void CDndHeadMenu::OnHead5() 
{
	// TODO: Add your control notification handler code here
	chosenhead=headsten*10+5;
	OnChosen();	
}

void CDndHeadMenu::OnHead6() 
{
	// TODO: Add your control notification handler code here
	chosenhead=headsten*10+6;
	OnChosen();	
}

void CDndHeadMenu::OnHead7() 
{
	// TODO: Add your control notification handler code here
	chosenhead=headsten*10+7;
	OnChosen();	
}

void CDndHeadMenu::OnHead8() 
{
	// TODO: Add your control notification handler code here
	chosenhead=headsten*10+8;
	OnChosen();
}

void CDndHeadMenu::OnHead9() 
{
	// TODO: Add your control notification handler code here
	chosenhead=headsten*10+9;
	OnChosen();	
}

void CDndHeadMenu::OnHead10() 
{
	// TODO: Add your control notification handler code here
	chosenhead=headsten*10+10;
	OnChosen();	
}

void CDndHeadMenu::OnChosen()
{
	CStatic* pChosenHead;
	HBITMAP def;
	CString filepath;
	filepath.Format(PortraitsPath+"\\default.bmp");

	def=(HBITMAP)LoadImage(NULL,filepath,IMAGE_BITMAP,0,0,
								LR_DEFAULTSIZE|LR_LOADFROMFILE);


		pChosenHead= (CStatic*)GetDlgItem(IDC_HEADCHOSEN);



		pChosenHead->SetBitmap(headbmp[chosenhead-1]);
		pChosenHead->EnableWindow(TRUE);



}

void CDndHeadMenu::OnOK() 
{
	// TODO: Add extra validation here
	for(int k=0;k<MaxHeadBitmaps;k++)
	{
		DeleteObject(headbmp[k]);
	}
	CDialog::OnOK();
}

