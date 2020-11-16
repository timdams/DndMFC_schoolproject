#if !defined(AFX_DNDSKETCHVIEW_H__6E1272BC_1151_49E1_8719_ED5306314FCC__INCLUDED_)
#define AFX_DNDSKETCHVIEW_H__6E1272BC_1151_49E1_8719_ED5306314FCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DndSketchView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DndSketchView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#include <afxtempl.h>

#endif


#include "DnDDoc.h"
#include "Picture.h"	// Added by ClassView


class DndSketchView : public CFormView
{
protected:
	DndSketchView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(DndSketchView)

// Form Data
public:
	//{{AFX_DATA(DndSketchView)
	enum { IDD = IDD_SKETCHVIEW };
	CStatic	m_coloutsideshow;
	CStatic	m_colinsideshow;
	CButton	m_toolbackground;
	CButton	m_toolSelect;
	CStatic	m_miniature;
	CButton	m_colpickin;
	CButton	m_toolCircle;
	CButton	m_toolLine;
	CStatic	m_sketcharea;
	BOOL	m_transparent;
	BOOL	m_liveupdate;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	int warning;
	CString ImagePath;
	bool GotLoadedImage;
	CPicture APicture;
	UINT tool;
	CBitmap m_toolBitmaps[4];
	UINT drawingline;
	UINT drawingcircle;
	bool m_bNoneSelected;
	COLORREF in;
	COLORREF out;
	CDnDDoc* GetDocument();
	CArray<CPTGameObject, CPTGameObject&> LocalSketch; 
	WINDOWPLACEMENT wplacecolin;
	WINDOWPLACEMENT wplacecolout;

	WINDOWPLACEMENT wsketch;
	WINDOWPLACEMENT wsketch2;
	float yscale;
	float xscale;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DndSketchView)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~DndSketchView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(DndSketchView)
	afx_msg void OnSketchblock();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLinetool();
	afx_msg void OnCircletool();
	afx_msg void OnColpickout();
	afx_msg void OnColpickin();
	afx_msg void OnClear();
	afx_msg void OnSendimage();
	afx_msg void OnSelecttool();
	afx_msg void OnLiveupdate();
	afx_msg void OnLoadimagebtn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DNDSKETCHVIEW_H__6E1272BC_1151_49E1_8719_ED5306314FCC__INCLUDED_)
