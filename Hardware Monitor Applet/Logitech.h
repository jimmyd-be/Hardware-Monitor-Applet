//-----------------------------------------------------------------
// Logitech File
// C++ Header - Logitech.h - version 0.1 (2013/06/13)
//-----------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "Defines.h"

#include "StartScreen.h"

//-----------------------------------------------------------------
// Logitech Class
//-----------------------------------------------------------------
class Logitech: public QObject
{
	Q_OBJECT

public:
	//---------------------------
	// Constructor(s)
	//---------------------------
	Logitech();

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~Logitech();

	//---------------------------
	// General Methods
	//---------------------------
	bool initKeyboard();
	KeyboardTypes getKeyboardType();

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
	CEzLcd lcd_;
	QTimer * timer_;
	int time_;
	KeyboardTypes keyboardType_;
	QVector<Screen *> screenList_;
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	Logitech(const Logitech& t);
	Logitech& operator=(const Logitech& t);

	private slots:
	void onTimer();
};