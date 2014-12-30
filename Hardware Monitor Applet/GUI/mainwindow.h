#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include "../Defines.h"
#include "../Logitech.h"
#include "SortScreenDialog.h"
#include "MainScreenWidget.h"
#include "../Settings.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(Logitech * logitech, QWidget *parent = 0);
	~MainWindow();

	void keyboardChanged(KeyboardTypes);

	void refreshPages();

private:
	void fillinPages();
	void removePages();

	Ui::MainWindowClass ui;
	Logitech * logitech_;
	QVector<MainScreenWidget *> widgetList_;

private slots:
	void openScreenWizard();

}; 

#endif // MAINWINDOW_H
