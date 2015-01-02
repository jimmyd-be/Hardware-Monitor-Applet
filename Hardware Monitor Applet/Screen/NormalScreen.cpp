//-----------------------------------------------------------------
// NormalScreen File
// C++ Source - NormalScreen.cpp - version 0.1 (2013/06/13)
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "NormalScreen.h"

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// NormalScreen methods
//-----------------------------------------------------------------
NormalScreen::NormalScreen(CEzLcd * logitech, QString name) : Screen(logitech, name)
{
	// nothing to create
}

NormalScreen::~NormalScreen()
{
	// nothing to destroy
}

ScreenType NormalScreen::getScreenType()
{
	return ScreenType::Normal;
}

void NormalScreen::drawColor()
{
	lcd_->ModifyControlsOnPage(screenId_);

	lcd_->ModifyDisplay(LG_COLOR);

	QPixmap background;

	bool success = background.load(":/MainWindow/Default");

	if (success)
	{
		background_ = QtWin::toHBITMAP(background);

		lcd_->SetBackground(background_);
	}

	HANDLE line1 = lcd_->AddText(LG_STATIC_TEXT, LG_MEDIUM, DT_CENTER, 320);
	lcd_->SetOrigin(line1, 0, 17);
	lcd_->SetTextFontColor(line1, RGB(255, 255, 255));
	lcd_->SetText(line1, _T("xxxxxxxxxxxxxxxxxxxxx"));

	HANDLE line2 = lcd_->AddText(LG_STATIC_TEXT, LG_MEDIUM, DT_CENTER, 320);
	lcd_->SetOrigin(line2, 0, 17 * 3);
	lcd_->SetTextFontColor(line2, RGB(255, 255, 255));
	lcd_->SetText(line2, _T("Open settings or"));

	HANDLE line3 = lcd_->AddText(LG_STATIC_TEXT, LG_MEDIUM, DT_CENTER, 320);
	lcd_->SetOrigin(line3, 0, 17 * 5);
	lcd_->SetTextFontColor(line3, RGB(255, 255, 255));
	lcd_->SetText(line3, _T("Press any Logitech key to"));

	HANDLE line4 = lcd_->AddText(LG_STATIC_TEXT, LG_MEDIUM, DT_CENTER, 320);
	lcd_->SetOrigin(line4, 0, 17 * 6);
	lcd_->SetTextFontColor(line4, RGB(255, 255, 255));
	lcd_->SetText(line4, _T("open settings"));

}

void NormalScreen::drawMonochrome()
{
	lcd_->ModifyControlsOnPage(screenId_);

	lcd_->ModifyDisplay(LG_MONOCHROME);

}

void NormalScreen::draw()
{
	drawColor();
}

void NormalScreen::update()
{
	
}