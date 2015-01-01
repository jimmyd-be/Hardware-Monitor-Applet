#pragma once

#include "qguiapplication.h"
#include "ui_OrderWindow.h"
#include "../Screen.h"
#include "qdialog.h"
#include "../Logitech.h"

class OrderWindow: public QDialog
{
	Q_OBJECT

public:
	OrderWindow(Logitech * logitech, QWidget *parent = 0);
	virtual ~OrderWindow();

private slots:
	void addMainButtonClicked();
	void mainListSelectionChanged();
	void removeMainButtonClicked();
	void leftMainButtonClicked();
	void rightMainButtonClicked();
	void addSubButtonClicked();
	void removeSubButtonClicked();
	void leftSubButtonClicked();
	void rightSubButtonClicked();

private:
	void fillinCreatedScreenList();

	Ui::OrderWindow ui;
	QWidget *widget_;
	Logitech * logitech_;

	QMap<QString, QList<QString>> subOrder_;

};