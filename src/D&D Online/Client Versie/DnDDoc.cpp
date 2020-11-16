// DnDDoc.cpp : implementation of the CDnDDoc class
//

#include "stdafx.h"
#include "DnD.h"

#include "DnDDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDnDDoc

IMPLEMENT_DYNCREATE(CDnDDoc, CDocument)

BEGIN_MESSAGE_MAP(CDnDDoc, CDocument)
	//{{AFX_MSG_MAP(CDnDDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDnDDoc construction/destruction

CDnDDoc::CDnDDoc()
{
	// TODO: add one-time construction code here

}

CDnDDoc::~CDnDDoc()
{
}

BOOL CDnDDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	receivedpackages=0;
	m_bConnChange=false;
	m_bChatChange=false;
	m_bCreateTemp=false;
	m_bConnected=false;
	MyName.Format("None");
	MyHead=-4;
	mClient.SetParent(this);
	int buffer=30;
//	mClient.SetSockOpt(SO_SNDBUF,&buffer,sizeof(buffer),SOL_SOCKET);
//	mClient.SetSockOpt(SO_RCVBUF,&buffer,sizeof(buffer),SOL_SOCKET);

	char FileName[MAX_PATH];
	GetModuleFileName(AfxGetInstanceHandle(),FileName,MAX_PATH);
	Path=(CString)FileName;
	Path=Path.Left(Path.ReverseFind('\\') );
	ImagePath=Path+"\\ImageTemp";
	CreateDirectory(ImagePath,NULL);
	MaxHeadBitmaps=0;
	CFileFind finder;
	PortraitsPath =Path+"\\Heads";
	CString FirstPath=PortraitsPath+ "\\head0.bmp";
	bool bWorking = finder.FindFile(FirstPath);
	while (bWorking)
	{
		MaxHeadBitmaps++;
		FirstPath.Format(PortraitsPath+"\\head%i.bmp",MaxHeadBitmaps+1);
		bWorking = finder.FindFile(FirstPath);
      
	}

	if(MaxHeadBitmaps==0)
		AfxMessageBox("No bitmaps found in " +PortraitsPath+". Continue at own risk!"); 
	else if(MaxHeadBitmaps>=160)
		MaxHeadBitmaps=159;
//	AfxMessageBox(ImagePath);

//	TempFile=fopen("Temp.DnD","w+t");

/*	if(!TempFile)
	{
		m_bCreateTemp=false;
		AfxMessageBox("No Temp file could be created!",MB_ICONSTOP);
	}
	else
	{
		m_bCreateTemp=true;
		fclose(TempFile);
	}*/

	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDnDDoc serialization

void CDnDDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDnDDoc diagnostics

#ifdef _DEBUG
void CDnDDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDnDDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDnDDoc commands

// All rights reserved to Cyberninja for this function :)
CString CDnDDoc::IPtoCString(CIPAddressCtrl &IP)
{
	CString sIP;
	BYTE a0, a1, a2, a3;
	
	IP.GetAddress(a0, a1, a2, a3);
    sIP.Format(_T("%u.%u.%u.%u"), a0, a1, a2, a3);

	return sIP;
}


void CDnDDoc::OnReceive()
{
	CString	strMessage, TmpStr;
	CDndPlayer dlg;
//	CCreatePlayer dlg2;
	int nParameter;
	CPlayerInfo chartmp;
	CPTGameObject obj;
	bool GottoClose=FALSE;
	char pBuffer[10];
	int numberofplayers;
	int headnumber;
	int size=0;
	DWORD fileLength;
	DWORD count=0;
	DWORD li=0;
	int i=0;
	int j=0;
	int imagesize=0;
	bool sketchrequest=FALSE;
	CFile  checkfile;
	CFileException	e;
	int error=0;

	TRY
	{
		CSocketFile file(&mClient);	
		CArchive arIn(&file,CArchive::load);

		if(mClient.AsyncSelect(0)==0)
		{
			AfxMessageBox("Server left (or network error occured...it's your call ;)");	
		}
		else
		{
		do{
			
			arIn>>nParameter;
			TmpStr.Format("  Param: %d   ",nParameter);
			switch(nParameter)
			{
			case IMAGEREQ1:
				arIn>>TmpStr;
				SketchImagePath=ImagePath+'\\'+TmpStr;
				arIn>>fileLength;
				//hebben we hem? Ja, teken hem
				if(TmpStr!="zepponop")
				{
					if(FileExists(SketchImagePath) )
					{
						checkfile.Open(SketchImagePath,CFile::modeRead | CFile::typeBinary);
						//maar eerst zien dat ie wel even groot is
						if(checkfile.GetLength()==fileLength)
						{
							checkfile.Close();
							AddToBarrel(IMAGEREQ1,SketchImagePath);
						}
						else
						{
							checkfile.Close();
							Send(IMAGEREQ2);
						}
						
					}
					else
						//anders tekening aan server vragen
						Send(IMAGEREQ2);
				}
				else
					AddToBarrel(IMAGEREQ1,TmpStr);
				break;
			case IMAGEREQ2:
				//hier een coole tekening voor je :p
				arIn>>TmpStr;
				SketchImagePath=ImagePath+'\\'+TmpStr;
				checkfile.Open(SketchImagePath,CFile::modeCreate | CFile::modeWrite | CFile::typeBinary, &e);
				arIn>>fileLength;
				count=0;
				while(count<fileLength-10)
				{
					
					for(i=0;i<10;i++)
						arIn>>pBuffer[i];
					checkfile.Write(pBuffer,10);
					count=count+10;
					checkfile.Seek(count,CFile::begin);
				}
				if(count!=fileLength)
				{
					
					for(i=0;i<fileLength-count;i++)
						arIn>>pBuffer[i];
					checkfile.Write(pBuffer, fileLength-count);
				}

				checkfile.Close();
				
				TmpStr.Format("Got %i bytes ",fileLength);
				AddToBarrel(IMAGEREQ1,SketchImagePath);
				break;
			case CHAT:
				arIn>>strMessage;
				TmpStr=strMessage;
				AddToBarrel(CHATTEXT,TmpStr);
				break;
			case NEWPLAYER:
				PlayerNames.RemoveAll();
				arIn>>numberofplayers;
				for(i=0;i<numberofplayers;i++)
				{
					
					arIn>>strMessage;
					PlayerNames.Add(strMessage);
					arIn>>headnumber;
					PlayerHeads[i]=headnumber;
					//als speler een karakter van een ander neemt heeft hij head nog niet
					//dat wordt hier opgevangen, en sowieso gecotnroleerd als hij toch reeds head had
					if(strMessage==MyName)
						MyHead=headnumber;
				}
				TmpStr.Format("Received new player information.%i player(s) on server now",PlayerNames.GetSize());
				AddToBarrel(CHATNEWPLAYER,TmpStr);
				break;
			case KEEPALIVE:
				break;
			case DISCONNECT:
				TmpStr="Connection with server has been closed!";
			case KICK:
				m_bConnected = false;
				sIPServer = "\0";
				TmpStr.Format("Disconnected from server");
				//mClient.Close();
				GottoClose=TRUE;
				PlayerNames.RemoveAll();
				MyHead=-3;
				MyName="None";
				AddToBarrel(CHATNEWPLAYER,TmpStr);
				AddToBarrel(CHAT,TmpStr);
				break;
			case NEWCONN:
				arIn>>strMessage;
				TmpStr="NEWCONN: ";
				TmpStr+=strMessage;
				AddToBarrel(CONNINFO,TmpStr);
				Send(USERNAME);
				break;
			case MAPITEMONE:
				arIn>>i;
				obj.Serialize(arIn);
				Map.SetAt(i,obj);
				TmpStr.Format("Got update of item number %i",i);
				AddToBarrel(MAPDM,TmpStr);
				break;
			case MAPVISONE:
				arIn>>i;
				arIn>>j;
				arIn>>PlayerVisible[i][j];
			//	TmpStr.Format("Got element [%i][%i] visibility update",i,j);
				AddToBarrel(MAPVIS,TmpStr);
				break;
			case MAPVIS:
				arIn>>MapBlocks;
				for(i=0;i<MapBlocks.x;i++)
				{
					for(j=0;j<MapBlocks.y;j++)
						arIn>>PlayerVisible[i][j];
				}
			//	if(MapBlocks.x==-1)
				
				TmpStr.Format("Got %ix%i visibility objects",MapBlocks.x,MapBlocks.y);
					AddToBarrel(MAPVIS,TmpStr);
				break;
			case MAPDM:
				Map.RemoveAll();

				arIn>>mapsize;
				for(i=0;i<mapsize;i++)
				{
					obj.Serialize(arIn);
					Map.Add(obj);
				}
				arIn>>m_mapname;
				TmpStr.Format("Got %i map objects",Map.GetSize());
					AddToBarrel(MAPDM,TmpStr);

				break;
			case SKETCH:
				//if(NewSketch);
				Sketch.RemoveAll();
				//Hoeveelheid figuren die zullen komen
				arIn>>size;

				for(i=0;i<size;i++)
				{
					obj.Serialize(arIn);	
					Sketch.Add(obj);
				}
				arIn>>sketchEndPoint;
				//debug
				TmpStr.Format("Got %i sketch objects",Sketch.GetSize());
			//	AfxMessageBox(TmpStr);
				AddToBarrel(SKETCH,TmpStr);
				break;
			case SKETCHUPDATE:
				//hebben we elementen gemist?
				arIn>>size;
				if(size-1!=Sketch.GetSize())
					//request full drawing please, I missed a bit
					//echter NA de rest
					sketchrequest=TRUE;
				obj.Serialize(arIn);
				Sketch.Add(obj);
				TmpStr.Format("Got sketch object nr %i",Sketch.GetSize());
				AddToBarrel(SKETCHUPDATE,TmpStr);
				if(sketchrequest)
				{
					Send(SKETCHUPDATE);
					AddToBarrel(CHAT,"Requested the full sketch");
				}
				sketchrequest=FALSE;
				break;
			case PLAYERUPDATE:
				//retrieve number of characters
				arIn>>userchars;
				//arIn>>chars themselve
				TempChars.RemoveAll();
				for(i=0;i<userchars;i++)
				{
					chartmp.Serialize(arIn);
					TempChars.Add(chartmp);	
				}
				if(userchars ==0)
				{//nieuwe char maken en naar server sturen
					
					CCreatePlayer dlg2;
					dlg2.PortraitsPath=PortraitsPath;
					dlg2.MaxHeadBitmaps=MaxHeadBitmaps;
					dlg2.DoModal();
					OnePlayer=dlg2.ThePlayer;
					MyName=OnePlayer.CharacterName;
					MyHead=OnePlayer.head;
				//	stuur allen brol naar server
					userchars=-1;
				}
				else
				{
					//choose character
					for(int i=0;i<userchars;i++)
						dlg.existingchars.Add(TempChars.GetAt(i));	
					dlg.DoModal();
					CCreatePlayer dlg2;
					dlg2.MaxHeadBitmaps=MaxHeadBitmaps;
					dlg2.PortraitsPath=PortraitsPath;
					if(dlg.newChar)
					{
						//gebruiker heeft reeds characters maar wenst nieuwe te maken
						//moet echter controle gebeuren intern dat nieuwe charname niet reeds bestaat
						for(int i=0;i<userchars;i++)
							dlg2.ForbiddenNames.Add(TempChars.GetAt(i).CharacterName);
						dlg2.DoModal();
						OnePlayer=dlg2.ThePlayer;
						MyName=OnePlayer.CharacterName;
						MyHead=OnePlayer.head;
						userchars=-1;
					}
					else
					{
						userchars=dlg.chosenchar;
						if(dlg.chosenchar!=-2 && dlg.chosenchar<=TempChars.GetSize() && dlg.chosenchar>=0)
						{
							MyName=userchar=TempChars.GetAt(userchars).CharacterName;											
							MyHead=TempChars.GetAt(userchars).head;
						}
						else if(dlg.chosenchar==-2)
						{
							MyName=userchar=dlg.m_unusedcharname;
							MyHead=0;
							userchars=-1;
							OnePlayer.CharacterName=userchar;
						}
					}

				}	
				if(userchars!=-3)
					//enkel als gebruiker een char kiest/nieuw kiest etc doorgaan. 
					Send(PLAYERINFO);
				else 
				{			
					Send(0);
					TmpStr.Format("Program disconnected itself:You have not chosen a character. Or you hit the escape button. Please refrain from doing so.");
					m_bConnected = false;
					sIPServer = "\0";
					AddToBarrel(CONNCLOSE,TmpStr);
					//mClient.Close();
					GottoClose=TRUE;
				}
				break;
			
			default:
				AfxMessageBox("Strange Parameter received: probably one or more serialized object have different version (desynchronised)");
			}

		}while(!arIn.IsBufferEmpty() && !GottoClose );
		if(!GottoClose)
			mClient.AsyncSelect();
		}
		if(GottoClose)
		{
			TmpStr="Disconnected";
			mClient.Close();
			AddToBarrel(CONNCLOSE,TmpStr);
		}
		arIn.Close();
		file.Close();
	}
	
	CATCH(CException, e)
	{
		AfxMessageBox("Tried to receive. Failed Miserably");
		e->Delete();
	}
	END_CATCH;

}


void CDnDDoc::Send(int nParameter)
{
//	UpdateData();
	CString tmp="Jef";
	TRY
	{

	CSocketFile file(&mClient);
	CArchive arOut(&file,CArchive::store);	
//	CString Username=m_sUsername;
	
		if(m_bConnected && mClient)
		{	
		
		switch(nParameter)
			{
			case 0:
				arOut<<nParameter;
				m_bConnected=0;
				PlayerNames.RemoveAll();
				MyHead=-3;
				MyName="None";
				AddToBarrel(CHATNEWPLAYER,"");
				break;
			case CHAT:
				arOut<<nParameter;
				arOut<<m_sSend;
				break;
			case USERNAME:
				arOut<<nParameter;
				arOut<<m_sUsername;
				arOut<<m_sPass;
				break;
			case PLAYERINFO:
				arOut<<nParameter;
				if(userchars==-1)
				{
					arOut<<userchars;
					OnePlayer.Serialize(arOut);

				}
				else
				{
					arOut<<userchars;
					arOut<<userchar;
				}

			//	arOut<<kop;
			//	arOut<<tmp;
				break;
			case KEEPALIVE:
				if(m_bConnected)
					arOut<<nParameter;
				//stuur lege message (enkel parameter)
				break;
			case IMAGEREQ2:
				arOut<<nParameter;
				break;
			default:
				AfxMessageBox("Trying to send Illegal or undefined parameter ,check Send()-function in doc");
			}
		}
	arOut.Close();	
	file.Close();
	}

	CATCH(CException, e)
	{
		AfxMessageBox("Tried to sent. Failed Miserably");
		e->Delete();
	}
	END_CATCH;
}

// Found this on http://archive.devx.com/free/tips/tipview.asp?content_id=3454
DWORD CDnDDoc::GetDWORDIPAddress(CString strIPAddress)
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

void CDnDDoc::OnCloseDocument() 
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_bConnected)
	{
		Send(0);
		mClient.Close();
	}

	CDocument::OnCloseDocument();
}

int CDnDDoc::AddToBarrel(int Type, CString str)
{
	CString strtemp;
	CString strInt;
	strInt.Format("%i:",Type);
	CBarrel temp;
	temp.data=str;
	temp.type=Type;
	switch(Type)
	{
	case ADMINCHAT:
	case PRIVATECHAT:
	case CHATTEXT:
	case CHAT:
		MapBarrel.Add(temp);
	case IMAGEREQ1:
	case CHATNEWPLAYER:
	case SKETCH:
	case SKETCHUPDATE:
		ChatBarrel.Add(temp);	
		break;
	case CONNINFO:
	case CONNCLOSE:
		ConnBarrel.Add(temp);
		break;
	case MAPDM:
	case MAPVIS:
		MapBarrel.Add(temp);
		ChatBarrel.Add(temp);
		break;
	default:
		strtemp="ILLEGAL CONTAINER REQUEST_"+strInt + str;
		temp.data=strtemp;
		temp.type=CONNINFO;
		ConnBarrel.Add(temp);
		break;
	}
	// Volgende lijn kunnen we specifieker maken en in switch zelf zette
	// en we zeggen dan 'die view alleen moet updaten'.
	if(Type!=CONNCLOSE)
		UpdateAllViews(NULL,0,NULL);
	else
		UpdateAllViews(NULL,CONNCLOSE,NULL);
	return 1;
}

BOOL CDnDDoc::FileExists(LPCTSTR lpFileName)
{
    DWORD dwFileAttr = GetFileAttributes(lpFileName);

    if ((dwFileAttr != 0xFFFFFFFF) &&
        !(dwFileAttr & FILE_ATTRIBUTE_DIRECTORY))
        return TRUE;
    else
        return FALSE;

}
