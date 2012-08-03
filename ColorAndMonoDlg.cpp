//************************************************************************
//  The Logitech LCD SDK, including all acompanying documentation,
//  is protected by intellectual property laws.  All use of the Logitech
//  LCD SDK is subject to the License Agreement found in the
//  "Logitech LCD SDK License Agreement" file and in the Reference Manual.  
//  All rights not expressly granted by Logitech are reserved.
//************************************************************************

// ColorAndMonoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ColorAndMono.h"
#include "ColorAndMonoDlg.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Defines for testing EZ LCD Wrapper functions that aren't being used in sample
//#define BUTTON_TESTING
//#define SCREEN_PRIORITY_TESTING
//#define FOREGROUND_TESTING
//#define VISIBLE_TESTING
//#define PAGE_TESTING

// CColorAndMonoDlg dialog

INT g_2IconsXPositions[2] = {106, 190};
INT g_iconsOriginHeight = 196;

CColorAndMonoDlg::CColorAndMonoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CColorAndMonoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_currentHighlightPosition = 1;

	wmi = new WMI();
}

void CColorAndMonoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CColorAndMonoDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_WINDOWPOSCHANGING()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CColorAndMonoDlg message handlers

BOOL CColorAndMonoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	ShowWindow(SW_HIDE);
	SetWindowPos(NULL, 0, 0, 0, 0, NULL);
	
	HRESULT hRes = m_lcd.Initialize(_T("Open Hardware Monitor"), LG_DUAL_MODE, FALSE, TRUE);

	if (hRes != S_OK)
	{
		// Something went wrong, when connecting to the LCD Manager software. Deal with it...
		PostQuitMessage(0);
		return FALSE;
	}

	InitLCDObjectsMonochrome();
	//  InitLCDObjectsColor();

	SetTimer(0xabab, 500, NULL); // for scrolling to work smoothly, timer should be pretty fast

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CColorAndMonoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CColorAndMonoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CColorAndMonoDlg::OnDestroy( )
{

}

void CColorAndMonoDlg::OnTimer(UINT_PTR nIDEvent)
{
	UNREFERENCED_PARAMETER(nIDEvent);

	InitLCDObjectsMonochrome();
	CheckButtonPresses();

	m_lcd.Update();

}

void CColorAndMonoDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	ASSERT(NULL != lpwndpos);

	if(NULL != lpwndpos)
	{
		lpwndpos->flags &= ~SWP_SHOWWINDOW;
	}

	CDialog::OnWindowPosChanging(lpwndpos);
}

VOID CColorAndMonoDlg::InitLCDObjectsMonochrome()
{
	wmi->refresh();

	vector<string> CPUText;
	vector<string> GPUText;
	vector<string> HDDText;
	vector<string> OtherText;

	CPUText = wmi->getCPUText();
	GPUText = wmi->getGPUText();
	HDDText = wmi->getHDDText();

	m_lcd.ModifyDisplay(LG_MONOCHROME);

	/***************/
	/* FIRST PAGE */
	/***************/

	for(int i=0; i < CPUText.size(); i++)
	{
		CPUScreen.push_back(m_lcd.AddText(LG_STATIC_TEXT, LG_SMALL, DT_LEFT, 155));
		m_lcd.SetOrigin(CPUScreen[CPUScreen.size()-1], 0, (i*7));

		wstring s2;
		s2.assign(CPUText[i].begin(), CPUText[i].end());
		m_lcd.SetText(CPUScreen[CPUScreen.size()-1], s2.c_str());
	}

	/***************/
	/* Second PAGE */
	/***************/

	m_lcd.AddNewPage();
	m_lcd.ModifyControlsOnPage(1);

	for(int i=0; i < GPUText.size(); i++)
	{
		GPUScreen.push_back(m_lcd.AddText(LG_STATIC_TEXT, LG_SMALL, DT_LEFT, 155));
		m_lcd.SetOrigin(GPUScreen[GPUScreen.size()-1], 0, (i*7));

		wstring s2;
		s2.assign(GPUText[i].begin(), GPUText[i].end());
		m_lcd.SetText(GPUScreen[GPUScreen.size()-1], s2.c_str());
	}


	/***************/
	/* Third PAGE */
	/***************/
	m_lcd.AddNewPage();
	m_lcd.ModifyControlsOnPage(2);

	for(int i=0; i < HDDText.size(); i++)
	{
		HDDScreen.push_back(m_lcd.AddText(LG_STATIC_TEXT, LG_SMALL, DT_LEFT, 155));
		m_lcd.SetOrigin(HDDScreen[HDDScreen.size()-1], 0, (i*7));

		wstring s2;
		s2.assign(HDDText[i].begin(), HDDText[i].end());
		m_lcd.SetText(HDDScreen[HDDScreen.size()-1], s2.c_str());
	}
}

VOID CColorAndMonoDlg::InitLCDObjectsColor()
{

}

VOID CColorAndMonoDlg::CheckButtonPresses()
{
	CheckbuttonPressesMonochrome();
	CheckbuttonPressesColor();
}

VOID CColorAndMonoDlg::CheckbuttonPressesMonochrome()
{
	m_lcd.ModifyDisplay(LG_MONOCHROME);

	currentPage = m_lcd.GetCurrentPageNumber();

	if (m_lcd.ButtonTriggered(LG_BUTTON_4))
	{
		m_lcd.ShowPage((m_lcd.GetCurrentPageNumber() + 1) % m_lcd.GetPageCount());
	}

	else if(m_lcd.ButtonTriggered(LG_BUTTON_1))
	{
		if(m_lcd.GetCurrentPageNumber() - 1 < 0)
		{
			m_lcd.ShowPage(m_lcd.GetPageCount()-1);
		}
		else
		{
			m_lcd.ShowPage((m_lcd.GetCurrentPageNumber() - 1) % m_lcd.GetPageCount());
		}
	}

	else
	{
		m_lcd.ShowPage(currentPage% m_lcd.GetPageCount());
	}
}

VOID CColorAndMonoDlg::CheckbuttonPressesColor()
{
	m_lcd.ModifyDisplay(LG_COLOR);

	if (m_lcd.ButtonTriggered(LG_BUTTON_LEFT))
	{
		if (m_currentHighlightPosition >= 1)
		{
			--m_currentHighlightPosition;
			m_lcd.SetOrigin(m_highlightColor1, g_2IconsXPositions[m_currentHighlightPosition] - 12, g_iconsOriginHeight - 4);
			m_lcd.SetOrigin(m_highlightColor2, g_2IconsXPositions[m_currentHighlightPosition] - 12, g_iconsOriginHeight - 4);
		}
	}

	if (m_lcd.ButtonTriggered(LG_BUTTON_RIGHT))
	{
		if (m_currentHighlightPosition < 1)
		{
			++m_currentHighlightPosition;
			m_lcd.SetOrigin(m_highlightColor1, g_2IconsXPositions[m_currentHighlightPosition] - 12, g_iconsOriginHeight - 4);
			m_lcd.SetOrigin(m_highlightColor2, g_2IconsXPositions[m_currentHighlightPosition] - 12, g_iconsOriginHeight - 4);
		}
	}

	if (m_lcd.ButtonTriggered(LG_BUTTON_OK))
	{
		if (0 == m_currentHighlightPosition)
		{
			if (0 == m_lcd.GetCurrentPageNumber())
			{
				m_lcd.ShowPage(m_lcd.GetPageCount() - 1);
			}
			else
			{
				m_lcd.ShowPage(m_lcd.GetCurrentPageNumber() - 1);
			}

		}
		else if (1 == m_currentHighlightPosition)
		{
			m_lcd.ShowPage((m_lcd.GetCurrentPageNumber() + 1) % m_lcd.GetPageCount());
		}
	}
}
