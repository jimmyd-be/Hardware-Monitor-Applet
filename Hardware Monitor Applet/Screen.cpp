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
Screen::Screen(KeyboardTypes keyboardType, CEzLcd * logitech) : keyboardType_(keyboardType), lcd_(logitech), background_(nullptr)
{
	screenId_ = lcd_->AddNewPage();
}

Screen::~Screen()
{
	lcd_->RemovePage(screenId_);

	if (background_ != nullptr)
	{
		DeleteObject(background_);
		background_ = nullptr;
	}

	/*for (int i = 0; i < lineHandles_.size(); i++)
	{
		CloseHandle(lineHandles_[i]);
	}*/

	screenLines_.clear();
}

ScreenType Screen::getScreenType()
{
	return ScreenType::No;
}

void Screen::update()
{
	//Nothing to do
}