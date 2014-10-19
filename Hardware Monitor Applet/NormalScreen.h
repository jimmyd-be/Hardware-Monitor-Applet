//-----------------------------------------------------------------
// NormalScreen File
// C++ Header - NormalScreen.h - version 0.1 (2013/06/13)
//-----------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Screen.h"

//-----------------------------------------------------------------
// NormalScreen Class
//-----------------------------------------------------------------
class NormalScreen : public Screen
{
public:
	//---------------------------
	// Constructor(s)
	//---------------------------
	NormalScreen(CEzLcd*, QString);

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~NormalScreen();

	//---------------------------
	// General Methods
	//---------------------------
	ScreenType getScreenType();
	void update();

	void drawColor();
	void drawMonochrome();

private:
	// -------------------------
	// Datamembers
	// -------------------------
	
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	NormalScreen(const NormalScreen& t);
	NormalScreen& operator=(const NormalScreen& t);
};