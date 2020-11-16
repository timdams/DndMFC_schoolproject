// ChatView.cpp : implementation file
//

#include "stdafx.h"
#include "DnD.h"
#include "ChatView.h"
#include "DnDDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChatView

IMPLEMENT_DYNCREATE(CChatView, CFormView)

CChatView::CChatView()
	: CFormView(CChatView::IDD)
{
	//{{AFX_DATA_INIT(CChatView)
	m_sEditChat = _T("");
	//}}AFX_DATA_INIT
}

CChatView::~CChatView()
{
}

void CChatView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChatView)
	DDX_Control(pDX, IDC_SKETCHBLCOK, m_miniature);
	DDX_Text(pDX, IDC_EDITCHAT, m_sEditChat);
	DDX_Control(pDX, IDC_LISTCHAT, m_ConnList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChatView, CFormView)
	//{{AFX_MSG_MAP(CChatView)
	ON_BN_CLICKED(IDC_BUTTONSEND, OnButtonSend)
	ON_BN_CLICKED(IDC_HEADME, OnHeadme)
	ON_BN_CLICKED(IDC_CHATOPTIONS, OnChatoptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatView diagnostics

#ifdef _DEBUG
void CChatView::AssertValid() const
{
	CFormView::AssertValid();
}

void CChatView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChatView message handlers

void CChatView::OnInitialUpdate() 
{
	firstpaint=0;
	InitUpdate=0;
	sketchmode=3;
	GotLoadedImage=FALSE;
	pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	hidden =0;
	LoadImages();

	lines=0;
	if(pDoc->Sketch.GetSize()==0)
		SketchAvailable=FALSE;
	else
		SketchAvailable=TRUE;
	CFormView::OnInitialUpdate();
	InitUpdate=1;
	pHeadMe= (CStatic*)GetDlgItem(IDC_HEADME);
	if(pDoc->MyHead!=-3 && pDoc->MyName!="None")
	{
		if(pDoc->MyHead < pDoc->MaxHeadBitmaps)
			pHeadMe->SetBitmap(headbmp[pDoc->MyHead]);
		else
			pHeadMe->SetBitmap(headbmp[0]);
	pHeadMe->ShowWindow(SW_SHOW);
	}
}

void CChatView::LoadImages()
{
	CString filepath;
	sketch.LoadBitmap(IDB_SKETCH);
	//xMessageBox(pDoc->PortraitsPath);
	for(int k=0;k<pDoc->MaxHeadBitmaps;k++)
	{
		
		filepath.Format(pDoc->PortraitsPath+"\\head%i.bmp",k);
		headbmp[k]=(HBITMAP)LoadImage(NULL,filepath,IMAGE_BITMAP,0,0,
								LR_DEFAULTSIZE|LR_LOADFROMFILE);
			if(!headbmp[k])
			{
			headbmp[k]=(HBITMAP)LoadImage(NULL,pDoc->PortraitsPath+"\\default.bmp",IMAGE_BITMAP,0,0,
								LR_DEFAULTSIZE|LR_LOADFROMFILE);
			
			}
	}



}

CDnDDoc* CChatView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDnDDoc)));
	return (CDnDDoc*)m_pDocument;
}
void CChatView::DrawTransparentResizedBitmap(CDC *pDC, CBitmap *pBitmap, short xStart, short yStart, COLORREF cTransparentColor, short xEnd,short yEnd, int mode)
{
	//Code gevonde in voorbeeldprogramma op codeproject.com	
	//Heb ik tot in den treure gebruikt in Paratrooper. Good toh have this hun back ;)
	//Net als vorige maar nu gaat bitmap geresized worden
	// Copiously plagiarized from the Microsoft Knowledge Base,
	// article Q79212...though I did convert it to C++/MFC.
	CDC dcTemp;
	dcTemp.CreateCompatibleDC(pDC);
	dcTemp.SelectObject(pBitmap);

	BITMAP bm;
	pBitmap->GetBitmap(&bm);
	POINT ptSize;
	ptSize.x = bm.bmWidth;		// Get width of bitmap
	ptSize.y = bm.bmHeight;		// Get height of bitmap

	dcTemp.DPtoLP(&ptSize, 1);	// Convert from device to logical points

	// Create some DCs to hold temporary data.
	CDC dcMem;
	dcMem.CreateCompatibleDC(pDC);
	CDC dcBack;
	dcBack.CreateCompatibleDC(pDC);
	CDC dcObject;
	dcObject.CreateCompatibleDC(pDC);
	CDC dcSave;
	dcSave.CreateCompatibleDC(pDC);

	// Monochrome DC
	CBitmap bmAndBack;
	bmAndBack.CreateBitmap(ptSize.x,ptSize.y,1,1,NULL);

	// Monochrome DC
	CBitmap bmAndObject;
	bmAndObject.CreateBitmap(ptSize.x,ptSize.y,1,1,NULL);

	// Color DCs
	CBitmap bmAndMem;
	bmAndMem.CreateCompatibleBitmap(pDC,ptSize.x,ptSize.y);
	CBitmap bmSave;
	bmSave.CreateCompatibleBitmap(pDC,ptSize.x,ptSize.y);

	// Each DC must select a bitmap object to store pixel data.
	CBitmap* bmBackOld = (CBitmap*)dcBack.SelectObject(&bmAndBack);
	CBitmap* bmObjectOld = (CBitmap*)dcObject.SelectObject(&bmAndObject);
	CBitmap* bmMemOld = (CBitmap*)dcMem.SelectObject(&bmAndMem);
	CBitmap* bmSaveOld = (CBitmap*)dcSave.SelectObject(&bmSave);

	// Set proper mapping mode.
	dcTemp.SetMapMode(pDC->GetMapMode());

	// Save the bitmap sent here, because it will be overwritten.
	dcSave.BitBlt(0,0,ptSize.x,ptSize.y,&dcTemp,0,0,SRCCOPY);

	// Set the background color of the source DC to the color.
	// contained in the parts of the bitmap that should be transparent
	COLORREF cColor;
	cColor = dcTemp.SetBkColor(cTransparentColor);

	// Create the object mask for the bitmap by performing a BitBlt
	// from the source bitmap to a monochrome bitmap.
	dcObject.BitBlt(0,0,ptSize.x,ptSize.y,&dcTemp,0,0,SRCCOPY);

	// Set the background color of the source DC back to the original
	// color.
	dcTemp.SetBkColor(cColor);

	// Create the inverse of the object mask.
	dcBack.BitBlt(0,0,ptSize.x,ptSize.y,&dcObject,0,0,NOTSRCCOPY);

	// Copy the background of the main DC to the destination.
	dcMem.BitBlt(0,0,ptSize.x,ptSize.y,pDC,xStart,yStart,SRCCOPY);

	// Mask out the places where the bitmap will be placed.
	dcMem.BitBlt(0,0,ptSize.x,ptSize.y,&dcObject,0,0,SRCAND);

	// Mask out the transparent colored pixels on the bitmap.
	dcTemp.BitBlt(0,0,ptSize.x,ptSize.y,&dcBack,0,0,SRCAND);

	// XOR the bitmap with the background on the destination DC.
	dcMem.BitBlt(0,0,ptSize.x,ptSize.y,&dcTemp,0,0,SRCPAINT);
	
	// Copy the destination to the screen.
//	pDC->BitBlt(xStart,yStart,ptSize.x,ptSize.y,&dcMem,0,0,SRCCOPY);
	pDC->SetStretchBltMode(mode);
	pDC->StretchBlt(xStart,yStart,xEnd,yEnd,&dcMem,0,0,ptSize.x,ptSize.y,SRCCOPY);
		
	// Restore the original bitmap.
	dcTemp.BitBlt(0,0,ptSize.x,ptSize.y,&dcSave,0,0,SRCCOPY);

	// Delete the memory bitmaps.
	dcBack.SelectObject(bmBackOld);
	dcObject.SelectObject(bmObjectOld);
	dcMem.SelectObject(bmMemOld);
	dcSave.SelectObject(bmSaveOld);
}

void CChatView::AddToListbox(CString str,int type)
{
	switch(type)
	{		
	case 0:
		m_ConnList.AddString( str,RGB(250,0,0));
		break;
	default:
		m_ConnList.AddString( str);
	}

	CRect rect;
	
	// Volgende lijn moet eigenlijk niet aangezien we met string werken
	// en er niet gesorteerd wordt.
	m_ConnList.SetCurSel(m_ConnList.GetCount()-1);
}


void CChatView::OnButtonSend() 
{
	// TODO: Add your control notification handler code here
//	CDnDDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);

	UpdateData();

	if(pDoc->m_bConnected)
	{
		AddToListbox("Send: "+m_sEditChat,0);

		pDoc->m_sSend=m_sEditChat;
		pDoc->Send(CHAT);

		CStatic* pStaticOutput=(CStatic*)GetDlgItem(IDC_EDITCHAT);
		pStaticOutput->SetWindowText("");
	}
}

void CChatView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	//de doc wordt verkregen 
//	CDnDDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
	pHeadMe= (CStatic*)GetDlgItem(IDC_HEADME);

	if(pDoc->MyHead!=-3 && pDoc->MyName!="None")
	{
		if(pDoc->MyHead < pDoc->MaxHeadBitmaps)
			pHeadMe->SetBitmap(headbmp[pDoc->MyHead]);
		else
			pHeadMe->SetBitmap(headbmp[0]);
	pHeadMe->ShowWindow(SW_SHOW);
	}
	else pHeadMe->ShowWindow(SW_HIDE);

	CString TmpIP,TmpStr;
	int size=pDoc->ChatBarrel.GetSize();
	CBarrel temp;
	int k,l,j=0;
	if(size!=0)
	{
		for(int i=lines;i<size;i++)
		{
			temp=pDoc->ChatBarrel.GetAt(i);
			switch(temp.type)
			{
				
				case IMAGEREQ1:

					if(temp.data=="zepponop")
					{
						GotLoadedImage=false;
					}
					else
					{
						if(ImagePath!=temp.data)
						{	ImagePath=temp.data;
							APicture.UnLoad();
							if(!APicture.Load(ImagePath))
								AfxMessageBox("Error loading Image:"+ImagePath);
						}
						GotLoadedImage=true;
					}
					Invalidate();
					break;
				case SKETCHUPDATE:
					pDoc->m_bChatChange=false;
					SketchAvailable=TRUE;
					//AddToListbox(temp.data,temp.type);
					LocalSketch.RemoveAll();
					if(pDoc->Sketch.GetSize())
					{
//						LocalSketch.Add(pDoc->Sketch.GetAt(pDoc->Sketch.GetSize()-1));
						for(j=0;j<pDoc->Sketch.GetSize();j++)
								LocalSketch.Add(pDoc->Sketch.GetAt(j));
					}
					else 
						SketchAvailable=FALSE;
					Invalidate();
					break;
				case SKETCH:
					pDoc->m_bChatChange=false;
					LocalSketch.RemoveAll();
					SketchAvailable=TRUE;
					if(pDoc->Sketch.GetSize())
					{
					//	AddToListbox(temp.data,temp.type);
			
						for(j=0;j<pDoc->Sketch.GetSize();j++)
								LocalSketch.Add(pDoc->Sketch.GetAt(j));
					}
					else 
						SketchAvailable=FALSE;
					Invalidate();
					break;
				case CHATNEWPLAYER:
					
						for(k=0;k<MAXNUMCLIENTS;k++)
						{
							pHead[k]= (CStatic*)GetDlgItem(IDC_HEAD1+k);
							pNames[k]=  (CStatic*)GetDlgItem(IDC_CHARN1+k);
						}
						for(l=0;l<MAXNUMCLIENTS;l++)
						{
								pNames[l]->ShowWindow(SW_HIDE);
								pHead[l]->ShowWindow(SW_HIDE);	
						}
						for(j=0;j<pDoc->PlayerNames.GetSize();j++)
						{
							//m_userbox.AddString(pDoc->mUsername.GetAt(j));
							pNames[j]->SetWindowText(pDoc->PlayerNames.GetAt(j));
							if(pDoc->PlayerHeads[j] < pDoc->MaxHeadBitmaps)
								pHead[j]->SetBitmap(headbmp[pDoc->PlayerHeads[j]]);
							else
								pHead[j]->SetBitmap(headbmp[0]);
							pHead[j]->ShowWindow(SW_SHOW);
							pNames[j]->ShowWindow(SW_SHOW);
						}
					
					Invalidate();
					break;
				default:
					AddToListbox(temp.data,temp.type);
			}

		}
		pDoc->ChatBarrel.RemoveAll();	
	}	

}


void CChatView::OnDraw(CDC* pDC) 
{
	
//	CDnDDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
	// TODO: Add your specialized code here and/or call the base class

	CString debug;
	int deb=0;
	int kort=0;
	CRect rect;
	CPoint pos;
	WINDOWPLACEMENT wsketch2;
	wsketch2.length=sizeof(WINDOWPLACEMENT);
	CPen* penold;
	CPen pen;
	
	CBrush* brushold;
	m_miniature.GetWindowPlacement(&wsketch2);
	CPTGameObject obj;
	int xlarge=pDoc->sketchEndPoint.x;
	int ylarge=pDoc->sketchEndPoint.y;
	int xsmall=wsketch2.rcNormalPosition.right-wsketch2.rcNormalPosition.left;
	int ysmall=wsketch2.rcNormalPosition.bottom-wsketch2.rcNormalPosition.top;
	float	xscale=1;
	float yscale=1;


	xscale=(float)xlarge/(float)xsmall;
	yscale=(float)ylarge/(float)ysmall;



	CBrush brush(RGB(100,100,100));
	//pDC->Rectangle(&wsketch2.rcNormalPosition);
	//tekenen van het perkament

	switch(sketchmode)
	{
	case 2:
	DrawTransparentResizedBitmap(pDC,&sketch,
		wsketch2.rcNormalPosition.left-30,wsketch2.rcNormalPosition.top-30,
		RGB(255,255,255),
		wsketch2.rcNormalPosition.right+50-wsketch2.rcNormalPosition.left
		,wsketch2.rcNormalPosition.bottom+50-wsketch2.rcNormalPosition.top,COLORONCOLOR);
		break;
	case 3:

	DrawTransparentResizedBitmap(pDC,&sketch,
		wsketch2.rcNormalPosition.left-30,wsketch2.rcNormalPosition.top-30,
		RGB(255,255,255),
		wsketch2.rcNormalPosition.right+50-wsketch2.rcNormalPosition.left
		,wsketch2.rcNormalPosition.bottom+50-wsketch2.rcNormalPosition.top,HALFTONE);
	break;
	case 1:
		pDC->Rectangle(&wsketch2.rcNormalPosition);
		break;
	};

	pos.x=wsketch2.rcNormalPosition.left;
	pos.y=wsketch2.rcNormalPosition.top;
	CSize size;
	size.cx=wsketch2.rcNormalPosition.right-10-wsketch2.rcNormalPosition.left;
	size.cy=wsketch2.rcNormalPosition.bottom-10-wsketch2.rcNormalPosition.top;

	if(GotLoadedImage)
	{
		APicture.Draw(pDC,pos,size);
	}

	if(SketchAvailable)
	{

	for(int lli=0;lli<LocalSketch.GetSize();lli++)
	{
		obj=LocalSketch.GetAt(lli);
		if(obj.m_nOnSketch)
		{
			switch(obj.m_nObjType)
			{
				case LINE:

					pen.CreatePen(PS_SOLID,1,obj.outside_color);
				
					penold=(CPen*)pDC->SelectObject(&pen);
					
					pos.x=obj.m_ptPos2.x/xscale+wsketch2.rcNormalPosition.left;
					pos.y=obj.m_ptPos2.y/yscale+wsketch2.rcNormalPosition.top;
					pDC->MoveTo(pos);
					
					pos.x=obj.m_ptPos1.x/xscale+wsketch2.rcNormalPosition.left;
					pos.y=obj.m_ptPos1.y/yscale+wsketch2.rcNormalPosition.top;
					pDC->LineTo(pos);
					pen.DeleteObject();
					pDC->SelectObject(penold);
					
					break;
				case CIRCLE:
					pen.CreatePen(PS_SOLID,1,obj.outside_color);
					penold=(CPen*)pDC->SelectObject(&pen);
					brush.Detach();
					brush.CreateSolidBrush(obj.inside_color);
				
					brushold=(CBrush*)pDC->SelectObject(&brush);
					rect.top=obj.m_ptPos1.y/yscale+wsketch2.rcNormalPosition.top;
					rect.bottom=obj.m_ptPos2.y/yscale+wsketch2.rcNormalPosition.bottom;
					rect.left=obj.m_ptPos1.x/xscale+wsketch2.rcNormalPosition.left;
					rect.right=obj.m_ptPos2.x/xscale+wsketch2.rcNormalPosition.right;
					pDC->Ellipse(rect);
					
					pDC->SelectObject(penold);
					pen.DeleteObject();

					pDC->SelectObject(brushold);

					break;
				default:
					pDC->TextOut(5,5,"Uknown figure");
				
			}

				
		}

	}
	
	}
	
}




void CChatView::OnHeadme() 
{
	// TODO: Add your control notification handler code here
	
	AfxMessageBox("This dialogscreen has not been implemented yet.Sorry for the inconveniece.");
}

void CChatView::OnChatoptions() 
{
	// TODO: Add your control notification handler code here
	CChatOptions dlg;
	dlg.m_sketchres=sketchmode;
	if(IDOK==dlg.DoModal())
	{
		sketchmode=dlg.m_sketchres;
	}
	Invalidate();
}
