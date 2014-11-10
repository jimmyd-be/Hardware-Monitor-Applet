//-----------------------------------------------------------------
// Screen File
// C++ Header - Screen.h - version 0.1 (2013/06/13)
//-----------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Defines.h"

//-----------------------------------------------------------------
// Screen Class
//-----------------------------------------------------------------
class Screen
{
public:
	//---------------------------
	// Constructor(s)
	//---------------------------
	Screen(CEzLcd*, QString name);

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~Screen();

	//---------------------------
	// General Methods
	//---------------------------
	virtual ScreenType getScreenType();
	QString getName();
	virtual void update();

	QList<LineText> getLines();
	AppletFont getFont();

	void clearLines();
	void addLine(QString, QMap<QString, Query>);

protected:
	// -------------------------
	// Datamembers
	// -------------------------
	HBITMAP background_;
	QString name_;
	CEzLcd * lcd_;
	int screenId_;
	AppletFont font_;

	QList<LineText> screenLines_;
private:
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	Screen(const Screen& t);
	Screen& operator=(const Screen& t);
};