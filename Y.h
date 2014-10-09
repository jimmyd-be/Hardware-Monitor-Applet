//-----------------------------------------------------------------
// Y File
// C++ Header - Y.h - version 0.1 (2013/06/13)
//-----------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "../GameEngine/ObjectDefines.h"

//-----------------------------------------------------------------
// Y Class
//-----------------------------------------------------------------
class Y//: public AbstractGame
{
public:
	//---------------------------
	// Constructor(s)
	//---------------------------
	Y();

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~Y();

	//---------------------------
	// General Methods
	//---------------------------

private:
	// -------------------------
	// Datamembers
	// -------------------------
	
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	Y(const Y& t);
	Y& operator=(const Y& t);
};