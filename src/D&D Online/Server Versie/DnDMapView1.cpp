// DnDMapView1.cpp : implementation file
//

#include "stdafx.h"
#include "DnD.h"
#include "DnDMapView1.h"
#include "MapSettings.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DnDMapView

IMPLEMENT_DYNCREATE(DnDMapView, CFormView)

DnDMapView::DnDMapView()
	: CFormView(DnDMapView::IDD)
{
	//{{AFX_DATA_INIT(DnDMapView)
	m_tool = _T("");
	m_mapname = _T("");
	m_blockinfo = _T("");
	m_blockinfo2 = _T("");
	m_blockinfo3 = _T("");
	m_stadeb = _T("");
	//}}AFX_DATA_INIT
}

DnDMapView::~DnDMapView()
{
}

void DnDMapView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DnDMapView)
	DDX_Control(pDX, IDC_LAYERCOMBO, m_layerctl);
	DDX_Control(pDX, IDC_DELETESM, m_deletesm);
	DDX_Control(pDX, IDC_COMBOMONSTER, m_monsterctl);
	DDX_Control(pDX, IDC_COMBOPLAYERS, m_playerctl);
	DDX_Control(pDX, IDC_ITEMSCOMBO, m_itemsctl);
	DDX_Control(pDX, IDC_DOORCOMBO, m_doorctl);
	DDX_Control(pDX, IDC_ROOMCOMBO, m_roomctl);
	DDX_Control(pDX, IDC_MAP, m_maparea);
	DDX_Text(pDX, IDC_CURRENTTOOL, m_tool);
	DDX_Text(pDX, IDC_MAPNAME, m_mapname);
	DDX_Text(pDX, IDC_STATINFOBL, m_blockinfo);
	DDX_Text(pDX, IDC_STATINFOBL2, m_blockinfo2);
	DDX_Text(pDX, IDC_STATINFOBL3, m_blockinfo3);
	DDX_Text(pDX, IDC_STATDEB, m_stadeb);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DnDMapView, CFormView)
	//{{AFX_MSG_MAP(DnDMapView)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_ROOMTOOL, OnRoomtool)
	ON_BN_CLICKED(IDC_TOOLCORRIDOR, OnToolcorridor)
	ON_BN_CLICKED(IDC_SETTINGS, OnSettings)
	ON_BN_CLICKED(IDC_TOOLDOOR, OnTooldoor)
	ON_BN_CLICKED(IDC_UNDO, OnUndo)
	ON_BN_CLICKED(IDC_ERASER, OnEraser)
	ON_CBN_SELCHANGE(IDC_ROOMCOMBO, OnSelchangeRoomcombo)
	ON_CBN_SELCHANGE(IDC_DOORCOMBO, OnSelchangeDoorcombo)
	ON_BN_CLICKED(IDC_ITEMS, OnItems)
	ON_CBN_SELCHANGE(IDC_ITEMSCOMBO, OnSelchangeItemscombo)
	ON_BN_CLICKED(IDC_CLEARMAP, OnClearmap)
	ON_BN_CLICKED(IDC_SAVEMAP, OnSavemap)
	ON_BN_CLICKED(IDC_LOADMAP, OnLoadmap)
	ON_BN_CLICKED(IDC_PLAYERS, OnPlayers)
	ON_CBN_SELCHANGE(IDC_COMBOPLAYERS, OnSelchangeComboplayers)
	ON_CBN_SELCHANGE(IDC_COMBOMONSTER, OnSelchangeCombomonster)
	ON_BN_CLICKED(IDC_MONSTER, OnMonster)
	ON_BN_CLICKED(IDC_TOOLSELECT, OnToolselect)
	ON_BN_CLICKED(IDC_DELETESM, OnDeletesm)
	ON_CBN_SELCHANGE(IDC_LAYERCOMBO, OnSelchangeLayercombo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DnDMapView diagnostics

#ifdef _DEBUG
void DnDMapView::AssertValid() const
{
	CFormView::AssertValid();
}

void DnDMapView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// DnDMapView message handlers

void DnDMapView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	mode=0;
	m_blocksize=30;
	layer=0; //show all layers
	debugenabled=FALSE;
	wmap.length=sizeof(WINDOWPLACEMENT);
	m_maparea.GetWindowPlacement(&wmap);
	int resizerke=wmap.rcNormalPosition.right-wmap.rcNormalPosition.left;
	resizerke=resizerke/m_blocksize;
	wmap.rcNormalPosition.right=m_blocksize*resizerke+wmap.rcNormalPosition.left;
	
	bmp_roomtile.LoadBitmap(TILE_ROOM);
	bmp_corridortile.LoadBitmap(TILE_CORRIDOR);
	bmp_herotile.LoadBitmap(TILE_HERO);
	bmp_partytile.LoadBitmap(TILE_PARTY);
	bmp_pittile.LoadBitmap(TILE_PIT);
	bmp_treasuretile.LoadBitmap(TILE_TREASURE);
	bmp_furnituretile.LoadBitmap(TILE_FURNITURE);
	resizerke=wmap.rcNormalPosition.bottom-wmap.rcNormalPosition.top;
	resizerke=resizerke/m_blocksize;
	wmap.rcNormalPosition.bottom=m_blocksize*resizerke+wmap.rcNormalPosition.top;
	CorridorStart.x=0;
	CorridorStart.y=0;
	HiRes=FALSE;
	DrawingCorridor=FALSE;;
	DrawingRoom=FALSE;
	tool=ROOM;
	CheckCounter=0;
	m_blockinfo="None selected";
	m_blockinfo2="";
	m_blockinfo3="";
	m_mapname="None";
	m_roomctl.SetCurSel(3);
	m_doorctl.SetCurSel(0);
	m_itemsctl.SetCurSel(0);
	m_playerctl.SetCurSel(8);
	m_monsterctl.SetCurSel(0);
	m_layerctl.SetCurSel(0);
	showgrid=TRUE;
	UpdateData(FALSE);
	OnRoomtool();
	

}

void DnDMapView::OnDraw(CDC* pDC) 
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
	
	
	//witte kader
	brushold=(CBrush*)pDC->SelectObject(&brushlwhite);
//mapveld met vakjes teken	
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




		//alle mapitems(floor,players,etc op veld plaatsen, naargelang layerfiler
	{
		for(int j=0;j<MapItems.GetSize();j++)
		{
			obj=MapItems.GetAt(j);
			if(size=obj.m_nOnSketch)
			{
				type=obj.m_nObjType;
				switch(type)
				{
				case MONSTER:
					if(layer==2||layer==0)
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
					if(layer==2||layer==0)
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
					if(layer==2||layer==0)
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
							if(obj.m_nFlags!=PILLAR && obj.m_nFlags!=TRAP )
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
							posbl.left=obj.m_ptPos1.x*obj.m_nOnSketch+wmap.rcNormalPosition.left+showgrid;
							posbl.top=obj.m_ptPos1.y*obj.m_nOnSketch+wmap.rcNormalPosition.top+showgrid;
							posbl.right=posbl.left+size;
							posbl.bottom=posbl.top+size;
							pDC->Rectangle(&posbl);
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
					if(layer==0||layer==1)
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
					if(layer==0||layer==1)
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
					if(layer==0||layer==1)
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
	pDC->SelectObject(brushold);
	pDC->SelectObject(penold);
	


}




void DnDMapView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CPTGameObject obj,obj2;
	CPoint pos,tmp;
	int j,i=0;
	int k=-1;
	int blocksize=m_blocksize;
	UpdateData(TRUE);
	CPoint roomsize;
	CString tmpstr,getal,tmpstr2;
	int roomx=0;
	int roomy=0;
	char ch;
	int HorVer=0; //vertical =1, horizontal=2
	//info afzette
	selectedblock.x=-1;
	selectedblock.y=-1;
	ShowBlockInfo();
	//
	if(point.x>=wmap.rcNormalPosition.left && point.x<=wmap.rcNormalPosition.right)
	{
		if(point.y>=wmap.rcNormalPosition.top && point.y<=wmap.rcNormalPosition.bottom)
		{
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
				ShowBlockInfo();
				break;
			case MONSTER:
				obj.m_nFlags=m_monsterctl.GetCurSel();
				obj.m_nOnSketch=blocksize;  //blokgrootte,0 is niet on field
				obj.m_nObjType=tool;
				obj.m_ptPos1=pos;
				MapItems.Add(obj);	
				LastPlacedObj=obj;
				CheckMap();
				Invalidate();
				break;
			case PLAYER:
				m_playerctl.GetLBText(m_playerctl.GetCurSel(),tmpstr);
				if(tmpstr[0]=='P' && tmpstr[1]=='l') //single player
				{
					tmpstr2.Format("%c",tmpstr[7]);
					obj.m_nFlags=atoi(tmpstr2);
					k=-1; //dubbele spelers uithalen
					for(i=0;i<MapItems.GetSize();i++)
					{
						obj2=MapItems.GetAt(i);
						if(obj2.m_nObjType==PLAYER && obj2.m_nFlags==obj.m_nFlags)
							k=i;
					}
					if(k!=-1)
						MapItems.RemoveAt(k,1);
				}
				else if(tmpstr[0]=='F') //familiar 
				{
					obj.m_nFlags=FAMILIAR;
				}
				else //party
				{
					k=-1; //dubbele parties uithalen
					for(i=0;i<MapItems.GetSize();i++)
					{
						obj2=MapItems.GetAt(i);
						if(obj2.m_nObjType==PLAYER && obj2.m_nFlags==PARTY)
							k=i;
					}
					if(k!=-1)
						MapItems.RemoveAt(k,1);
					obj.m_nFlags=PARTY;
				}
				obj.m_nOnSketch=blocksize;  //blokgrootte,0 is niet on field
				obj.m_nObjType=tool;
				obj.m_ptPos1=pos;
				MapItems.Add(obj);
				LastPlacedObj=obj;
				CheckMap();
				Invalidate();
				break;
			case ERASER:
				for(i=0;i<MapItems.GetSize();i++)
				{
					obj=MapItems.GetAt(i);
					if(obj.m_ptPos1==pos)
					{
						obj.m_nOnSketch=0;
						MapItems.SetAt(i,obj);
						LastPlacedObj=obj;
					}
				}
				Invalidate();
				break;
			case ITEM:
				m_itemsctl.GetLBText(m_itemsctl.GetCurSel(),tmpstr);
				if(tmpstr=="Trap")
					obj.m_nFlags=TRAP;
				if(tmpstr=="Pit")
					 obj.m_nFlags=PIT;
				if(tmpstr=="Furniture")
					obj.m_nFlags=FURNITURE;
				if(tmpstr=="Treasure")
					obj.m_nFlags=TREASURE;
				if(tmpstr=="Pillar")
					obj.m_nFlags=PILLAR;
				obj.m_nOnSketch=blocksize;  //blokgrootte,0 is niet on field
				obj.m_nObjType=tool;
				obj.m_ptPos1=pos;
				MapItems.Add(obj);
				LastPlacedObj=obj;
				CheckMap();
				Invalidate();
				break;
			case DOOR:
				m_doorctl.GetLBText(m_doorctl.GetCurSel(),tmpstr);
				if(tmpstr=="Horizontal")
					HorVer=2;
				else HorVer=1;
				obj.m_nOnSketch=blocksize;  //blokgrootte,0 is niet on field
				obj.m_nObjType=tool;
				obj.m_ptPos1=pos;
				obj.m_nFlags=HorVer;
				MapItems.Add(obj);
				LastPlacedObj=obj;
				CheckMap();
				Invalidate();
				break;
			case ROOM:
				m_roomctl.GetLBText(m_roomctl.GetCurSel(),tmpstr);
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
						roomx=atoi(getal);
						getal.Empty();
		
					}

					roomx=atoi(getal);
				}
				roomy=atoi(getal);
				DrawingRoom=FALSE;
				obj.m_nOnSketch=blocksize;  //blokgrootte,0 is niet on field
				obj.m_nObjType=tool;
				for(i=0;i<roomx;i++)
				{
					obj.m_ptPos1.x=pos.x+i;
					for(j=0;j<roomy;j++)
					{
					
					obj.m_ptPos1.y=pos.y+j;

					MapItems.Add(obj);
					
					LastPlacedObj=obj;
					}

				}
				CheckMap();
				Invalidate();
				break;
			case CORRIDOR:
				if(!DrawingCorridor)
				{
					DrawingCorridor=TRUE;
					CorridorStart.x=pos.x;
					CorridorStart.y=pos.y;
				}
				else
				{
					DrawingCorridor=FALSE;
					obj.m_nOnSketch=blocksize;
					obj.m_nObjType=tool;
					obj.m_ptPos1=CorridorStart;
					MapItems.Add(obj);
					//path berekenen
					tmpstr.Format("Corridorstart:%i,%i. PosEnd:%i,%i",CorridorStart.x,CorridorStart.y,pos.x,pos.y);
					//AfxMessageBox(tmpstr);
					if(CorridorStart.y==pos.y)
					{
						if(CorridorStart.x<pos.x)
						{
							for(i=pos.x;i>CorridorStart.x;i--)
							{
								obj.m_ptPos1.x=i;
								MapItems.Add(obj);
							}
						}
						else
							for(i=CorridorStart.x;i>pos.x;i--)
							{
								obj.m_ptPos1.x=i;
								MapItems.Add(obj);
							}
						obj.m_ptPos1=pos;
						MapItems.Add(obj);

					}

					else if(CorridorStart.x==pos.x)
					{
						if(CorridorStart.y<pos.y)
						{
							for(i=pos.y;i>CorridorStart.y;i--)
							{
								obj.m_ptPos1.y=i;
								MapItems.Add(obj);
							}
						}
						else
							for(i=CorridorStart.y;i>pos.y;i--)
							{
								obj.m_ptPos1.y=i;
								MapItems.Add(obj);
							}
						obj.m_ptPos1=pos;
						MapItems.Add(obj);	
						LastPlacedObj=obj;
					}


					CheckMap();
					Invalidate();
				}
				break;
			
			};

		}
	}
	
	CFormView::OnLButtonDown(nFlags, point);
}

void DnDMapView::OnRoomtool() 
{
	// TODO: Add your control notification handler code here
	tool=ROOM;
	DrawingCorridor=FALSE;
	DrawingRoom=FALSE;
	CString tmp;
	m_roomctl.GetLBText(m_roomctl.GetCurSel(),tmp);
	m_tool="Room-tool selected:"+tmp;
	UpdateData(FALSE);
}

void DnDMapView::OnToolcorridor() 
{
	// TODO: Add your control notification handler code here
	tool=CORRIDOR;
	DrawingCorridor=FALSE;
	DrawingRoom=FALSE;
	m_tool="Corridor tool selected";
	UpdateData(FALSE);
}


void DnDMapView::OnSettings() 
{
	// TODO: Add your control notification handler code here
	MapSettings dlg;
	dlg.m_dispgrid=showgrid;
	dlg.m_blocksize=m_blocksize;
	dlg.m_hires=HiRes;
	dlg.m_debugcleanup=debugenabled;
	int resizerke;
	if(IDOK==dlg.DoModal())
	{
		if(m_blocksize!=dlg.m_blocksize || dlg.clear)
		{	
			//nieuwe map maken;
			MapItems.RemoveAll();
			m_blocksize=dlg.m_blocksize;
			CheckCounter=0;

			resizerke=wmap.rcNormalPosition.right-wmap.rcNormalPosition.left;
			resizerke=resizerke/m_blocksize;
			wmap.rcNormalPosition.right=m_blocksize*resizerke+wmap.rcNormalPosition.left;
	

			resizerke=wmap.rcNormalPosition.bottom-wmap.rcNormalPosition.top;
			resizerke=resizerke/m_blocksize;
			wmap.rcNormalPosition.bottom=m_blocksize*resizerke+wmap.rcNormalPosition.top;
				m_mapname="None";
			UpdateData(FALSE);
		}
		showgrid=dlg.m_dispgrid;
		HiRes=dlg.m_hires;
		debugenabled=dlg.m_debugcleanup;
		if(!debugenabled)
			m_stadeb="";
		UpdateData(FALSE);
		CheckMap();
		Invalidate();
	}
		
}

void DnDMapView::CheckMap()
{
	int xbreedte=wmap.rcNormalPosition.right-wmap.rcNormalPosition.left;
	int ylengte=wmap.rcNormalPosition.bottom-wmap.rcNormalPosition.top;
	CPTGameObject obj,obj2;
	CArray<CPTGameObject, CPTGameObject&> MapItemsTmp;
	CArray<CPTGameObject, CPTGameObject&> MapItemsItemsTmp;
	int size;
	int j,i;
	int after,before,foundd=0;
	obj2.m_nOnSketch=0;
	 before=MapItems.GetSize();
	CString debug;

	//new cleanupcode
	CArray<CPTGameObject, CPTGameObject&> TmpItem;
	CArray<CPTGameObject, CPTGameObject&> TmpGround;
	CArray<CPTGameObject, CPTGameObject&> TmpPlayerMonster;
	foundd=0;
	before=MapItems.GetSize();
	for(i=0;i<before;i++)
	{
		obj=MapItems.GetAt(i);
		if(size=obj.m_nOnSketch)
		{
			//zaken die buiten scherm zouden komen verwijderen
			if(xbreedte/size<=obj.m_ptPos1.x || ylengte/size<=obj.m_ptPos1.y  || !obj.m_nOnSketch);//skippen die handel
			else
			{
				//we maken drie 'layers' aan die we stuk voor stuk nadien gaan nazien op cungruentie
				switch(obj.m_nObjType)
				{
				case CORRIDOR:
				case ROOM:
				case DOOR:
					TmpGround.Add(obj);
					break;
				case PLAYER:
				case MONSTER:
					TmpPlayerMonster.Add(obj);
					break;
				default:
					TmpItem.Add(obj);
				};
			}

		}
	}
	MapItems.RemoveAll();
	for(i=TmpGround.GetSize()-1;i>=0;i--)
	{
		foundd=0;
		obj=TmpGround.GetAt(i);
		for(j=0;j<i;j++)
		{
			if(TmpGround.GetAt(j).m_ptPos1==obj.m_ptPos1)
			{
				foundd=1;
			}
			
		}
		if(!foundd)
			MapItems.Add(obj);
		else 
		{
			TmpGround.RemoveAt(i,1);
			foundd=0;
		}
		
	}
	for(i=TmpItem.GetSize()-1;i>=0;i--)
	{
		foundd=0;
		obj=TmpItem.GetAt(i);
		for(j=0;j<i;j++)
		{
			if(TmpItem.GetAt(j).m_ptPos1==obj.m_ptPos1)
			{
				foundd=1;
			}
			
		}
		if(!foundd)
			MapItems.Add(obj);
		else 
		{
			TmpItem.RemoveAt(i,1);
			foundd=0;
		}
		
	}
	for(i=TmpPlayerMonster.GetSize()-1;i>=0;i--)
	{
		foundd=0;
		obj=TmpPlayerMonster.GetAt(i);
		for(j=0;j<i;j++)
		{
			if(TmpPlayerMonster.GetAt(j).m_ptPos1==obj.m_ptPos1)
			{
				foundd=1;
			}
			
		}
		if(!foundd)
			MapItems.Add(obj);
		else 
		{
			TmpPlayerMonster.RemoveAt(i,1);
			foundd=0;
		}
		
	}
	after=MapItems.GetSize();


	if(debugenabled)
	{
		after=MapItems.GetSize();
		debug.Format("Cleanup maparray:Before:%i. After:%i",before,after);
		m_stadeb=debug;
		UpdateData(FALSE);
	}


}

void DnDMapView::OnTooldoor() 
{
	// TODO: Add your control notification handler code here
	tool=DOOR;
	DrawingCorridor=FALSE;
	DrawingRoom=FALSE;
	CString tmp;
	m_doorctl.GetLBText(m_doorctl.GetCurSel(),tmp);
	m_tool=tmp+" door tool selected";
	UpdateData(FALSE);
}

void DnDMapView::OnUndo() 
{
	// TODO: Add your control notification handler code here
	CPTGameObject obj;
	int indextodelete=-1;
	for(int i=0;i<MapItems.GetSize();i++)
	{
		obj=MapItems.GetAt(i);
		if(obj.m_nFlags==LastPlacedObj.m_nFlags && obj.m_nObjType==LastPlacedObj.m_nObjType && obj.m_ptPos1==LastPlacedObj.m_ptPos1)
			indextodelete=i;
	}
	if(indextodelete!=-1)
		MapItems.RemoveAt(indextodelete,1);
	ShowBlockInfo();
	Invalidate();
}

void DnDMapView::OnEraser() 
{
	// TODO: Add your control notification handler code here
	tool=ERASER;
	DrawingCorridor=FALSE;
	DrawingRoom=FALSE;	
	m_tool="Eraser-tool selected";
	UpdateData(FALSE);
}

void DnDMapView::OnSelchangeRoomcombo() 
{
	// TODO: Add your control notification handler code here
	OnRoomtool();
}

void DnDMapView::OnSelchangeDoorcombo() 
{
	// TODO: Add your control notification handler code here
	OnTooldoor();
}

void DnDMapView::OnItems() 
{
	// TODO: Add your control notification handler code here
	tool=ITEM;
	DrawingCorridor=FALSE;
	DrawingRoom=FALSE;
	CString tmp;
	m_itemsctl.GetLBText(m_itemsctl.GetCurSel(),tmp);

	m_tool="Item-tool selected:"+tmp;
	UpdateData(FALSE);
}

void DnDMapView::OnSelchangeItemscombo() 
{
	// TODO: Add your control notification handler code here
	OnItems();
}

void DnDMapView::OnClearmap() 
{
	// TODO: Add your control notification handler code here
	if(IDYES==AfxMessageBox("Are you sure?",MB_YESNO))
	{
		MapItems.RemoveAll();
		m_mapname="None";
		UpdateData(FALSE);
		Invalidate();
	}

}

void DnDMapView::OnSavemap() 
{
	// TODO: Add your control notification handler code here
	CString path;
	CFileDialog *dlg;
	UpdateData(TRUE);
	dlg= new CFileDialog(FALSE,NULL,"DnD Dungeon Maps",NULL,"Setting Files (*.ddm)|*.ddm|All Files (*.*)|*.*",this);
	if(IDOK==dlg->DoModal())
	{
		
			path=dlg->GetPathName();

	}
	dlg->Detach();
	CFile outFile(path+".ddm",CFile::modeCreate|CFile::modeWrite);
	CArchive arOut(&outFile,CArchive::store);
	CheckMap();
	arOut<<MapItems.GetSize();
	for(int i=0;i<MapItems.GetSize();i++)
	{
		MapItems.GetAt(i).Serialize(arOut);
	}
	arOut<<m_mapname;
}

void DnDMapView::OnLoadmap() 
{
	// TODO: Add your control notification handler code here
	CString tmp;
	if(MapItems.GetSize())
	{
		if(IDYES==AfxMessageBox("Loading new map will result in loss of current one. Safe this one first?",MB_YESNO))
			OnSavemap();
	}

	
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
	m_mapname=tmp+" <"+filename+">";
	m_blocksize=obj.m_nOnSketch;
	CheckMap();
	Invalidate();
	UpdateData(FALSE);
}



void DnDMapView::OnPlayers() 
{
	// TODO: Add your control notification handler code here
	tool=PLAYER;
	DrawingCorridor=FALSE;
	DrawingRoom=FALSE;
	CString tmp;
	m_playerctl.GetLBText(m_playerctl.GetCurSel(),tmp);
	m_tool="Player-tool selected:"+tmp;
	UpdateData(FALSE);
}

void DnDMapView::OnSelchangeComboplayers() 
{
	// TODO: Add your control notification handler code here
	OnPlayers();
}

void DnDMapView::OnSelchangeCombomonster() 
{
	// TODO: Add your control notification handler code here
	OnMonster();
}

void DnDMapView::OnMonster() 
{
	// TODO: Add your control notification handler code here
	tool=MONSTER;
	DrawingCorridor=FALSE;
	DrawingRoom=FALSE;
	CString tmp;
	m_monsterctl.GetLBText(m_monsterctl.GetCurSel(),tmp);
	m_tool="Monster-tool selected:"+tmp;
	UpdateData(FALSE);
}

void DnDMapView::OnToolselect() 
{
	// TODO: Add your control notification handler code here
	tool=SELECT;
	DrawingCorridor=FALSE;
	DrawingRoom=FALSE;
	m_tool="Select-tool selected";
	UpdateData(FALSE);
}

void DnDMapView::ShowBlockInfo()
{
	CArray<CPTGameObject, CPTGameObject&> ThisBlock;
	CPTGameObject obj;
	int i;
	if(selectedblock.x!=-1 && MapItems.GetSize())
	{
		for(i=0;i<MapItems.GetSize();i++)
		{
			obj=MapItems.GetAt(i);
			if(obj.m_ptPos1==selectedblock && obj.m_nOnSketch)
			{
				ThisBlock.Add(MapItems.GetAt(i));
			}
		}
		switch(ThisBlock.GetSize())
		{
		case 0:m_blockinfo="Empty";	m_deletesm.EnableWindow(FALSE);
			break;
		case 1:
			obj=ThisBlock.GetAt(0);
			m_blockinfo.Format("Type:%s,Flags:%i",DefinesConvert(obj.m_nObjType),obj.m_nFlags);
			m_blockinfo2="";
			m_blockinfo3="";
			m_deletesm.EnableWindow(TRUE);
			break;
		case 2:
			obj=ThisBlock.GetAt(0);
			m_blockinfo.Format("1)Type:%s,Flags:%i",DefinesConvert(obj.m_nObjType),obj.m_nFlags);
			obj=ThisBlock.GetAt(1);
			m_blockinfo2.Format("2)Type:%s,Flags:%i",DefinesConvert(obj.m_nObjType),obj.m_nFlags);
			m_blockinfo3="";
			m_deletesm.EnableWindow(TRUE);

			break;
		case 3:
			obj=ThisBlock.GetAt(0);
			m_blockinfo.Format("1)Type:%s,Flags:%i",DefinesConvert(obj.m_nObjType),obj.m_nFlags);
			obj=ThisBlock.GetAt(1);
			m_blockinfo2.Format("2)Type:%s,Flags:%i",DefinesConvert(obj.m_nObjType),obj.m_nFlags);
			obj=ThisBlock.GetAt(2);
			m_blockinfo3.Format("3)Type:%s,Flags:%i",DefinesConvert(obj.m_nObjType),obj.m_nFlags);
			m_deletesm.EnableWindow(TRUE);
			break;
		};
	}
	else
	{
		m_blockinfo="None selected";
		m_blockinfo2="";
		m_blockinfo3="";
		m_deletesm.EnableWindow(FALSE);
	}
	UpdateData(FALSE);
}

void DnDMapView::OnDeletesm() 
{
	// TODO: Add your control notification handler code here
	CPTGameObject obj;
	int k[3];
	int found=0;
	int i;
	for(i=0;i<MapItems.GetSize();i++)
	{
		obj=MapItems.GetAt(i);
		if(obj.m_ptPos1==selectedblock && obj.m_nOnSketch)
		{
			
			if(found<=3)
				k[found]=i;//store locations
			found++;
		}

	}
	/*
	//delete all locations 
	for(i=found-1;i>=0;i--)
	{
		MapItems.RemoveAt(k[i],1);
	}*/
	MapItems.RemoveAt(k[found-1],1);
	//info updaten

	ShowBlockInfo();
	Invalidate();
}

UINT DnDMapView::CheckBlock(CPoint pos)
{
 return 0;
}

void DnDMapView::DrawTransparentBitmap(CDC *pDC, CBitmap *pBitmap, short xStart, short yStart, COLORREF cTransparentColor, short xEnd,short yEnd)
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
void DnDMapView::DrawTransparentResizedBitmap(CDC *pDC, CBitmap *pBitmap, short xStart, short yStart, COLORREF cTransparentColor, short xEnd,short yEnd)
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

CString DnDMapView::DefinesConvert(int def1)
{
	CString ret="No info";
	switch(def1)
	{
	case ROOM: ret="Room";break; 
	case CORRIDOR :ret="Room";break;
case DOOR :ret="Door";break;
case MONSTER :ret="Monster";break;
case PLAYER :ret="Player";break;
case TRAP :ret="TRAP";break;
case STAIR :ret="STAIR";break;
case ITEM :ret="Item/Trap/etc";break;
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

void DnDMapView::OnSelchangeLayercombo() 
{
	// TODO: Add your control notification handler code here
	layer=m_layerctl.GetCurSel();
	Invalidate();

}
