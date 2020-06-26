#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include "../Defines.h"
#include "../Logitech.h"
#include "SortScreenDialog.h"
#include "MainScreenWidget.h"
#include "../HwaSettings.h"
#include "OrderWindow.h"
#include <QDesktopServices>
#include <QScrollArea>
#include "AboutDialog.h"
#include <GUI/influxdbdialog.h>


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
    MainWindow(Logitech * logitech, QWidget *parent = 0);
	~MainWindow();

	void keyboardChanged(KeyboardTypes);

protected:
	void closeEvent(QCloseEvent * event);

private:
	void fillinPages();
	void removePages();
	QList<Screen *> sortScreenList(QList<Screen*>);

	Ui::MainWindowClass ui;
	Logitech * logitech_;
	QApplication * qApp_;
	QVector<MainScreenWidget *> widgetList_;
	QActionGroup * degreeGroup_;
	QActionGroup * autoStartGroup_;

public slots:
    void refreshPages();

private slots:
	void openScreenWizard();
	void openOrderWindow();
	void closeProgram();
	void closeWindow();
	void settingsChanged();
	void reportIssue();
	void openAboutWindow();
    void openInfluxDialog();

}; 

#endif // MAINWINDOW_H
