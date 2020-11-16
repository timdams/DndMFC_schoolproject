// ChatView.cpp : implementation file
//

#include "stdafx.h"
#include "DnD.h"
#include "ChatView.h"
#include "resource.h"
#include "StatsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChatView

IMPLEMENT_DYNCREATE(CChatView, CFormView)

CChatView::CChatView()
	: CFormView(CChatView::IDD)
{
	//{{AFX_DATA_INIT(CChatView)
	m_commando = _T("");
	m_sendstringchat = _T("");
	//}}AFX_DATA_INIT
}

CChatView::~CChatView()
{
}

void CChatView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChatView)
	DDX_Control(pDX, IDC_HEAD8, m_head8);
	DDX_Control(pDX, IDC_HEAD7, m_head7);
	DDX_Control(pDX, IDC_HEAD6, m_head6);
	DDX_Control(pDX, IDC_HEAD5, m_head5);
	DDX_Control(pDX, IDC_HEAD3, m_head3);
	DDX_Control(pDX, IDC_HEAD4, m_head4);
	DDX_Control(pDX, IDC_HEAD2, m_head2);
	DDX_Control(pDX, IDC_HEAD1, m_head1);
	DDX_Control(pDX, IDC_COMMANDBOX, m_comcombo);
	DDX_Control(pDX, IDC_USERLIST, m_userbox);
	DDX_Control(pDX, IDC_CHATBOX, m_chatbox);
	DDX_CBString(pDX, IDC_COMMANDBOX, m_commando);
	DDX_Text(pDX, IDC_EDITTOSENDCHAT, m_sendstringchat);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChatView, CFormView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CChatView)
	ON_BN_CLICKED(IDC_BUTTONSEND, OnButtonSend)
	ON_CBN_CLOSEUP(IDC_COMMANDBOX, OnCloseupCommandbox)
	ON_BN_CLICKED(IDC_HEAD1, OnHead1)
	ON_BN_CLICKED(IDC_HEAD2, OnHead2)
	ON_BN_CLICKED(IDC_HEAD3, OnHead3)
	ON_BN_CLICKED(IDC_HEAD4, OnHead4)
	ON_BN_CLICKED(IDC_HEAD5, OnHead5)
	ON_BN_CLICKED(IDC_HEAD6, OnHead6)
	ON_BN_CLICKED(IDC_HEAD7, OnHead7)
	ON_BN_CLICKED(IDC_HEAD8, OnHead8)
	ON_COMMAND(ID_POPUP_WHISPER, OnPopupWhisper)
	ON_COMMAND(ID_POPUP_PLAYERSTATS, OnPopupPlayerstats)
	ON_UPDATE_COMMAND_UI(ID_POPUP_PLAYERSTATS, OnUpdatePopupPlayerstats)
	ON_UPDATE_COMMAND_UI(ID_POPUP_BAN, OnUpdatePopupBan)
	ON_COMMAND(ID_POPUP_BAN, OnPopupBan)
	ON_COMMAND(ID_POPUP_KICK, OnPopupKick)
	ON_UPDATE_COMMAND_UI(ID_POPUP_KICK, OnUpdatePopupKick)
	ON_WM_RBUTTONDOWN()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTNSEND, OnBtnsend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatView diagnostics

#ifdef _DEBUG
void CChatView::AssertValid() const
{
	CFormView::AssertValid();
}

void CChatView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChatView message handlers

void CChatView::OnInitialUpdate() 
{
	firstpaint=0;
	pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	LoadImages();

	CFormView::OnInitialUpdate();


	lines=0;
	m_comcombo.SetTopIndex(1);
	



}

void CChatView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
//	CDnDDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);

	CString TmpIP,TmpStr;
	CBarrel obj;		
	int size=pDoc->ChatBarrel.GetSize();
	if(size>=1)
	{
	
		for(int i=0;i<size;i++)
		{
			obj=pDoc->ChatBarrel.GetAt(i);
			if(obj.type==CHAT || obj.type==CHATTEXT || obj.type==ADMINCHAT || obj.type==PRIVATECHAT)
				AddToListbox(obj.data,obj.type);
			
		}
		pDoc->ChatBarrel.RemoveAll();
	}			
/*	if(size!=lines && size!=0)
	{
		for(int i=lines;i<size;i++)
		{
			AddToListbox(pDoc->ChatBarrel.GetAt(i).data,pDoc->ChatBarrel.GetAt(i).type);
		}
		lines=size;
	}	

*/


	if(pDoc->m_bPlayerChange && firstpaint)
	{

		//m_userbox.ResetContent();
		for(int l=0;l<pDoc->MaxNumClients;l++)
		{
		
			pHead[l]->ShowWindow(SW_HIDE);
			
		}
		for(int j=0;j<pDoc->m_nNumClients;j++)
		{
			//m_userbox.AddString(pDoc->mUsername.GetAt(j));
			if(pDoc->mClient[j]->m_nHeadFigure < pDoc->MaxHeadBitmaps)
				pHead[j]->SetBitmap(headbmp[pDoc->mClient[j]->m_nHeadFigure]);
			else
				pHead[j]->SetBitmap(headbmp[0]);
			pHead[j]->ShowWindow(SW_SHOW);
		}
		pDoc->m_bPlayerChange=0;
	}

}

CDnDDoc* CChatView::GetDocument()
{
//	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDnDDoc)));
	m_pDocument->IsKindOf(RUNTIME_CLASS(CDnDDoc));
	return (CDnDDoc*)m_pDocument;

}

void CChatView::AddToListbox(CString str,int type)
{
	CString StrTmp;
	CString StrTmp2;
	StrTmp=str;
	switch(type)
	{		
	case PRIVATECHAT:
		if(StrTmp.GetLength()>MAXLISTCHARS)
		{
			do
			{
				StrTmp2=StrTmp.Mid(MAXLISTCHARS);
				m_chatbox.AddString(StrTmp.Mid(0,MAXLISTCHARS),RGB(0,110,0));
				StrTmp=StrTmp2;
			}while(StrTmp.GetLength()>MAXLISTCHARS);
			m_chatbox.AddString(StrTmp,RGB(0,110,0));
		} 
		else 		
			m_chatbox.AddString(StrTmp.Mid(0,MAXLISTCHARS-1),RGB(0,110,0));

		break;
	case ADMINCHAT:
		if(StrTmp.GetLength()>MAXLISTCHARS)
		{
			do
			{
				StrTmp2=StrTmp.Mid(MAXLISTCHARS);
				m_chatbox.AddString(StrTmp.Mid(0,MAXLISTCHARS),RGB(250,50,0));
				StrTmp=StrTmp2;
			}while(StrTmp.GetLength()>MAXLISTCHARS);
			m_chatbox.AddString(StrTmp,RGB(250,50,0));
		} 
		else 		
			m_chatbox.AddString(StrTmp.Mid(0,MAXLISTCHARS-1),RGB(250,50,0));
		break;
	default:
		if(StrTmp.GetLength()>MAXLISTCHARS)
		{
			do
			{
				StrTmp2=StrTmp.Mid(MAXLISTCHARS);
				m_chatbox.AddString(StrTmp.Mid(0,MAXLISTCHARS));
				StrTmp=StrTmp2;
			}while(StrTmp.GetLength()>MAXLISTCHARS);
			m_chatbox.AddString(StrTmp);
		} 
		else 		
			m_chatbox.AddString(StrTmp.Mid(0,MAXLISTCHARS-1));


	}

	m_chatbox.SetCurSel(m_chatbox.GetCount()-1);

}

void CChatView::OnButtonSend(bool m_bUserTyped) 
{
/*

	CString Tmp;
	// TODO: Add your control notification handler code here   (LPCTSTR)
	UpdateData();


	CString temp=m_StrSend;
	CString TmpStr,TmpStr2;
	if(!temp.Find("/"))
	{
		int size=temp.GetLength();
		int i;
		CString ListString;
		CString slashless=temp.Right(size-1);
		char* NewString=slashless.GetBuffer(size-1);
		CString commando=strtok(NewString," ");
		CString firstpar=strtok(NULL," ");
		pDoc->msMsg=strtok(NULL,"\n");
		slashless.ReleaseBuffer();
		
		if(commando=="ban" || commando=="b")
		{
			i=pDoc->BanUser(firstpar,1);
			if(i==1)
			{
				ListString="Banned "+ firstpar;
				ListString+=".Use /unban [user] or /ub [user] to remove from banlist.";
			}
			else
			{
				ListString=firstpar + " allready banned";
				ListString+=".Use /unban [user] or /ub [user] to remove from banlist.";
			}
//			pDoc->AddToCont(pDoc->Cont,ADMINCHAT,ListString);
			pDoc->AddToBarrel(ADMINCHAT,ListString);
		}
		if(commando=="unban" || commando=="ub")
		{
			i=pDoc->BanUser(firstpar,0);
			if(i==1)
				ListString="Removed "+firstpar +" from banned list";
			else
				ListString=firstpar + " was not banned anyway";
//			pDoc->AddToCont(pDoc->Cont,ADMINCHAT,ListString);
			pDoc->AddToBarrel(ADMINCHAT,ListString);

		}
		if(commando=="kick" || commando=="k")
		{
			i=pDoc->KickUser(pDoc->FindUser(firstpar),KICK);
			if(i>=0)
			{
				ListString="Kicked ";
				ListString+=firstpar;
			}
			else
			{
				ListString="User ";
				ListString+=firstpar;
				ListString+=" isn't connected.";
			}
//			pDoc->AddToCont(pDoc->Cont,ADMINCHAT,ListString);
			pDoc->AddToBarrel(ADMINCHAT,ListString);

		}

		if(commando=="list" || commando=="ls")
		{
			CStringArray List;
			if(firstpar=="ban")
			{
				pDoc->ListBan(List);
				pDoc->AddToBarrel(ADMINCHAT,"Banned players are:");
				for(int j=0;j<List.GetSize();j++)
					pDoc->AddToBarrel(ADMINCHAT,List[j]);
			}
			else if(firstpar=="users")
			{
				pDoc->ListUsers(List);
				pDoc->AddToBarrel(ADMINCHAT,"Online players are:");
				for(int j=0;j<List.GetSize();j++)
					pDoc->AddToBarrel(ADMINCHAT,List[j]);
			}

		}

		if(commando=="clear" || commando=="cl")
		{
			CString TableName;
			if(firstpar=="ban")
			{
				TableName="Ban_List";
				pDoc->ClearTable(TableName);
				pDoc->AddToBarrel(ADMINCHAT,"The ban list has been cleared!");
			}

		}

		if(commando=="remove" || commando=="rm")
		{
			i=pDoc->RemoveUser(firstpar);
			if(i>=0)
			{
				ListString="Removed ";
				ListString+=firstpar;
			}
			else
			{
				ListString="User ";
				ListString+=firstpar;
				ListString+=" doesn't exist.";
			}
			pDoc->AddToBarrel(ADMINCHAT,ListString);
		}

		if(commando=="info")
		{
			if(pDoc->ExistTable(firstpar)) // info over player
				if(pDoc->msMsg=="char")
				{
					CStringArray List;
					pDoc->FindChar(firstpar,List);
					for(int j=0;j<List.GetSize();j++)
						pDoc->AddToBarrel(ADMINCHAT,List[j]);
				}

		}
		if(commando=="whisper"||commando=="w")
		{
			i=pDoc->FindUser(firstpar);
			if(i>=0)
			{
				ListString="Whispered to ";
				ListString+=firstpar;
				ListString+=": ";
				ListString+=pDoc->msMsg;
				pDoc->SendToUser(CHAT,firstpar);
//				pDoc->AddToCont(pDoc->Cont,PRIVATECHAT,ListString);
				pDoc->AddToBarrel(PRIVATECHAT,ListString);
			}
			else
			{
				ListString="User ";
				ListString+=firstpar;
				ListString+=" isn't online.";
				//oc->AddToCont(pDoc->Cont,PRIVATECHAT,ListString);
				pDoc->AddToBarrel(PRIVATECHAT,ListString);

			}
			
		}

	}
	
	else if(pDoc->m_nNumClients>0)
	{
		pDoc->msMsg=m_StrSend;
		pDoc->SendToAll(CHAT);
		
		pDoc->AddToBarrel(CHAT,pDoc->msMsg);


	}
	else
		if(pDoc->m_nNumClients==0)
	{
		pDoc->AddToBarrel(CHAT, "No clients connected");
	}

	CStatic* pStaticOutput=(CStatic*)GetDlgItem(IDC_SENDCHAT);
	pStaticOutput->SetWindowText("");
*/	
	
}

void CChatView::OnCloseupCommandbox() 
{
	// TODO: Add your control notification handler code here
//	CDnDDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
/*	CString TmpStr, ListString;
	CString NameStr;
	UpdateData(TRUE);
	if(m_userbox.GetSelCount ()>0)
	{
		for(int i=0;i<m_userbox.GetCount();i++)
		{
			
			if(m_userbox.GetSel(i) )
			{	
				if(m_commando=="whisper")
				{
					m_userbox.GetText(i,NameStr);
					pDoc->msMsg=m_StrSend;
					ListString="Whispered to ";
					ListString+=NameStr;
					ListString+=": ";
					ListString+=pDoc->msMsg;
					pDoc->SendToUser(CHAT,NameStr);
//					pDoc->AddToCont(pDoc->Cont,PRIVATECHAT,ListString);
					pDoc->AddToBarrel(PRIVATECHAT,ListString);

					pDoc->Send(CHAT,pDoc->mClient[i]);
					CStatic* pStaticOutput=(CStatic*)GetDlgItem(IDC_SENDCHAT);
					pStaticOutput->SetWindowText("");
				}
				else
				{
					if(AfxMessageBox("You sure you want to do this?",MB_YESNO)==IDYES)
					{
						m_userbox.GetText(i,NameStr);
						TmpStr="/"+m_commando+" "+NameStr;
						m_StrSend=TmpStr;
						OnButtonSend(FALSE);
					}
				}
			}
			
		}	
		m_userbox.SetSel(-1,FALSE);

		
	}*/
}

void CChatView::LoadImages()
{
	CString filepath;
	
	for(int k=0;k<pDoc->MaxHeadBitmaps;k++)
	{
		filepath.Format(pDoc->PortraitsPath+"\\head%i.bmp",k);
		headbmp[k]=(HBITMAP)LoadImage(NULL,filepath,IMAGE_BITMAP,0,0,
								LR_DEFAULTSIZE|LR_LOADFROMFILE);
			if(!headbmp[k])
			{
			headbmp[k]=(HBITMAP)LoadImage(NULL,pDoc->PortraitsPath+"\\default.bmp",IMAGE_BITMAP,0,0,
								LR_DEFAULTSIZE|LR_LOADFROMFILE);
			
			}
	}



}

void CChatView::OnHead1() 
{
	// TODO: Add your control notification handler code here
	ClickedHead(0);
}

void CChatView::OnHead2() 
{
	// TODO: Add your control notification handler code here
	ClickedHead(1);
}

void CChatView::OnHead3() 
{
	// TODO: Add your control notification handler code here
	ClickedHead(2);
}

void CChatView::OnHead4() 
{
	// TODO: Add your control notification handler code here
	ClickedHead(3);
}

void CChatView::OnHead5() 
{
	// TODO: Add your control notification handler code here
	ClickedHead(4);
}

void CChatView::OnHead6() 
{
	// TODO: Add your control notification handler code here
	ClickedHead(5);
}

void CChatView::OnHead7() 
{
	// TODO: Add your control notification handler code here
	ClickedHead(6);
}

void CChatView::OnHead8() 
{
	// TODO: Add your control notification handler code here
	ClickedHead(7);
}

void CChatView::ClickedHead(int k)
{
//	CDnDDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
	//CString tmp;
	//tmp.Format("Clicked head %i, kicked user %i",k,k);
	//pDoc->KickUser(k,KICK);
	//AfxMessageBox(tmp);
	CPoint pt;
	::GetCursorPos(&pt);

	CStatsDialog dlg(pt);
	dlg.SetAniStyles(AS_REFER, AS_REFER); //AS_CENTER

	CString ListString,charname=pDoc->mClient[k]->CharName,tempName=pDoc->mUsername.GetAt(k);
	CStringArray List;
	pDoc->GetStats(charname,List);
	dlg.m_Username=pDoc->mUsername.GetAt(k);
	dlg.m_Charname=charname;
	dlg.m_Armor=List[0];
	dlg.m_Items=List[1];
	dlg.m_Strength=List[2];
	dlg.m_Dexterity=List[3];
	dlg.m_Constitution=List[4];
	dlg.m_Intelligence=List[5];
	dlg.m_Wisdom=List[6];
	dlg.m_Charisma=List[7];

	dlg.DoModal();

	if(dlg.b_kick)
	{
		pDoc->KickUser(k,KICK);
		ListString="Kicked ";
		ListString+=tempName;
		pDoc->AddToBarrel(ADMINCHAT,ListString);
	}
	if(dlg.b_ban)
	{
		pDoc->BanUser(tempName,1);
		ListString="Banned "+ tempName;
		ListString+=".Use /unban [user] or /ub [user] to remove from banlist.";
		pDoc->AddToBarrel(ADMINCHAT,ListString);
	}
	if(dlg.b_update)
	{
		CStringArray Statnames,Statvalues;
		for(int k=0;k<dlg.Statnames.GetSize();k++)
		{
			Statnames.Add(dlg.Statnames[k]);
			Statvalues.Add(dlg.Statvalues[k]);
		}
		pDoc->SetStats(dlg.m_Charname,Statnames,Statvalues);
	}
}

void CChatView::OnContextMenu(CWnd*, CPoint point)
{

	// CG: This block was added by the Pop-up Menu component
	{
		if (point.x == -1 && point.y == -1){
			//keystroke invocation
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu;
	
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_CHAT_VIEW));
		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);

		CWnd* pWndPopupOwner = this;
		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();
		
		
		
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
		
	}
}

void CChatView::OnPopupWhisper() 
{
	// TODO: Add your command handler code here
	
	AfxMessageBox("Test");

}

void CChatView::OnPopupPlayerstats() 
{
	// TODO: Add your command handler code here
	CString deb;
	deb.Format("Head %i",IsHead(LastPopup));
	AfxMessageBox(deb);

}


int CChatView::IsHead(CPoint point)
{

	int ret=-1;
//	CDnDDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);


	
		WINDOWPLACEMENT whead1;
	m_head1.GetWindowPlacement(&whead1);
		WINDOWPLACEMENT whead2;
	m_head2.GetWindowPlacement(&whead2);
		WINDOWPLACEMENT whead3;
	m_head3.GetWindowPlacement(&whead3);
		WINDOWPLACEMENT whead4;
	m_head4.GetWindowPlacement(&whead4);
		WINDOWPLACEMENT whead5;
	m_head5.GetWindowPlacement(&whead5);
		WINDOWPLACEMENT whead6;
	m_head6.GetWindowPlacement(&whead6);
		WINDOWPLACEMENT whead7;
	m_head7.GetWindowPlacement(&whead7);
		WINDOWPLACEMENT whead8;
	m_head8.GetWindowPlacement(&whead8);

	


	
	
	if(point.x>=whead1.rcNormalPosition.left && point.x<=whead1.rcNormalPosition.right)
	{
		if(point.y>=whead1.rcNormalPosition.top && point.y<=whead1.rcNormalPosition.bottom)
			ret=0;
	}

	
	else if(point.x>=whead2.rcNormalPosition.left && point.x<=whead2.rcNormalPosition.right)
	{
		if(point.y>=whead2.rcNormalPosition.top && point.y<=whead2.rcNormalPosition.bottom)
		ret=1;
	}
	
	else if(point.x>=whead3.rcNormalPosition.left && point.x<=whead3.rcNormalPosition.right)
	{
		if(point.y>=whead3.rcNormalPosition.top && point.y<=whead3.rcNormalPosition.bottom)
		ret=2;
	}

	
	else if(point.x>=whead4.rcNormalPosition.left && point.x<=whead4.rcNormalPosition.right)
	{
		if(point.y>=whead4.rcNormalPosition.top && point.y<=whead4.rcNormalPosition.bottom)
		ret=3;
	}


	
	else if(point.x>=whead5.rcNormalPosition.left && point.x<=whead5.rcNormalPosition.right)
	{
		if(point.y>=whead5.rcNormalPosition.top && point.y<=whead5.rcNormalPosition.bottom)
		ret=4;
	}


	
	else if(point.x>=whead6.rcNormalPosition.left && point.x<=whead6.rcNormalPosition.right)
	{
		if(point.y>=whead6.rcNormalPosition.top && point.y<=whead6.rcNormalPosition.bottom)
		ret=5;
	}


	
	else if(point.x>=whead7.rcNormalPosition.left && point.x<=whead7.rcNormalPosition.right)
	{
		if(point.y>=whead7.rcNormalPosition.top && point.y<=whead7.rcNormalPosition.bottom)
		ret=6;
	}

	
	else if(point.x>=whead8.rcNormalPosition.left && point.x<=whead8.rcNormalPosition.right)
	{
		if(point.y>=whead8.rcNormalPosition.top && point.y<=whead8.rcNormalPosition.bottom)
		ret=7;
	}
	
//	if(pDoc->m_nNumClients<=ret+1)
//		ret=-1;

	return ret;
}

void CChatView::OnUpdatePopupPlayerstats(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	int k=IsHead(LastPopup);
	if(k>=0)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CChatView::OnUpdatePopupBan(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	int k=IsHead(LastPopup);
	if(k>=0)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);	
}

void CChatView::OnPopupBan() 
{
	// TODO: Add your command handler code here
	
}

void CChatView::OnPopupKick() 
{
	// TODO: Add your command handler code here
//	CDnDDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
	CString tmp;
	
	int k=IsHead(LastPopup);
	tmp.Format("Kick this user? [usernumber:%i]",k);	
	if(IDYES==AfxMessageBox(tmp,MB_ICONQUESTION|MB_YESNO,0))
		pDoc->KickUser(k,KICK);
	
	
}

void CChatView::OnUpdatePopupKick(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	int k=IsHead(LastPopup);
	if(k>=0)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);	
}

void CChatView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	LastPopup=point;
	CFormView::OnRButtonDown(nFlags, point);
}

void CChatView::SetStats(CString m_Charname,CStringArray& Statnames,CStringArray& Statvalues)
{
//	CDnDDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);

	pDoc->SetStats(m_Charname,Statnames,Statvalues);
}

void CChatView::OnPaint() 
{


	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
     if(!firstpaint)
	 {
       for(int k=0;k<pDoc->MaxNumClients;k++)
		{
			pHead[k]= (CStatic*)GetDlgItem(IDC_HEAD1+k);
		}

		for(int j=0;j<pDoc->m_nNumClients;j++)
		{
			if(pDoc->mClient[j]->m_nHeadFigure < pDoc->MaxHeadBitmaps)
				pHead[j]->SetBitmap(headbmp[pDoc->mClient[j]->m_nHeadFigure]);
			else
				pHead[j]->SetBitmap(headbmp[0]);
			pHead[j]->ShowWindow(SW_SHOW);
		}            
		firstpaint=1;
     }
            

	// Do not call CFormView::OnPaint() for painting messages
}

void CChatView::OnBtnsend() 
{
	// TODO: Add your control notification handler code here
	

	CString Tmp;
	// TODO: Add your control notification handler code here   (LPCTSTR)
	UpdateData();

	CString temp=m_sendstringchat;
	CString TmpStr,TmpStr2;
	if(!temp.Find("/"))
	{
		int size=temp.GetLength();
		int i;
		CString ListString;
		CString slashless=temp.Right(size-1);
		char* NewString=slashless.GetBuffer(size-1);
		CString commando=strtok(NewString," ");
		CString firstpar=strtok(NULL," ");
		pDoc->msMsg=strtok(NULL,"\n");
		slashless.ReleaseBuffer();
		
		if(commando=="ban" || commando=="b")
		{
			i=pDoc->BanUser(firstpar,1);
			if(i==1)
			{
				ListString="Banned "+ firstpar;
				ListString+=".Use /unban [user] or /ub [user] to remove from banlist.";
			}
			else
			{
				ListString=firstpar + " allready banned";
				ListString+=".Use /unban [user] or /ub [user] to remove from banlist.";
			}
//			pDoc->AddToCont(pDoc->Cont,ADMINCHAT,ListString);
			pDoc->AddToBarrel(ADMINCHAT,ListString);
		}
		if(commando=="unban" || commando=="ub")
		{
			i=pDoc->BanUser(firstpar,0);
			if(i==1)
				ListString="Removed "+firstpar +" from banned list";
			else
				ListString=firstpar + " was not banned anyway";
//			pDoc->AddToCont(pDoc->Cont,ADMINCHAT,ListString);
			pDoc->AddToBarrel(ADMINCHAT,ListString);

		}
		if(commando=="kick" || commando=="k")
		{
			i=pDoc->KickUser(pDoc->FindUser(firstpar),KICK);
			if(i>=0)
			{
				ListString="Kicked ";
				ListString+=firstpar;
			}
			else
			{
				ListString="User ";
				ListString+=firstpar;
				ListString+=" isn't connected.";
			}
//			pDoc->AddToCont(pDoc->Cont,ADMINCHAT,ListString);
			pDoc->AddToBarrel(ADMINCHAT,ListString);

		}

		if(commando=="list" || commando=="ls")
		{
			CStringArray List;
			if(firstpar=="ban")
			{
				pDoc->ListBan(List);
				pDoc->AddToBarrel(ADMINCHAT,"Banned players are:");
				for(int j=0;j<List.GetSize();j++)
					pDoc->AddToBarrel(ADMINCHAT,List[j]);
			}
			else if(firstpar=="users")
			{
				pDoc->ListUsers(List);
				pDoc->AddToBarrel(ADMINCHAT,"Online players are:");
				for(int j=0;j<List.GetSize();j++)
					pDoc->AddToBarrel(ADMINCHAT,List[j]);
			}

		}

		if(commando=="clear" || commando=="cl")
		{
			CString TableName;
			if(firstpar=="ban")
			{
				TableName="Ban_List";
				pDoc->ClearTable(TableName);
				pDoc->AddToBarrel(ADMINCHAT,"The ban list has been cleared!");
			}

		}

		if(commando=="remove" || commando=="rm")
		{
			i=pDoc->RemoveUser(firstpar);
			if(i>=0)
			{
				ListString="Removed ";
				ListString+=firstpar;
			}
			else
			{
				ListString="User ";
				ListString+=firstpar;
				ListString+=" doesn't exist.";
			}
			pDoc->AddToBarrel(ADMINCHAT,ListString);
		}

		if(commando=="info")
		{
			if(pDoc->ExistTable(firstpar)) // info over player
				if(pDoc->msMsg=="char")
				{
					CStringArray List;
					pDoc->FindChar(firstpar,List);
					for(int j=0;j<List.GetSize();j++)
						pDoc->AddToBarrel(ADMINCHAT,List[j]);
				}

		}
		if(commando=="whisper"||commando=="w")
		{
			i=pDoc->FindUser(firstpar);
			if(i>=0)
			{
				ListString="Whispered to ";
				ListString+=firstpar;
				ListString+=": ";
				ListString+=pDoc->msMsg;
				pDoc->SendToUser(CHAT,firstpar);
//				pDoc->AddToCont(pDoc->Cont,PRIVATECHAT,ListString);				pDoc->AddToBarrel(PRIVATECHAT,ListString);
			}
			else
			{
				ListString="User ";
				ListString+=firstpar;
				ListString+=" isn't online.";
				//oc->AddToCont(pDoc->Cont,PRIVATECHAT,ListString);
				pDoc->AddToBarrel(PRIVATECHAT,ListString);

			}
			
		}

	}
	
	else if(pDoc->m_nNumClients>0)
	{
		pDoc->msMsg=m_sendstringchat;
		pDoc->SendToAll(CHAT);
		
		pDoc->AddToBarrel(CHAT,pDoc->msMsg);


	}
	else
		if(pDoc->m_nNumClients==0)
	{
		pDoc->AddToBarrel(CHAT, "No clients connected");
	}

	CStatic* pStaticOutput=(CStatic*)GetDlgItem(IDC_EDITTOSENDCHAT);
	pStaticOutput->SetWindowText("");

}
