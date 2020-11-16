#if !defined(AFX_DNDMAPPLAY_H__C2585496_676A_4AD9_A329_1FD27372DAC4__INCLUDED_)
#define AFX_DNDMAPPLAY_H__C2585496_676A_4AD9_A329_1FD27372DAC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DnDMapPlay.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDnDMapPlay form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#include <afxtempl.h>
#endif
#include "DnDDoc.h"

class CDnDMapPlay : public CFormView
{
protected:
	CDnDMapPlay();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDnDMapPlay)

// Form Data
public:
	//{{AFX_DATA(CDnDMapPlay)
	enum { IDD = IDD_MAPPLAYVIEW };
	CListBox	m_chatmapbox;
	CStatic	m_maparea;
	CString	m_StrSend;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	int layer;
	WINDOWPLACEMENT wmap;
	bool HiRes;
	int PlayerVisible[160][160]; //groter dan 150*150 kan een map normaal niet zijn

	int showgrid;
	int m_blocksize;
	bool MapLoaded;
	int lines;
	CDnDDoc* GetDocument();
	CDnDDoc* pDoc;
	CArray<CPTGameObject, CPTGameObject&> LocalMap; 

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDnDMapPlay)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDnDMapPlay();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDnDMapPlay)
	afx_msg void OnBtnchat();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DNDMAPPLAY_H__C2585496_676A_4AD9_A329_1FD27372DAC4__INCLUDED_)
