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

	HANDLE line1 = lcd_->AddText(LG_STATIC_TEXT, LG_MEDIUM, DT_CENTER, 320);
	lcd_->SetOrigin(line1, 0, 17);
	lcd_->SetTextFontColor(line1, RGB(255, 255, 255));
	lcd_->SetText(line1, _T("Thanks for using"));

	HANDLE line2 = lcd_->AddText(LG_STATIC_TEXT, LG_MEDIUM, DT_CENTER, 320);
	lcd_->SetOrigin(line2, 0, 17 * 3);
	lcd_->SetTextFontColor(line2, RGB(255, 255, 255));
	lcd_->SetText(line2, _T("Hardware Monitor Applet"));

	HANDLE line3 = lcd_->AddText(LG_STATIC_TEXT, LG_MEDIUM, DT_CENTER, 320);
	lcd_->SetOrigin(line3, 0, 17 * 5);
	lcd_->SetTextFontColor(line3, RGB(255, 255, 255));
	lcd_->SetText(line3, _T("Open settings to"));

	HANDLE line4 = lcd_->AddText(LG_STATIC_TEXT, LG_MEDIUM, DT_CENTER, 320);
	lcd_->SetOrigin(line4, 0, 17 * 6);
	lcd_->SetTextFontColor(line4, RGB(255, 255, 255));
	lcd_->SetText(line4, _T("create new screens"));
}

void StartScreen::drawMonochrome()
{
	lcd_->ModifyControlsOnPage(screenPage_);

	lcd_->ModifyDisplay(LG_MONOCHROME);

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

	if (lcd_->IsDeviceAvailable(LG_COLOR))
	{
		lcd_->ModifyDisplay(LG_COLOR);
	}

	else if (lcd_->IsDeviceAvailable(LG_MONOCHROME))
	{
		lcd_->ModifyDisplay(LG_MONOCHROME);
	}
}