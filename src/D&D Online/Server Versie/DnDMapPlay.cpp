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
	m_maptitle = _T("");
	m_strSend = _T("");
	//}}AFX_DATA_INIT
}

CDnDMapPlay::~CDnDMapPlay()
{
}

void CDnDMapPlay::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDnDMapPlay)
	DDX_Control(pDX, IDC_CHATINMAP, m_chatmap);
	DDX_Control(pDX, IDC_Start, m_playbutton);
	DDX_Control(pDX, IDC_UNHIDE, m_hidebutton);
	DDX_Control(pDX, IDC_COMBOAREA, m_hidearea);
	DDX_Control(pDX, IDC_DOWN, m_down);
	DDX_Control(pDX, IDC_LEFT, m_left);
	DDX_Control(pDX, IDC_RIGHT, m_right);
	DDX_Control(pDX, IDC_UP, m_up);
	DDX_Control(pDX, IDC_CHECKNAME2, m_checkname2);
	DDX_Control(pDX, IDC_CHECKNAME, m_checkname1);
	DDX_Control(pDX, IDC_VISCOMBO, m_visctl);
	DDX_Control(pDX, IDC_MAP, m_maparea);
	DDX_Text(pDX, IDC_STATMAPTITLE, m_maptitle);
	DDX_Text(pDX, IDC_CHATMAP, m_strSend);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDnDMapPlay, CFormView)
	//{{AFX_MSG_MAP(CDnDMapPlay)
	ON_BN_CLICKED(IDC_LOADMAP, OnLoadmap)
	ON_CBN_SELCHANGE(IDC_VISCOMBO, OnSelchangeViscombo)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_UP, OnUp)
	ON_BN_CLICKED(IDC_DOWN, OnDown)
	ON_BN_CLICKED(IDC_LEFT, OnLeft)
	ON_BN_CLICKED(IDC_RIGHT, OnRight)
	ON_BN_CLICKED(IDC_CHECKNAME, OnCheckname)
	ON_BN_CLICKED(IDC_CHECKNAME2, OnCheckname2)
	ON_BN_CLICKED(IDC_UNHIDE, OnUnhide)
	ON_BN_CLICKED(IDC_Start, OnStart)
	ON_BN_CLICKED(IDC_CHATSEND, OnChatsend)
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

	else{
		for(int j=0;j<MapItems.GetSize();j++)
		{
			obj=MapItems.GetAt(j);
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
							if(obj.m_nFlags==PARTY)
								DrawTransparentResizedBitmap(pDC,&bmp_partytile,posbl.left,posbl.top,RGB(201,201,201),m_blocksize,m_blocksize);
							else if(obj.m_nFlags!=FAMILIAR)
								DrawTransparentResizedBitmap(pDC,&bmp_herotile,posbl.left,posbl.top,RGB(201,201,201),m_blocksize,m_blocksize);

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
							if(obj.m_nFlags!=PILLAR)
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
						}
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
							DrawTransparentResizedBitmap(pDC,&bmp_corridortile,posbl.left,posbl.top,RGB(0,0,-50),m_blocksize,m_blocksize);
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
						if(HiRes)
						DrawTransparentResizedBitmap(pDC,&bmp_roomtile,posbl.left,posbl.top,RGB(0,0,-50),m_blocksize,m_blocksize);
						else
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
						if(HiRes)
							DrawTransparentResizedBitmap(pDC,&bmp_corridortile,posbl.left,posbl.top,RGB(0,0,-50),m_blocksize,m_blocksize);
						else
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
					if(HiRes)
						DrawTransparentResizedBitmap(pDC,&bmp_corridortile,posbl.left,posbl.top,RGB(0,0,-50),m_blocksize,m_blocksize);
					else
						pDC->Rectangle(&posbl);
				}

			}
		}
	}
	//visibility layer van dm
	int i,j;
	if(layer==2)
	{
		pDC->SetBkMode(TRANSPARENT);
		brushold=(CBrush*)pDC->SelectObject(&brushdmvis);
		penold=(CPen*)pDC->SelectObject(&pennull);

		for(i=0;i<=MapBlocks.x;i++)
		{
			for(j=0;j<=MapBlocks.y;j++)
			{
				
				if(!PlayerVisible[i][j])
				{
					posbl.left=i*size+wmap.rcNormalPosition.left;
					posbl.top=j*size+wmap.rcNormalPosition.top;
					posbl.right=posbl.left+size;
					posbl.bottom=posbl.top+size;
					pDC->Rectangle(&posbl);	
				}
			}

		}
	}

		pDC->SelectObject(brushold);
	pDC->SelectObject(penold);
	
	
}

void CDnDMapPlay::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class

	// TODO: Add your specialized code here and/or call the base class
	MapLoaded=FALSE;
	m_blocksize=30;
	m_hidebutton.EnableWindow(FALSE);
	showgrid=0;
	tool=SELECT;
	layer=0;
	m_visctl.SetCurSel(0);
	m_hidearea.SetCurSel(0);
	selitem1=-1;
	selitem2=-1;
	bPlaying=FALSE;
	wmap.length=sizeof(WINDOWPLACEMENT);
	m_maparea.GetWindowPlacement(&wmap);
	int resizerke=wmap.rcNormalPosition.right-wmap.rcNormalPosition.left;
	resizerke=resizerke/m_blocksize;
	wmap.rcNormalPosition.right=m_blocksize*resizerke+wmap.rcNormalPosition.left;
	
	resizerke=wmap.rcNormalPosition.bottom-wmap.rcNormalPosition.top;
	resizerke=resizerke/m_blocksize;
	wmap.rcNormalPosition.bottom=m_blocksize*resizerke+wmap.rcNormalPosition.top;
	HiRes=FALSE;
	bmp_roomtile.LoadBitmap(TILE_ROOM);
	bmp_corridortile.LoadBitmap(TILE_CORRIDOR);
	bmp_herotile.LoadBitmap(TILE_HERO);
	bmp_partytile.LoadBitmap(TILE_PARTY);
	bmp_pittile.LoadBitmap(TILE_PIT);
	bmp_treasuretile.LoadBitmap(TILE_TREASURE);
	bmp_furnituretile.LoadBitmap(TILE_FURNITURE);

		m_up.EnableWindow(FALSE);
		m_down.EnableWindow(FALSE);
		m_left.EnableWindow(FALSE);
		m_right.EnableWindow(FALSE);
		//info afzette
	selectedblock.x=-1;
	selectedblock.y=-1;
	EnableBlock();
	UpdateData(FALSE);

	
}

void CDnDMapPlay::OnLoadmap() 
{
	// TODO: Add your control notification handler code here
	CString tmp;

	
	CString path,filename;
	CPTGameObject obj;
	CFileDialog *dlg;
	int size;
	dlg= new CFileDialog(TRUE,NULL,"",NULL,"Setting Files (*.ddm)|*.ddm|All Files (*.*)|*.*",this);
	if(IDOK==dlg->DoModal())
	{
			path=dlg->GetPathName();
			filename=dlg->GetFileName();
	}
	dlg->Detach();
	CFile outFile(path,CFile::modeRead);
	CArchive arIn(&outFile,CArchive::load);
	arIn>>size;
	MapItems.RemoveAll();
	for(int i=0;i<size;i++)
	{
		obj.Serialize(arIn);
		MapItems.Add(obj);
	}
	arIn>>tmp;
	m_maptitle=tmp;
	m_blocksize=obj.m_nOnSketch;
	if(MapItems.GetSize())
	{
		MapLoaded=TRUE;
		if(!MakeVisibilityLayer(0)) //we maken layer waar spelers reeds hun vakje zien
			AfxMessageBox("Error occured during making of Visibility layer. Please open map in editor and resave it");
	}
	else
	{
		MapLoaded=FALSE;
		AfxMessageBox("This map is empty(most likely), corrupted or outdated.Please remake it in the editor");
	}
		UpdateData(FALSE);

	xbreedte=wmap.rcNormalPosition.right-wmap.rcNormalPosition.left;

	ylengte=wmap.rcNormalPosition.bottom-wmap.rcNormalPosition.top;
	Invalidate();

}

void CDnDMapPlay::DrawTransparentBitmap(CDC *pDC, CBitmap *pBitmap, short xStart, short yStart, COLORREF cTransparentColor, short xEnd,short yEnd)
{
	//Code gevonde in voorbeeldprogramma op codeproject.com	
	//Heb ik tot in den treure gebruikt in Paratrooper. Good toh have this hun back ;)
	// Copiously plagiarized from the Microsoft Knowledge Base,
	// article Q79212...though I did convert it to C++/MFC.
	CDC dcTemp;
	dcTemp.CreateCompatibleDC(pDC);
	dcTemp.SelectObject(pBitmap);

	BITMAP bm;
	pBitmap->GetBitmap(&bm);
	POINT ptSize;
//	ptSize.x = bm.bmWidth;		// Get width of bitmap
//	ptSize.y = bm.bmHeight;		// Get height of bitmap
	ptSize.x = xEnd;
	ptSize.y = yEnd;
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
	pDC->BitBlt(xStart,yStart,ptSize.x,ptSize.y,&dcMem,0,0,SRCCOPY);
//	pDC->StretchBlt(xStart,yStart,ptSize.x,ptSize.y,&dcMem,0,0,xEnd,yEnd,SRCCOPY);
	// Restore the original bitmap.
	dcTemp.BitBlt(0,0,ptSize.x,ptSize.y,&dcSave,0,0,SRCCOPY);

	// Delete the memory bitmaps.
	dcBack.SelectObject(bmBackOld);
	dcObject.SelectObject(bmObjectOld);
	dcMem.SelectObject(bmMemOld);
	dcSave.SelectObject(bmSaveOld);
}
void CDnDMapPlay::DrawTransparentResizedBitmap(CDC *pDC, CBitmap *pBitmap, short xStart, short yStart, COLORREF cTransparentColor, short xEnd,short yEnd)
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
	pDC->SetStretchBltMode(COLORONCOLOR);
	pDC->StretchBlt(xStart,yStart,xEnd,yEnd,&dcMem,0,0,ptSize.x,ptSize.y,SRCCOPY);
		
	// Restore the original bitmap.
	dcTemp.BitBlt(0,0,ptSize.x,ptSize.y,&dcSave,0,0,SRCCOPY);

	// Delete the memory bitmaps.
	dcBack.SelectObject(bmBackOld);
	dcObject.SelectObject(bmObjectOld);
	dcMem.SelectObject(bmMemOld);
	dcSave.SelectObject(bmSaveOld);
}

void CDnDMapPlay::OnSelchangeViscombo() 
{
	// TODO: Add your control notification handler code here
	layer=m_visctl.GetCurSel();
	if(layer==2)
	{
		m_hidebutton.EnableWindow(TRUE);
		m_hidearea.EnableWindow(TRUE);
		tool=HIDE;
	}
	else
	{	
		m_hidebutton.EnableWindow(FALSE);
		tool=SELECT;
		m_hidearea.EnableWindow(FALSE);
	}
	
	Invalidate();
}

void CDnDMapPlay::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CPTGameObject obj,obj2;
	CPoint pos,tmp;
	int j,i=0;
	int k=-1;
	int blocksize=m_blocksize;
	CPoint roomsize;
	CString tmpstr,getal,tmpstr2;
	int areax=0;
	int areay=0;
	char ch;
	if(point.x>=wmap.rcNormalPosition.left && point.x<=wmap.rcNormalPosition.right)
	{
		if(point.y>=wmap.rcNormalPosition.top && point.y<=wmap.rcNormalPosition.bottom)
		{
			//info afzette
			selectedblock.x=-1;
			selectedblock.y=-1;
			m_checkname1.SetCheck(FALSE);
			m_checkname2.SetCheck(FALSE);

			EnableBlock();

			pos.x=(point.x-wmap.rcNormalPosition.left)/blocksize;
			pos.y=(point.y-wmap.rcNormalPosition.top)/blocksize;
			switch(tool)
			{
			case SELECT:
				if(pos==selectedblock) //deselect
				{
					selectedblock.x=-1;
					selectedblock.y=-1;
				}
				else  selectedblock=pos;
				//ding is geselcteerd,nu er nog iets mee doen....
				EnableBlock();
				break;
			case HIDE:
				m_hidearea.GetLBText(m_hidearea.GetCurSel(),tmpstr);
				for(i=0;i<tmpstr.GetLength();i++)
				{
					ch=tmpstr[i];
					if(ch!='x' && ch!='X')
					{
						tmpstr2=getal;
						getal.Format("%s%c",tmpstr2,ch);
					}
					else
					{
						areax=atoi(getal);
						getal.Empty();
		
					}

					areax=atoi(getal);
				}
				areay=atoi(getal);
				for(i=0;i<areax;i++)
				{
					for(j=0;j<areay;j++)
					{
						if(PlayerVisible[pos.x+i][pos.y+j])
						{
							PlayerVisible[pos.x+i][pos.y+j]=0;
							if(bPlaying)
								SendVisibilityUpdate(pos.x+i,pos.y+j,0);
						}
						else 
						{
							PlayerVisible[pos.x+i][pos.y+j]=1;
							if(bPlaying)
								SendVisibilityUpdate(pos.x+i,pos.y+j,1);
							
						}

					}

				}

			

				Invalidate();
				break;
			};
		}
	}
	CFormView::OnLButtonDown(nFlags, point);
}

void CDnDMapPlay::EnableBlock()
{
	CArray<CPTGameObject, CPTGameObject&> ThisBlock;
	CPTGameObject obj;
	CString info;
	int i;
	if(selectedblock.x!=-1 && MapItems.GetSize())
	{
		
		for(i=0;i<MapItems.GetSize();i++)
		{
			obj=MapItems.GetAt(i);
			if(obj.m_ptPos1==selectedblock && obj.m_nOnSketch && obj.m_nObjType!=ROOM && obj.m_nObjType!=DOOR && obj.m_nObjType!=CORRIDOR)
			{
				ThisBlock.Add(MapItems.GetAt(i));
				if(selitem1==-1)
					selitem1=i;
				else if(selitem2==-1)
					selitem2=i;
			}
		}
		switch(ThisBlock.GetSize())
		{
		case 3:
		case 4:
		case 5:
		case 2:
			obj=ThisBlock.GetAt(1);
			info.Format("%s-%s",DefinesConvert(obj.m_nObjType),DefinesConvert(obj.m_nFlags));
			if(obj.m_nObjType==PLAYER && obj.m_nFlags!=PARTY)
				info.Format("%s-Player %i",DefinesConvert(obj.m_nObjType),obj.m_nFlags);

			m_checkname2.SetWindowText(info);
			m_checkname2.EnableWindow(TRUE);
			
		case 1:
			obj=ThisBlock.GetAt(0);
			info.Format("%s-%s",DefinesConvert(obj.m_nObjType),DefinesConvert(obj.m_nFlags));
			if(obj.m_nObjType==PLAYER && obj.m_nFlags!=PARTY)
				info.Format("%s-Player %i",DefinesConvert(obj.m_nObjType),obj.m_nFlags);


			m_checkname1.SetWindowText(info);
			m_checkname1.EnableWindow(TRUE);
			break;
		case 0:	m_checkname1.EnableWindow(FALSE);m_checkname2.EnableWindow(FALSE);selitem2=selitem1=-1;
			break;


		};
	}
	else
	{
		m_checkname1.EnableWindow(FALSE);m_checkname2.EnableWindow(FALSE);
		selitem1=-1;selitem2=-1;
		m_up.EnableWindow(FALSE);
		m_down.EnableWindow(FALSE);
		m_left.EnableWindow(FALSE);
		m_right.EnableWindow(FALSE);

	}
	UpdateData(FALSE);
}

CString CDnDMapPlay::DefinesConvert(int def1)
{
	CString ret="No info";
	switch(def1)
	{
	case ROOM: ret="Room";break; 
	case CORRIDOR :ret="Room";break;
	case DOOR :ret="Door";break;
	case MONSTER :ret="Monster";break;
	case PLAYER :ret="Player";break;
	case TRAP :ret="Trap";break;
	case STAIR :ret="STAIR";break;
	case ITEM :ret="Item";break;
	case PIT :ret="Pit";break;
	case FURNITURE :ret="Furniture";break;
	case TREASURE :ret="Treasure";break;
	case PILLAR :ret="Pillar";break;
	case WATER :ret="Water";break;
	case FAMILIAR :ret="Familiar";break;
	case PARTY :ret="Party";break;
	};
	return ret;
}

void CDnDMapPlay::OnUp() 
{
	// TODO: Add your control notification handler code here
	MoveItem(UP);
}

void CDnDMapPlay::OnDown() 
{
	// TODO: Add your control notification handler code here
	MoveItem(DOWN);
}

void CDnDMapPlay::OnLeft() 
{
	// TODO: Add your control notification handler code here
	MoveItem(LEFT);
}

void CDnDMapPlay::OnRight() 
{
	// TODO: Add your control notification handler code here
	MoveItem(RIGHT);
}

void CDnDMapPlay::MoveItem(int direction)
{
	//welk item gaan we moven?
	int itemnr=-1;
	if(m_checkname1.GetCheck())
		itemnr=selitem1;
	else if(m_checkname2.GetCheck())
		itemnr=selitem2;

	// we gaan item 'itemnr' uit MapItems moven
	//dit gebeurt nog zonder controle voorlopig
	CPTGameObject obj;
	
	obj=MapItems.GetAt(itemnr);
	switch(direction)
	{
	case UP:
		obj.m_ptPos1.y=obj.m_ptPos1.y-1;
		if(obj.m_ptPos1.y<0)
			obj.m_ptPos1.y=0;
		break;
	case DOWN:
		obj.m_ptPos1.y=obj.m_ptPos1.y+1;
			if(obj.m_ptPos1.y*m_blocksize>=ylengte)	
				obj.m_ptPos1.y=obj.m_ptPos1.y-1;
		break;
	case LEFT:
		obj.m_ptPos1.x=obj.m_ptPos1.x-1;
		if(obj.m_ptPos1.x<0)
			obj.m_ptPos1.x=0;
		break;
	case RIGHT:
		obj.m_ptPos1.x=obj.m_ptPos1.x+1;
		if(obj.m_ptPos1.x*m_blocksize>=xbreedte)	
				obj.m_ptPos1.x=obj.m_ptPos1.x-1;
		break;
	}
	if(obj.m_nObjType==PLAYER)
	{
		PlayerVisible[obj.m_ptPos1.x][obj.m_ptPos1.y]=1;
		if(bPlaying)
		{
			SendVisibilityUpdate(obj.m_ptPos1.x,obj.m_ptPos1.y,1);
		}

	}
	//en terug in array steken
	MapItems.SetAt(itemnr,obj);
	if(bPlaying)
	{
		SentItemUpdate(itemnr, obj);
	}
	Invalidate();
}

void CDnDMapPlay::OnCheckname() 
{
	// TODO: Add your control notification handler code here
	if(m_checkname1.GetCheck())
	{
		m_up.EnableWindow(TRUE);
		m_down.EnableWindow(TRUE);
		m_left.EnableWindow(TRUE);
		m_right.EnableWindow(TRUE);
		m_checkname2.SetCheck(FALSE);
	}
	else
	{
		m_up.EnableWindow(FALSE);
		m_down.EnableWindow(FALSE);
		m_left.EnableWindow(FALSE);
		m_right.EnableWindow(FALSE);

	}

}

void CDnDMapPlay::OnCheckname2() 
{
	// TODO: Add your control notification handler code here
	if(m_checkname2.GetCheck())
	{
		m_up.EnableWindow(TRUE);
		m_down.EnableWindow(TRUE);
		m_left.EnableWindow(TRUE);
		m_right.EnableWindow(TRUE);
		m_checkname1.SetCheck(FALSE);

	}	
	else
	{

		m_up.EnableWindow(FALSE);
		m_down.EnableWindow(FALSE);
		m_left.EnableWindow(FALSE);
		m_right.EnableWindow(FALSE);
	}
}

int CDnDMapPlay::MakeVisibilityLayer(int type)
{
	int xbreedte=wmap.rcNormalPosition.right-wmap.rcNormalPosition.left;
	int ylengte=wmap.rcNormalPosition.bottom-wmap.rcNormalPosition.top;
	int xborder=xbreedte/m_blocksize;
	int yborder=ylengte/m_blocksize;
	MapBlocks.x=xborder;
	MapBlocks.y=yborder;
	int j,i=0;
	CPTGameObject obj;
	for(i=0;i<xborder;i++)
	{
		for(j=0;j<yborder;j++)
			PlayerVisible[i][j]=0;
	}
	if(type==0)
	{
		//voor allezekerheid reeds de party zichtbaarmaken
		for(i=0;i<MapItems.GetSize();i++)
		{
			obj=MapItems.GetAt(i);
			if(obj.m_nObjType==PLAYER)
				PlayerVisible[obj.m_ptPos1.x][obj.m_ptPos1.y]=1;
		}
	}
	return 1;
}

void CDnDMapPlay::OnUnhide() 
{
	// TODO: Add your control notification handler code here
/*	if(m_visctl.GetCurSel()==2)
		tool=HIDE;
	else
		tool=SELECT;*/
}

void CDnDMapPlay::OnStart() 
{
	// TODO: Add your control notification handler code here
	CString debug;
	int count=0;
	CDnDDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int i,j;
	if(MapLoaded && !bPlaying)
	{
		pDoc->Map.RemoveAll();
		for(i=0;i<MapItems.GetSize();i++)
		{
			pDoc->Map.Add(MapItems.GetAt(i));
			
		}
		for(i=0;i<MapBlocks.x;i++)
		{
			for(j=0;j<MapBlocks.y;j++)
				pDoc->PlayerVisible[i][j]=PlayerVisible[i][j];
		}
		pDoc->MapBlocks=MapBlocks;
		pDoc->m_mapname=m_maptitle;
		pDoc->SendToAll(MAPDM);	
		pDoc->SendToAll(MAPVIS);
		bPlaying=TRUE;
		pDoc->bPlaying=TRUE;
		m_playbutton.SetWindowText("STOP playing");
	}
	else if(MapLoaded && bPlaying)
	{
		m_playbutton.SetWindowText("START playing");
		bPlaying=FALSE;
		pDoc->bPlaying=FALSE;
	}
	else 
	{
		AfxMessageBox("First load a playable map before continuing.");
		pDoc->bPlaying=FALSE;
	}

	UpdateData(FALSE);
}

void CDnDMapPlay::SendVisibilityUpdate(int x, int y, bool IsShown)
{
	CDnDDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(bPlaying)
	{
		pDoc->VisSend.x=x;
		pDoc->VisSend.y=y;
		pDoc->PlayerVisible[x][y]=IsShown;
		pDoc->SendToAll(MAPVISONE);
	}
}

void CDnDMapPlay::SentItemUpdate(int number, CPTGameObject ob)
{
	CDnDDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(bPlaying)
	{
		pDoc->VisSend.x=number;
		pDoc->MapObj=ob;
		pDoc->SendToAll(MAPITEMONE);
	}	
}

void CDnDMapPlay::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	CDnDDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CString TmpIP,TmpStr;
	CBarrel obj;	
	int size=pDoc->MapPlayBarrel.GetSize();
	if(size>=1)
	{
		for(int i=0;i<size;i++)
		{
			obj=pDoc->MapPlayBarrel.GetAt(i);
			if(obj.type==CHAT)
			{
				m_chatmap.AddString(obj.data);
			}
			else
				m_chatmap.AddString(obj.data);
			
		}
		m_chatmap.SetCurSel(m_chatmap.GetCount()-1);
		pDoc->MapPlayBarrel.RemoveAll();
	}			

	
}

void CDnDMapPlay::OnChatsend() 
{

	CDnDDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	UpdateData();


	CString temp=m_strSend;
	CString TmpStr,TmpStr2;
	if(!temp.Find("/"))
	{
		int size=temp.GetLength();
		int i;
		CString ListString;
		CString slashless=temp.Right(size-1);
		char* NewString=slashless.GetBuffer(size-1);
		CString commando=strtok(NewString," ");
		CString firstpar=strtok(NULL," ");
		pDoc->msMsg=strtok(NULL,"\n");
		slashless.ReleaseBuffer();
		
		if(commando=="ban" || commando=="b")
		{
			i=pDoc->BanUser(firstpar,1);
			if(i==1)
			{
				ListString="Banned "+ firstpar;
				ListString+=".Use /unban [user] or /ub [user] to remove from banlist.";
			}
			else
			{
				ListString=firstpar + " allready banned";
				ListString+=".Use /unban [user] or /ub [user] to remove from banlist.";
			}
//			pDoc->AddToCont(pDoc->Cont,ADMINCHAT,ListString);
			pDoc->AddToBarrel(ADMINCHAT,ListString);
		}
		if(commando=="unban" || commando=="ub")
		{
			i=pDoc->BanUser(firstpar,0);
			if(i==1)
				ListString="Removed "+firstpar +" from banned list";
			else
				ListString=firstpar + " was not banned anyway";
//			pDoc->AddToCont(pDoc->Cont,ADMINCHAT,ListString);
			pDoc->AddToBarrel(ADMINCHAT,ListString);

		}
		if(commando=="kick" || commando=="k")
		{
			i=pDoc->KickUser(pDoc->FindUser(firstpar),KICK);
			if(i>=0)
			{
				ListString="Kicked ";
				ListString+=firstpar;
			}
			else
			{
				ListString="User ";
				ListString+=firstpar;
				ListString+=" isn't connected.";
			}
//			pDoc->AddToCont(pDoc->Cont,ADMINCHAT,ListString);
			pDoc->AddToBarrel(ADMINCHAT,ListString);

		}

		if(commando=="list" || commando=="ls")
		{
			CStringArray List;
			if(firstpar=="ban")
			{
				pDoc->ListBan(List);
				pDoc->AddToBarrel(ADMINCHAT,"Banned players are:");
				for(int j=0;j<List.GetSize();j++)
					pDoc->AddToBarrel(ADMINCHAT,List[j]);
			}
			else if(firstpar=="users")
			{
				pDoc->ListUsers(List);
				pDoc->AddToBarrel(ADMINCHAT,"Online players are:");
				for(int j=0;j<List.GetSize();j++)
					pDoc->AddToBarrel(ADMINCHAT,List[j]);
			}

		}

		if(commando=="clear" || commando=="cl")
		{
			CString TableName;
			if(firstpar=="ban")
			{
				TableName="Ban_List";
				pDoc->ClearTable(TableName);
				pDoc->AddToBarrel(ADMINCHAT,"The ban list has been cleared!");
			}

		}

		if(commando=="remove" || commando=="rm")
		{
			i=pDoc->RemoveUser(firstpar);
			if(i>=0)
			{
				ListString="Removed ";
				ListString+=firstpar;
			}
			else
			{
				ListString="User ";
				ListString+=firstpar;
				ListString+=" doesn't exist.";
			}
			pDoc->AddToBarrel(ADMINCHAT,ListString);
		}

		if(commando=="info")
		{
			if(pDoc->ExistTable(firstpar)) // info over player
			//	if(pDoc->msMsg=="char")
				{
					CStringArray List;
					pDoc->FindChar(firstpar,List);
					for(int j=0;j<List.GetSize();j++)
						pDoc->AddToBarrel(ADMINCHAT,List[j]);
				}

		}
		if(commando=="whisper"||commando=="w")
		{
			i=pDoc->FindUser(firstpar);
			if(i>=0)
			{
				ListString="Whispered to ";
				ListString+=firstpar;
				ListString+=": ";
				ListString+=pDoc->msMsg;
				pDoc->SendToUser(CHAT,firstpar);
//				pDoc->AddToCont(pDoc->Cont,PRIVATECHAT,ListString);
				pDoc->AddToBarrel(PRIVATECHAT,ListString);
			}
			else
			{
				ListString="User ";
				ListString+=firstpar;
				ListString+=" isn't online.";
				//oc->AddToCont(pDoc->Cont,PRIVATECHAT,ListString);
				pDoc->AddToBarrel(PRIVATECHAT,ListString);

			}
			
		}
	}
	
	else if(pDoc->m_nNumClients>0)
	{
		pDoc->msMsg=m_strSend;
		pDoc->SendToAll(CHAT);
		pDoc->AddToBarrel(CHAT,pDoc->msMsg);


	}
	else if(pDoc->m_nNumClients==0)
	{
		
		pDoc->AddToBarrel(CHAT,"No clients connected");


	}
	CStatic* pStaticOutput=(CStatic*)GetDlgItem(IDC_CHATMAP);
	pStaticOutput->SetWindowText("");	
}
