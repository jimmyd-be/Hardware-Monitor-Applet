#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <external\QSingleApplication\qtsingleapplication.h>
#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include "../Defines.h"
#include "../Logitech.h"
#include "SortScreenDialog.h"
#include "MainScreenWidget.h"
#include "../Settings.h"
#include "OrderWindow.h"
#include <QDesktopServices>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(Logitech * logitech, QtSingleApplication* app, QWidget *parent = 0);
	~MainWindow();

	void keyboardChanged(KeyboardTypes);

	void refreshPages();

private:
	void fillinPages();
	void removePages();
	
	Ui::MainWindowClass ui;
	Logitech * logitech_;
	QVector<MainScreenWidget *> widgetList_;
	QtSingleApplication * app_;

private slots:
	void openScreenWizard();
	void openOrderWindow();
	void closeProgram();
	void closeWindow();
	void settingsChanged();
	void reportIssue();
}; 

#endif // MAINWINDOW_H
