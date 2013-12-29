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

	if (lcd_.IsDeviceAvailable(LG_COLOR))
	{
		initLCDObjectsColor();
	}

	else if (lcd_.IsDeviceAvailable(LG_MONOCHROME))
	{
		initLCDObjectsMonochrome();
	}

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

	vector<int> totalLines = settings_->totalLines();
	vector<string> backgrounds = settings_->backgrounds();

	string backgroundPath = settings_->getSettingsPath();
	backgroundPath.append("\\Images\\");

	for (int page = 0; page < settings_->totalPages(); page++)
	{
		if (page > 0)
		{
			lcd_.AddNewPage();
			lcd_.ModifyControlsOnPage(page);
		}

		string backgroundsTemp = backgroundPath;
		backgroundsTemp.append(backgrounds[page]);

		cBitmap tempBackground;
		tempBackground.LoadFromFile(NULL, (LPCTSTR)backgroundsTemp.c_str());
		backgrounds_.push_back(tempBackground);

		HBITMAP bmpBkg_ = tempBackground.GetHBITMAP();
		lcd_.SetBackground(bmpBkg_);

		vector<HANDLE> lines;

		for (int line = 0; line < totalLines[page]; line++)
		{
			HANDLE temp = lcd_.AddText(LG_STATIC_TEXT, LG_MEDIUM, DT_LEFT, 320);
			lcd_.SetOrigin(temp, 0, (line * 17));
			lcd_.SetTextFontColor(temp, RGB(255, 255, 255));
			lcd_.SetText(temp, _T(""));

			lines.push_back(temp);
		}

		textLines_[page] = lines;
	}
}

VOID CColorAndMonoDlg::checkButtonPresses()
{
	if (lcd_.IsDeviceAvailable(LG_COLOR))
	{
		checkbuttonPressesColor();
	}

	else if (lcd_.IsDeviceAvailable(LG_MONOCHROME))
	{
		checkbuttonPressesMonochrome();
	}
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
			currentPage_ = settings_->totalPages() - 1;
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
	if (lcd_.IsDeviceAvailable(LG_COLOR))
	{
		updatePageColor();
	}

	else if (lcd_.IsDeviceAvailable(LG_MONOCHROME))
	{
		updatePageMonochrome();
	}
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
	lcd_.ModifyDisplay(LG_COLOR);

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
