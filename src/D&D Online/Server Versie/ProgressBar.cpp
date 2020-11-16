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
#include "ProgressBar.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProgressBar::CProgressBar()
{
	INITCOMMONCONTROLSEX icc;

	icc.dwICC = ICC_PROGRESS_CLASS;	//Initialize the Progress Bar Class
	icc.dwSize = sizeof(INITCOMMONCONTROLSEX);

	InitCommonControlsEx(&icc);

	hInst = GetModuleHandle(NULL);
	
	hProgressBar = NULL;
	hPBParent    = NULL;

	strcpy(szPBDisTxt,_T(""));
	strcpy(szPBTitleTxt,_T(""));
}

CProgressBar::~CProgressBar()
{
	SendMessage(hPBParent,WM_CLOSE,0,0);
}

bool CProgressBar::CreateProgressBar(HWND hWnd, int width, int height, DWORD dwStyle,LPTSTR lpDisTxt,LPSTR lpTitleTxt)
{
	//Not a Valid Parent Window 
	if (!IsWindow(hWnd)) return false;

	//The Size of the Progress Bar cant be zero
	if (width <= 0 || height <= 0) return false;

	//If there is a title text to be displayed verify and copy the string.
	if ((dwStyle & PBS_TITLETEXT) && (dwStyle & PBS_TITLEBAR))
	{
		if((lpTitleTxt != NULL) || (strlen(lpTitleTxt) <= MAX_PATH))
		{
			strcpy(szPBTitleTxt,lpTitleTxt);
		}
		else return false;
	}

	//If there is some display test to be displayed verify and copy the string
	if (dwStyle & PBS_DISPLAYTEXT)
	{
		if((lpDisTxt != NULL) || (strlen(lpDisTxt) <= MAX_PATH))
		{
			strcpy(szPBDisTxt,lpDisTxt);
		}
		else return false;
	}
	
	dwPBStyle = dwStyle;

	RECT rt;
	SIZE size;

	size.cx = 0;
	size.cy = 0;

	//Get the Parent's Window Co-Ordinates.
	GetWindowRect(hWnd,&rt);

	//Center the PB Window to the Parent's Window
	rt.left += ((rt.right-rt.left)/2);
	rt.top  += ((rt.bottom-rt.top)/2);

	//start of with the size of the Progress bar window to be the user desired 
	//add padding
	rt.right = width + 20 + 2*GetSystemMetrics(SM_CXDLGFRAME);
	rt.bottom = height + 10 + 2*GetSystemMetrics(SM_CYDLGFRAME);

	//resize the PB window width to match the Initial Display Text Len
	if (dwStyle & PBS_DISPLAYTEXT)
	{
		HDC hdc = GetDC(NULL);
		GetTextExtentPoint32(hdc,szPBDisTxt,strlen(szPBDisTxt),&size);
		ReleaseDC(NULL,hdc);
		
		if (rt.right < size.cx)
		{
			rt.right = size.cx + 20;
		}

		rt.bottom += size.cy + 2;
	}

	//If Title Bar style, add Title Bar width
	if ((dwStyle & PBS_TITLEBAR))
	{
		rt.bottom += GetSystemMetrics(SM_CYCAPTION);
	}

	//Center the PB Window to the Parent's Window
	rt.left -= (rt.right/2);
	rt.top  -= (rt.bottom/2);

	if (!CreateProgBarParent(hWnd, &rt)) return false;
	
	GetClientRect(hPBParent,&rt);
	
	rt.top = 5; rt.left = 10; rt.right -= 10; rt.bottom -= 10;

	//Add offset for Text Display
	if (dwStyle & PBS_DISPLAYTEXT)
	{
		rt.top += size.cy + 2;
	}

	if (width < size.cx)
	{
		rt.left = (size.cx / 2) - (width / 2) + 10;
	}

    hProgressBar = CreateWindowEx(0, PROGRESS_CLASS, NULL, 
									WS_CHILD | WS_VISIBLE,
									rt.left, rt.top,width, height, 
									hPBParent, (HMENU) 0, hInst, NULL); 

	if (hProgressBar == NULL) return false;

	return true;
}

bool CProgressBar::SetProgressBarRange(int range,int step)
{
	if (range <= 0) return false;
	if (step <= 0) return false;

	SendMessage(hProgressBar, PBM_SETRANGE, 0, MAKELPARAM(0, range)); 
	SendMessage(hProgressBar, PBM_SETSTEP, (WPARAM) step, 0);

	return true;
}

bool CProgressBar::IncrProgressBar()
{
	SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
	return true;
}

bool CProgressBar::SetProgressBarPos(int NewPos)
{
	if (NewPos < 0) return false;

	SendMessage(hProgressBar,PBM_SETPOS,(WPARAM) NewPos, 0);

	return true;
}

bool CProgressBar::CreateProgBarParent(HWND hWnd, LPRECT lpWndPos)
{
	WNDCLASSEX wndclass ;
	
	wndclass.cbSize        = sizeof (wndclass) ;
	wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
	wndclass.lpfnWndProc   = PBPWndProc ;
	wndclass.cbClsExtra    = 0 ;
	wndclass.cbWndExtra    = 0 ;
	wndclass.hInstance     = hInst ;
	wndclass.hIcon         = NULL;
	wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
	wndclass.hbrBackground = GetSysColorBrush(COLOR_BTNFACE) ;
	wndclass.lpszMenuName  = NULL ;
	wndclass.lpszClassName = _T("progbarparent");
	wndclass.hIconSm       = NULL ;
	
	RegisterClassEx (&wndclass) ;

	DWORD dwStyle =  WS_VISIBLE;
	DWORD dwExStyle = 0;
	RECT rt;

	CopyRect(&rt,lpWndPos);

	if(dwPBStyle & PBS_DLGFRAME)
	{ 
		dwStyle |= WS_CHILD | WS_DLGFRAME | WS_POPUP;
	}
	else 
	{
		dwExStyle = WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE | WS_EX_CONTROLPARENT;//0x00010109L;
		dwStyle |=  WS_POPUPWINDOW | WS_CLIPSIBLINGS | WS_DLGFRAME | WS_OVERLAPPED;//0x94c80000L;
	}

	hPBParent = CreateWindowEx(dwExStyle, _T("progbarparent"), szPBTitleTxt,
							dwStyle, rt.left, rt.top,rt.right, rt.bottom,
							hWnd, (HMENU) 0, hInst, (LPVOID)this); 


	if (hPBParent == NULL) return false;

	return true;
}

LRESULT CALLBACK CProgressBar::PBPWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HFONT hfont;
	switch (uMsg)
	{
	case WM_CREATE:
			hfont = CreateFont((-9)*GetDeviceCaps(GetDC(GetDesktopWindow()), 
								LOGPIXELSY)/72, 
								0, 0, 0, 
								FW_NORMAL, //FONT WEIGHT
								0, //Italic
								0, //UnderLine
								0, //Strikeout
								ANSI_CHARSET,
								OUT_DEFAULT_PRECIS,
								CLIP_DEFAULT_PRECIS, 
								PROOF_QUALITY, 
								VARIABLE_PITCH | FF_SWISS, 
								"Verdana");

		SetWindowLong(hWnd,GWL_USERDATA,(LONG)((LPCREATESTRUCT) lParam)->lpCreateParams);
		return 0;

	case WM_PAINT :
		{
			CProgressBar * pThis = (CProgressBar*) GetWindowLong(hWnd,GWL_USERDATA);
			
			if (pThis->dwPBStyle & PBS_DISPLAYTEXT)
			{
				PAINTSTRUCT ps;
				RECT rect;
				
				HDC hdc = BeginPaint (hWnd, &ps) ;
				
				SetBkMode(hdc,TRANSPARENT) ;
				
				GetClientRect (hWnd, &rect) ;
				rect.left += 10;
				SelectObject(hdc,(HGDIOBJ)hfont);

				DrawText (hdc, pThis->szPBDisTxt, -1, &rect,DT_LEFT) ;
				
				EndPaint (hWnd, &ps) ;
				return 0 ;
			}
		}
		break;
	case WM_CLOSE:
		CProgressBar * pThis = (CProgressBar*) GetWindowLong(hWnd,GWL_USERDATA);
		DeleteObject((HGDIOBJ)hfont);
		if (pThis->hProgressBar) DestroyWindow(pThis->hProgressBar);
		pThis->hProgressBar = NULL;
		pThis->hPBParent = NULL;
		DestroyWindow(hWnd);
		return 0;
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

bool CProgressBar::SetProgressBarDisplayText(LPCTSTR lpDisTxt)
{
	if (!(dwPBStyle & PBS_DISPLAYTEXT) || hPBParent == NULL) return false;

	if((lpDisTxt != NULL) || (strlen(lpDisTxt) <= MAX_PATH))
	{
		strcpy(szPBDisTxt,lpDisTxt);
		InvalidateRect(hPBParent,NULL,TRUE);
		return true;
	}
	else return false;
}

bool CProgressBar::SetProgressBarTitleText(LPCTSTR lpTitleTxt)
{
	if (!(dwPBStyle & PBS_TITLETEXT) || hPBParent == NULL) return false;

	if((lpTitleTxt != NULL) || (strlen(lpTitleTxt) <= MAX_PATH))
	{
		strcpy(szPBTitleTxt,lpTitleTxt);
		SetWindowText(hPBParent,szPBTitleTxt);
		return true;
	}
	else return false;
}

bool CProgressBar::DeleteProgressBar()
{
	SendMessage(hPBParent,WM_CLOSE,0,0);
	return true;
}
