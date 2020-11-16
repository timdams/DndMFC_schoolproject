// ConnView.cpp : implementation file
//

#include "stdafx.h"
#include "DnD.h"
#include "ConnView.h"
#include "DndDoc.h"
#include "MainFrm.h"
#include "mmsystem.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConnView

IMPLEMENT_DYNCREATE(CConnView, CFormView)

CConnView::CConnView()
	: CFormView(CConnView::IDD)
{
	//{{AFX_DATA_INIT(CConnView)
	m_nPort = 0;
	m_bTimeOut = FALSE;
	m_ipadapter = _T("");
	m_ipadapter2 = _T("");
	m_connectedhosts = _T("");
	//}}AFX_DATA_INIT
}

CConnView::~CConnView()
{
}

void CConnView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConnView)
	DDX_Control(pDX, IDC_Link, m_link);
	DDX_Control(pDX, IDC_SVRSTATLIST, m_svrstatlist);
	DDX_Text(pDX, IDC_PORT, m_nPort);
	DDX_Check(pDX, IDC_BTIMEOUT, m_bTimeOut);
	DDX_Text(pDX, IDC_IP1, m_ipadapter);
	DDX_Text(pDX, IDC_CONHOST, m_connectedhosts);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConnView, CFormView)
	//{{AFX_MSG_MAP(CConnView)
	ON_BN_CLICKED(IDC_BTN_STARTSVR, OnStartServer)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConnView diagnostics

#ifdef _DEBUG
void CConnView::AssertValid() const
{
	CFormView::AssertValid();
}

void CConnView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CConnView message handlers



void CConnView::OnStartServer() 
{
	// TODO: Add your control notification handler code here



	UpdateData(TRUE);

	//de doc wordt verkregen 
//	CDnDDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
	CString strTemp;
	//de knop wordt verkregen zodat we de caption kunnen veranderen.
	CStatic* btnstartstop=(CStatic*)GetDlgItem(IDC_BTN_STARTSVR);
	//enkel nieuwe socket maken als die nog niet bestaat
	//dit is dus enkel als server niet 'aan staat'.
	if(!pDoc->m_bSocketCreated) 
	{
		if(m_nPort<1025 || m_nPort>60000)
		{
			AfxMessageBox("Illegal Port\nRange:1025-60000\nSet to default:12455");
			m_nPort=12455;
			UpdateData(FALSE);
		}
		
		if(pDoc->svrSocket.Create(m_nPort)) //gelukt
		{
			pDoc->m_bSocketCreated=TRUE;
			AddToListbox("Server socket created",0);
		}
		else  //ni gelukt: proberen fout te geven
		{
			AddToListbox("Server can't create a socket(desc follows):",CONNINFOERROR);
			AddToListbox(ConvertSocketError(pDoc->svrSocket.GetLastError()),CONNINFOERROR);
		}
	}
		
	//vervolgens beginnen we te luisteren, 
	//enkel ALS socket er is EN hij nog niet aan het luisteren was
	if(!pDoc->m_bSocketListening && pDoc->m_bSocketCreated)	
	{
		if(pDoc->svrSocket.Listen()) //succes
		{
			strTemp.Format("Server is listening on port %u",m_nPort);
			AddToListbox(strTemp,0);
			btnstartstop->SetWindowText("Close server");
			pDoc->m_bSocketListening=TRUE;
			if(m_bTimeOut)
				SetTimer(1,1000,NULL); //TimeoutTimer
		}
		else //ni gelukt: proberen fout te geven
		{
			AddToListbox("Server is NOT listening(desc follows):",CONNINFOERROR);
			AddToListbox(ConvertSocketError(pDoc->svrSocket.GetLastError()),CONNINFOERROR);
			
		
		}
	}
	else //als server al aan't listenen was , server afzetten en klaar
		//maken voor volgende sessie
	{
		if(AfxMessageBox("Server active. Are you sure you want to stop the server?",MB_YESNO)==IDYES)
		{
			KillTimer(1);
			for(int i=0;i<pDoc->m_nNumClients;i++)
			{
				pDoc->msMsg.Format("Server has been shut down");
				pDoc->Send(CHAT,pDoc->mClient[i]);	// Send error message
				pDoc->Send(0,pDoc->mClient[i]);	// Close connection
			}
			
			btnstartstop->SetWindowText("Start Server");
			pDoc->svrSocket.Close();
			pDoc->m_bSocketListening=FALSE;
			pDoc->m_bSocketCreated=FALSE;
			AddToListbox("Server stopped listening but can be restarted at your command",CONNINFOERROR);
		}
	}
		
}


void CConnView::AddToListbox(CString str,int type)
{
	
	CString strd;
	//ook lijn nummer ervoor tonen
	strd.Format("%i: "+str,m_svrstatlist.GetCount());
	switch(type)
	{		
	case CONNINFOERROR:
		m_svrstatlist.AddString( strd,RGB(250,0,0));
		break;
	case CONNINFO:
	case 0:
		m_svrstatlist.AddString( strd);
		
		break;
	default:
		m_svrstatlist.AddString( strd);
	}

	CRect rect;
	
	// Volgende lijn moet eigenlijk niet aangezien we met string werken
	// en er niet gesorteerd wordt.
	m_svrstatlist.SetCurSel(m_svrstatlist.GetCount()-1);
	UpdateData(true);
}

CDnDDoc* CConnView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDnDDoc)));
	return (CDnDDoc*)m_pDocument;
}

void CConnView::OnInitialUpdate() 
{
	pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CFormView::OnInitialUpdate();
	m_nPort=12455;
	m_bTimeOut=TRUE;
	UpdateData(FALSE);
	lines=0;
	// TODO: Add your specialized code here and/or call the base class
  
	char     szHostname[100];
    HOSTENT *pHostEnt;
	//ip retrieval   
	m_link.SetUnderline(CHyperLink::ulHover);
    gethostname( szHostname, sizeof( szHostname ));
    pHostEnt = gethostbyname( szHostname );

  
        char m_szBuf[101];
        int m_iaIP[4];
        unsigned char m_caH[4];

        for(int t=0;t<4;t++)
        {
            m_caH[t] = 
 (unsigned char)(pHostEnt->h_addr_list[0][t]);
            m_iaIP[t] = (int) m_caH[t];
        }

        
		m_ipadapter.Format("%d.%d.%d.%d", m_iaIP[0], m_iaIP[1],
	m_iaIP[2], m_iaIP[3]);



		UpdateData(false);

    

}

void CConnView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	//de doc wordt verkregen 
//	CDnDDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
	int size=pDoc->ConnBarrel.GetSize();
	CString TmpIP,TmpStr;
	if(size>=1)
	{
		for(int i=0;i<size;i++)
		{
			AddToListbox(pDoc->ConnBarrel.GetAt(i).data,0);
		}
		pDoc->ConnBarrel.RemoveAll();
	}
	int aantal=0;
	
	aantal=pDoc->m_nNumClients;
	
	switch(aantal)
	{
	case 0: m_connectedhosts.Format("None");break;
	case 1: m_connectedhosts.Format("1 host", aantal);break;
	default: m_connectedhosts.Format("%i hosts",aantal);
	};

	UpdateData(false);
	



	
}

CString CConnView::ConvertSocketError(int error)
{
	switch(error)
	{
	case WSANOTINITIALISED:return (CString)("A successful AfxSocketInit must occur before using this API.");
		   break;
	case WSAENETDOWN:return (CString)("The Windows Sockets implementation detected that the network subsystem failed.");
		   break;
	case WSAEAFNOSUPPORT:return (CString)("The specified address family is not supported.");
		   break;
	case WSAEINPROGRESS:return (CString)("A blocking Windows Sockets operation is in progress.");
		   break;
	case WSAEMFILE:return (CString)("No more file descriptors are available.");
		   break;
	case WSAENOBUFS:return (CString)("No buffer space is available. The socket cannot be created.");
		   break;
	case WSAEPROTONOSUPPORT:return (CString)("The specified port is not supported.");
		   break;
	case WSAEPROTOTYPE:return (CString)("The specified port is the wrong type for this socket.");
		   break;
	case WSAESOCKTNOSUPPORT:return (CString)("The specified socket type is not supported in this address family.");
		   break;
	case WSAEADDRINUSE:return (CString)("An attempt has been made to listen on an address in use.");
			break;
	case WSAEINVAL:return (CString)("The socket has not been bound with Bind or is already connected.");
			break;
	case WSAEISCONN:return (CString)("The socket is already connected.");
			break;
	case WSAENOTSOCK:return (CString)("The descriptor is not a socket.");
			break;
	case WSAEOPNOTSUPP:return (CString)("The referenced socket is not of a type that supports the Listen operation.") ;
			break;

	default:return (CString)("Unknown error occured");

	}
}
void CConnView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
//	CDnDDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
	int KickArray[pDoc->MaxNumClients];
	pDoc->SendToAll(KEEPALIVE);
	if(m_bTimeOut)
	{
	
		for(int k=0;k<pDoc->MaxNumClients;k++)
		{
			KickArray[k]=999;
		}
		int KickNumber=0;
		if(nIDEvent==1)
		{
		pDoc->appTime=timeGetTime();
		 for(int i=0;i<pDoc->m_nNumClients;i++)
		 {
			if(pDoc->timeoutTimer[i]!=0)
			{
				if(pDoc->appTime - pDoc->timeoutTimer[i]>7000)
				{
				//	KickArray[KickNumber]=i;
				//	KickNumber++;
					pDoc->KickUser(i,DISCONNECT);
					
				}
			}
		 }

		}
	}
	CFormView::OnTimer(nIDEvent);
}

BOOL CConnView::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	//Killalltimers!
	
	KillTimer(1);
	return CFormView::DestroyWindow();
}

void CConnView::OnButton1() 
{
	// TODO: Add your control notification handler code here
	pDoc->SendToAll(NEWPLAYER);


}
