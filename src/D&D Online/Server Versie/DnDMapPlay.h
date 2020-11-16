#if !defined(AFX_DNDMAPPLAY_H__D44930FB_A72F_425F_BA86_02766947AA3A__INCLUDED_)
#define AFX_DNDMAPPLAY_H__D44930FB_A72F_425F_BA86_02766947AA3A__INCLUDED_

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

#include "PTGameObject.h"
class CDnDMapPlay : public CFormView
{
protected:
	CDnDMapPlay();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDnDMapPlay)

// Form Data
public:
	//{{AFX_DATA(CDnDMapPlay)
	enum { IDD = IDD_MAPPLAY };
	CListBox	m_chatmap;
	CButton	m_playbutton;
	CButton	m_hidebutton;
	CComboBox	m_hidearea;
	CButton	m_down;
	CButton	m_left;
	CButton	m_right;
	CButton	m_up;
	CButton	m_checkname2;
	CButton	m_checkname1;
	CComboBox	m_visctl;
	CStatic	m_maparea;
	CString	m_maptitle;
	CString	m_strSend;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	void SentItemUpdate(int number, CPTGameObject ob);
	void SendVisibilityUpdate(int x,int y, bool IsShown);
	bool bPlaying;
	CPoint MapBlocks;
	int MakeVisibilityLayer(int type);
	int selitem2;
	int selitem1;
	void MoveItem(int direction);
	CString DefinesConvert(int def1);
	void EnableBlock();
	CPoint selectedblock;
	int tool;
	int PlayerVisible[160][160]; //groter dan 150*150 kan een map normaal niet zijn
	int layer;
	bool MapLoaded;
	bool showgrid;
	int m_blocksize;
	bool HiRes;
	int ylengte; //lengte van tekenveld
	int xbreedte;//breedte van tekenveld
	WINDOWPLACEMENT wmap;
	CArray<CPTGameObject, CPTGameObject&> MapItems;
	CBitmap bmp_corridortile;
	CBitmap bmp_roomtile;
	CBitmap bmp_herotile;
	CBitmap bmp_partytile;
	CBitmap bmp_treasuretile;
	CBitmap bmp_pittile;
	CBitmap bmp_furnituretile;
	void DrawTransparentBitmap(CDC* pDC, CBitmap* pBitmap, short xStart,short yStart, COLORREF cTransparentColor,short xEnd,short yEnd);
	void DrawTransparentResizedBitmap(CDC* pDC, CBitmap* pBitmap, short xStart,short yStart, COLORREF cTransparentColor,short xEnd,short yEnd);
	CDnDDoc* GetDocument();

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
	afx_msg void OnLoadmap();
	afx_msg void OnSelchangeViscombo();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnUp();
	afx_msg void OnDown();
	afx_msg void OnLeft();
	afx_msg void OnRight();
	afx_msg void OnCheckname();
	afx_msg void OnCheckname2();
	afx_msg void OnUnhide();
	afx_msg void OnStart();
	afx_msg void OnChatsend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DNDMAPPLAY_H__D44930FB_A72F_425F_BA86_02766947AA3A__INCLUDED_)
