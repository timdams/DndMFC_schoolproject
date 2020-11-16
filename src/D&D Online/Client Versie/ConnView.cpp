// ConnView.cpp : implementation file
//

#include "stdafx.h"
#include "DnD.h"
#include "ConnView.h"
#include "DnDDoc.h"

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
	m_nPort = 12455;
	m_sEditUsername = _T("");
	m_sEditPass = _T("");
	//}}AFX_DATA_INIT
}

CConnView::~CConnView()
{
}

void CConnView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConnView)
	DDX_Control(pDX, IDC_USERPROFILE, m_userprof);
	DDX_Control(pDX, IDC_CONNPROFILE, m_combprof);
	DDX_Control(pDX, IDC_IPADDRESS, m_cIP);
	DDX_Control(pDX, IDC_LISTCONN, m_ConnList);
	DDX_Text(pDX, IDC_EDITPORT, m_nPort);
	DDV_MinMaxInt(pDX, m_nPort, 0, 999999);
	DDX_Text(pDX, IDC_EDITUSERNAME, m_sEditUsername);
	DDX_Text(pDX, IDC_EDITPASS, m_sEditPass);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConnView, CFormView)
	//{{AFX_MSG_MAP(CConnView)
	ON_BN_CLICKED(IDC_BUTTONCONNECT, OnButtonConnect)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_DEBUGBTN, OnDebugbtn)
	ON_BN_CLICKED(IDC_PLAYERSET, OnPlayerset)
	ON_CBN_SELCHANGE(IDC_CONNPROFILE, OnSelchangeConnprofile)
	ON_CBN_SELCHANGE(IDC_USERPROFILE, OnSelchangeUserprofile)
	ON_BN_CLICKED(IDC_PROFMANAGER, OnProfmanager)
	ON_BN_CLICKED(IDC_DEBUGBTN2, OnDebugbtn2)
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


void CConnView::OnButtonConnect() 
{
	// TODO: Add your control notification handler code here
	
	CString TmpIP,TmpStr;
	UINT TmpPort;

//	CDnDDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);

//	m_cIP.SetAddress(pDoc->GetDWORDIPAddress("127.0.0.1"));
	
//	m_sEditUsername.Format("Lagge");
//	m_sEditPass.Format("abc");
//(	UpdateData(FALSE);
	CStatic* btnconn=(CStatic*)GetDlgItem(IDC_BUTTONCONNECT);

	
	UpdateData(TRUE);
	
	if(!pDoc->m_bConnected)
	{
		if(!m_sEditPass.IsEmpty() && !m_sEditUsername.IsEmpty() && m_sEditUsername.Find(" ")==-1)
		{
			pDoc->sIPServer=pDoc->IPtoCString(m_cIP);
			pDoc->m_sUsername=m_sEditUsername;
			pDoc->m_sPass=m_sEditPass;
			UpdateData();
			if(pDoc->mClient.Create())
					if(pDoc->mClient.Connect(pDoc->sIPServer,m_nPort))
					{
						pDoc->m_bConnected = true;
						pDoc->mClient.GetPeerName(TmpIP,TmpPort);
						TmpStr.Format("  Port:%u",TmpPort);
						AddToListbox("Connection established; IP: "+TmpIP+TmpStr,1);
						SetTimer(KEEPALIVE,2000,NULL);
						btnconn->SetWindowText("Disconnect");
					}
					else
					{
						pDoc->mClient.Close();
						AddToListbox("Can't connect with server - : "+pDoc->sIPServer,1);
					//	AfxMessageBox("Connection failed",MB_ICONSTOP);
					}
			else
			{
				AddToListbox("Can't connect with server - "+pDoc->sIPServer,1);
			}
		}
		else
		{
			if(m_sEditPass.IsEmpty() && m_sEditUsername.IsEmpty())
				AfxMessageBox("No username and/or password given, please do so before connecting to a server");
			else 
				AfxMessageBox("No spaces are allowed in username, please choose another name");
		}
	}
	else
	{
		pDoc->Send(0);
		pDoc->mClient.Close();
		btnconn->SetWindowText("Connect");
		AddToListbox("Disconnected from server",0);
	}
	
}

void CConnView::CloseConnect()
{
	
	KillTimer(KEEPALIVE);
	Sleep(2000);
}

void CConnView::AddToListbox(CString str,int type)
{
	
	CString strd;
	//ook lijn nummer ervoor tonen
	strd.Format("%i: "+str,m_ConnList.GetCount());
	switch(type)
	{		
	case 0:
		m_ConnList.AddString( strd,RGB(250,0,0));
		break;
	case 1:
		m_ConnList.AddString( strd,RGB(0,250,0));
		break;
	default:
		m_ConnList.AddString( strd);
	}

	CRect rect;
	
	// Volgende lijn moet eigenlijk niet aangezien we met string werken
	// en er niet gesorteerd wordt.
	m_ConnList.SetCurSel(m_ConnList.GetCount()-1);
}

CDnDDoc* CConnView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDnDDoc)));
	return (CDnDDoc*)m_pDocument;
}

void CConnView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	//de doc wordt verkregen 
//	CDnDDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
	int size=pDoc->ConnBarrel.GetSize();
	CString TmpIP,TmpStr;
	if(size!=lines && size!=0)
	{
		for(int i=lines;i<size;i++)
		{
			AddToListbox(pDoc->ConnBarrel.GetAt(i).data,0);
		}
		lines=size;
	}
	if(lHint==CONNCLOSE)
		CloseConnect();
	if(!pDoc->m_bConnected)
	{
		CStatic* btnconn=(CStatic*)GetDlgItem(IDC_BUTTONCONNECT);
		btnconn->SetWindowText("Connect");
	}
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

	if(nIDEvent==KEEPALIVE && pDoc->m_bConnected)
		pDoc->Send(KEEPALIVE);
	CFormView::OnTimer(nIDEvent);
}

void CConnView::OnInitialUpdate() 
{
	pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CFormView::OnInitialUpdate();

	m_strFile.Format("settings.ini");
	//AfxMessageBox(m_strFile);
	LoadProfiles();
	m_combprof.ResetContent();
	for(int i=0;i<ProfileStack.GetSize();i++)
		m_combprof.AddString(ProfileStack.GetAt(i).ServerName);


	pDoc->kop=0;

	lines=0;
	// TODO: Add your specialized code here and/or call the base class
	srand( (unsigned)time( NULL ) );	
	
}

void CConnView::OnDebugbtn() 
{
	CCreatePlayer dlg;
	dlg.DoModal();

}

void CConnView::OnPlayerset() 
{
	// TODO: Add your control notification handler code here
//	CDnDDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
	CDndPlayer dlg;
	if(dlg.DoModal()==IDOK)
	{
		AfxMessageBox("OK");
		pDoc->kop=dlg.chosenchar;
	}
	else AfxMessageBox("NOK");
}

void CConnView::OnSelchangeConnprofile() 
{
	// TODO: Add your control notification handler code here
//	CDnDDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
	CString temp;
	int k=m_combprof.GetCurSel();
	
	if(k!=CB_ERR)
	{
		m_sEditUsername=ProfileStack.GetAt(k).UserName;
		m_sEditPass=ProfileStack.GetAt(k).UserPass;
		m_cIP.SetAddress(pDoc->GetDWORDIPAddress(ProfileStack.GetAt(k).ServerIP));
	}
	UpdateData(FALSE);
}

void CConnView::OnSelchangeUserprofile() 
{
	// TODO: Add your control notification handler code here
	//not used anymore
		// TODO: Add your control notification handler code here
//	CDnDDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
	CString temp;
	//voorlopig zo
	if(m_userprof.GetCurSel()!=CB_ERR)
	{
		m_userprof.GetLBText(m_userprof.GetCurSel(),temp);
		m_sEditUsername=temp;
		m_sEditPass.Format("abc");
	}
		UpdateData(FALSE);
}

void CConnView::OnProfmanager() 
{
	// TODO: Add your control notification handler code here
	CProfManager dlg;
	
	dlg.DoModal();
	m_strFile.Format("%s",dlg.m_strFile);
	LoadProfiles();
	m_combprof.ResetContent();
	for(int i=0;i<ProfileStack.GetSize();i++)
		m_combprof.AddString(ProfileStack.GetAt(i).ServerName);
	UpdateData(FALSE);
}


UINT CConnView::LoadProfiles()
{
	//With kind permission of Sven Deruyter
	FILE* inFile;
	char ch;
	int i = 0;
	bool bFound = FALSE, bError = FALSE;
	CString str, strRead, strHead, arg[4],strTmp;
	ProfileStack.RemoveAll();
	CProfile obj;
	inFile = fopen(m_strFile,"rt");
	if(inFile != NULL)
	{	while(!feof(inFile) && !bError)
		{	strRead = "";
			//////////////////////////////////////////////////////////////////
			//	Hier moet de notatie van de header geïnitialiseerd worden.	//
			//////////////////////////////////////////////////////////////////
			strHead = "SP";	// Profile.
			ch = fgetc(inFile);
			while((strRead != strHead) && !feof(inFile))	// Zoeken tot juiste header gevonden is.
			{	while(ch != '#' && !feof(inFile))
					ch = fgetc(inFile);	// Zoeken tot '#' gevonden is.
				if(ch == '#')
				{	ch = fgetc(inFile);
					str.Format("%c",ch);
					ch = fgetc(inFile);
					while(ch != '\t' && !feof(inFile))
					{	strRead.Format("%s%c",str,ch);
						str = strRead;
						ch = fgetc(inFile);
					}
					if(strRead == strHead)
						bFound = TRUE;
				}
				else
				{	if(!bFound)
					{	
						str.Format("Geen headers gevonden in bestand %s.",m_strFile);
						AfxMessageBox(str);
						bError = TRUE;
					}
				}
			}
			
			if(strRead == strHead)
			{	bFound = TRUE;
				//////////////////////////////////////////////////////////
				//	Hier moet het aantal argumenten ingegeven worden.	//
				//////////////////////////////////////////////////////////
				for(i = 0; i < 4; i++)	// 4 argumenten.
				{	ch = fgetc(inFile);
					str = "";
					while(ch != '\t')
					{	if(ch == '\n')
						{	
							str.Format("Te weinig argumenten voor header %s in bestand %s.",strHead,m_strFile);
							AfxMessageBox(str);
							bError = TRUE;
						}
						arg[i].Format("%s%c",str,ch);
						str = arg[i];
						ch = fgetc(inFile);
					}
				}
				//////////////////////////////////////////////////////////////////////
				//	Hier moet ingegeven worden in welke variabelen de argumenten	//
				//	opgeslagen moeten worden.										//
				//////////////////////////////////////////////////////////////////////
				obj.ServerName = arg[0];
				obj.ServerIP = arg[1];
				obj.UserName = arg[2];
				obj.UserPass= arg[3];
				ProfileStack.Add(obj);
			}
			else
			{	if(!bFound)
				{	
						str.Format("Geen headers gevonden van type %s in bestand %s.",strHead,m_strFile);
						AfxMessageBox(str);
					
					bError = TRUE;
				}
			}
		}
		fclose(inFile);
  	}
	else
	{	str.Format("Kan bestand %s niet vinden.",m_strFile);
	//	AfxMessageBox(str);
	}
	
	if(bError)
		bFound = FALSE;

	return !bError;
}

void CConnView::OnDebugbtn2() 
{
	// TODO: Add your control notification handler code here
	int i[2];
	i[3]=3;
}
