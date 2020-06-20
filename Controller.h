//-----------------------------------------------------------------
// Controller File
// C++ Header - Controller.h - version 0.1 (2014/08/31)
//-----------------------------------------------------------------
#ifndef CONTROLLER_H
#define CONTROLLER_H

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <external/QSingleApplication/SingleApplication.h>
#include "GUI/mainwindow.h"
#include "Logitech.h"
#include "Screen/StartScreen.h"
#include "HwaSettings.h"


//-----------------------------------------------------------------
// Controller Class
//-----------------------------------------------------------------
class Controller: public QObject
{
	Q_OBJECT
public:
		
	//---------------------------
	// Constructor(s)
	//---------------------------
	Controller(QApplication*, SingleApplication*);

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~Controller();

	//---------------------------
	// General Methods
	//---------------------------
	void openSettingsScreen();
	void closeSettingsScreen();
	void quitApplication();

private:

	// -------------------------
	// Datamembers
	// -------------------------
    MainWindow * mainWindow_;
	Logitech * logitech_;
	HwaSettings * settings_;
	QApplication * app_;
	SingleApplication * singleApp_;


protected slots:
	void messageReceivedFromOtherInst(QString);
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	//Controller(const Controller& t);
	//Controller& operator=(const Controller& t);
};
#endif
