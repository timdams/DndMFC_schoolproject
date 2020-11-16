#if !defined(AFX_MYSOCKET_H__342C6DDB_3E31_48FF_99F2_9C65146716E4__INCLUDED_)
#define AFX_MYSOCKET_H__342C6DDB_3E31_48FF_99F2_9C65146716E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MySocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CMySocket command target

class CMySocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CMySocket();
	virtual ~CMySocket();

// Overrides
public:
	int m_nHeadFigure;
	CString CharName;
	void SetParent(CDocument *pDoc);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySocket)
	public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CMySocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
private:
	CDocument* m_Parent;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSOCKET_H__342C6DDB_3E31_48FF_99F2_9C65146716E4__INCLUDED_)
