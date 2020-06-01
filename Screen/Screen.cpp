//-----------------------------------------------------------------
// Screen File
// C++ Source - Screen.cpp - version 0.1 (2013/06/13)
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Screen.h"

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Screen methods
//-----------------------------------------------------------------
#ifdef __linux__
Screen::Screen( QString name) : name_(name), backgroundString_(""), firstStart_(true)
{
    data_ = Data::Instance();
}
#elif _WIN32
Screen::Screen(CEzLcd * logitech, QString name) : lcd_(logitech), background_(nullptr), name_(name), backgroundString_(""), firstStart_(true)
{
    data_ = Data::Instance();

    screenPage_ = lcd_->AddNewPage();
}
#endif

Screen::~Screen()
{
    #ifdef _WIN32
	lcd_->RemovePage(screenPage_);

	if (background_ != nullptr)
	{
		DeleteObject(background_);
		background_ = nullptr;
	}
#endif
}


ScreenType Screen::getScreenType()
{
	return ScreenType::No;
}

void Screen::update()
{
	//Nothing to do
}

void Screen::draw()
{
	//Nothing to do
}

void Screen::cleanData()
{
	//Nothing to do
}

void Screen::openCustomScreen()
{
	//Nothing to do
}

QString Screen::getName()
{
	return name_;
}

void Screen::setBackground(QString background)
{
    #ifdef _WIN32
	lcd_->ModifyControlsOnPage(screenPage_);
	lcd_->ModifyDisplay(LG_COLOR);

	QString backgroundTemp = "";

	if (background.isEmpty())
	{
		backgroundTemp = ":/MainWindow/Resources/Default.png";
	}
	else
	{
		backgroundString_ = background;
		backgroundTemp = Defines::getSettingsFolder() + "/Background/" + background;
	}

	QPixmap backgroundPixMap(backgroundTemp);

	if (!backgroundPixMap.isNull())
	{
		background_ = QtWin::toHBITMAP(backgroundPixMap);

		lcd_->SetBackground(background_);
	}
#endif
}

QString Screen::getBackground()
{
	return backgroundString_;
}

#ifdef _WIN32
CEzLcdPage* Screen::getPage()
{
	return screenPage_;
}
#endif
