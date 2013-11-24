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

// CColorAndMonoDlg dialog

INT g_2IconsXPositions[2] = { 106, 190 };
INT g_iconsOriginHeight = 196;

CColorAndMonoDlg::CColorAndMonoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CColorAndMonoDlg::IDD, pParent)
{
		m_hIcon = AfxGetApp()->LoadIcon(IDR_LOGO);

		currentPage = 0;

		time = 500;

		Settings * tet = new Settings();
		delete tet;
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

		HRESULT hRes = m_lcd.Initialize(_T("Open Hardware Monitor"), LG_DUAL_MODE, TRUE, TRUE);

		if (hRes != S_OK)
		{
			// Something went wrong, when connecting to the LCD Manager software. Deal with it...
			PostQuitMessage(0);
			return FALSE;
		}

		m_lcd.SetAsForeground(true);

		if (m_lcd.IsDeviceAvailable(LG_MONOCHROME))
		{
			InitLCDObjectsMonochrome();
		}

		else if (m_lcd.IsDeviceAvailable(LG_COLOR))
		{
			InitLCDObjectsColor();
		}

		SetTimer(0xabab, 30, NULL); // for scrolling to work smoothly, timer should be pretty fast

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

void CColorAndMonoDlg::OnDestroy()
{

}

void CColorAndMonoDlg::OnTimer(UINT_PTR nIDEvent)
{

	//UNREFERENCED_PARAMETER(nIDEvent);
	//time += 30;

	//CheckButtonPresses();

	//if (time > 1000)
	//{
	//	if (m_lcd.IsDeviceAvailable(LG_MONOCHROME))
	//	{
	//		InitLCDObjectsMonochrome();
	//	}

	//	else if (m_lcd.IsDeviceAvailable(LG_COLOR))
	//	{
	//		InitLCDObjectsColor();
	//	}
	//	time = 0;
	//}
	//m_lcd.Update();
}

void CColorAndMonoDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	ASSERT(NULL != lpwndpos);

	if (NULL != lpwndpos)
	{
		lpwndpos->flags &= ~SWP_SHOWWINDOW;
	}

	CDialog::OnWindowPosChanging(lpwndpos);

}

VOID CColorAndMonoDlg::InitLCDObjectsMonochrome()
{
		m_lcd.ModifyDisplay(LG_MONOCHROME);



}

VOID CColorAndMonoDlg::InitLCDObjectsColor()
{
		m_lcd.ModifyDisplay(LG_COLOR);

}

VOID CColorAndMonoDlg::CheckButtonPresses()
{
		if (m_lcd.IsDeviceAvailable(LG_MONOCHROME) && CheckbuttonPressesMonochrome())
		{
			InitLCDObjectsMonochrome();
			time = 0;
		}

		else if (m_lcd.IsDeviceAvailable(LG_COLOR) && CheckbuttonPressesColor())
		{
			InitLCDObjectsColor();
			time = 0;
		}
}

bool CColorAndMonoDlg::CheckbuttonPressesMonochrome()
{
	bool buttonPressed = false;

		m_lcd.ModifyDisplay(LG_MONOCHROME);

		//Go to next page
		if (m_lcd.ButtonTriggered(LG_BUTTON_4))
		{
			currentPage++;

			if (currentPage >= 4)
			{
				currentPage = 0;
			}

			buttonPressed = true;
		}

		//Go to previous page
		else if (m_lcd.ButtonTriggered(LG_BUTTON_1))
		{
			currentPage--;

			if (currentPage < 0)
			{
				currentPage = 3;
			}
			buttonPressed = true;
		}

		//Scroll down
		else if (m_lcd.ButtonTriggered(LG_BUTTON_2))
		{
			//if (currentPage == 0 && scrollCPUScreen != 0)
			//{
			//	scrollCPUScreen--;
			//}

			//if (currentPage == 1 && scrollGPUScreen != 0)
			//{
			//	scrollGPUScreen--;
			//}

			//if (currentPage == 2 && scrollHDDScreen != 0)
			//{
			//	scrollHDDScreen--;
			//}
			buttonPressed = true;
		}

		//Scroll up
		else if (m_lcd.ButtonTriggered(LG_BUTTON_3))
		{
			//if (currentPage == 0 && !(scrollCPUScreen + 6 >= (int)text.size()))
			//{
			//	scrollCPUScreen++;
			//}

			//else if (currentPage == 1 && !(scrollGPUScreen + 6 >= (int) text.size()))
			//{
			//	scrollGPUScreen++;
			//}

			//else if (currentPage == 2 && !(scrollHDDScreen + 6 >= (int) text.size()))
			//{
			//	scrollHDDScreen++;
			//}
			buttonPressed = true;
		}

	return buttonPressed;
}

bool CColorAndMonoDlg::CheckbuttonPressesColor()
{
	m_lcd.ModifyDisplay(LG_COLOR);

	bool buttonPressed = false;

		if (m_lcd.ButtonReleased(LG_BUTTON_RIGHT))
		{
			currentPage++;

			if (currentPage >= 4)
			{
				currentPage = 0;
			}

			buttonPressed = true;
		}

		if (m_lcd.ButtonReleased(LG_BUTTON_LEFT))
		{
			currentPage--;

			if (currentPage < 0)
			{
				currentPage = 3;
			}
			buttonPressed = true;
		}

		if (m_lcd.ButtonReleased(LG_BUTTON_DOWN))
		{
			/*if (currentPage == 0 && !((scrollCPUScreen + 10) >= (int) text.size()))
			{
				scrollCPUScreen++;
			}

			if (currentPage == 1 && !((scrollGPUScreen + 10) >= (int) text.size()))
			{
				scrollGPUScreen++;
			}

			if (currentPage == 2 && !((scrollHDDScreen + 10) >= (int) text.size()))
			{
				scrollHDDScreen++;
			}*/
			buttonPressed = true;
		}

		if (m_lcd.ButtonReleased(LG_BUTTON_UP))
		{
			/*if (currentPage == 0 && scrollCPUScreen != 0)
			{
				scrollCPUScreen--;
			}

			if (currentPage == 1 && scrollGPUScreen != 0)
			{
				scrollGPUScreen--;
			}

			if (currentPage == 2 && scrollHDDScreen != 0)
			{
				scrollHDDScreen--;
			}*/
			buttonPressed = true;
		}

	return buttonPressed;
}