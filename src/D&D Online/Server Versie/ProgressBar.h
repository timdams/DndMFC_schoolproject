/////////////////////////////////////////////////////////////////////////////////////////////////
//				Class		: CProgressBar													   //
//										 													   //
//				Author		: Natarajan T													   //
//																							   //
//				Version		: 1.0															   //
//																							   //
//				Purpose		: C++ Class for creating a Progress Bar Control Diaolog Box		   //
//																							   //
//				Disclaimer	: This Source code is given in asis condition and nothimg is 	   //
//								guaranted, The Source code is to be used on own risk.		   //
//								This Source code is distributed in good faith and Author is not//
//								responsible for any damage done, to the user, in any manner    //
//								perceived to be caused by the use of this source code.		   //
//																							   //
/////////////////////////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROGRESSBAR_H__465C1A68_DD3F_4BE2_89A8_7A0869BC0F81__INCLUDED_)
#define AFX_PROGRESSBAR_H__465C1A68_DD3F_4BE2_89A8_7A0869BC0F81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <commctrl.h>
#include <tchar.h>

#pragma comment(lib, "comctl32.lib")

#define PBS_DLGFRAME			0x00400000L
#define PBS_TITLEBAR			0x00010000L

#define PBS_TITLETEXT			0x00000001L
#define PBS_DISPLAYTEXT			0x00000002L

//Yet to be implemented
#define PBS_SMOOTHPROGRESS		0x00000010L
#define PBS_UNITPROGRESS		0x00000020L

#define PBS_DISPLAYPERCENT		0x00000100L
#define PBS_CANCANCEL			0x00000200L

	class CProgressBar  
{
public:
	bool DeleteProgressBar();
	bool SetProgressBarTitleText(LPCTSTR lpTitleTxt);
	bool SetProgressBarDisplayText(LPCTSTR);
	bool SetProgressBarPos(int NewPos);
	bool SetProgressBarRange(int range,int step);
	bool IncrProgressBar();
	bool CreateProgressBar(HWND hWnd, int width, int height, DWORD dwPBStyle,LPTSTR lpDisTxt,LPSTR lpTitleTxt);
	
	CProgressBar();
	virtual ~CProgressBar();

private:
	DWORD dwPBStyle;
	TCHAR szPBDisTxt[MAX_PATH];
	TCHAR szPBTitleTxt[MAX_PATH];
	HINSTANCE hInst;
	HWND hPBParent;
	HWND hProgressBar;
	static LRESULT CALLBACK PBPWndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
	bool CreateProgBarParent(HWND hWnd, LPRECT lpWndPos);
};

#endif // !defined(AFX_PROGRESSBAR_H__465C1A68_DD3F_4BE2_89A8_7A0869BC0F81__INCLUDED_)
