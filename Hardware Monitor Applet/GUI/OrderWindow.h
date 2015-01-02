#pragma once

#include "qguiapplication.h"
#include "ui_OrderWindow.h"
#include "../Screen/Screen.h"
#include "qdialog.h"
#include "../Logitech.h"
#include "../Settings.h"

class OrderWindow: public QDialog
{
	Q_OBJECT

public:
	OrderWindow(Logitech * logitech, QWidget *parent = 0);
	virtual ~OrderWindow();

	QList<QString> getMainOrder();
	QMap<QString, QList<QString>> getSubOrder();

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
	void accept();
	void reject();

private:
	void fillinCreatedScreenList();
	void initialize();

	Ui::OrderWindow ui;
	QWidget *widget_;
	Logitech * logitech_;

	QMap<QString, QList<QString>> subOrder_;

	QList<QString> mainOrder_;

};