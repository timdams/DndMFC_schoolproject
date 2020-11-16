// DnDMapPlay.cpp : implementation file
//

#include "stdafx.h"
#include "DnD.h"
#include "DnDMapPlay.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDnDMapPlay

IMPLEMENT_DYNCREATE(CDnDMapPlay, CFormView)

CDnDMapPlay::CDnDMapPlay()
	: CFormView(CDnDMapPlay::IDD)
{
	//{{AFX_DATA_INIT(CDnDMapPlay)
	m_StrSend = _T("");
	//}}AFX_DATA_INIT
}

CDnDMapPlay::~CDnDMapPlay()
{
}

void CDnDMapPlay::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDnDMapPlay)
	DDX_Control(pDX, IDC_LIST1, m_chatmapbox);
	DDX_Control(pDX, IDC_MAPAREA, m_maparea);
	DDX_Text(pDX, IDC_MAPCHAT, m_StrSend);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDnDMapPlay, CFormView)
	//{{AFX_MSG_MAP(CDnDMapPlay)
	ON_BN_CLICKED(IDC_BTNCHAT, OnBtnchat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDnDMapPlay diagnostics

#ifdef _DEBUG
void CDnDMapPlay::AssertValid() const
{
	CFormView::AssertValid();
}

void CDnDMapPlay::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG
CDnDDoc* CDnDMapPlay::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDnDDoc)));
	return (CDnDDoc*)m_pDocument;
}

/////////////////////////////////////////////////////////////////////////////
// CDnDMapPlay message handlers

void CDnDMapPlay::OnInitialUpdate() 
{
	 pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	lines=0;
	MapLoaded=FALSE;
	CFormView::OnInitialUpdate();
	m_blocksize=30;
	showgrid=0;
	layer=1;
	wmap.length=sizeof(WINDOWPLACEMENT);
	m_maparea.GetWindowPlacement(&wmap);
	int resizerke=wmap.rcNormalPosition.right-wmap.rcNormalPosition.left;
	resizerke=resizerke/m_blocksize;
	wmap.rcNormalPosition.right=m_blocksize*resizerke+wmap.rcNormalPosition.left;
	resizerke=wmap.rcNormalPosition.bottom-wmap.rcNormalPosition.top;
	resizerke=resizerke/m_blocksize;
	wmap.rcNormalPosition.bottom=m_blocksize*resizerke+wmap.rcNormalPosition.top;

	HiRes=FALSE;

	//visibility layer aanzetten
	int xbreedte=wmap.rcNormalPosition.right-wmap.rcNormalPosition.left;
	int ylengte=wmap.rcNormalPosition.bottom-wmap.rcNormalPosition.top;
	int xborder=xbreedte/m_blocksize;
	int yborder=ylengte/m_blocksize;
	int j,i=0;
	CPTGameObject obj;
	for(i=0;i<160;i++)
	{
		for(j=0;j<160;j++)
			PlayerVisible[i][j]=0;
	}
	
//	CDnDDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
	if(pDoc->Map.GetSize())
		MapLoaded=TRUE;
	Invalidate();
	
	// TODO: Add your specialized code here and/or call the base class

}

void CDnDMapPlay::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	CPTGameObject obj;
	CRect posbl;
	CPen pen;
	pen.CreatePen(PS_SOLID,1,RGB(0,0,0));
	CPen pennull;
	
	pennull.CreatePen(PS_NULL,1,RGB(0,0,0));
	CBrush brushlwhite(RGB(220,220,220));
	CBrush brushred(RGB(250,0,0));
	CBrush brushlred(RGB(220,20,50));
	CBrush brushbrown(RGB(139,45,13));
	CBrush brushyellow(RGB(255,255,0));
	CBrush brushblack(RGB(1,1,1));
	CBrush brushmonster(RGB(80,96,18));
//	CBrush brushdmvis(HS_BDIAGONAL,RGB(0,0,0));
	CBrush brushdmvis(HS_DIAGCROSS,RGB(0,0,0));

	CBrush brushhatch(HS_DIAGCROSS,RGB(1,1,1));
	CPen penbrown(PS_SOLID,2,RGB(150,0,150));
	CPen penyellow(PS_SOLID,1,RGB(255,255,0));
	CBrush brushlgreen(RGB(40,255,0));
	CBrush brushdgreen(RGB(150,255,80));
	CBrush brushgreen(RGB(0,255,0));
	CBrush* brushold;
	CPen* penold;
	CPoint StartPos;
	CString out;
	int ylengte; //lengte van tekenveld
	int xbreedte;//breedte van tekenveld
	xbreedte=wmap.rcNormalPosition.right-wmap.rcNormalPosition.left;
	ylengte=wmap.rcNormalPosition.bottom-wmap.rcNormalPosition.top;
	
	
	int blocksize=m_blocksize;
	int size=0;
	int type=0;

	penold=(CPen*)pDC->SelectObject(&pen);
	
	pDC->SetBkMode(TRANSPARENT);
	//mapveld met vakjes teken
	brushold=(CBrush*)pDC->SelectObject(&brushlwhite);
	pDC->Rectangle(&wmap.rcNormalPosition);
	if(showgrid)
	{
		for(int i=0;i<=xbreedte/blocksize;i++)
		{
		
			StartPos.x=wmap.rcNormalPosition.left+i*blocksize;
			StartPos.y=wmap.rcNormalPosition.top;
			pDC->MoveTo(StartPos);
			pDC->LineTo(StartPos.x,wmap.rcNormalPosition.bottom);
		}

		for(int y=0;y<=ylengte/blocksize;y++)
		{
		
			StartPos.x=wmap.rcNormalPosition.left;
			StartPos.y=wmap.rcNormalPosition.top+y*blocksize;
			pDC->MoveTo(StartPos);
			pDC->LineTo(wmap.rcNormalPosition.right,StartPos.y);
		}
	}
		pDC->SelectObject(brushold);

	if(!MapLoaded)
	{
		CString info;
		info.Format("No map currently loaded");
		pDC->TextOut(wmap.rcNormalPosition.left+10,wmap.rcNormalPosition.top+10,info);
	}

	else
	{
		for(int j=0;j<LocalMap.GetSize();j++)
		{
			obj=LocalMap.GetAt(j);
			if(size=obj.m_nOnSketch)
			{
				type=obj.m_nObjType;
				switch(type)
				{
				case MONSTER:
					if((layer==1 && PlayerVisible[obj.m_ptPos1.x][obj.m_ptPos1.y])||layer==0|| layer==2)
					{
						brushold=(CBrush*)pDC->SelectObject(&brushmonster);
						penold=(CPen*)pDC->SelectObject(&pennull);
						posbl.left=obj.m_ptPos1.x*obj.m_nOnSketch+wmap.rcNormalPosition.left+showgrid;
						posbl.top=obj.m_ptPos1.y*obj.m_nOnSketch+wmap.rcNormalPosition.top+showgrid;
						posbl.right=posbl.left+size;
						posbl.bottom=posbl.top+size;
						pDC->Ellipse(&posbl);
						
						if(m_blocksize>16) //anders overlapt tekst andere vakken
						{
							out.Format("%i",obj.m_nFlags);
							penold=(CPen*)pDC->SelectObject(&penyellow);
							pDC->SetBkMode(TRANSPARENT);
							pDC->TextOut(posbl.left+1,posbl.top+1,out);
							pDC->SetBkMode(OPAQUE);
						}
					}
					break;
				case PLAYER:
					if((layer==1&& PlayerVisible[obj.m_ptPos1.x][obj.m_ptPos1.y])||layer==0|| layer==2)
					{
						switch(obj.m_nFlags)
						{
						case FAMILIAR:brushold=(CBrush*)pDC->SelectObject(&brushdgreen);out.Format("F"); break;
						case PARTY:brushold=(CBrush*)pDC->SelectObject(&brushlgreen);out.Format("P"); break;
						default: brushold=(CBrush*)pDC->SelectObject(&brushgreen);out.Format("%i",obj.m_nFlags);
						};
						
						penold=(CPen*)pDC->SelectObject(&pennull);
						posbl.left=obj.m_ptPos1.x*obj.m_nOnSketch+wmap.rcNormalPosition.left+showgrid;
						posbl.top=obj.m_ptPos1.y*obj.m_nOnSketch+wmap.rcNormalPosition.top+showgrid;
						posbl.right=posbl.left+size;
						posbl.bottom=posbl.top+size;
						if(HiRes)
						{
/*							if(obj.m_nFlags==PARTY)
								DrawTransparentResizedBitmap(pDC,&bmp_partytile,posbl.left,posbl.top,RGB(201,201,201),m_blocksize,m_blocksize);
							else if(obj.m_nFlags!=FAMILIAR)
								DrawTransparentResizedBitmap(pDC,&bmp_herotile,posbl.left,posbl.top,RGB(201,201,201),m_blocksize,m_blocksize);
*/
						}
						else
						pDC->Ellipse(posbl);
						 
						if(m_blocksize>16) //anders overlapt tekst andere vakken
						{
							penold=(CPen*)pDC->SelectObject(&penyellow);
							pDC->SetBkMode(TRANSPARENT);
							pDC->TextOut(posbl.left+1,posbl.top+1,out);
							pDC->SetBkMode(OPAQUE);
						}
					}
					break;
				case ITEM:
					if((layer==1&& PlayerVisible[obj.m_ptPos1.x][obj.m_ptPos1.y])||layer==0|| layer==2)
					{

						switch(obj.m_nFlags)
						{
						case PIT:brushold=(CBrush*)pDC->SelectObject(&brushblack);	break;
						case PILLAR:brushold=(CBrush*)pDC->SelectObject(&brushlwhite);	break;
						case TRAP:brushold=(CBrush*)pDC->SelectObject(&brushhatch);	break;
						case FURNITURE:brushold=(CBrush*)pDC->SelectObject(&brushbrown);	break;
						case TREASURE:brushold=(CBrush*)pDC->SelectObject(&brushyellow);	break;	
						default:brushold=(CBrush*)pDC->SelectObject(&brushblack);
						};
						penold=(CPen*)pDC->SelectObject(&pennull);
						if(HiRes)
						{
/*							if(obj.m_nFlags!=PILLAR)
							{
							posbl.left=obj.m_ptPos1.x*obj.m_nOnSketch+wmap.rcNormalPosition.left+showgrid;
							posbl.top=obj.m_ptPos1.y*obj.m_nOnSketch+wmap.rcNormalPosition.top+showgrid;
							posbl.right=posbl.left+size;
							posbl.bottom=posbl.top+size;
							switch(obj.m_nFlags)
							{
								case PIT:DrawTransparentResizedBitmap(pDC,&bmp_pittile,posbl.left,posbl.top,RGB(201,201,201),m_blocksize,m_blocksize);break;
								case FURNITURE:DrawTransparentResizedBitmap(pDC,&bmp_furnituretile,posbl.left,posbl.top,RGB(201,201,201),m_blocksize,m_blocksize);break;
								case TREASURE:DrawTransparentResizedBitmap(pDC,&bmp_treasuretile,posbl.left,posbl.top,RGB(201,201,201),m_blocksize,m_blocksize);break;	
							};
							}
							else
							{

								posbl.left=obj.m_ptPos1.x*obj.m_nOnSketch+wmap.rcNormalPosition.left+showgrid;
								posbl.top=obj.m_ptPos1.y*obj.m_nOnSketch+wmap.rcNormalPosition.top+showgrid;
								posbl.right=posbl.left+size;
								posbl.bottom=posbl.top+size;
								pDC->Ellipse(posbl);
								
							}
					*/	}
						else
						{
							if(obj.m_nFlags!=PILLAR)
							{	
							pDC->SetBkMode(OPAQUE);			
							posbl.left=obj.m_ptPos1.x*obj.m_nOnSketch+wmap.rcNormalPosition.left+showgrid;
							posbl.top=obj.m_ptPos1.y*obj.m_nOnSketch+wmap.rcNormalPosition.top+showgrid;
							posbl.right=posbl.left+size;
							posbl.bottom=posbl.top+size;
							pDC->Rectangle(&posbl);
							pDC->SetBkMode(TRANSPARENT);
							}
							else
							{
								
								posbl.left=obj.m_ptPos1.x*obj.m_nOnSketch+wmap.rcNormalPosition.left+showgrid;
								posbl.top=obj.m_ptPos1.y*obj.m_nOnSketch+wmap.rcNormalPosition.top+showgrid;
								posbl.right=posbl.left+size;
								posbl.bottom=posbl.top+size;
								pDC->Ellipse(posbl);
							}
						}
					}
					break;
				case DOOR:
					if((layer==1&& PlayerVisible[obj.m_ptPos1.x][obj.m_ptPos1.y])||layer==0|| layer==2)
					{
						brushold=(CBrush*)pDC->SelectObject(&brushlred);
						penold=(CPen*)pDC->SelectObject(&pennull);
						posbl.left=obj.m_ptPos1.x*obj.m_nOnSketch+wmap.rcNormalPosition.left+showgrid;
						posbl.top=obj.m_ptPos1.y*obj.m_nOnSketch+wmap.rcNormalPosition.top+showgrid;
						posbl.right=posbl.left+size;
						posbl.bottom=posbl.top+size;
						if(HiRes)
						{
				/*			DrawTransparentResizedBitmap(pDC,&bmp_corridortile,posbl.left,posbl.top,RGB(0,0,-50),m_blocksize,m_blocksize);
							penold=(CPen*)pDC->SelectObject(&penbrown);
							if(obj.m_nFlags==1) //Vertical
							{
								pDC->MoveTo(posbl.left+(m_blocksize/2),posbl.top);
								pDC->LineTo(posbl.left+(m_blocksize/2),posbl.bottom-showgrid);
							}
							else
							{
								pDC->MoveTo(posbl.left,posbl.top+(m_blocksize/2));
								pDC->LineTo(posbl.right-showgrid,posbl.top+(m_blocksize/2));
							}
				*/		}
						else
						{
							pDC->Rectangle(&posbl);
							penold=(CPen*)pDC->SelectObject(&penbrown);
							if(obj.m_nFlags==1) //Vertical
							{
								pDC->MoveTo(posbl.left+(m_blocksize/2),posbl.top);
								pDC->LineTo(posbl.left+(m_blocksize/2),posbl.bottom-showgrid);
							}
							else
							{
								pDC->MoveTo(posbl.left,posbl.top+(m_blocksize/2));
								pDC->LineTo(posbl.right-showgrid,posbl.top+(m_blocksize/2));
							}
						}
					}
					break;
				case ROOM:
					if((layer==1&& PlayerVisible[obj.m_ptPos1.x][obj.m_ptPos1.y])||layer==0|| layer==2)
					{
						brushold=(CBrush*)pDC->SelectObject(&brushred);
						penold=(CPen*)pDC->SelectObject(&pennull);
						posbl.left=obj.m_ptPos1.x*obj.m_nOnSketch+wmap.rcNormalPosition.left+showgrid;
						posbl.top=obj.m_ptPos1.y*obj.m_nOnSketch+wmap.rcNormalPosition.top+showgrid;
						posbl.right=posbl.left+size;
						posbl.bottom=posbl.top+size;
					//	if(HiRes)
					//	DrawTransparentResizedBitmap(pDC,&bmp_roomtile,posbl.left,posbl.top,RGB(0,0,-50),m_blocksize,m_blocksize);
					//	else
						pDC->Rectangle(&posbl);
					}
					break;
				case CORRIDOR:
					if((layer==1&& PlayerVisible[obj.m_ptPos1.x][obj.m_ptPos1.y])||layer==0|| layer==2)
					{
						brushold=(CBrush*)pDC->SelectObject(&brushlred);
						penold=(CPen*)pDC->SelectObject(&pennull);
						posbl.left=obj.m_ptPos1.x*obj.m_nOnSketch+wmap.rcNormalPosition.left+showgrid;
						posbl.top=obj.m_ptPos1.y*obj.m_nOnSketch+wmap.rcNormalPosition.top+showgrid;
						posbl.right=posbl.left+size;
						posbl.bottom=posbl.top+size;
					//	if(HiRes)
					//		DrawTransparentResizedBitmap(pDC,&bmp_corridortile,posbl.left,posbl.top,RGB(0,0,-50),m_blocksize,m_blocksize);
					//	else
							pDC->Rectangle(&posbl);
					}
					break;
				default:
					brushold=(CBrush*)pDC->SelectObject(&brushred);
					penold=(CPen*)pDC->SelectObject(&pennull);
					posbl.left=obj.m_ptPos1.x*obj.m_nOnSketch+wmap.rcNormalPosition.left+showgrid;
					posbl.top=obj.m_ptPos1.y*obj.m_nOnSketch+wmap.rcNormalPosition.top+showgrid;
					posbl.right=posbl.left+size;
					posbl.bottom=posbl.top+size;
				//	if(HiRes)
				//		DrawTransparentResizedBitmap(pDC,&bmp_corridortile,posbl.left,posbl.top,RGB(0,0,-50),m_blocksize,m_blocksize);
				//	else
						pDC->Rectangle(&posbl);
				}

			}
		}
	}


	pDC->SelectObject(brushold);
	pDC->SelectObject(penold);	
	
}

void CDnDMapPlay::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	//CDnDDoc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);

	CBarrel temp;
	int j=0;
	int size=pDoc->MapBarrel.GetSize();

	if(size!=0)
	{
		for(int i=0;i<size;i++)
		{
			temp=pDoc->MapBarrel.GetAt(i);
			switch(temp.type)
			{
					
				case CHATTEXT:
				case PRIVATECHAT:
				case ADMINCHAT:
				case CHAT:
					m_chatmapbox.AddString(temp.data);
					m_chatmapbox.SetCurSel(m_chatmapbox.GetCount()-1);
				break;
				case MAPVIS:
					for(i=0;i<pDoc->MapBlocks.x;i++)
					{
						for(j=0;j<pDoc->MapBlocks.y;j++)
							PlayerVisible[i][j]=pDoc->PlayerVisible[i][j];
					//	PlayerVisible[i][j]=1;

					}
					break;
				case MAPDM:
				
					MapLoaded=TRUE;
					LocalMap.RemoveAll();
					if(pDoc->Map.GetSize())
					{
						for(j=0;j<pDoc->Map.GetSize();j++)
								LocalMap.Add(pDoc->Map.GetAt(j));

					
					}
				
					else 
						MapLoaded=FALSE;
					break;

			}

		}
		Invalidate();

		pDoc->MapBarrel.RemoveAll();
	}	
	
}

void CDnDMapPlay::OnBtnchat() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	if(pDoc->m_bConnected)
	{
		m_chatmapbox.AddString("Send: "+m_StrSend);

		pDoc->m_sSend=m_StrSend;
		pDoc->Send(CHAT);

		CStatic* pStaticOutput=(CStatic*)GetDlgItem(IDC_MAPCHAT);
		pStaticOutput->SetWindowText("");
	}
}
