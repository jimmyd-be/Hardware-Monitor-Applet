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
NormalScreen::NormalScreen(KeyboardTypes keyboardType, CEzLcd * logitech) : Screen(keyboardType, logitech)
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