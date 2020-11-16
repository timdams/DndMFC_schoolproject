// DnDDoc.cpp : implementation of the CDnDDoc class
//


#include "stdafx.h"

#include "ACCESS.H"
#include "DnD.h"

//#include "ProgDlg.h"
#include <afxcmn.h>
#include "ProgressBar.h"

#include <fstream.h>

#include "DnDDoc.h"
#include "mmsystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
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
/*
struct Container
{
	UINT type;
	CString data;
}Cont[MAX_CONTAINER];
*/
CDnDDoc::CDnDDoc()
{
	// TODO: add one-time construction code here

}

CDnDDoc::~CDnDDoc()
{
}

BOOL CDnDDoc::OnNewDocument()
{
	// nodig om met goede ACCESS versie te kunnen werken
	AfxGetModuleState()->m_dwVersion = 0x0601;

	FILE *TempFile;
	m_bConnChange=false;
	m_bChatChange=false;
	m_bCreateTemp=false;
	m_bPlayerChange=false;

	char FileName[MAX_PATH];
	GetModuleFileName(AfxGetInstanceHandle(),FileName,MAX_PATH);
	Path=(CString)FileName;
	Path=Path.Left(Path.ReverseFind('\\') );
	DBPath=Path+"\\DnDDatabase";
	m_bPlayerChange=FALSE;
	ACCESS DnDDB;
	DbExists=DnDDB.Open(DBPath);//("DnDDatabase");
	DnDDB.CreateUserTable();
	DnDDB.CreateBan();
	DnDDB.CreateOverView();
	DnDDB.CreateCharacterTable();
	DnDDB.Close();

	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	svrSocket.SetParent(this);
	
	
	for (int i=0; i<MaxNumClients; i++) 
	{	
		mClient[i] = new CMySocket;
		
		mClient[i]->SetParent(this);	
	}
	m_bSocketCreated=FALSE;
	m_bSocketListening=FALSE;
	m_nNumClients=0;
		


	for(int k=0;k<MaxNumClients;k++)
	{
		timeoutTimer[k]=0;
	}

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

//	TempFile=fopen("Temp.DnD","w+t");

//	if(!TempFile)
//	{
//		m_bCreateTemp=false;
//		AfxMessageBox("No Temp file could be created!",MB_ICONSTOP);
//	}
//	else
//	{
//		m_bCreateTemp=true;
//		fclose(TempFile);
//	}
	SketchPicturePath="zepponop"; 
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

void CDnDDoc::OnAccept()
{
	if (m_nNumClients<MaxNumClients) 
	{
		if (svrSocket.Accept(*mClient[m_nNumClients])) 
		{
			UpdateAllViews(NULL,CONNINFO,NULL);	
			m_nNumClients++;
			msMsg.Format("Connecting to D&D-Online Server Alpha 1.2");
			Send(NEWCONN,mClient[m_nNumClients-1]);
			timeoutTimer[m_nNumClients-1]=timeGetTime();
		}
	
	}
	else {
		CMySocket client;
		client.SetParent(this);
		if (svrSocket.Accept(client)) 
		{
			msMsg.Format("Maximum clients of %i reached. No more clients allowed.",m_nNumClients);
			Send(3,&client);	// Send error message
			Send(0,&client);	// Close connection
			AddToBarrel(CONNINFO,msMsg);
			client.Close();
		}
		else AddToBarrel(CONNINFO,"Server full, new client could not connect");
	}
	UpdateAllViews(NULL,0,0);
}

void CDnDDoc::OnReceive(CMySocket *pSocket)
{
	ACCESS DnDDB;

	int nParameter,i,j,x,ClientNr;
	bool bNameExists=false,NameExists=false;bool continued=TRUE;
	bool IsAlive=TRUE;
	CString TmpStr,TheUserName;
	CString tmp,tmpIP,FindUserName;
	CStringArray CharList;
	CString charname;
	CMySocket *pTmpSocket;

	UINT tmpPort;
	CFileException	e;
	TRY
	{
	CSocketFile file(pSocket);	
	CArchive arIn(&file,CArchive::load);	
	svrSocket.AsyncSelect(0);      //  Disable receive notifications during Reads()
	for (ClientNr=0; ClientNr<m_nNumClients && pSocket!=mClient[ClientNr]; ClientNr++) ;
	do
     {
		arIn>>nParameter;
		if(nParameter==PLAYERINFO || nParameter==USERNAME)
		{
			DnDDB.Open(DBPath);
		}
		
	
	//		TmpStr.Format("  Client: %d",ClientNr);
		switch(nParameter)
		{

		
		case CHAT:
			arIn>>msMsg;
			
			TmpStr.Format("%s:",mUsername.GetAt(ClientNr));
			msMsg=TmpStr+msMsg;
			for(i=0;i<m_nNumClients;i++)
			{
				if(i!=ClientNr)
					Send(CHAT,mClient[i]);
			}
			AddToBarrel(CHAT,msMsg);
			timeoutTimer[ClientNr]=timeGetTime(); 
			break;
		case KICK:
		case DISCONNECT:
			TmpStr.Format("Client %s has left",mUsername.GetAt(ClientNr));
			mClient[ClientNr]->Close();
			timeoutTimer[ClientNr]=0; 
			m_nNumClients--;
			mUsername.RemoveAt(ClientNr);
			pTmpSocket=mClient[ClientNr];			// Save closed socket
			for (j=ClientNr; j<m_nNumClients; j++)	// Shift sockets
			{
				mClient[j]=mClient[j+1];
				timeoutTimer[j]=timeoutTimer[j+1];
			}
			mClient[m_nNumClients]=pTmpSocket;		//Keep on using allocated socket
			
			m_bPlayerChange=1;
			
			AddToBarrel(CONNINFO,TmpStr);
			IsAlive=FALSE;
			break;

		case PLAYERINFO:
			timeoutTimer[ClientNr]=timeGetTime(); 
			arIn>>charsize;
			if(charsize==-3)
			{
				//deze 'fout' mag normaal niet voorkomen. Gebeurt dit wel: error bij client
				TmpStr.Format("User disconnecting.Reason:Illegal character  chosen.User has been notified of this");
				
			}
			else if(charsize==-1)
			{
				OnePlayer.Serialize(arIn);
				TmpStr.Format("User chooses new player");
				mClient[ClientNr]->CharName=OnePlayer.CharacterName;

//				DnDDB.Close();
//				DnDDB.Open(DBPath);


				if(DbExists)  // we zijn vertrokken van een bestaande database
				{
					DnDDB.GetCharArray(mUsername.GetAt(ClientNr),CharList);
					for(x=0;x<CharList.GetSize();x++)
					{
						if(CharList[x]==OnePlayer.CharacterName)
						{
							//Normaal gezien controleert Client dit reeds maar je weet maar nooit
							AfxMessageBox("CharacterName is already controlled by this User");
							NameExists=true;
						}
					}
				}
				if(!NameExists)
				{
					if(DbExists) // we zijn vertrokken van een bestaande database
					{
						DnDDB.GetArray("CHARACTERTABLE","Name",CharList);
						for(x=0;x<CharList.GetSize();x++)
						{
							if(CharList[x]==OnePlayer.CharacterName)
							{
								NameExists=true;
								CString tempString;
								tempString="Can user: '";
								tempString+=mUsername.GetAt(ClientNr);
								tempString+="' use someone else's character ('";
								tempString+=OnePlayer.CharacterName;
								tempString+="')?";
								//"Can user x use someone else's character(charname)?"
								DnDDB.Close();
								int nResponse=AfxMessageBox(tempString,MB_YESNO|MB_ICONQUESTION);
								if(nResponse==IDYES)
								{
									DnDDB.Open(DBPath);
									DnDDB.UseSameChar(mUsername.GetAt(ClientNr),OnePlayer.CharacterName);
									continued=FALSE;
								}
								else 
								{
									FillCharArray(mUsername.GetAt(ClientNr));
									Send(PLAYERUPDATE,mClient[ClientNr]);
								}
							}
						}
					}
				
				if(continued)
				{
					if(!DbExists) // we zijn vertrokken van een nieuwe database
					{
						DbExists=true;
					// INDIEN DATABASE NIEUW IS -> MAG NIET BEGINNEN TELLEN...
						DnDDB.MakeNewChar2(mUsername.GetAt(ClientNr),OnePlayer.CharacterName);
					}
					else
						DnDDB.MakeNewChar(mUsername.GetAt(ClientNr),OnePlayer.CharacterName);
				}	
			//	if(!DnDDB.ExistTable(mUsername.GetAt(ClientNr)))
			//		DnDDB.CreateTable(mUsername.GetAt(ClientNr));

				CString Age,Charisma,Wisdom,Intelligence,Constitution,Dexterity,Strength,Head;
				Age.Format("%d",OnePlayer.Age);
				Head.Format("%d",OnePlayer.head);
				Charisma.Format("%d",OnePlayer.Charisma);
				Wisdom.Format("%d",OnePlayer.Wisdom);
				Intelligence.Format("%d",OnePlayer.Intelligence);
				Constitution.Format("%d",OnePlayer.Constitution);
				Dexterity.Format("%d",OnePlayer.Dexterity);
				Strength.Format("%d",OnePlayer.Strength);

				DnDDB.FillCharTable(OnePlayer.CharacterName,OnePlayer.Race,OnePlayer.Class,OnePlayer.Deity,\
					OnePlayer.Alignment,OnePlayer.Familiar,"Common",OnePlayer.Gender,Head,\
					OnePlayer.Description,Age,Strength,Dexterity,Constitution,Intelligence,\
					Wisdom,Charisma);
				mClient[ClientNr]->m_nHeadFigure=atoi(DnDDB.GetValue("CHARACTERTABLE","NAME","PICTURE",mClient[ClientNr]->CharName));

				DnDDB.Close();
					if(Sketch.GetSize())
						Send(SKETCH,mClient[ClientNr]);
					if(bPlaying && Map.GetSize())
					{
						Send(MAPDM,mClient[ClientNr]);
						Send(MAPVIS,mClient[ClientNr]);
					}
					if(SketchPicturePath!="zepponop")
					{
						Send(IMAGEREQ1,mClient[ClientNr]);
					}
				}
				// Send naar alle players
				SendToAll(NEWPLAYER);
				
			}
			else 
			{
				arIn>>charname;
				TmpStr.Format("User chooses existing player no %i", charsize);
				mClient[ClientNr]->CharName=charname;
				tmp.Format("%i",0);
				long number=atoi(tmp);
				if(DbExists)
				{	
					ACCESS DnDDB;
					DnDDB.Open(DBPath);	
					mClient[ClientNr]->m_nHeadFigure=atoi(DnDDB.GetValue("CHARACTERTABLE","NAME","PICTURE",mClient[ClientNr]->CharName));
					
					DnDDB.Close();
				}
				if(Sketch.GetSize())
					Send(SKETCH,mClient[ClientNr]);
				if(bPlaying && Map.GetSize())
				{
						Send(MAPDM,mClient[ClientNr]);
						Send(MAPVIS,mClient[ClientNr]);
				}
				// Send naar alle players
				SendToAll(NEWPLAYER);
			}
			//Niefe sketch ?
			m_bPlayerChange=1;

			AddToBarrel(CONNINFO,TmpStr);
			break;
		case USERNAME:// Username wordt gestuurd door client om te controleren							 
			// of deze naam geldig is en client mag connecten
			arIn>>msMsg;
			TheUserName=msMsg;
			if(msMsg=="")// geen lege username pls (serversided regelen?)
			{
				bNameExists=true;
				msMsg="You have been disconnected... Please fill in a username!";
				Send(KICK,mClient[ClientNr]);
				mClient[ClientNr]->Close();
				m_nNumClients--;
				timeoutTimer[ClientNr]=0; 
				
			}

			i=FindUser(msMsg);// controleer eerst of username niet reeds bestaat
			if(i>=0)
			{
				bNameExists=true;
				tmp.Format("You have been disconnected... Username: %s is already in use!",msMsg);
				msMsg=tmp;
				Send(KICK,mClient[ClientNr]);
				mClient[ClientNr]->Close();
				m_nNumClients--;
				timeoutTimer[ClientNr]=0; 

			}

			// check of het IP nog niet in de Ban_List staat
			mClient[ClientNr]->GetPeerName(tmpIP,tmpPort);
			if(DbExists)
				FindUserName=DnDDB.GetValue("Ban_List","IP",tmpIP);
			else
				FindUserName="Not found";
			if(FindUserName!="Not found")
			{
				bNameExists=true;
				tmp.Format("%s has been disconnected... %s's IP is on banned list.",msMsg,msMsg);
				msMsg=tmp;
				AddToBarrel(CONNINFO,tmp);
				Send(KICK,mClient[ClientNr]);
				mClient[ClientNr]->Close();
				m_nNumClients--;
				timeoutTimer[ClientNr]=0;
			}

			if(!bNameExists)
			{
				ACCESS DnDDB;
				DnDDB.Open(DBPath);
				CString userpass,dbpass,existuser;
				arIn>>msMsg;
				userpass=msMsg;

				if(!DbExists) // Vertrokken van nieuwe database
				{
					DnDDB.AddUser(TheUserName,userpass);
					CString temp=TheUserName;
					temp+=" is a new user. His name was added to the database.";
					AfxMessageBox(temp);
					mUsername.InsertAt(ClientNr,TheUserName);
					mClient[ClientNr]->GetPeerName(tmpIP,tmpPort);
					tmp.Format("New client connected: IP: %s, Port: %d, Username: %s",\
						tmpIP,tmpPort,TheUserName);
					
					timeoutTimer[ClientNr]=timeGetTime();

					//FillCharArray(mUsername.GetAt(ClientNr));
					charsize=0;
					Send(PLAYERUPDATE,mClient[ClientNr]);
					// Voorlopig zo:
					// mClient[ClientNr]->m_nHeadFigure=0;
					AddToBarrel(CONNINFO,tmp);
					// DbExists=true; nog niet hier, pas na nieuwe char
				}
				else
				{

					if(!DnDDB.ExistUser(TheUserName)) //new user
					{
						DnDDB.AddUser(TheUserName,userpass);
						CString temp=TheUserName;
						temp+=" is a new user. His name was added to the database.";
						AfxMessageBox(temp);
						mUsername.InsertAt(ClientNr,TheUserName);
						mClient[ClientNr]->GetPeerName(tmpIP,tmpPort);
						tmp.Format("New client connected: IP: %s, Port: %d, Username: %s",\
							tmpIP,tmpPort,TheUserName);
						
						timeoutTimer[ClientNr]=timeGetTime();

						//FillCharArray(mUsername.GetAt(ClientNr));
						charsize=0;
						Send(PLAYERUPDATE,mClient[ClientNr]);
						// Voorlopig zo:
						// mClient[ClientNr]->m_nHeadFigure=0;
						AddToBarrel(CONNINFO,tmp);
						
							//SendToAll(SKETCH);
					}

					else
					{
						dbpass=DnDDB.GetValue("OVERVIEW","USERNAME","PASSWORD",TheUserName);
						if(userpass==dbpass)
						{
							mUsername.InsertAt(ClientNr,TheUserName);
							mClient[ClientNr]->GetPeerName(tmpIP,tmpPort);
							tmp.Format("New client connected: IP: %s, Port: %d, Username: %s",\
								tmpIP,tmpPort,TheUserName);
							timeoutTimer[ClientNr]=timeGetTime(); 
							FillCharArray(mUsername.GetAt(ClientNr));
							Send(PLAYERUPDATE,mClient[ClientNr]);
							//Voorlopig zo:
							//mClient[ClientNr]->m_nHeadFigure=0;
							//m_bPlayerChange=1;
							AddToBarrel(CONNINFO,tmp);
							//Niefe sketch ?

						}
						else
						{
							tmp.Format("%s entered a wrong password (%s instead of %s)"\
								,TheUserName,userpass,dbpass);
							AddToBarrel(CONNINFO,tmp);
							Send(KICK,mClient[ClientNr]);
							mClient[ClientNr]->Close();
							m_nNumClients--;
							timeoutTimer[ClientNr]=0;
						}
					}
				}
				DnDDB.Close();
			}
		
			break;
		case SKETCHUPDATE:
			timeoutTimer[ClientNr]=timeGetTime(); 
			Send(SKETCH,mClient[ClientNr]);
			break;
		case IMAGEREQ2:
			timeoutTimer[ClientNr]=timeGetTime(); 
			//stuur image;
		//	AfxMessageBox("User doesn't have this image.So far for this code.To be continued thoug.Expect image-over-network-sending :)))");
			Send(IMAGEREQ2,mClient[ClientNr]);
			break;
		case KEEPALIVE:
			//do nothing but keep'm alive
			timeoutTimer[ClientNr]=timeGetTime(); 
			break;
		default:
			tmp.Format("Illegal parameter(%i) received from user %s",nParameter,mUsername.GetAt(ClientNr));
			AddToBarrel(CONNINFO,tmp);
			
			break;
		}
		if(nParameter==PLAYERINFO || nParameter==USERNAME) //zeer belangrijk , anders gaat dbase telkens
			//geopend en geclosed worden, zelfs als er gewoon een dom paketje binnenkomt dat niets but keepalive doet
		{
			DnDDB.Close();
		}
	}
	while (!arIn.IsBufferEmpty() && !bNameExists && IsAlive);
	svrSocket.AsyncSelect();

	arIn.Close();
	file.Close();

	if(!IsAlive)
	{
		SendToAll(NEWPLAYER);
	}

	}
	CATCH(CException, e)
	{
		AfxMessageBox("Tried to receive. Failed Miserably");
		e->Delete();
	}
	END_CATCH;

	
}

int CDnDDoc::FindUser(CString Username)
{
	int size=mUsername.GetSize();
	for(int i=0;i<size;i++)
		if(!Username.CompareNoCase(mUsername.GetAt(i)))// kop nie over breken, MFC is vreemd!
			return i;
	return i=-1;
}

void CDnDDoc::SendToAll(int nParameter)
{
	for(int i=0;i<m_nNumClients;i++)
		Send(nParameter,mClient[i]);
}

void CDnDDoc::SendToUser(int nParameter,CString Username)
{
	int i=FindUser(Username);
	if(i>=0)
		Send(nParameter,mClient[i]);
}


void CDnDDoc::Send(int nParameter,CMySocket *pSocket)
{
	DWORD dwSize=256;
	char pBuffer[10];
	CFileException	e;
	CString strMessage,TmpStr;
	int i=5;
	int j;
	CPTGameObject obj;
	CString tempke;
	unsigned char onechar[2];
	CFile Image;
	DWORD li=0;
	DWORD fileLength=0;
	DWORD count;


//	CProgressDlg *pModelessDlg = new CProgressDlg();
//	m_pMainWnd = pModelessDlg;
//	pModelessDlg->Create();
//	return TRUE;



	TRY
	{
		CSocketFile file(pSocket);
		CArchive arOut(&file,CArchive::store);	

		switch(nParameter)
		{
		case IMAGEREQ1:
			//hoi, ik ga deze image sturen? Heb je die al?Zo ja, teken hem aub
			if(SketchPicturePath!="zepponop")
			{
				Image.Open(SketchPicturePath,CFile::modeRead | CFile::typeBinary);
				fileLength=Image.GetLength();
				Image.Close();
			}
			else
			{
				fileLength=0;
			}
			arOut<<nParameter;
			arOut<<SketchPicturePath;
			arOut<<fileLength;
			break;
		case IMAGEREQ2:
			//je heb hem nog niet? Hier komt ie dan, please stand by
			if(SketchPicturePath!="zepponop")
			{
				Image.Open(SketchPicturePath,CFile::modeRead | CFile::typeBinary);
				fileLength=Image.GetLength();
				
				arOut<<nParameter;
				arOut<<SketchPicturePath;
				arOut<<fileLength;
				count=0;
				

				while(count<fileLength-10)
				{
					Image.Read(pBuffer, 10);
					for(i=0;i<10;i++)
						arOut<<pBuffer[i];
					
					count=count+10;
					Image.Seek(count,CFile::begin);
			

				}
				
				if(count!=fileLength)
				{
					Image.Read(pBuffer, fileLength-count);
					for(i=0;i<fileLength-count;i++)
						arOut<<pBuffer[i];
				}
				//dlg.DeleteProgressBar();
				Image.Close();
			}
			break;
		case DISCONNECT:
			arOut<<nParameter;
			m_bPlayerChange=1;
			
			break;
		case CHAT:											
			arOut<<nParameter<<msMsg;
			break;
		case NEWCONN:
			arOut<<nParameter<<msMsg;
			break;
		case KICK:
			arOut<< KICK;
			m_bPlayerChange=1;
			
			break;
		case MAPITEMONE:
			arOut<<nParameter;
			arOut<<VisSend.x;
			MapObj.Serialize(arOut);
			break;
		case MAPVISONE:
			arOut<<nParameter;
			arOut<<VisSend.x;
			arOut<<VisSend.y;
			arOut<<PlayerVisible[VisSend.x][VisSend.y];
			break;
		case MAPVIS:
			arOut<<nParameter;
			arOut<<MapBlocks;
			for(i=0;i<MapBlocks.x;i++)
			{
				for(j=0;j<MapBlocks.y;j++)
					arOut<<PlayerVisible[i][j];
			}
			break;
		case MAPDM:
			arOut<<nParameter;
			arOut<<Map.GetSize();
			for(i=0;i<Map.GetSize();i++)
			{
				Map.GetAt(i).Serialize(arOut);
			}
			arOut<<m_mapname;
		//	AddToBarrel(CHAT,"Sending a map");
			break;

		case SKETCH:
			arOut<<nParameter;
			//eerst grootte sketch doorsturen
			arOut<<Sketch.GetSize();
			//alle schets objecten
			for(i=0;i<Sketch.GetSize();i++)
			{
				obj=Sketch.GetAt(i);
				obj.Serialize(arOut);
			}
			//vervolgens relatieve grootte van originele sketch
			arOut<<sketchEndPoint;

		//	AddToBarrel(CHAT,"Sending a Sketch");
			break;
		case SKETCHUPDATE:
			arOut<<nParameter;
			// voorlopig kunne we niet zien of er nieuwe schets is
			//arOut<<random waarde van huidige schets
			//Hier komt element x van de sketch
			arOut<<Sketch.GetSize();
			obj=Sketch.GetAt(Sketch.GetSize()-1);
			obj.Serialize(arOut);
		//	AddToBarrel(ADMINCHAT,"Debug stuff: send an update of sketch");
			break;

		case PLAYERUPDATE:
			arOut<<nParameter;	
			// aantal characters, vervolgens characters zelf
			
			arOut<<charsize;
			//arOut<<charlist;
			for(i=0;i<charsize;i++)
				TempChars.GetAt(i).Serialize(arOut);
			break;

		case NEWPLAYER:
			arOut<<nParameter;	
			// eerst aantal characters, vervolgens charname, dan headnummer 
			arOut<<m_nNumClients;
			for(i=0;i<m_nNumClients;i++)
			{
				arOut<<mClient[i]->CharName;
				arOut<<mClient[i]->m_nHeadFigure;
			}
			break;

		default:
			arOut<<nParameter;

		}
		arOut.Close();
		file.Close();
	}
	CATCH(CException, e)
	{
		AfxMessageBox("Error occured: Tried to send to client.Continue at own risk :(");
		e->Delete();
	}
	END_CATCH;



}

void CDnDDoc::OnCloseDocument() 
{
	// TODO: Add your specialized code here and/or call the base class
	msMsg.Format("Server has been shut down");
	if(m_bSocketListening)
	{
		SendToAll(CHAT);
		SendToAll(DISCONNECT);
		svrSocket.Close();
	}
/*	for (int i=MaxNumClients-1; i<=0; i++) 
	{		
		delete mClient[i];	
	}*/
	CDocument::OnCloseDocument();

}

/*void CDnDDoc::AddToCont(Container *Cont, int Type, CString Str)
{
	int i=0;
	CString tempstring;

	while((i<MAX_CONTAINER-1)&&(Cont[i].type!=EMPTY))
	{
		i++;
	}


	if(i>=MAX_CONTAINER-1)
	{
		if(m_bCreateTemp)// enkel schrijven indien we een nieuwe tempfile kunnen openen/maken
		{
			FILE *TempFile;
			TempFile=fopen("Temp.DnD","a+t");
			for(i=0;i<MAX_CONTAINER-1;i++)
			{
				tempstring.Format("%d:\t",Cont[i].type);
				fprintf(TempFile,tempstring);
				fprintf(TempFile,Cont[i].data);
				fprintf(TempFile,"\n");
				Cont[i].type=0;
			}
			fclose(TempFile);
		}
		i=0;
	}

	Cont[i].data=Str;
	Cont[i].type=Type;
	if(Cont[i].type==CONNINFO)
		m_bConnChange=true;
	else if((Cont[i].type==CHATTEXT)||(Cont[i].type==PRIVATECHAT)||(Cont[i].type==ADMINCHAT))
		m_bChatChange=true;
	UpdateAllViews(NULL,0,NULL);

}
*/
int CDnDDoc::KickUser(int k,int type)
{
//	m_bPlayerChange=TRUE;
	CString TmpStr;
	CMySocket *pTmpSocket;
	if(k!=-1)
	{
		if(type!=DISCONNECT)
			Send(KICK,mClient[k]);
		if(k<mUsername.GetSize())
		{
			if(type!=DISCONNECT)
			TmpStr.Format("%s was kicked",mUsername.GetAt(k));
			else 
			TmpStr.Format("%s timed-out",mUsername.GetAt(k));
			mUsername.RemoveAt(k);
		}
		else 
			TmpStr.Format("Illegal user was kicked");

		timeoutTimer[k]=0; 
		mClient[k]->Close();
		m_nNumClients--;
		
		pTmpSocket=mClient[k];				// Save closed socket
		for (int j=k; j<m_nNumClients; j++)	// Shift sockets
		{
			mClient[j]=mClient[j+1];
			timeoutTimer[j]=timeoutTimer[j+1];
		}
		mClient[m_nNumClients]=pTmpSocket;	//Keep on using allocated socket
		AddToBarrel(CONNINFO,TmpStr);
		SendToAll(NEWPLAYER);
		return k;
	}

	return -1;
}

int CDnDDoc::RemoveUser(CString UserName)
{
	int i=0;
	bool found=false;
	CStringArray List;
	ListUsers(List);
	for(int j=0;j<List.GetSize();j++)
	{
		if(List[j]==UserName)
		{
			found=true;
			j=List.GetSize();
		}
	}
	if(found)
	{
		ACCESS DnDDB;
		DnDDB.Open(DBPath);
		DnDDB.DeleteUser(UserName);
		i=2;
		DnDDB.Close();
	}
	return i;
}

int CDnDDoc::BanUser(CString UserName,int type)
{
	CString tmpIP,FindIP;
	UINT tmpPort;

	ACCESS DnDDB;
	DnDDB.Open(DBPath);

	mClient[FindUser(UserName)]->GetPeerName(tmpIP,tmpPort);

	//AfxMessageBox(tmpIP);

//	m_bPlayerChange=TRUE;

	if(type==1) //bannen de user
	{
		if(FindUser(UserName)!=-1)
		{
			KickUser(FindUser(UserName),KICK);
		}
		DnDDB.AddBan(tmpIP,UserName);
		
		DnDDB.Close();

		return 1;
	}

	if(type==0) //unbannen de user
	{
		FindIP=DnDDB.GetValue("Ban_List","USERNAME",UserName);
		if(FindIP!="Not found")
			DnDDB.UnBan(FindIP);
			
		else
		{
			DnDDB.Close();
			return -2;
		}
		DnDDB.Close();
		return 1;
	}
	DnDDB.Close();
	return 1;
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
	case CHAT:
	case ADMINCHAT:
	case PRIVATECHAT:
		ChatBarrel.Add(temp);
		MapPlayBarrel.Add(temp);
		break;
	case CONNINFO:
		ConnBarrel.Add(temp);
		break;
	default:
		strtemp="ILLEGAL CONTAINER REQUEST_"+strInt + str;
		temp.data=strtemp;
		temp.type=CONNINFOERROR;
		ConnBarrel.Add(temp);
		break;
	}

	// Volgende lijn kunnen we specifieker maken en in switch zelf zette
	// en we zeggen dan 'die view alleen moet updaten'.
	UpdateAllViews(NULL,0,NULL);
		
	return 1;
}

void CDnDDoc::ListBan(CStringArray &List)
{
	ACCESS DnDDB;
	DnDDB.Open(DBPath);

	DnDDB.GetBan_List(List);

	DnDDB.Close();
}

void CDnDDoc::ListUsers(CStringArray &List)
{
	ACCESS DnDDB;
	DnDDB.Open(DBPath);

	DnDDB.GetUsers_List(List);

	DnDDB.Close();
}

void CDnDDoc::ClearTable(CString TableName)
{
	ACCESS DnDDB;
	DnDDB.Open(DBPath);

	DnDDB.CleanTable(TableName);

	DnDDB.Close();
}

void CDnDDoc::FindChar(CString UserName,CStringArray &List)
{
	if(DbExists)
	{
	//	CString temp,c_Print;
		ACCESS DnDDB;
		DnDDB.Open(DBPath);
		DnDDB.GetCharArray(UserName,List);
		DnDDB.Close();
		if(List[0]=="The list is empty")
		{	
		//	List.Add("No database table available for this player.");
			List.RemoveAll();
			// MAKE A NEW TABLE
		//	DnDDB.CreateTable(UserName);
		}

		/*for(int j=0;j<List.GetSize();j++)
			AfxMessageBox(List[j]);*/
	}
}

bool CDnDDoc::ExistTable(CString TableName)
{
	ACCESS DnDDB;
	DnDDB.Open(DBPath);
	if(DnDDB.ExistTable(TableName))
		return true;
	else
		return false;
	DnDDB.Close();
}

void CDnDDoc::FillCharArray(CString User)
{
	CPlayerInfo objtmp;
	CStringArray names;
	CStringArray races;
	CStringArray classes;
	CStringArray deities;
	CStringArray alignments;
	CStringArray heads;
	CStringArray gender;
	CStringArray familiars;
	CStringArray descriptions;
	CStringArray ages;
	CStringArray strengths;
	CStringArray dexterities;
	CStringArray constitutions;
	CStringArray intelligences;
	CStringArray wisdoms;
	CStringArray charismas;

	charlist.RemoveAll();
	FindChar(User,charlist);
	charsize=charlist.GetSize();
	TempChars.RemoveAll();
	if(DbExists)
	{	
		ACCESS DnDDB;
		DnDDB.Open(DBPath);
		DnDDB.GetCharArray(User,names);
		if(names[0]!="The list is empty")
		{
			int size=names.GetSize();
			for(int i=0;i<size;i++)
				races.Add(DnDDB.GetValue("CHARACTERTABLE","NAME","RACE",names[i]));

			for(i=0;i<size;i++)
				classes.Add(DnDDB.GetValue("CHARACTERTABLE","NAME","CLASS",names[i]));

			for(i=0;i<size;i++)
				deities.Add(DnDDB.GetValue("CHARACTERTABLE","NAME","DEITY",names[i]));

			for(i=0;i<size;i++)
				alignments.Add(DnDDB.GetValue("CHARACTERTABLE","NAME","ALIGNMENT",names[i]));

			for(i=0;i<size;i++)
				heads.Add(DnDDB.GetValue("CHARACTERTABLE","NAME","PICTURE",names[i]));

			for(i=0;i<size;i++)
				gender.Add(DnDDB.GetValue("CHARACTERTABLE","NAME","GENDER",names[i]));

			for(i=0;i<size;i++)
				familiars.Add(DnDDB.GetValue("CHARACTERTABLE","NAME","FAMILIAR",names[i]));

			for(i=0;i<size;i++)
				descriptions.Add(DnDDB.GetValue("CHARACTERTABLE","NAME","DESCRIPTION",names[i]));

			for(i=0;i<size;i++)
				ages.Add(DnDDB.GetValue("CHARACTERTABLE","NAME","AGE",names[i]));

			for(i=0;i<size;i++)
				strengths.Add(DnDDB.GetValue("CHARACTERTABLE","NAME","STRENGTH",names[i]));

			for(i=0;i<size;i++)
				dexterities.Add(DnDDB.GetValue("CHARACTERTABLE","NAME","DEXTERITY",names[i]));

			for(i=0;i<size;i++)
				constitutions.Add(DnDDB.GetValue("CHARACTERTABLE","NAME","CONSTITUTION",names[i]));

			for(i=0;i<size;i++)
				intelligences.Add(DnDDB.GetValue("CHARACTERTABLE","NAME","INTELLIGENCE",names[i]));

			for(i=0;i<size;i++)
				wisdoms.Add(DnDDB.GetValue("CHARACTERTABLE","NAME","WISDOM",names[i]));

			for(i=0;i<size;i++)
				charismas.Add(DnDDB.GetValue("CHARACTERTABLE","NAME","CHARISMA",names[i]));
		}
		DnDDB.Close();	
	}
	for(int i=0;i<charsize;i++)
	{
		objtmp.CharacterName=names.GetAt(i);
		objtmp.Race=races.GetAt(i);
		objtmp.Class=classes.GetAt(i);
		objtmp.Deity=deities.GetAt(i);
		objtmp.Alignment=alignments.GetAt(i);
		objtmp.Gender=gender.GetAt(i);
		objtmp.head=atoi(heads.GetAt(i));
		objtmp.Familiar=familiars .GetAt(i);
		objtmp.Description=descriptions.GetAt(i);
		objtmp.Age=atoi(ages.GetAt(i));
		objtmp.Strength=atoi(strengths.GetAt(i));
		objtmp.Dexterity=atoi(dexterities.GetAt(i));
		objtmp.Constitution=atoi(constitutions.GetAt(i));
		objtmp.Intelligence=atoi(intelligences.GetAt(i));
		objtmp.Wisdom=atoi(wisdoms.GetAt(i));
		objtmp.Charisma=atoi(charismas.GetAt(i));
		TempChars.Add(objtmp);
	}
	// hier alle andere brol van database in CPlayerInfo array proppen aub

}

void CDnDDoc::GetStats(CString Charname,CStringArray &List)
{
	ACCESS DnDDB;
	DnDDB.Open(DBPath);
	List.Add(DnDDB.GetValue("CHARACTERTABLE","NAME","ARMORCLASS",Charname));
	List.Add(DnDDB.GetValue("CHARACTERTABLE","NAME","ITEMLIST_ID",Charname));
	List.Add(DnDDB.GetValue("CHARACTERTABLE","NAME","STRENGTH",Charname));
	List.Add(DnDDB.GetValue("CHARACTERTABLE","NAME","DEXTERITY",Charname));
	List.Add(DnDDB.GetValue("CHARACTERTABLE","NAME","CONSTITUTION",Charname));
	List.Add(DnDDB.GetValue("CHARACTERTABLE","NAME","INTELLIGENCE",Charname));
	List.Add(DnDDB.GetValue("CHARACTERTABLE","NAME","WISDOM",Charname));
	List.Add(DnDDB.GetValue("CHARACTERTABLE","NAME","CHARISMA",Charname));
	DnDDB.Close();
}

void CDnDDoc::SetStats(CString charname, CStringArray &Statnames,CStringArray &Statvalues)
{
	// NOT USED
	ACCESS DnDDB;
	DnDDB.Open(DBPath);
	for(int i=0;i<Statnames.GetSize();i++)
	{
		DnDDB.SetStat(charname,Statnames[i],Statvalues[i]);
	}
	DnDDB.Close();
}


