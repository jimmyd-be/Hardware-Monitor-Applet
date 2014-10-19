//-----------------------------------------------------------------
// Tool File
// C++ Header - Tool.h - version 0.1 (2013/06/13)
//-----------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "../Defines.h"

//-----------------------------------------------------------------
// Tool Class
//-----------------------------------------------------------------
class Tool
{
public:
	//---------------------------
	// Constructor(s)
	//---------------------------
	Tool();

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~Tool();

	//---------------------------
	// General Methods
	//---------------------------
	virtual QVector<HardwareSensor> getAllSensors();

private:
	// -------------------------
	// Datamembers
	// -------------------------
	
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	Tool(const Tool& t);
	Tool& operator=(const Tool& t);
};