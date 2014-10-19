//-----------------------------------------------------------------
// GraphScreen File
// C++ Header - GraphScreen.h - version 0.1 (2013/06/13)
//-----------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Screen.h"

//-----------------------------------------------------------------
// GraphScreen Class
//-----------------------------------------------------------------
class GraphScreen : public Screen
{
public:
	//---------------------------
	// Constructor(s)
	//---------------------------
	GraphScreen(CEzLcd *, QString);

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~GraphScreen();

	//---------------------------
	// General Methods
	//---------------------------
	ScreenType getScreenType();

private:
	// -------------------------
	// Datamembers
	// -------------------------
	
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	GraphScreen(const GraphScreen& t);
	GraphScreen& operator=(const GraphScreen& t);
};