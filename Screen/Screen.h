//-----------------------------------------------------------------
// Screen File
// C++ Header - Screen.h - version 0.1 (2013/06/13)
//-----------------------------------------------------------------
#ifndef SCREEN_H
#define SCREEN_H

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Defines.h"
#include "../Tools/Data.h"

//-----------------------------------------------------------------
// Screen Class
//-----------------------------------------------------------------
class Screen
{
public:
	//---------------------------
	// Constructor(s)
	//---------------------------

#ifdef __linux__
    Screen(QString name);
#elif _WIN32
    Screen(CEzLcd*, QString name);

#endif

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
	virtual void draw();
	virtual void cleanData();
	virtual void openCustomScreen();

	virtual void setBackground(QString background);
#ifdef _WIN32
	CEzLcdPage* getPage();
#endif

	QString getBackground();

protected:
	// -------------------------
	// Datamembers
    // -------------------------

#ifdef _WIN32
    CEzLcd * lcd_;
    HBITMAP background_;
    CEzLcdPage* screenPage_;
#endif

	QString name_;
	QString backgroundString_;
	bool firstStart_;
	Data * data_;

private:
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	Screen(const Screen& t);
	Screen& operator=(const Screen& t);
};
#endif
