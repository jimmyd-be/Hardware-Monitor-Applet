//-----------------------------------------------------------------
// StartScreen File
// C++ Source - StartScreen.cpp - version 0.1 (2013/06/13)
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "StartScreen.h"

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// StartScreen methods
//-----------------------------------------------------------------
StartScreen::StartScreen(CEzLcd * logitech, QString name) : Screen(logitech, name)
{
}

StartScreen::~StartScreen()
{

}

ScreenType StartScreen::getScreenType()
{
	return ScreenType::Start;
}

void StartScreen::update()
{

}


void StartScreen::drawColor()
{
	lcd_->ModifyControlsOnPage(screenPage_);

	lcd_->ModifyDisplay(LG_COLOR);

	setBackground("");

	HANDLE line1 = lcd_->AddText(LG_STATIC_TEXT, LG_MEDIUM, DT_CENTER, 320, 5);
	lcd_->SetOrigin(line1, 0, 17);
	lcd_->SetTextFontColor(line1, RGB(255, 255, 255));
	lcd_->SetText(line1, (LPCTSTR)QObject::tr("Thanks for using Hardware Monitor Applet.\nOpen settings to create new screens").utf16());
	 
	firstStart_ = false;
}

void StartScreen::drawMonochrome()
{
	lcd_->ModifyControlsOnPage(screenPage_);

	lcd_->ModifyDisplay(LG_MONOCHROME);

	HANDLE line1 = lcd_->AddText(LG_STATIC_TEXT, LG_SMALL, DT_CENTER, 160, 5);
	lcd_->SetOrigin(line1, 0, 0);
	lcd_->SetText(line1, (LPCTSTR)QObject::tr("Thanks for using Hardware Monitor Applet. Open settings to create new screens").utf16());

	firstStart_ = false;
}

void StartScreen::draw()
{
	if (firstStart_)
	{
		if (lcd_->IsDeviceAvailable(LG_COLOR))
		{
			drawColor();
		}

		else if (lcd_->IsDeviceAvailable(LG_MONOCHROME))
		{
			drawMonochrome();
		}
		firstStart_ = false;
	}

	lcd_->ShowPage(screenPage_);
}