//-----------------------------------------------------------------
// StartScreen File
// C++ Header - StartScreen.h - version 0.1 (2013/06/13)
//-----------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Screen.h"

//-----------------------------------------------------------------
// StartScreen Class
//-----------------------------------------------------------------
class StartScreen: public Screen
{
public:
	//---------------------------
	// Constructor(s)
	//---------------------------
	StartScreen(CEzLcd*, QString);

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~StartScreen();

	//---------------------------
	// General Methods
	//---------------------------
	ScreenType getScreenType();
	void update();
	void draw();
	
	void drawColor();
	void drawMonochrome();
	void NormalScreen();

private:
	// -------------------------
	// Datamembers
	// -------------------------

	QList<HANDLE> lineHandles_;
	
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	StartScreen(const StartScreen& t);
	StartScreen& operator=(const StartScreen& t);
};