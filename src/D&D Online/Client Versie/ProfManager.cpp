// ProfManager.cpp : implementation file
//

#include "stdafx.h"
#include "DnD.h"
#include "ProfManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProfManager dialog


CProfManager::CProfManager(CWnd* pParent /*=NULL*/)
	: CDialog(CProfManager::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProfManager)
	m_strFile = _T("");
	m_bpathcheck = FALSE;
	//}}AFX_DATA_INIT
}


void CProfManager::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProfManager)
	DDX_Control(pDX, IDC_FILE, m_ctlfile);
	DDX_Control(pDX, IDC_BROWSEFILE, m_ctlbrowse);
	DDX_Control(pDX, IDC_STATFILE, m_ctlfilestat);
	DDX_Control(pDX, IDC_PROFILES, m_ctlProfiles);
	DDX_Text(pDX, IDC_FILE, m_strFile);
	DDX_Check(pDX, IDC_CHANGEPATH, m_bpathcheck);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProfManager, CDialog)
	//{{AFX_MSG_MAP(CProfManager)
	ON_BN_CLICKED(IDC_SAVECHANGES, OnSavechanges)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_CHANGE, OnChange)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_BROWSEFILE, OnBrowsefile)
	ON_BN_CLICKED(IDC_CHANGEPATH, OnChangepath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProfManager message handlers

void CProfManager::OnSavechanges() 
{
	// TODO: Add your control notification handler code here


}

void CProfManager::OnAdd() 
{
	// TODO: Add your control notification handler code here
	CAddProfile dlg;
	CProfile obj;
	CString sIP;
	UpdateData(TRUE);
	if(IDOK==dlg.DoModal())
	{
		//allen brol toevoegen aan lijstje	
		obj.ServerIP=dlg.ServerIP;
		obj.ServerName=dlg.m_profname;
		obj.UserName=dlg.m_username;
		obj.UserPass=dlg.m_pass;
		ProfileStack.Add(obj);
	}
	m_ctlProfiles.ResetContent();
	for(int i=0;i<ProfileStack.GetSize();i++)
		m_ctlProfiles.AddString(ProfileStack.GetAt(i).ServerName);
	UpdateData(FALSE);
	CString deb;
	deb.Format("%i",ProfileStack.GetSize());

}

void CProfManager::OnChange() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CAddProfile dlg;
	CProfile obj;
	CString deb;
	int k=m_ctlProfiles.GetCurSel();
	if(k!=-1)
	{
	dlg.m_pass=ProfileStack.GetAt(k).UserPass;
	dlg.m_username=ProfileStack.GetAt(k).UserName;
	dlg.m_profname=ProfileStack.GetAt(k).ServerName;
	dlg.ServerIP=ProfileStack.GetAt(k).ServerIP;
	if(IDOK==dlg.DoModal())
		{
			//modify changes
			obj.ServerIP=dlg.ServerIP;
			obj.ServerName=dlg.m_profname;
			obj.UserName=dlg.m_username;
			obj.UserPass=dlg.m_pass;
			ProfileStack.SetAt(k,obj);
		}
	}
}


DWORD CProfManager::GetDWORDIPAddress(CString strIPAddress)
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

void CProfManager::OnDelete() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CArray<CProfile, CProfile&> stacktmp;
	CProfile obj;
	int i;
	int k=m_ctlProfiles.GetCurSel();
	if(k!=-1)
	{
		for(i=0;i<ProfileStack.GetSize();i++)
		{
			if(i!=k)
			{
				obj=ProfileStack.GetAt(i);
				stacktmp.Add(obj);
			}
		}
		ProfileStack.RemoveAll();
		for(i=0;i<stacktmp.GetSize();i++)
		{
			obj=stacktmp.GetAt(i);
			ProfileStack.Add(obj);
		}
	}
	
	m_ctlProfiles.ResetContent();
	for(i=0;i<ProfileStack.GetSize();i++)
		m_ctlProfiles.AddString(ProfileStack.GetAt(i).ServerName);
	UpdateData(FALSE);
}

void CProfManager::OnBrowsefile() 
{
	// TODO: Add your control notification handler code here
	
	CFileDialog *dlg;
	dlg= new CFileDialog(TRUE,NULL,"settings",NULL,"Setting Files (*.ini)|*.ini|All Files (*.*)|*.*",this);
	if(IDOK==dlg->DoModal())
		m_strFile=dlg->GetPathName();
	UpdateData(FALSE);
}

BOOL CProfManager::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	m_strFile="settings.ini";
	UpdateData(FALSE);
	LoadChanges();
	m_ctlProfiles.ResetContent();
	for(int i=0;i<ProfileStack.GetSize();i++)
		m_ctlProfiles.AddString(ProfileStack.GetAt(i).ServerName);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CProfManager::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	int k=SaveChanges();
	if(k==1)
		CDialog::OnOK();
}

UINT CProfManager::LoadChanges()
{
	CString Key = "HA2003"; //niemand mag deze key weten!
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
		AfxMessageBox(str);
	}
	
	if(bError)
		bFound = FALSE;

	return !bError;
}

UINT CProfManager::SaveChanges()
{


	
	
	//With kind permission of Sven Deruyter
	


	FILE* outFile;
	int i,j,k;
	CString str, strSave,strHead;
	bool bSuccess = TRUE;

	UpdateData(TRUE);
	if(m_strFile!="")
	{
		outFile=fopen(m_strFile,"wt");
	}
	else
	{
		AfxMessageBox("No filename was given, please do so before continuing.",MB_ICONSTOP  ,0);
		bSuccess=FALSE;
	}
	if(outFile != NULL && bSuccess)
	{
		for(j=0;j<ProfileStack.GetSize();j++)
		{
			//Header
			strHead= "SP";
			fputc('#',outFile);
			for(i=0;i<strHead.GetLength();i++)
				fputc(strHead[i],outFile);
			fputc('\t',outFile);

			//Arguments
			for(k=0;k<4;k++)
			{
				switch(k)
				{
				case  0:
					strSave=ProfileStack.GetAt(j).ServerName;
					break;
				case 1:
					strSave=ProfileStack.GetAt(j).ServerIP;
					break;
				case 2:
					strSave=ProfileStack.GetAt(j).UserName;
					break;
				case 3:
					strSave=ProfileStack.GetAt(j).UserPass;
					break;
				default:
					AfxMessageBox("Hier moogde ni komen hoor");
				};
				for(i=0;i< strSave.GetLength();i++)
					fputc(strSave[i],outFile);
					fputc('\t',outFile);
			}
			fputc('\n',outFile);
		}

		fclose(outFile);
	}
	else
	{
		str.Format("Could not find file %s", m_strFile);
		bSuccess=FALSE;
		AfxMessageBox(str);
	}
	if(bSuccess)
		int k=0;
		//LoadFromFile();
	
	if(bSuccess)
		return 1;
	else return -1;
}

void CProfManager::OnChangepath() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_bpathcheck)
	{
		m_ctlfilestat.EnableWindow(TRUE);
		m_ctlbrowse.EnableWindow(TRUE);
		m_ctlfile.EnableWindow(TRUE);
		
	}
	else
	{
		m_ctlfilestat.EnableWindow(FALSE);
		m_ctlbrowse.EnableWindow(FALSE);
		m_ctlfile.EnableWindow(FALSE);
		
	}
}
