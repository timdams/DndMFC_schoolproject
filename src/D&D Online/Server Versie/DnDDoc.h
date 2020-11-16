// DnDDoc.h : interface of the CDnDDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DNDDOC_H__5583A96A_020E_11D7_832F_0050BA26DFA6__INCLUDED_)
#define AFX_DNDDOC_H__5583A96A_020E_11D7_832F_0050BA26DFA6__INCLUDED_
#include "PlayerInfo.h"
#include "AfxTempl.h"
#include "MySocket.h"	// Added by ClassView
#include "MainFrm.h"
#include "PTGameObject.h"
#include "Barrel.h"
#include "defines.h"

//#include "ACCESS.H"
#if _MSC_VER > 1000



#pragma once
#endif // _MSC_VER > 1000

#define CRTDBG_MAP_ALLOC
//to detect memory leaks

class CDnDDoc : public CDocument
{
protected: // create from serialization only
	
	DECLARE_DYNCREATE(CDnDDoc)

// Attributes
public:

// Operations
public:
	CDnDDoc(); //Stond vroeger protected,aangepast (KW) om StatsDialog Update io te krijgen

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDnDDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	CString PortraitsPath;
	int MaxHeadBitmaps;
	CString SketchPicturePath;
	bool bPlaying;
	CPTGameObject MapObj;
	CPoint VisSend;
	void SetStats(CString charname, CStringArray &Statnames,CStringArray &Statvalues);
	void GetStats(CString Charname,CStringArray& List);
	CPoint MapBlocks;
	CString m_mapname;
	void FillCharArray(CString User);
	CStringArray charlist;
	bool ExistTable(CString TableName);
	void FindChar(CString UserName,CStringArray &List);
	int AddToBarrel(int Type, CString str);
	DWORD appTime;
	int BanUser(CString UserName,int type);
	int KickUser(int k,int type);
	int RemoveUser(CString UserName);
	void ListBan(CStringArray &List);
	void ListUsers(CStringArray &List);
	void ClearTable(CString TableName);
	CPlayerInfo OnePlayer;
	CArray<CBarrel, CBarrel&> MapPlayBarrel;

	CArray<CBarrel, CBarrel&> ChatBarrel;
	CArray<CBarrel, CBarrel&> ConnBarrel;
	CArray<CPlayerInfo, CPlayerInfo&> TempChars;
	CArray<CPTGameObject, CPTGameObject&> Sketch;
	CArray<CPTGameObject, CPTGameObject&> Map;
	int PlayerVisible[160][160]; //groter dan 150*150 kan een map normaal niet zijn

	CPoint sketchEndPoint;
	bool m_bCreateTemp;
	bool m_bPlayerChange;
	bool m_bConnChange;
	bool m_bChatChange;
	enum { MaxNumClients = MAXNUMCLIENTS };
	bool m_bSocketListening;
	CString msMsg;
	void OnReceive(CMySocket *pSocket);
	int FindUser(CString Username);
	void SendToAll(int nParameter);
	void SendToUser(int nParameter,CString Username);
	void Send(int nParameter,CMySocket *pSocket);
	void OnAccept();
	CMySocket svrSocket;
	CMySocket* mClient[MaxNumClients];
	CStringArray mUsername;
	DWORD timeoutTimer[MaxNumClients];
	
	int m_nNumClients;
	int charsize;
	bool m_bSocketCreated;
	bool DbExists;
	virtual ~CDnDDoc();
	CString Path;
	CString DBPath;
//	ACCESS DnDDB;

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDnDDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DNDDOC_H__5583A96A_020E_11D7_832F_0050BA26DFA6__INCLUDED_)
