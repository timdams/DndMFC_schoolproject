// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "DnD.h"

#include "MainFrm.h"

#include "DnDMapView1.h"
#include "ConnView.h"
#include "ChatView.h"
#include "DnDMapPlay.h"
#include "DnDSketchView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_CONNECT, OnConnect)
	ON_COMMAND(ID_CHAT, OnChat)
	ON_WM_TIMER()
	ON_UPDATE_COMMAND_UI(ID_CHAT, OnUpdateChat)
	ON_COMMAND(ID_SKETCH, OnSketch)
	ON_COMMAND(ID_MAP, OnMap)
	ON_COMMAND(ID_MAPPLAY, OnMapplay)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

void CMainFrame::CreateActivateView(CRuntimeClass *pNewViewClass, UINT nID)
{
	CView* pOldView = GetActiveView();
	CView* pNewView = NULL;

	CDocument* pDoc = GetActiveDocument();
	POSITION pos = pDoc->GetFirstViewPosition();
	
	while(pos && !pNewView)
	{
		CView* pView = pDoc->GetNextView(pos);
		if(pView->IsKindOf(pNewViewClass))
			pNewView = pView;
	}

	if(pNewView == NULL)
	{
		CCreateContext context;
		context.m_pCurrentDoc = pDoc;

		pNewView = (CView*)pNewViewClass->CreateObject();
		pNewView->Create(NULL, NULL, 0, CFrameWnd::rectDefault, this, nID, &context);
		pNewView->OnInitialUpdate();
	}

	SetActiveView(pNewView);
	pNewView->ShowWindow(SW_SHOW);
	pOldView->ShowWindow(SW_HIDE);

	pOldView->SetDlgCtrlID(pNewView->GetDlgCtrlID());
	pNewView->SetDlgCtrlID(AFX_IDW_PANE_FIRST);

	RecalcLayout();

}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	
	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;
	cs.style&=~FWS_ADDTOTITLE; // Remove document name from title
	
//	cs.style&=~WS_THICKFRAME;  // To avoid resizing
	
//	cs.style&=~WS_MAXIMIZEBOX; // Disable maximize button

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}



#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnConnect() 
{
	// TODO: Add your command handler code here
	CreateActivateView(RUNTIME_CLASS(CConnView),1);
}

void CMainFrame::OnChat() 
{
	// TODO: Add your command handler code here
	CreateActivateView(RUNTIME_CLASS(CChatView),2);
	CDocument* pDoc = GetActiveDocument();	
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

//	m_wndToolBar.SetButtonInfo(11,ID_CONNECT,TBBS_BUTTON,2);
	
	CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnUpdateChat(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}



void CMainFrame::OnSketch() 
{
	// TODO: Add your command handler code here
	CreateActivateView(RUNTIME_CLASS(DndSketchView),3);
	CDocument* pDoc = GetActiveDocument();	

}

void CMainFrame::OnMap() 
{
	// TODO: Add your command handler code here
	CreateActivateView(RUNTIME_CLASS(DnDMapView),4);
	CDocument* pDoc = GetActiveDocument();	
}

void CMainFrame::OnMapplay() 
{
	// TODO: Add your command handler code here
		CreateActivateView(RUNTIME_CLASS(CDnDMapPlay),5);
	CDocument* pDoc = GetActiveDocument();
}
