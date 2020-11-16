// DndSketchView.cpp : implementation file
//

#include "stdafx.h"
#include "DnD.h"
#include "DndSketchView.h"
#include "PtGameObject.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DndSketchView

IMPLEMENT_DYNCREATE(DndSketchView, CFormView)

DndSketchView::DndSketchView()
	: CFormView(DndSketchView::IDD)
{
	//{{AFX_DATA_INIT(DndSketchView)
	m_transparent = FALSE;
	m_liveupdate = FALSE;
	//}}AFX_DATA_INIT
}

DndSketchView::~DndSketchView()
{
}

void DndSketchView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DndSketchView)
	DDX_Control(pDX, IDC_COLOUT, m_coloutsideshow);
	DDX_Control(pDX, IDC_COLIN, m_colinsideshow);
	DDX_Control(pDX, IDC_LOADIMAGEBTN, m_toolbackground);
	DDX_Control(pDX, IDC_SELECTTOOL, m_toolSelect);
	DDX_Control(pDX, IDC_SKETCHBLOCK2, m_miniature);
	DDX_Control(pDX, IDC_COLPICKIN, m_colpickin);
	DDX_Control(pDX, IDC_CIRCLETOOL, m_toolCircle);
	DDX_Control(pDX, IDC_LINETOOL, m_toolLine);
	DDX_Control(pDX, IDC_SKETCHBLOCK, m_sketcharea);
	DDX_Check(pDX, IDC_LIVEUPDATE, m_liveupdate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DndSketchView, CFormView)
	//{{AFX_MSG_MAP(DndSketchView)
	ON_BN_CLICKED(IDC_SKETCHBLOCK, OnSketchblock)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_LINETOOL, OnLinetool)
	ON_BN_CLICKED(IDC_CIRCLETOOL, OnCircletool)
	ON_BN_CLICKED(IDC_COLPICKOUT, OnColpickout)
	ON_BN_CLICKED(IDC_COLPICKIN, OnColpickin)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_BN_CLICKED(IDC_SENDIMAGE, OnSendimage)
	ON_BN_CLICKED(IDC_SELECTTOOL, OnSelecttool)
	ON_BN_CLICKED(IDC_LIVEUPDATE, OnLiveupdate)
	ON_BN_CLICKED(IDC_LOADIMAGEBTN, OnLoadimagebtn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DndSketchView diagnostics

#ifdef _DEBUG
void DndSketchView::AssertValid() const
{
	CFormView::AssertValid();
}

void DndSketchView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}


#endif //_DEBUG
CDnDDoc* DndSketchView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDnDDoc)));
	return (CDnDDoc*)m_pDocument;
}

/////////////////////////////////////////////////////////////////////////////
// DndSketchView message handlers

void DndSketchView::OnSketchblock() 
{
	// TODO: Add your control notification handler code here	
}

void DndSketchView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDnDDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CRect rect;
	CString debug;
	UpdateData(TRUE);


	bool selecthit=FALSE;
	CPTGameObject obj1,obj2;

	if(point.x>=wsketch.rcNormalPosition.left && point.x<=wsketch.rcNormalPosition.right)
	{
		if(point.y>=wsketch.rcNormalPosition.top && point.y<=wsketch.rcNormalPosition.bottom)
		{
			
			switch(tool)
			{
	/*			case SELECT:

						for(s=0;s<LocalSketch.size;s++)
						{
							obj1=LocalSketch.FirstSketch.GetAt(s);
							switch(obj1.m_nObjType)
							{
							case LINE:

								if(obj1.m_nOnSketch && point.y-obj1.m_ptPos1.y+(double)(((double)(obj1.m_ptPos2.y-obj1.m_ptPos1.y)/(double)(obj1.m_ptPos2.x-obj1.m_ptPos1.x))*(point.x-obj1.m_ptPos1.x))<=20)
								{
									selecthit=TRUE;	
								}
								
								break;
							case CIRCLE:
								break;
							}
						
								
						

						}
					if(selecthit)
					{
						AfxMessageBox("BAM");
						if(m_bNoneSelected)
							{//select
							}
						else
							{//unselect
							}
					}
			
					break;*/
				case LINE:
					switch(drawingline){
						case 0:
							drawingline=1;
							obj1.m_ptPos1.x=point.x-wsketch.rcNormalPosition.left;
							obj1.m_ptPos1.y=point.y-wsketch.rcNormalPosition.top;
							obj1.outside_color=out;
							obj1.m_nObjType=LINE;
							if(m_liveupdate)
							{
								pDoc->Sketch.Add(obj1);
								pDoc->SendToAll(SKETCH);
							}
							LocalSketch.Add(obj1);
							
							break;
						case 1:
							
							obj1=LocalSketch.GetAt(LocalSketch.GetSize()-1);
							
							obj1.m_nObjType=LINE;
							obj2.m_nObjType=LINE;
							obj1.m_ptPos2.x=point.x-wsketch.rcNormalPosition.left;
							obj1.m_ptPos2.y=point.y-wsketch.rcNormalPosition.top;
							obj2.m_ptPos1.x=point.x-wsketch.rcNormalPosition.left;
							obj2.m_ptPos1.y=point.y-wsketch.rcNormalPosition.top;

							obj1.m_nOnSketch=TRUE;
							obj1.outside_color=out;
							LocalSketch.SetAt(LocalSketch.GetSize()-1,obj1);
							if(m_liveupdate)
							{
								pDoc->Sketch.Add(obj2);
								pDoc->SendToAll(SKETCH);
							}
							//nog geen controle om hierover te gaan, oppassen!)
							LocalSketch.Add(obj2);
							
							if(LocalSketch.GetSize()>=5)
								int s=0;
							Invalidate();
							break;
						}
						break;
					case CIRCLE:
						switch(drawingcircle){
							case 0:
								drawingcircle=1;
								obj1.m_ptPos1.x=point.x-wsketch.rcNormalPosition.left;
								obj1.m_ptPos1.y=point.y-wsketch.rcNormalPosition.top;
								obj1.m_nObjType=CIRCLE;
								obj1.outside_color=out;
								if(!m_transparent)
									obj1.inside_color=in;
								else
									obj1.inside_color=RGB(1,1,1);
								
								
								LocalSketch.Add(obj1);
								break;
							case 1:
								obj1=LocalSketch.GetAt(LocalSketch.GetSize()-1);
//hier klopt iets niet!
								drawingcircle=0;
								obj1.m_ptPos2.y=point.y-wsketch.rcNormalPosition.bottom;
								obj1.m_ptPos2.x=point.x-wsketch.rcNormalPosition.right;
								obj1.m_nOnSketch=TRUE;
								obj1.inside_color=in;
								obj1.outside_color=out;
								LocalSketch.Add(obj1);
								if(m_liveupdate)
								{
									pDoc->Sketch.Add(obj1);
									pDoc->SendToAll(SKETCHUPDATE);
								}
								Invalidate();
								break;
							}

						break;
				

			}
		}
	if(LocalSketch.GetSize()>200 && warning == 0)
	{
		AfxMessageBox("Sketch is becoming awfully big. Perhaps it is a good time to clear the current one and start a new drawing",MB_ICONINFORMATION);
		warning++;
	}
	if(LocalSketch.GetSize()>300 && warning == 1)
	{
		AfxMessageBox("Making this sketch any larger will probably result in low bandwidth and or crashing clients. Stop drawing please :p",MB_ICONINFORMATION);
		warning++;
	}

	}


	else
		drawingline=0;
	CFormView::OnLButtonDown(nFlags, point);

}

void DndSketchView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class
	drawingline=0;
	drawingcircle=0;
	m_bNoneSelected=0;
	CFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void DndSketchView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	drawingline=0;
	m_bNoneSelected=0;
	Invalidate();
	CFormView::OnLButtonDblClk(nFlags, point);
}

void DndSketchView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class

	
}

void DndSketchView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CString debug;
	int deb=0;
	int kort=0;
	CRect rect;
	CPoint pos;
	CPoint pos2;
	CPTGameObject obj;

	CPen* penold;
	CPen pen;
	//kleurkes blokjes:
	CBrush brushin(in);
	CBrush* brusholdb=(CBrush*)pDC->SelectObject(&brushin);

	pDC->Rectangle(&wplacecolin.rcNormalPosition);
	pDC->SelectObject(brusholdb);
	
	CBrush brushout(out);
	brusholdb=(CBrush*)pDC->SelectObject(&brushout);

	pDC->Rectangle(&wplacecolout.rcNormalPosition);
	pDC->SelectObject(brusholdb);
	
	//tekenveld
	pDC->Rectangle(&wsketch.rcNormalPosition);
	

	//picture 
	pos.x=wsketch.rcNormalPosition.left;
	pos.y=wsketch.rcNormalPosition.top;
	CSize size;
	size.cx=wsketch.rcNormalPosition.right-wsketch.rcNormalPosition.left;
	size.cy=wsketch.rcNormalPosition.bottom-wsketch.rcNormalPosition.top;
	if(GotLoadedImage)
	{
		APicture.Draw(pDC,pos,size);
	}

	//sketch
	for(int li=0;li<LocalSketch.GetSize();li++)
	{
		obj=LocalSketch.GetAt(li);
		if(obj.m_nOnSketch)
		{
			switch(obj.m_nObjType)
			{
				case LINE:
					deb++;
					pen.CreatePen(PS_SOLID,1,obj.outside_color);
				
					penold=(CPen*)pDC->SelectObject(&pen);
					
					pos.x=obj.m_ptPos2.x+wsketch.rcNormalPosition.left;
					pos.y=obj.m_ptPos2.y+wsketch.rcNormalPosition.top;
					pDC->MoveTo(pos);
					
					pos.x=obj.m_ptPos1.x+wsketch.rcNormalPosition.left;
					pos.y=obj.m_ptPos1.y+wsketch.rcNormalPosition.top;
					pDC->LineTo(pos);
					pen.DeleteObject();
					pDC->SelectObject(penold);
					
					break;
				case CIRCLE:
					pen.CreatePen(PS_SOLID,1,obj.outside_color);
					CPen* penold=(CPen*)pDC->SelectObject(&pen);
					CBrush brush(obj.inside_color);
					CBrush* brushold=(CBrush*)pDC->SelectObject(&brush);
					rect.top=obj.m_ptPos1.y+wsketch.rcNormalPosition.top;
					rect.bottom=obj.m_ptPos2.y+wsketch.rcNormalPosition.bottom;
					rect.left=obj.m_ptPos1.x+wsketch.rcNormalPosition.left;
					rect.right=obj.m_ptPos2.x+wsketch.rcNormalPosition.right;
					pDC->Ellipse(rect);
					
					pDC->SelectObject(penold);
					pen.DeleteObject();

					pDC->SelectObject(brushold);

					break;
			}

				
		}

	}
//	debug.Format("%i",deb);
//	pDC->TextOut(20,20,debug);
	//Hier komt poging tot een miniatuurweergave. Fingers crossed

	CBrush brush(RGB(100,100,100));
	pDC->Rectangle(&wsketch2.rcNormalPosition);
	size.cx=wsketch2.rcNormalPosition.right-wsketch2.rcNormalPosition.left;
	size.cy=wsketch2.rcNormalPosition.bottom-wsketch2.rcNormalPosition.top;
	pos.x=wsketch2.rcNormalPosition.left;
	pos.y=wsketch2.rcNormalPosition.top;

	if(GotLoadedImage)
	{
		APicture.Draw(pDC,pos,size);
	}
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
					CPen* penold=(CPen*)pDC->SelectObject(&pen);
					CBrush brush(obj.inside_color);
					CBrush* brushold=(CBrush*)pDC->SelectObject(&brush);
					rect.top=obj.m_ptPos1.y/yscale+wsketch2.rcNormalPosition.top;
					rect.bottom=obj.m_ptPos2.y/yscale+wsketch2.rcNormalPosition.bottom;
					rect.left=obj.m_ptPos1.x/xscale+wsketch2.rcNormalPosition.left;
					rect.right=obj.m_ptPos2.x/xscale+wsketch2.rcNormalPosition.right;
					pDC->Ellipse(rect);
					
					pDC->SelectObject(penold);
					pen.DeleteObject();

					pDC->SelectObject(brushold);

					break;
			}

				
		}

	}

}

void DndSketchView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	GotLoadedImage=FALSE;
		LocalSketch.RemoveAll();
	warning=0;
	tool=LINE;
	m_toolLine.SetBitmap((HBITMAP)m_toolBitmaps[0]);
	m_toolCircle.SetBitmap((HBITMAP)m_toolBitmaps[1]);
	m_toolSelect.SetBitmap((HBITMAP)m_toolBitmaps[2]);
	m_toolbackground.SetBitmap((HBITMAP)m_toolBitmaps[3]);
	
	wsketch.length=sizeof(WINDOWPLACEMENT);
	wsketch2.length=sizeof(WINDOWPLACEMENT);
	wplacecolin.length=sizeof(WINDOWPLACEMENT);
	wplacecolout.length=sizeof(WINDOWPLACEMENT);
	
	m_sketcharea.GetWindowPlacement(&wsketch);
	m_miniature.GetWindowPlacement(&wsketch2);
	m_colinsideshow.GetWindowPlacement(&wplacecolin);
	m_coloutsideshow.GetWindowPlacement(&wplacecolout);

	int xlarge=wsketch.rcNormalPosition.right-wsketch.rcNormalPosition.left;
	int ylarge=wsketch.rcNormalPosition.bottom-wsketch.rcNormalPosition.top;
	int xsmall=wsketch2.rcNormalPosition.right-wsketch2.rcNormalPosition.left;
	int ysmall=wsketch2.rcNormalPosition.bottom-wsketch2.rcNormalPosition.top;
	xscale=(float)xlarge/(float)xsmall;
	yscale=(float)ylarge/(float)ysmall;
	in=COLORREF(RGB(0,0,0));
	out=COLORREF(RGB(0,0,0));

}

BOOL DndSketchView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_toolBitmaps[0].LoadBitmap(IDB_LINE);
	m_toolBitmaps[1].LoadBitmap(IDB_CIRCLE);
	m_toolBitmaps[2].LoadBitmap(IDB_SELECT);
	m_toolBitmaps[3].LoadBitmap(IDB_BCKGRND);
	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void DndSketchView::OnLinetool() 
{
	// TODO: Add your control notification handler code here
	tool=LINE;
}

void DndSketchView::OnCircletool() 
{
	// TODO: Add your control notification handler code here
	tool=CIRCLE;
}

void DndSketchView::OnColpickout() 
{
	// TODO: Add your control notification handler code here
	CColorDialog *dlg=new CColorDialog(out,0,0);
	if(dlg->DoModal()==IDOK)
	{
		out=dlg->GetColor();
		Invalidate();
	}
}

void DndSketchView::OnColpickin() 
{
	// TODO: Add your control notification handler code here
	CColorDialog *dlg=new CColorDialog(in,0,0);
	if(dlg->DoModal()==IDOK)
	{
		
		in=dlg->GetColor();
		Invalidate();
	}
}

void DndSketchView::OnClear() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if(AfxMessageBox("Clear image",MB_YESNO)==IDYES)
	{
		LocalSketch.RemoveAll();
		APicture.Load("sgjdmghxbldxnbldxvhbebvluj");
		GotLoadedImage=FALSE;
		ImagePath="zepponop";
		warning=0;
		if(m_liveupdate)
			OnSendimage();
	}
	Invalidate();
}

void DndSketchView::OnSendimage() 
{
	// TODO: Add your control notification handler code here
	CString debug;
	int count=0;
	CDnDDoc* pDoc = GetDocument();
	
	ASSERT_VALID(pDoc);
	pDoc->Sketch.RemoveAll();
	for(int i=0;i<LocalSketch.GetSize();i++)
	{
		pDoc->Sketch.Add(LocalSketch.GetAt(i));
		//send extra params (sketch grootte)
		pDoc->sketchEndPoint.x=wsketch.rcNormalPosition.right-wsketch.rcNormalPosition.left;
		pDoc->sketchEndPoint.y=wsketch.rcNormalPosition.bottom-wsketch.rcNormalPosition.top;

	}
	if(GotLoadedImage)
		pDoc->SketchPicturePath=ImagePath;	
	else
		pDoc->SketchPicturePath="zepponop";
	pDoc->SendToAll(IMAGEREQ1);
	pDoc->SendToAll(SKETCH);
}

void DndSketchView::OnSelecttool() 
{
	// TODO: Add your control notification handler code here
	tool=SELECT;	
}

void DndSketchView::OnLiveupdate() 
{
	// TODO: Add your control notification handler code here
	if(!m_liveupdate)
		OnSendimage();
}

void DndSketchView::OnLoadimagebtn() 
{

	// TODO: Add your control notification handler code here
	
	CDnDDoc* pDoc = GetDocument();
	GotLoadedImage=FALSE;
	ASSERT_VALID(pDoc);	
	CString path,filename;
	filename=ImagePath;
	CFile Image;
	CFileDialog *dlg;
	DWORD length;
	int size;
	dlg= new CFileDialog(TRUE,NULL,"",NULL,"All Files (*.*)|*.*",this);
	if(IDOK==dlg->DoModal())
	{
			path=dlg->GetPathName();
			filename=dlg->GetFileName();
			Image.Open(filename,CFile::modeRead | CFile::typeBinary);
			length=Image.GetLength();
			Image.Close();
			if(length>100000) //†
			{
				AfxMessageBox("Image exceeds 100kBytes. Picture will not be loaded");
				GotLoadedImage=FALSE;
				ImagePath="zepponop";
			}
			else
			{
				APicture.Load(filename);
				ImagePath=filename;
				GotLoadedImage=TRUE;
			}
			

	}

	
		

	if(m_liveupdate)
	{
		pDoc->SketchPicturePath=ImagePath;
		pDoc->SendToAll(IMAGEREQ1);

		
	}
	Invalidate();
}
