// AddProfile.cpp : implementation file
//

#include "stdafx.h"
#include "DnD.h"
#include "AddProfile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddProfile dialog


CAddProfile::CAddProfile(CWnd* pParent /*=NULL*/)
	: CDialog(CAddProfile::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddProfile)
	m_pass = _T("");
	m_profname = _T("");
	m_username = _T("");
	//}}AFX_DATA_INIT
}


void CAddProfile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddProfile)
	DDX_Control(pDX, IDC_SERVIP, m_ctIP);
	DDX_Text(pDX, IDC_PASS, m_pass);
	DDX_Text(pDX, IDC_PROFNAME, m_profname);
	DDX_Text(pDX, IDC_USERNAME, m_username);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddProfile, CDialog)
	//{{AFX_MSG_MAP(CAddProfile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddProfile message handlers

void CAddProfile::OnOK() 
{
	bool bSuccess=TRUE;
	// TODO: Add extra validation here
	BYTE b0,b1,b2,b3;
	UpdateData(TRUE);
	
	//controleren dat alles is ingevuld
	if(m_profname=="")
		bSuccess=FALSE;
	if(m_username=="")
		bSuccess=FALSE;
	if(m_pass=="")
		bSuccess=FALSE;
	//conversie naar cstring van ip
	m_ctIP.GetAddress(b0,b1,b2,b3);
	if(b0==0)
		bSuccess=FALSE;
	ServerIP.Format(_T("%u.%u.%u.%u"),b0,b1,b2,b3);
	if(bSuccess)
		CDialog::OnOK();
	else
		AfxMessageBox("Not all fields are filled in.",MB_ICONSTOP ,0);
}

BOOL CAddProfile::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ctIP.SetAddress(GetDWORDIPAddress(ServerIP));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
DWORD CAddProfile::GetDWORDIPAddress(CString strIPAddress)
{
	strIPAddress.MakeReverse();// Start from behind

	char DOT = '.';
	DWORD dwReturnValue = 0;

	double dPower = 0.0;

	int length = strIPAddress.GetLength();

	DWORD dwByteTemp = 0;
	int nWhichByte = 0;
	int i = 0;
	for(i; i<length ; i++ )
	{
		volatile int nTemp = 0;
		char aChar = strIPAddress.GetAt(i);

		if(aChar != DOT)
		{
			int nChar = 0;
			switch(aChar)
			{
				case '1': nChar = 1; break;
				case '2': nChar = 2; break;
				case '3': nChar = 3; break;
				case '4': nChar = 4; break;
				case '5': nChar = 5; break;
				case '6': nChar = 6; break;
				case '7': nChar = 7; break;
				case '8': nChar = 8; break;
				case '9': nChar = 9; break;
				case '0': nChar = 0; break;
				default: break;
			}
			nTemp = nChar * (int)pow(10.0 ,dPower);
			dwByteTemp += nTemp;
			dPower++;

			if(i == length-1 )//Last Byte
			{
				dwByteTemp <<= (nWhichByte * 8);//8 Bits = Byte Length
				dwReturnValue = dwReturnValue | dwByteTemp;
				dPower = 0;
				dwByteTemp = 0;
				nWhichByte++;
			}
		} 
		else 
		{
			dwByteTemp <<= (nWhichByte * 8);// 8 Bits =Byte Length
			dwReturnValue = dwReturnValue | dwByteTemp;
			dPower = 0;
			dwByteTemp = 0;
			nWhichByte++;
		}
	}
	strIPAddress.MakeReverse();//Undo
	return dwReturnValue;
}
