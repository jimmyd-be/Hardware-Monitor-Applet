#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include "../Defines.h"
#include "../Logitech.h"
#include "SortScreenDialog.h"
#include "MainScreenWidget.h"
#include "../Settings.h"
#include "OrderWindow.h"
#include <QDesktopServices>
#include <QScrollArea>
#include "AboutDialog.h"

class Controller;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(Logitech * logitech, Controller * controller, QWidget *parent = 0);
	~MainWindow();

	void keyboardChanged(KeyboardTypes);

	void refreshPages();

protected:
	void closeEvent(QCloseEvent * event);

private:
	void fillinPages();
	void removePages();
	
	Ui::MainWindowClass ui;
	Logitech * logitech_;
	QVector<MainScreenWidget *> widgetList_;
	Controller * controller_;
	QActionGroup * degreeGroup_;
	QScrollArea * scrollArea_;

private slots:
	void openScreenWizard();
	void openOrderWindow();
	void closeProgram();
	void closeWindow();
	void settingsChanged();
	void reportIssue();
	void openAboutWindow();
}; 

#endif // MAINWINDOW_H
