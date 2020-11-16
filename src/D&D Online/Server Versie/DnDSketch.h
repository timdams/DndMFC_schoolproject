#if !defined(AFX_DNDSKETCH_H__A47CFCB6_0C8E_4B40_9C8F_754F229192A6__INCLUDED_)
#define AFX_DNDSKETCH_H__A47CFCB6_0C8E_4B40_9C8F_754F229192A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DnDSketch.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDnDSketch form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CDnDSketch : public CFormView
{
protected:
	CDnDSketch();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDnDSketch)

// Form Data
public:
	//{{AFX_DATA(CDnDSketch)
	enum { IDD = IDD_SKETCHVIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDnDSketch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDnDSketch();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDnDSketch)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DNDSKETCH_H__A47CFCB6_0C8E_4B40_9C8F_754F229192A6__INCLUDED_)
