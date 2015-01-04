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
	screenLines_.clear();
}

ScreenType NormalScreen::getScreenType()
{
	return ScreenType::Normal;
}
QList<LineText> NormalScreen::getLines()
{
	return screenLines_;
}

void NormalScreen::setData(QList<LineText> data)
{
	screenLines_ = data;
}

QList<CustomSettings> NormalScreen::getSettings()
{
	return lineSettings_;
}

void NormalScreen::setSettings(QList<CustomSettings> settings)
{
	lineSettings_ = settings;
}

void NormalScreen::drawColor()
{
	lcd_->ModifyControlsOnPage(screenId_);

	lcd_->ModifyDisplay(LG_COLOR);

	lcd_->SetBackground(background_);

	int textPosition = 0;

	for (int i = 0; i < screenLines_.size(); i++)
	{
		CustomSettings custom = lineSettings_[i];

		LGObjectType objectType;
		int aligment;

		if (custom.textScrolling)
		{
			objectType = LG_SCROLLING_TEXT;
		}
		else
		{
			objectType = LG_STATIC_TEXT;
		}

		switch (custom.aligment)
		{
			case Alignment::Center:
				aligment = DT_CENTER; 
				break;
			case Alignment::Left:
				aligment = DT_LEFT;
				break;
			case Alignment::Right:
				aligment = DT_RIGHT;
				break;
			default:
				aligment = DT_LEFT;
				break;
		}

		HANDLE lineHandle = lcd_->AddText(objectType, LG_SMALL, aligment, 320);

		textPosition += custom.lineSpacing;

		if (i > 0)
		{
			textPosition += lineSettings_[i - 1].font.pointSize();
		}

		lcd_->SetOrigin(lineHandle, 0, textPosition);
		lcd_->SetTextFontColor(lineHandle, RGB(custom.fontColor.red(), custom.fontColor.green(), custom.fontColor.blue()));
		//lcd_->SetText(lineHandle, (LPCTSTR)(screenLines_[i].text.toLocal8Bit().constData()));
		lcd_->SetText(lineHandle, _T("TEST"));

		screenLines_[i].textHandle = lineHandle;
	}

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