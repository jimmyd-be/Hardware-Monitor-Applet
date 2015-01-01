#pragma once

#include "qwizard.h"
#include "qguiapplication.h"
#include "ui_CustomizePageLineWidget.h"
#include "../Screen.h"
#include "../Defines.h"
#include <QFontDialog>

class CustomizePageLineWidget: public QWidget
{
	Q_OBJECT

public:
	CustomizePageLineWidget(QString text, QWidget *parent = 0);
	virtual ~CustomizePageLineWidget();

	CustomSettings getSettings();

private slots:
	void openFontDialog();

private:

	Ui::CustomizePageLineWidget ui;
	QFont font_;
};