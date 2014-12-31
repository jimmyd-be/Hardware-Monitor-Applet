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

protected:

private:
	void fillinCreatedScreenList();

	Ui::OrderWindow ui;
	QWidget *widget_;
	Logitech * logitech_;

};