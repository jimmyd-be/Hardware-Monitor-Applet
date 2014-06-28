//-----------------------------------------------------------------
// AboutWindow File
// C++ Header - AboutWindow.h - version 0.1 (2014/06/28)
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include <QDialog>

namespace Ui {
class AboutWindow;
}

//-----------------------------------------------------------------
// AboutWindow Class
//-----------------------------------------------------------------
class AboutWindow : public QDialog
{
    Q_OBJECT

public:
	//---------------------------
	// Constructor(s)
	//---------------------------
    explicit AboutWindow(QWidget *parent = 0);

	//---------------------------
	// Destructor
	//---------------------------
    ~AboutWindow();

	//---------------------------
	// General Methods
	//---------------------------

	//---------------------------
	// General Slots
	//---------------------------

private:
	// -------------------------
	// Datamembers
	// -------------------------
    Ui::AboutWindow *ui;

	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	AboutWindow(const AboutWindow& t);
	AboutWindow& operator=(const AboutWindow& t);
};
