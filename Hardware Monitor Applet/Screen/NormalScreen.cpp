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
	lcd_->ModifyControlsOnPage(screenPage_);

	lcd_->ModifyDisplay(LG_COLOR);

	lcd_->SetBackground(background_);

	int textPosition = 0;

	QStringList lines = data_->translateLines(screenLines_);

	for (int i = 0; i < lines.size(); i++)
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

		HANDLE lineHandle = lcd_->AddCustomText(objectType, custom.font.pointSize(), aligment, 320, (LPCTSTR)custom.font.family().utf16(), custom.font.bold());

		textPosition += custom.lineSpacing;

		if (i > 0)
		{
			textPosition += lineSettings_[i - 1].font.pointSize();;
		}

		lcd_->SetOrigin(lineHandle, 0, textPosition);
		lcd_->SetTextFontColor(lineHandle, RGB(custom.fontColor.red(), custom.fontColor.green(), custom.fontColor.blue()));
		lcd_->SetText(lineHandle, (LPCTSTR)lines[i].utf16());

		screenLines_[i].textHandle = lineHandle;
	}
}

void NormalScreen::drawMonochrome()
{
	lcd_->ModifyControlsOnPage(screenPage_);

	lcd_->ModifyDisplay(LG_MONOCHROME);

	int textPosition = 0;

	QStringList lines = data_->translateLines(screenLines_);

	for (int i = 0; i < lines.size(); i++)
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

		HANDLE lineHandle = lcd_->AddCustomText(objectType, custom.font.pointSize(), aligment, 320, (LPCTSTR)custom.font.family().utf16(), custom.font.bold());

		textPosition += custom.lineSpacing;

		if (i > 0)
		{
			textPosition += lineSettings_[i - 1].font.pointSize();;
		}

		lcd_->SetOrigin(lineHandle, 0, textPosition);
		lcd_->SetText(lineHandle, (LPCTSTR)lines[i].utf16());

		screenLines_[i].textHandle = lineHandle;
	}

}

void NormalScreen::draw()
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

	QStringList lines = data_->translateLines(screenLines_);

	if (lcd_->IsDeviceAvailable(LG_COLOR))
	{
		lcd_->ModifyDisplay(LG_COLOR);
	}

	else if (lcd_->IsDeviceAvailable(LG_MONOCHROME))
	{
		lcd_->ModifyDisplay(LG_MONOCHROME);
	}


	for (int i = 0; i < screenLines_.size(); i++)
	{
		lcd_->SetText(screenLines_[i].textHandle, (LPCTSTR)lines[i].utf16());
	}
}

void NormalScreen::update()
{
	
}

void NormalScreen::cleanData()
{

}