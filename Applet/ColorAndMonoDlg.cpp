//-----------------------------------------------------------------
// CColorAndMonoDlg Object
// C++ Source - CColorAndMonoDlg.cpp - version v3.0 (2013-12-29)
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "stdafx.h"
#include "ColorAndMono.h"
#include "ColorAndMonoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CColorAndMonoDlg dialog

INT g_2IconsXPositions[2] = { 106, 190 };
INT g_iconsOriginHeight = 196;

//-----------------------------------------------------------------
// CColorAndMonoDlg methods
//-----------------------------------------------------------------

CColorAndMonoDlg::CColorAndMonoDlg(CWnd* pParent /*=NULL*/)
: CDialog(CColorAndMonoDlg::IDD, pParent), settings_(nullptr), textLines_(0), currentPage_(0), wmi_(nullptr), time_(0)
{
	icon_ = AfxGetApp()->LoadIcon(LOGO);

	settings_ = new Settings();
	wmi_ = new WMI();

	if (settings_->totalPages() > 0)
	{
		textLines_ = new vector<HANDLE>[settings_->totalPages()];
	}
}

void CColorAndMonoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CColorAndMonoDlg, CDialog)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()


BOOL CColorAndMonoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(icon_, TRUE);			// Set big icon
	SetIcon(icon_, FALSE);		// Set small icon

	ShowWindow(SW_HIDE);
	SetWindowPos(NULL, 0, 0, 0, 0, NULL);

	HRESULT hRes = lcd_.Initialize(_T("Open Hardware Monitor"), LG_DUAL_MODE, TRUE, TRUE);

	if (hRes != S_OK)
	{
		// Something went wrong, when connecting to the LCD Manager software. Deal with it...
		PostQuitMessage(0);
		return FALSE;
	}

	initLCDObjectsMonochrome();
	initLCDObjectsColor();

	SetTimer(0xabab, 30, NULL); // for scrolling to work smoothly, timer should be pretty fast

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CColorAndMonoDlg::OnDestroy()
{
	if (settings_ != nullptr)
	{
		delete settings_;
		settings_ = nullptr;
	}

	if (textLines_ != 0)
	{
		delete textLines_;
		textLines_ = 0;
	}
}

void CColorAndMonoDlg::OnTimer(UINT_PTR nIDEvent)
{
	UNREFERENCED_PARAMETER(nIDEvent);

	time_ += 30;

	checkButtonPresses();

	if (time_ >= 1000)
	{
		updatePage();
		time_ = 0;
	}

	lcd_.Update();

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

VOID CColorAndMonoDlg::initLCDObjectsMonochrome()
{
	lcd_.ModifyDisplay(LG_MONOCHROME);

	vector<int> totalLines = settings_->totalLines();

	for (int page = 0; page < settings_->totalPages(); page++)
	{
		if (page > 0)
		{
			lcd_.AddNewPage();
			lcd_.ModifyControlsOnPage(page);
		}

		vector<HANDLE> lines;

		for (int line = 0; line < totalLines[page]; line++)
		{
			HANDLE temp = lcd_.AddText(LG_STATIC_TEXT, LG_SMALL, DT_LEFT, 160);
			lcd_.SetOrigin(temp, 0, -1 + (7 * line));
			lcd_.SetText(temp, _T(""));

			lines.push_back(temp);
		}

		textLines_[page] = lines;
	}
}

VOID CColorAndMonoDlg::initLCDObjectsColor()
{
	lcd_.ModifyDisplay(LG_COLOR);

	/***************/
	/* FIRST PAGE */
	/***************/
	//m_background.LoadFromResource(NULL, AfxGetInstanceHandle(), IDR_BACKGROUND, _T("PNG"));
	//HBITMAP bmpBkg_ = m_background.GetHBITMAP();
	//m_lcd.SetBackground(bmpBkg_);

	//m_tinyTextColor1 = m_lcd.AddText(LG_SCROLLING_TEXT, LG_TINY, DT_LEFT, 140);
	//m_lcd.SetOrigin(m_tinyTextColor1, 10, 10);
	//m_lcd.SetText(m_tinyTextColor1, _T("Tiny text is scrolling all the time and all over the place..."));
	//m_lcd.SetTextFontColor(m_tinyTextColor1, RGB(255, 0, 0));

	//m_tinyTextColor2 = m_lcd.AddText(LG_SCROLLING_TEXT, LG_TINY, DT_LEFT, 140, 1, FW_HEAVY);
	//m_lcd.SetOrigin(m_tinyTextColor2, 170, 10);
	//m_lcd.SetText(m_tinyTextColor2, _T("Tiny text is scrolling with a heavy font..."));
	//m_lcd.SetTextFontColor(m_tinyTextColor2, RGB(0, 255, 0));
	//m_lcd.SetTextBackground(m_tinyTextColor2, OPAQUE, RGB(0, 0, 255));

	//m_smallTextColor = m_lcd.AddText(LG_SCROLLING_TEXT, LG_SMALL, DT_CENTER, LGLCD_QVGA_BMP_WIDTH);
	//m_lcd.SetOrigin(m_smallTextColor, 0, 40);
	//m_lcd.SetText(m_smallTextColor, _T("Small text is centered"));
	//m_lcd.SetTextFontColor(m_smallTextColor, RGB(0, 0, 0));

	//m_mediumTextColor = m_lcd.AddText(LG_STATIC_TEXT, LG_MEDIUM, DT_CENTER, LGLCD_QVGA_BMP_WIDTH, 3);
	//m_lcd.SetOrigin(m_mediumTextColor, 0, 70);
	//m_lcd.SetText(m_mediumTextColor, _T("Medium text has muliple lines so we can write a lot of stuff in just one string."));
	//m_lcd.SetTextFontColor(m_mediumTextColor, RGB(0, 0, 255));

	//m_bigTextColor = m_lcd.AddText(LG_SCROLLING_TEXT, LG_BIG, DT_CENTER, LGLCD_QVGA_BMP_WIDTH, 1, FW_HEAVY);
	//m_lcd.SetOrigin(m_bigTextColor, 0, 150);
	//m_lcd.SetText(m_bigTextColor, _T("BIG text has a gray background"));
	//m_lcd.SetTextFontColor(m_bigTextColor, RGB(150, 150, 150));
	//m_lcd.SetTextBackground(m_bigTextColor, OPAQUE, RGB(200, 200, 200));

	//m_next.LoadFromResource(NULL, AfxGetInstanceHandle(), IDR_NEXT, _T("PNG"));
	//HBITMAP next_ = m_next.GetHBITMAP();
	//m_rightColor1 = m_lcd.AddBitmap(24, 24);
	//m_lcd.SetBitmap(m_rightColor1, next_);
	//m_lcd.SetOrigin(m_rightColor1, g_2IconsXPositions[1], g_iconsOriginHeight);

	//m_previous.LoadFromResource(NULL, AfxGetInstanceHandle(), IDR_PREVIOUS, _T("PNG"));
	//HBITMAP previous_ = m_previous.GetHBITMAP();
	//m_leftColor1 = m_lcd.AddBitmap(24, 24);
	//m_lcd.SetBitmap(m_leftColor1, previous_);
	//m_lcd.SetOrigin(m_leftColor1, g_2IconsXPositions[0], g_iconsOriginHeight);

	//m_highlight.LoadFromResource(NULL, AfxGetInstanceHandle(), IDR_HIGHLIGHT, _T("PNG"));
	//HBITMAP highlight_ = m_highlight.GetHBITMAP();
	//m_highlightColor1 = m_lcd.AddBitmap(48, 32);
	//m_lcd.SetBitmap(m_highlightColor1, highlight_);
	//m_lcd.SetOrigin(m_highlightColor1, g_2IconsXPositions[m_currentHighlightPosition] - 12, g_iconsOriginHeight - 4);

	///***************/
	///* SECOND PAGE */
	///***************/
	//m_lcd.AddNewPage();
	//m_lcd.ModifyControlsOnPage(1);

	//m_lcd.SetBackground(RGB(160, 180, 200));

	//m_logoSmall.LoadFromResource(NULL, AfxGetInstanceHandle(), IDR_LOGO_SMALL, _T("PNG"));
	//HBITMAP logoSmall_ = m_logoSmall.GetHBITMAP();
	//m_logoColor = m_lcd.AddBitmap(50, 44);
	//m_lcd.SetBitmap(m_logoColor, logoSmall_);
	//m_lcd.SetOrigin(m_logoColor, 260, 10);

	//m_sliderBase.LoadFromResource(NULL, AfxGetInstanceHandle(), IDR_SLIDER_BASE, _T("PNG"));
	//HBITMAP volSliderBase_ = m_sliderBase.GetHBITMAP();

	//m_sliderHighlight.LoadFromResource(NULL, AfxGetInstanceHandle(), IDR_SLIDER_HIGHLIGHT, _T("PNG"));
	//HBITMAP volSliderHilite_ = m_sliderHighlight.GetHBITMAP();

	//m_sliderLeft.LoadFromResource(NULL, AfxGetInstanceHandle(), IDR_SLIDER_LEFT, _T("PNG"));
	//HBITMAP volSliderLeft_ = m_sliderLeft.GetHBITMAP();

	//m_sliderMid.LoadFromResource(NULL, AfxGetInstanceHandle(), IDR_SLIDER_MID, _T("PNG"));
	//HBITMAP volSliderMid_ = m_sliderMid.GetHBITMAP();

	//m_sliderRight.LoadFromResource(NULL, AfxGetInstanceHandle(), IDR_SLIDER_RIGHT, _T("PNG"));
	//HBITMAP volSliderRight_ = m_sliderRight.GetHBITMAP();

	//m_sliderBase2.LoadFromResource(NULL, AfxGetInstanceHandle(), IDR_SLIDER_BASE_2, _T("PNG"));
	//HBITMAP volSliderBase2_ = m_sliderBase2.GetHBITMAP();

	//m_sliderHighlight2.LoadFromResource(NULL, AfxGetInstanceHandle(), IDR_SLIDER_HIGHLIGHT_2, _T("PNG"));
	//HBITMAP volSliderHilite2_ = m_sliderHighlight2.GetHBITMAP();

	//m_progressbar1Color = m_lcd.AddProgressBar(LG_CURSOR);
	//m_lcd.SetProgressBarSize(m_progressbar1Color, 200, 10);
	//m_lcd.SetProgressBarColors(m_progressbar1Color, RGB(255, 0, 0), RGB(0, 255, 255));
	//m_lcd.SetProgressBarBackgroundColor(m_progressbar1Color, RGB(0, 255, 0));
	//m_lcd.SetOrigin(m_progressbar1Color, 10, 30);

	//m_progressbar2Color = m_lcd.AddProgressBar(LG_FILLED);
	//m_lcd.SetProgressBarSize(m_progressbar2Color, 300, 20);
	////m_lcd.SetProgressBarColors(m_progressbar3Color, RGB(255, 0, 0), RGB(0, 255, 255));
	//m_lcd.SetProgressBarBackgroundColor(m_progressbar2Color, RGB(0, 0, 255));
	//m_lcd.SetOrigin(m_progressbar2Color, 10, 70);

	//m_progressbar3Color = m_lcd.AddSkinnedProgressBar(LG_FILLED);
	//m_lcd.SetSkinnedProgressBarBackground(m_progressbar3Color, volSliderBase_, 302, 17);
	//m_lcd.SetSkinnedProgressBarThreePieceCursor(m_progressbar3Color,
	//    volSliderLeft_, 8, 17,
	//    volSliderMid_, 8, 17,
	//    volSliderRight_, 8, 17);
	//m_lcd.SetSkinnedProgressHighlight(m_progressbar3Color, volSliderHilite_, 302, 17);
	//m_lcd.SetOrigin(m_progressbar3Color, 9, 110);

	//m_progressbar4Color = m_lcd.AddSkinnedProgressBar(LG_CURSOR);
	//m_lcd.SetSkinnedProgressBarBackground(m_progressbar4Color, volSliderBase2_, 150, 17);
	//m_lcd.SetSkinnedProgressBarThreePieceCursor(m_progressbar4Color,
	//    volSliderLeft_, 8, 17,
	//    volSliderMid_, 8, 17,
	//    volSliderRight_, 8, 17);
	//m_lcd.SetSkinnedProgressHighlight(m_progressbar4Color, volSliderHilite2_, 150, 17);
	//m_lcd.SetOrigin(m_progressbar4Color, 9, 150);

	//m_next2.LoadFromResource(NULL, AfxGetInstanceHandle(), IDR_NEXT, _T("PNG"));
	//next_ = m_next2.GetHBITMAP();
	//m_rightColor2 = m_lcd.AddBitmap(24, 24);
	//m_lcd.SetBitmap(m_rightColor2, next_);
	//m_lcd.SetOrigin(m_rightColor2, g_2IconsXPositions[1], g_iconsOriginHeight);

	//m_previous2.LoadFromResource(NULL, AfxGetInstanceHandle(), IDR_PREVIOUS, _T("PNG"));
	//previous_ = m_previous2.GetHBITMAP();
	//m_leftColor2 = m_lcd.AddBitmap(24, 24);
	//m_lcd.SetBitmap(m_leftColor2, previous_);
	//m_lcd.SetOrigin(m_leftColor2, g_2IconsXPositions[0], g_iconsOriginHeight);

	//m_highlight2.LoadFromResource(NULL, AfxGetInstanceHandle(), IDR_HIGHLIGHT, _T("PNG"));
	//highlight_ = m_highlight2.GetHBITMAP();
	//m_highlightColor2 = m_lcd.AddBitmap(48, 32);
	//m_lcd.SetBitmap(m_highlightColor2, highlight_);
	//m_lcd.SetOrigin(m_highlightColor2, g_2IconsXPositions[m_currentHighlightPosition] - 12, g_iconsOriginHeight - 4);
}

VOID CColorAndMonoDlg::checkButtonPresses()
{
	checkbuttonPressesMonochrome();
	checkbuttonPressesColor();
}

VOID CColorAndMonoDlg::checkbuttonPressesMonochrome()
{
	lcd_.ModifyDisplay(LG_MONOCHROME);

	if (lcd_.ButtonTriggered(LG_BUTTON_4))
	{
		currentPage_++;

		if (currentPage_ >= settings_->totalPages())
		{
			currentPage_ = 0;
		}
		lcd_.ShowPage(currentPage_);
	}

	else if (lcd_.ButtonTriggered(LG_BUTTON_1))
	{
		currentPage_--;

		if (currentPage_ < 0)
		{
			currentPage_ = settings_->totalPages()-1;
		}
		lcd_.ShowPage(currentPage_);
	}
}

VOID CColorAndMonoDlg::checkbuttonPressesColor()
{
	 lcd_.ModifyDisplay(LG_COLOR);

	 if (lcd_.ButtonTriggered(LG_BUTTON_RIGHT))
	 {
		 currentPage_++;

		 if (currentPage_ >= settings_->totalPages())
		 {
			 currentPage_ = 0;
		 }
		 lcd_.ShowPage(currentPage_);
	 }

	 else if (lcd_.ButtonTriggered(LG_BUTTON_LEFT))
	 {
		 currentPage_--;

		 if (currentPage_ < 0)
		 {
			 currentPage_ = settings_->totalPages() - 1;
		 }
		 lcd_.ShowPage(currentPage_);
	 }
}

VOID CColorAndMonoDlg::updatePage()
{
	updatePageMonochrome();
	updatePageColor();
}

VOID CColorAndMonoDlg::updatePageMonochrome()
{
	lcd_.ModifyDisplay(LG_MONOCHROME);

	vector<string*> lines = settings_->lines();

	string * lineText = lines[currentPage_];
	int totalLines = settings_->totalLines()[currentPage_];

	vector<HANDLE> handelers = textLines_[currentPage_];

	for (int i = 0; i < totalLines; i++)
	{
		string temp = wmi_->convertLine(lineText[i]);
		wstring ws;
		ws.assign(temp.begin(), temp.end());
		lcd_.SetText(handelers[i], ws.c_str());
		ws.clear();
	}
}

VOID CColorAndMonoDlg::updatePageColor()
{
	/*  m_lcd.ModifyDisplay(LG_COLOR);

	  static INT currentValue_ = 0;

	  if (1 == m_lcd.GetCurrentPageNumber())
	  {
	  m_lcd.SetProgressBarPosition(m_progressbar1Color, static_cast<FLOAT>(currentValue_ % 100));
	  m_lcd.SetProgressBarPosition(m_progressbar2Color, static_cast<FLOAT>(currentValue_ % 100));
	  m_lcd.SetProgressBarPosition(m_progressbar3Color, static_cast<FLOAT>(currentValue_ % 100));
	  m_lcd.SetProgressBarPosition(m_progressbar4Color, static_cast<FLOAT>(currentValue_ % 100));

	  ++currentValue_;
	  }*/

}
