// DnDSketch.cpp : implementation file
//

#include "stdafx.h"
#include "DnD.h"
#include "DnDSketch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDnDSketch

IMPLEMENT_DYNCREATE(CDnDSketch, CFormView)

CDnDSketch::CDnDSketch()
	: CFormView(CDnDSketch::IDD)
{
	//{{AFX_DATA_INIT(CDnDSketch)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDnDSketch::~CDnDSketch()
{
}

void CDnDSketch::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDnDSketch)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDnDSketch, CFormView)
	//{{AFX_MSG_MAP(CDnDSketch)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDnDSketch diagnostics

#ifdef _DEBUG
void CDnDSketch::AssertValid() const
{
	CFormView::AssertValid();
}

void CDnDSketch::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDnDSketch message handlers
