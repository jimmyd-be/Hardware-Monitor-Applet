//-----------------------------------------------------------------
// Controller File
// C++ Header - Controller.h - version 0.1 (2014/08/31)
//-----------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "external\QSingleApplication\qtsingleapplication.h"
#include "GUI\mainwindow.h"
#include "Logitech.h"
#include "Screen\StartScreen.h"
#include "Settings.h"


//-----------------------------------------------------------------
// Controller Class
//-----------------------------------------------------------------
class Controller: public QObject
{
	//Q_OBJECT
public:
		
	//---------------------------
	// Constructor(s)
	//---------------------------
	Controller(QtSingleApplication*);

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~Controller();

	//---------------------------
	// General Methods
	//---------------------------
	void openSettingsScreen();

private:

	// -------------------------
	// Datamembers
	// -------------------------
	MainWindow * mainWindow_;
	Logitech * logitech_;
	Settings * settings_;
	QtSingleApplication * app_;


private slots:
	void vMessageReceivedFromOtherInst(const QString &  msg);
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	//Controller(const Controller& t);
	//Controller& operator=(const Controller& t);
};