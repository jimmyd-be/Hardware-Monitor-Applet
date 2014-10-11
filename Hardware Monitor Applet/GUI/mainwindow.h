#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include "../Defines.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(KeyboardTypes, QWidget *parent = 0);
	~MainWindow();

	void keyboardChanged(KeyboardTypes);

private:
	Ui::MainWindowClass ui;

	QActionGroup * temperatureActionGroup_;
	QActionGroup * monitorToolActionGroup_;
};

#endif // MAINWINDOW_H
