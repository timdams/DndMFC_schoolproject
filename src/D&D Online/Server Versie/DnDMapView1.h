#if !defined(AFX_DNDMAPVIEW1_H__CF41F119_5220_4F13_9E49_730E025F24AD__INCLUDED_)
#define AFX_DNDMAPVIEW1_H__CF41F119_5220_4F13_9E49_730E025F24AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DnDMapView1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DnDMapView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#include <afxtempl.h>

#endif
#include "DnDDoc.h"
#include "Mapsettings.h"
#include "PTGameObject.h"	// Added by ClassView
class DnDMapView : public CFormView
{
protected:
	DnDMapView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(DnDMapView)

// Form Data
public:
	//{{AFX_DATA(DnDMapView)
	enum { IDD = IDD_MAPVIEW };
	CComboBox	m_layerctl;
	CButton	m_deletesm;
	CComboBox	m_monsterctl;
	CComboBox	m_playerctl;
	CComboBox	m_itemsctl;
	CComboBox	m_doorctl;
	CComboBox	m_roomctl;
	CStatic	m_maparea;
	CString	m_tool;
	CString	m_mapname;
	CString	m_blockinfo;
	CString	m_blockinfo2;
	CString	m_blockinfo3;
	CString	m_stadeb;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	bool debugenabled;
	int layer;
	CString DefinesConvert(int def1);
	bool HiRes;
	CBitmap bmp_corridortile;
	CBitmap bmp_roomtile;
	CBitmap bmp_herotile;
	CBitmap bmp_partytile;
	CBitmap bmp_treasuretile;
	CBitmap bmp_pittile;
	CBitmap bmp_furnituretile;
	UINT CheckBlock(CPoint pos);
	void DrawTransparentBitmap(CDC* pDC, CBitmap* pBitmap, short xStart,short yStart, COLORREF cTransparentColor,short xEnd,short yEnd);
	void DrawTransparentResizedBitmap(CDC* pDC, CBitmap* pBitmap, short xStart,short yStart, COLORREF cTransparentColor,short xEnd,short yEnd);

	void ShowBlockInfo();
	CPoint selectedblock;
	int mode;
	CString mappath;
	int showgrid;
	int CheckCounter;
	void CheckMap();
	int m_blocksize;
	bool DrawingCorridor;
	bool DrawingRoom;
	CPoint CorridorStart;
	int tool;
	WINDOWPLACEMENT wmap;
	CPTGameObject LastPlacedObj;
	CArray<CPTGameObject, CPTGameObject&> MapItems;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DnDMapView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~DnDMapView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(DnDMapView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRoomtool();
	afx_msg void OnToolcorridor();
	afx_msg void OnSettings();
	afx_msg void OnTooldoor();
	afx_msg void OnUndo();
	afx_msg void OnEraser();
	afx_msg void OnSelchangeRoomcombo();
	afx_msg void OnSelchangeDoorcombo();
	afx_msg void OnItems();
	afx_msg void OnSelchangeItemscombo();
	afx_msg void OnClearmap();
	afx_msg void OnSavemap();
	afx_msg void OnLoadmap();
	afx_msg void OnPlayers();
	afx_msg void OnSelchangeComboplayers();
	afx_msg void OnSelchangeCombomonster();
	afx_msg void OnMonster();
	afx_msg void OnToolselect();
	afx_msg void OnDeletesm();
	afx_msg void OnSelchangeLayercombo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DNDMAPVIEW1_H__CF41F119_5220_4F13_9E49_730E025F24AD__INCLUDED_)
