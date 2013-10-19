//-----------------------------------------------------------------
// Error File
// C++ Header - Error.h - version 0.1 (2013/06/13)
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include <string>
#include <stdlib.h>
#include <stdio.h> 
#include <iostream>
#include <fstream>
#include <time.h>
#include <Shlobj.h>
#include <direct.h>
#include "stdafx.h"

using namespace std;
//-----------------------------------------------------------------
// Error Class
//-----------------------------------------------------------------
class Error
{
public:
	//---------------------------
	// Constructor(s)
	//---------------------------
	Error();	//Dot not make a instance of this class (use the static void writeMessage(string message) method

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~Error();

	//---------------------------
	// General Methods
	//---------------------------
	static void writeMessage(string message);
	static string getCurrentTime();

private:
	// -------------------------
	// Datamembers
	// -------------------------

	wstring getHomePath();


	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	Error(const Error& t);
	Error& operator=(const Error& t);
};