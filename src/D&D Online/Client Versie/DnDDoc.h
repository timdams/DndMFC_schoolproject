// DnDDoc.h : interface of the CDnDDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DNDDOC_H__5583A96A_020E_11D7_832F_0050BA26DFA6__INCLUDED_)
#define AFX_DNDDOC_H__5583A96A_020E_11D7_832F_0050BA26DFA6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "AfxTempl.h"
#include "Barrel.h"
#include "MySocket.h"
#include "PTGameObject.h"
#include "defines.h"
#include "DndPlayer.h"
#include "PlayerInfo.h"
#include "CreatePlayer.h"

class CDnDDoc : public CDocument
{
protected: // create from serialization only
	CDnDDoc();
	DECLARE_DYNCREATE(CDnDDoc)

// Attributes
public:
	bool m_bConnected;
	bool m_bCreateTemp;
	bool m_bConnChange;
	bool m_bChatChange;
	CMySocket mClient;
	CString sIPServer;
	CString m_sUsername;
	CString m_sPass;
	CString m_sSend;
	CArray<CBarrel,CBarrel&> ChatBarrel;
	CArray<CBarrel,CBarrel&> ConnBarrel;
	CArray<CBarrel,CBarrel&> MapBarrel;

	CArray<CPTGameObject, CPTGameObject&> Sketch;
	CArray<CPTGameObject, CPTGameObject&> Map;

	CArray<CPlayerInfo, CPlayerInfo&> TempChars;
	CStringArray PlayerNames;
	int PlayerHeads[MAXNUMCLIENTS];
	CPlayerInfo OnePlayer;
	CPoint sketchEndPoint;
// Operations
public:
	int AddToBarrel(int Type, CString str);

	CString IPtoCString(CIPAddressCtrl &IP);
	void OnReceive();
	void Send(int nParameter);
	DWORD GetDWORDIPAddress(CString strIPAddress);

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
	BOOL FileExists(LPCTSTR lpFileName);
	CString SketchImagePath;
	CString Path;
	CString ImagePath;
	CString MyName;
	int MyHead;
	int PlayerVisible[160][160];
	CPoint MapBlocks;
	CString m_mapname;
	int mapsize;
	int userchars;
	CString userchar;
	int kop;
	int receivedpackages;
	virtual ~CDnDDoc();
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
