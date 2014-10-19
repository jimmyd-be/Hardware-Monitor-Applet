//-----------------------------------------------------------------
// GraphScreen File
// C++ Source - GraphScreen.cpp - version 0.1 (2013/06/13)
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "GraphScreen.h"

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// GraphScreen methods
//-----------------------------------------------------------------
GraphScreen::GraphScreen(CEzLcd * logitech, QString name) : Screen(logitech, name)
{
	// nothing to create
}

GraphScreen::~GraphScreen()
{
	// nothing to destroy
}

ScreenType GraphScreen::getScreenType()
{
	return ScreenType::Graph;
}