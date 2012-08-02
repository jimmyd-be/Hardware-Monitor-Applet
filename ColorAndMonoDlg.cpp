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

#ifdef BUTTON_TESTING
	ExtraTester::DoButtonTestingMono(m_lcd);
	ExtraTester::DoButtonTestingColor(m_lcd);
#endif

#ifdef SCREEN_PRIORITY_TESTING
	ExtraTester::DoScreenPriorityTesting(m_lcd);
#endif

#ifdef FOREGROUND_TESTING
	ExtraTester::DoForegroundTesting(m_lcd);
#endif

#ifdef VISIBLE_TESTING
	std::vector<HANDLE> handles_;
	handles_.push_back(m_smallText1);
	handles_.push_back(m_mediumText);
	handles_.push_back(m_progressbar2);
	handles_.push_back(m_logo);
	handles_.push_back(m_right1);
	handles_.push_back(m_tinyTextColor1);
	handles_.push_back(m_smallTextColor);
	handles_.push_back(m_bigTextColor);
	handles_.push_back(m_leftColor1);
	handles_.push_back(m_leftColor2);
	handles_.push_back(m_highlightColor1);
	handles_.push_back(m_highlightColor2);
	handles_.push_back(m_progressbar2Color);
	handles_.push_back(m_progressbar4Color);
	handles_.push_back(m_logoColor);
	ExtraTester::DoVisibleTesting(m_lcd, handles_);
#endif

#ifdef PAGE_TESTING
	ExtraTester::DoPageTesting(m_lcd);
#endif
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
	//HDDText = wmi->getHDDText();

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

	//	GPUText.push_back(m_lcd.AddText(LG_STATIC_TEXT, LG_SMALL, DT_LEFT, 155));
	//m_lcd.SetOrigin(GPUText[GPUText.size()-1], 0, 32);
	//m_lcd.SetText(GPUText[GPUText.size()-1], _T("Small text is scrolling"));
	//

	//m_lcd.AddNewPage();
	//  m_lcd.ModifyControlsOnPage(2);
	//	HDDText.push_back(m_lcd.AddText(LG_STATIC_TEXT, LG_SMALL, DT_LEFT, 155));
	//m_lcd.SetOrigin(HDDText[HDDText.size()-1], 0, 0);
	//m_lcd.SetText(HDDText[HDDText.size()-1], _T("Small text is scrolling"));

	//vector<HANDLE> HDDText;
	//vector<HANDLE> OtherText;

	//   m_smallText1 = m_lcd.AddText(LG_SCROLLING_TEXT, LG_SMALL, DT_CENTER, 70);
	//   m_lcd.SetOrigin(m_smallText1, 0, 0);
	//   m_lcd.SetText(m_smallText1, _T("Small text is scrolling"));

	//   m_smallText2 = m_lcd.AddText(LG_STATIC_TEXT, LG_SMALL, DT_LEFT, 80);
	//   m_lcd.SetOrigin(m_smallText2, 80, 0);
	//   m_lcd.SetText(m_smallText2, _T("Small text is static instead of scrolling"));

	//   m_mediumText = m_lcd.AddText(LG_STATIC_TEXT, LG_MEDIUM, DT_CENTER, LGLCD_BW_BMP_WIDTH);
	//   m_lcd.SetOrigin(m_mediumText, 0, 11);
	//   m_lcd.SetText(m_mediumText, _T("Medium text is centered"));

	//   m_bigText = m_lcd.AddText(LG_STATIC_TEXT, LG_BIG, DT_LEFT, LGLCD_BW_BMP_WIDTH);
	//   m_lcd.SetOrigin(m_bigText, 0, 25);
	//   m_lcd.SetText(m_bigText, _T("Big text on left"));

	//   HICON rightIcon_ = static_cast<HICON>(LoadImage(
	//       AfxGetInstanceHandle(), 
	//       MAKEINTRESOURCE(IDI_NEXT),
	//       IMAGE_ICON, 
	//       16, 
	//       16, 
	//       LR_MONOCHROME));
	//   m_right1 = m_lcd.AddIcon(rightIcon_, 16, 16);
	//   m_lcd.SetOrigin(m_right1, 142, 35);

	//   /***************/
	//   /* SECOND PAGE */
	//   /***************/
	//   m_lcd.AddNewPage();
	//   m_lcd.ModifyControlsOnPage(1);

	//   m_progressbar1 = m_lcd.AddProgressBar(LG_DOT_CURSOR);
	//   m_lcd.SetProgressBarSize(m_progressbar1, 90, 5);
	//   m_lcd.SetOrigin(m_progressbar1, 70, 0);

	//   m_progressbar2 = m_lcd.AddProgressBar(LG_FILLED);
	//   m_lcd.SetProgressBarSize(m_progressbar2, 60, 8);
	//   m_lcd.SetOrigin(m_progressbar2, 70, 10);

	//   m_progressbar3 = m_lcd.AddProgressBar(LG_CURSOR);
	//   m_lcd.SetProgressBarSize(m_progressbar3, 30, 3);
	//   m_lcd.SetOrigin(m_progressbar3, 70, 25);

	//   HBITMAP logoBitmap_ = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_LOGO));
	//   m_logo = m_lcd.AddBitmap(55, 43);
	//   m_lcd.SetBitmap(m_logo, logoBitmap_);
	//   m_lcd.SetOrigin(m_logo, 0, 0);

	//   m_right2 = m_lcd.AddIcon(rightIcon_, 16, 16);
	//   m_lcd.SetOrigin(m_right2, 142, 35);
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
		m_lcd.ShowPage(currentPage);
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
