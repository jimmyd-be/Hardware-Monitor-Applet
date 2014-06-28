//-----------------------------------------------------------------
// MainWindow File
// C++ Header - MainWindow.h - version 0.1 (2014/06/28)
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include <QSettings>
#include <QMainWindow>
#include <QPushButton>
#include <QFileDialog>
#include <qdir.h>
#include <qimage.h>
#include <qfile.h>
#include <QMessageBox>
#include <qfileinfo.h>
#include <QDesktopServices>
#include "tabwidget.h"
#include "WMI.h"
#include <qimage.h>
#include "aboutwindow.h"

namespace Ui {
class MainWindow;
}

//-----------------------------------------------------------------
// MainWindow Class
//-----------------------------------------------------------------

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	//---------------------------
	// Constructor(s)
	//---------------------------
    explicit MainWindow(WMI* wmi, QWidget *parent = 0);

	//---------------------------
	// Destructor
	//---------------------------
    ~MainWindow();

private slots:
//---------------------------
// General Slots
//---------------------------
    void addNewPage();
    void removePage();
	void browseBackground();
	void reportIssue();
	void openAboutWindow();
	void keyboardLayoutChanged(QAbstractButton*);
	void close();

	//---------------------------
	// General Methods
	//---------------------------
	void loadSettings();
	void saveSettings();

private:
	// -------------------------
	// Datamembers
	// -------------------------
    Ui::MainWindow *ui;

    QPushButton* addPageButton;
	WMI * wmi_;

	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	MainWindow(const MainWindow& t);
	MainWindow& operator=(const MainWindow& t);
};

