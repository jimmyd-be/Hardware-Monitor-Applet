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
#include "ExtraTester.h"
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

    HRESULT hRes = m_lcd.Initialize(_T("Logitech Dual Mode Sample"), LG_DUAL_MODE, FALSE, TRUE);

    if (hRes != S_OK)
    {
        // Something went wrong, when connecting to the LCD Manager software. Deal with it...
        PostQuitMessage(0);
        return FALSE;
    }

    InitLCDObjectsMonochrome();
    InitLCDObjectsColor();

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

void CColorAndMonoDlg::OnDestroy( )
{
    
}

void CColorAndMonoDlg::OnTimer(UINT_PTR nIDEvent)
{
    UNREFERENCED_PARAMETER(nIDEvent);

    CheckButtonPresses();

    UpdateProgressBars();

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
    m_lcd.ModifyDisplay(LG_MONOCHROME);

    /***************/
    /* FIRST PAGE */
    /***************/

    m_smallText1 = m_lcd.AddText(LG_SCROLLING_TEXT, LG_SMALL, DT_CENTER, 70);
    m_lcd.SetOrigin(m_smallText1, 0, 0);
    m_lcd.SetText(m_smallText1, _T("Small text is scrolling"));

    m_smallText2 = m_lcd.AddText(LG_STATIC_TEXT, LG_SMALL, DT_LEFT, 80);
    m_lcd.SetOrigin(m_smallText2, 80, 0);
    m_lcd.SetText(m_smallText2, _T("Small text is static instead of scrolling"));

    m_mediumText = m_lcd.AddText(LG_STATIC_TEXT, LG_MEDIUM, DT_CENTER, LGLCD_BW_BMP_WIDTH);
    m_lcd.SetOrigin(m_mediumText, 0, 11);
    m_lcd.SetText(m_mediumText, _T("Medium text is centered"));

    m_bigText = m_lcd.AddText(LG_STATIC_TEXT, LG_BIG, DT_LEFT, LGLCD_BW_BMP_WIDTH);
    m_lcd.SetOrigin(m_bigText, 0, 25);
    m_lcd.SetText(m_bigText, _T("Big text on left"));

    HICON rightIcon_ = static_cast<HICON>(LoadImage(
        AfxGetInstanceHandle(), 
        MAKEINTRESOURCE(IDI_NEXT),
        IMAGE_ICON, 
        16, 
        16, 
        LR_MONOCHROME));
    m_right1 = m_lcd.AddIcon(rightIcon_, 16, 16);
    m_lcd.SetOrigin(m_right1, 142, 35);

    /***************/
    /* SECOND PAGE */
    /***************/
    m_lcd.AddNewPage();
    m_lcd.ModifyControlsOnPage(1);

    m_progressbar1 = m_lcd.AddProgressBar(LG_DOT_CURSOR);
    m_lcd.SetProgressBarSize(m_progressbar1, 90, 5);
    m_lcd.SetOrigin(m_progressbar1, 70, 0);

    m_progressbar2 = m_lcd.AddProgressBar(LG_FILLED);
    m_lcd.SetProgressBarSize(m_progressbar2, 60, 8);
    m_lcd.SetOrigin(m_progressbar2, 70, 10);

    m_progressbar3 = m_lcd.AddProgressBar(LG_CURSOR);
    m_lcd.SetProgressBarSize(m_progressbar3, 30, 3);
    m_lcd.SetOrigin(m_progressbar3, 70, 25);

    HBITMAP logoBitmap_ = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_LOGO));
    m_logo = m_lcd.AddBitmap(55, 43);
    m_lcd.SetBitmap(m_logo, logoBitmap_);
    m_lcd.SetOrigin(m_logo, 0, 0);

    m_right2 = m_lcd.AddIcon(rightIcon_, 16, 16);
    m_lcd.SetOrigin(m_right2, 142, 35);
}

VOID CColorAndMonoDlg::InitLCDObjectsColor()
{
    m_lcd.ModifyDisplay(LG_COLOR);

    /***************/
    /* FIRST PAGE */
    /***************/
    m_background.LoadFromResource(NULL, AfxGetInstanceHandle(), IDR_BACKGROUND, _T("PNG"));
    HBITMAP bmpBkg_ = m_background.GetHBITMAP();
    m_lcd.SetBackground(bmpBkg_);

    m_tinyTextColor1 = m_lcd.AddText(LG_SCROLLING_TEXT, LG_TINY, DT_LEFT, 140);
    m_lcd.SetOrigin(m_tinyTextColor1, 10, 10);
    m_lcd.SetText(m_tinyTextColor1, _T("Tiny text is scrolling all the time and all over the place..."));
    m_lcd.SetTextFontColor(m_tinyTextColor1, RGB(255, 0, 0));

    m_tinyTextColor2 = m_lcd.AddText(LG_SCROLLING_TEXT, LG_TINY, DT_LEFT, 140, 1, FW_HEAVY);
    m_lcd.SetOrigin(m_tinyTextColor2, 170, 10);
    m_lcd.SetText(m_tinyTextColor2, _T("Tiny text is scrolling with a heavy font..."));
    m_lcd.SetTextFontColor(m_tinyTextColor2, RGB(0, 255, 0));
    m_lcd.SetTextBackground(m_tinyTextColor2, OPAQUE, RGB(0, 0, 255));

    m_smallTextColor = m_lcd.AddText(LG_SCROLLING_TEXT, LG_SMALL, DT_CENTER, LGLCD_QVGA_BMP_WIDTH);
    m_lcd.SetOrigin(m_smallTextColor, 0, 40);
    m_lcd.SetText(m_smallTextColor, _T("Small text is centered"));
    m_lcd.SetTextFontColor(m_smallTextColor, RGB(0, 0, 0));

    m_mediumTextColor = m_lcd.AddText(LG_STATIC_TEXT, LG_MEDIUM, DT_CENTER, LGLCD_QVGA_BMP_WIDTH, 3);
    m_lcd.SetOrigin(m_mediumTextColor, 0, 70);
    m_lcd.SetText(m_mediumTextColor, _T("Medium text has muliple lines so we can write a lot of stuff in just one string."));
    m_lcd.SetTextFontColor(m_mediumTextColor, RGB(0, 0, 255));

    m_bigTextColor = m_lcd.AddText(LG_SCROLLING_TEXT, LG_BIG, DT_CENTER, LGLCD_QVGA_BMP_WIDTH, 1, FW_HEAVY);
    m_lcd.SetOrigin(m_bigTextColor, 0, 150);
    m_lcd.SetText(m_bigTextColor, _T("BIG text has a gray background"));
    m_lcd.SetTextFontColor(m_bigTextColor, RGB(150, 150, 150));
    m_lcd.SetTextBackground(m_bigTextColor, OPAQUE, RGB(200, 200, 200));

    m_next.LoadFromResource(NULL, AfxGetInstanceHandle(), IDR_NEXT, _T("PNG"));
    HBITMAP next_ = m_next.GetHBITMAP();
    m_rightColor1 = m_lcd.AddBitmap(24, 24);
    m_lcd.SetBitmap(m_rightColor1, next_);
    m_lcd.SetOrigin(m_rightColor1, g_2IconsXPositions[1], g_iconsOriginHeight);

    m_previous.LoadFromResource(NULL, AfxGetInstanceHandle(), IDR_PREVIOUS, _T("PNG"));
    HBITMAP previous_ = m_previous.GetHBITMAP();
    m_leftColor1 = m_lcd.AddBitmap(24, 24);
    m_lcd.SetBitmap(m_leftColor1, previous_);
    m_lcd.SetOrigin(m_leftColor1, g_2IconsXPositions[0], g_iconsOriginHeight);

    m_highlight.LoadFromResource(NULL, AfxGetInstanceHandle(), IDR_HIGHLIGHT, _T("PNG"));
    HBITMAP highlight_ = m_highlight.GetHBITMAP();
    m_highlightColor1 = m_lcd.AddBitmap(48, 32);
    m_lcd.SetBitmap(m_highlightColor1, highlight_);
    m_lcd.SetOrigin(m_highlightColor1, g_2IconsXPositions[m_currentHighlightPosition] - 12, g_iconsOriginHeight - 4);

    /***************/
    /* SECOND PAGE */
    /***************/
    m_lcd.AddNewPage();
    m_lcd.ModifyControlsOnPage(1);

    m_lcd.SetBackground(RGB(160, 180, 200));

    m_logoSmall.LoadFromResource(NULL, AfxGetInstanceHandle(), IDR_LOGO_SMALL, _T("PNG"));
    HBITMAP logoSmall_ = m_logoSmall.GetHBITMAP();
    m_logoColor = m_lcd.AddBitmap(50, 44);
    m_lcd.SetBitmap(m_logoColor, logoSmall_);
    m_lcd.SetOrigin(m_logoColor, 260, 10);

    m_sliderBase.LoadFromResource(NULL, AfxGetInstanceHandle(), IDR_SLIDER_BASE, _T("PNG"));
    HBITMAP volSliderBase_ = m_sliderBase.GetHBITMAP();

    m_sliderHighlight.LoadFromResource(NULL, AfxGetInstanceHandle(), IDR_SLIDER_HIGHLIGHT, _T("PNG"));
    HBITMAP volSliderHilite_ = m_sliderHighlight.GetHBITMAP();

    m_sliderLeft.LoadFromResource(NULL, AfxGetInstanceHandle(), IDR_SLIDER_LEFT, _T("PNG"));
    HBITMAP volSliderLeft_ = m_sliderLeft.GetHBITMAP();

    m_sliderMid.LoadFromResource(NULL, AfxGetInstanceHandle(), IDR_SLIDER_MID, _T("PNG"));
    HBITMAP volSliderMid_ = m_sliderMid.GetHBITMAP();

    m_sliderRight.LoadFromResource(NULL, AfxGetInstanceHandle(), IDR_SLIDER_RIGHT, _T("PNG"));
    HBITMAP volSliderRight_ = m_sliderRight.GetHBITMAP();

    m_sliderBase2.LoadFromResource(NULL, AfxGetInstanceHandle(), IDR_SLIDER_BASE_2, _T("PNG"));
    HBITMAP volSliderBase2_ = m_sliderBase2.GetHBITMAP();

    m_sliderHighlight2.LoadFromResource(NULL, AfxGetInstanceHandle(), IDR_SLIDER_HIGHLIGHT_2, _T("PNG"));
    HBITMAP volSliderHilite2_ = m_sliderHighlight2.GetHBITMAP();

    m_progressbar1Color = m_lcd.AddProgressBar(LG_CURSOR);
    m_lcd.SetProgressBarSize(m_progressbar1Color, 200, 10);
    m_lcd.SetProgressBarColors(m_progressbar1Color, RGB(255, 0, 0), RGB(0, 255, 255));
    m_lcd.SetProgressBarBackgroundColor(m_progressbar1Color, RGB(0, 255, 0));
    m_lcd.SetOrigin(m_progressbar1Color, 10, 30);

    m_progressbar2Color = m_lcd.AddProgressBar(LG_FILLED);
    m_lcd.SetProgressBarSize(m_progressbar2Color, 300, 20);
    //m_lcd.SetProgressBarColors(m_progressbar3Color, RGB(255, 0, 0), RGB(0, 255, 255));
    m_lcd.SetProgressBarBackgroundColor(m_progressbar2Color, RGB(0, 0, 255));
    m_lcd.SetOrigin(m_progressbar2Color, 10, 70);

    m_progressbar3Color = m_lcd.AddSkinnedProgressBar(LG_FILLED);
    m_lcd.SetSkinnedProgressBarBackground(m_progressbar3Color, volSliderBase_, 302, 17);
    m_lcd.SetSkinnedProgressBarThreePieceCursor(m_progressbar3Color,
        volSliderLeft_, 8, 17,
        volSliderMid_, 8, 17,
        volSliderRight_, 8, 17);
    m_lcd.SetSkinnedProgressHighlight(m_progressbar3Color, volSliderHilite_, 302, 17);
    m_lcd.SetOrigin(m_progressbar3Color, 9, 110);

    m_progressbar4Color = m_lcd.AddSkinnedProgressBar(LG_CURSOR);
    m_lcd.SetSkinnedProgressBarBackground(m_progressbar4Color, volSliderBase2_, 150, 17);
    m_lcd.SetSkinnedProgressBarThreePieceCursor(m_progressbar4Color,
        volSliderLeft_, 8, 17,
        volSliderMid_, 8, 17,
        volSliderRight_, 8, 17);
    m_lcd.SetSkinnedProgressHighlight(m_progressbar4Color, volSliderHilite2_, 150, 17);
    m_lcd.SetOrigin(m_progressbar4Color, 9, 150);

    m_next2.LoadFromResource(NULL, AfxGetInstanceHandle(), IDR_NEXT, _T("PNG"));
    next_ = m_next2.GetHBITMAP();
    m_rightColor2 = m_lcd.AddBitmap(24, 24);
    m_lcd.SetBitmap(m_rightColor2, next_);
    m_lcd.SetOrigin(m_rightColor2, g_2IconsXPositions[1], g_iconsOriginHeight);

    m_previous2.LoadFromResource(NULL, AfxGetInstanceHandle(), IDR_PREVIOUS, _T("PNG"));
    previous_ = m_previous2.GetHBITMAP();
    m_leftColor2 = m_lcd.AddBitmap(24, 24);
    m_lcd.SetBitmap(m_leftColor2, previous_);
    m_lcd.SetOrigin(m_leftColor2, g_2IconsXPositions[0], g_iconsOriginHeight);

    m_highlight2.LoadFromResource(NULL, AfxGetInstanceHandle(), IDR_HIGHLIGHT, _T("PNG"));
    highlight_ = m_highlight2.GetHBITMAP();
    m_highlightColor2 = m_lcd.AddBitmap(48, 32);
    m_lcd.SetBitmap(m_highlightColor2, highlight_);
    m_lcd.SetOrigin(m_highlightColor2, g_2IconsXPositions[m_currentHighlightPosition] - 12, g_iconsOriginHeight - 4);
}

VOID CColorAndMonoDlg::CheckButtonPresses()
{
    CheckbuttonPressesMonochrome();
    CheckbuttonPressesColor();
}

VOID CColorAndMonoDlg::CheckbuttonPressesMonochrome()
{
    m_lcd.ModifyDisplay(LG_MONOCHROME);

    if (m_lcd.ButtonTriggered(LG_BUTTON_4))
    {
        m_lcd.ShowPage((m_lcd.GetCurrentPageNumber() + 1) % m_lcd.GetPageCount());
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

VOID CColorAndMonoDlg::UpdateProgressBars()
{
    UpdateProgressBarsMonochrome();
    UpdateProgressBarsColor();
}

VOID CColorAndMonoDlg::UpdateProgressBarsMonochrome()
{
    m_lcd.ModifyDisplay(LG_MONOCHROME);

    static INT currentValue_ = 0;

    if (1 == m_lcd.GetCurrentPageNumber())
    {
        m_lcd.SetProgressBarPosition(m_progressbar1, static_cast<FLOAT>(currentValue_ % 100));
        m_lcd.SetProgressBarPosition(m_progressbar2, static_cast<FLOAT>(currentValue_ % 100));
        m_lcd.SetProgressBarPosition(m_progressbar3, static_cast<FLOAT>(currentValue_ % 100));

        ++currentValue_;
    }

}

VOID CColorAndMonoDlg::UpdateProgressBarsColor()
{
    m_lcd.ModifyDisplay(LG_COLOR);

    static INT currentValue_ = 0;

    if (1 == m_lcd.GetCurrentPageNumber())
    {
        m_lcd.SetProgressBarPosition(m_progressbar1Color, static_cast<FLOAT>(currentValue_ % 100));
        m_lcd.SetProgressBarPosition(m_progressbar2Color, static_cast<FLOAT>(currentValue_ % 100));
        m_lcd.SetProgressBarPosition(m_progressbar3Color, static_cast<FLOAT>(currentValue_ % 100));
        m_lcd.SetProgressBarPosition(m_progressbar4Color, static_cast<FLOAT>(currentValue_ % 100));

        ++currentValue_;
    }

}
