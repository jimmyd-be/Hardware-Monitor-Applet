//-----------------------------------------------------------------
// AppletThread File
// C++ Header - AppletThread.h - version 0.1 (2013/06/13)
//-----------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <Defines.h>
#include <qthread.h>
#include <Logitech.h>

//-----------------------------------------------------------------
// AppletThread Class
//-----------------------------------------------------------------
class AppletThread: public QThread
{
	Q_OBJECT

public:
	//---------------------------
	// Constructor(s)
	//---------------------------
	AppletThread(CEzLcd* lcd, Logitech * logitech);

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~AppletThread();

	//---------------------------
	// General Methods
	//---------------------------
	void run();

private:
	void initLCDObjectsMonochrome();
	void initLCDObjectsColor();
	void checkButtonPresses();
	void checkbuttonPressesMonochrome();
	void checkbuttonPressesColor();
	void updatePage();

	// -------------------------
	// Datamembers
	// -------------------------
	CEzLcd * lcd_;
	Logitech * logitech_;
	int time_;
	int OkButtonTime_;
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	AppletThread(const AppletThread& t);
	AppletThread& operator=(const AppletThread& t);
};