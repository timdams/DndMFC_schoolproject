#if !defined(AFX_CHATVIEW_H__5583A977_020E_11D7_832F_0050BA26DFA6__INCLUDED_)
#define AFX_CHATVIEW_H__5583A977_020E_11D7_832F_0050BA26DFA6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChatView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChatView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include "AfxTempl.h"
#include "ColorListBox.h"
#include "DnDDoc.h"
#include "ChatOptions.h"
#include "Picture.h"	// Added by ClassView

class CChatView : public CFormView
{
protected:
	CChatView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CChatView)

// Form Data
public:
	//{{AFX_DATA(CChatView)
	enum { IDD = IDD_CHATVIEW };
	CStatic	m_miniature;
	CString	m_sEditChat;
	CColorListBox	m_ConnList;
	//}}AFX_DATA

// Attributes
public:

// Operations
	CArray<CPTGameObject, CPTGameObject&> LocalSketch; 
	CDnDDoc* GetDocument();
	void AddToListbox(CString str,int type);
	void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
public:
	bool GotLoadedImage;
	CString ImagePath;
	CPicture APicture;
	int sketchmode;
	int hidden;
	int InitUpdate;
	void LoadImages();
	CStatic* pHead[MAXNUMCLIENTS];
	CStatic* pNames[MAXNUMCLIENTS];

	CStatic* pHeadMe;
	HBITMAP headbmp[160];
	void DrawTransparentResizedBitmap(CDC* pDC, CBitmap* pBitmap,short xStart,short yStart, COLORREF cTransparentColor,short xEnd,short yEnd,int mode);
	CBitmap sketch;
	int firstpaint;
	int lines;
	bool SketchAvailable;
	CDnDDoc* pDoc;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CChatView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CChatView)
	afx_msg void OnButtonSend();
	afx_msg void OnHeadme();
	afx_msg void OnChatoptions();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATVIEW_H__5583A977_020E_11D7_832F_0050BA26DFA6__INCLUDED_)
