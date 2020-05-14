#pragma once

#include "qwizard.h"
#include "qguiapplication.h"
#include "ui_CustomizePageLineWidget.h"
#include "../Screen\Screen.h"
#include "../Defines.h"
#include <QFontDialog>
#include <qcolordialog.h>

class CustomizePageLineWidget: public QWidget
{
	Q_OBJECT

public:
	CustomizePageLineWidget(KeyboardTypes type, QString text, QWidget *parent = 0);
	CustomizePageLineWidget(KeyboardTypes type, QString text, CustomSettings custom, QWidget *parent = 0);
	virtual ~CustomizePageLineWidget();

	CustomSettings getSettings();

	void setEnabled(bool);
	void setFont(QFont);
	void setColor(QColor);
	void setAlligment(QString);
	void setTextScrolling(bool);
	void setLineSpace(int);

	QColor getColor();
	QFont getFont();
	QString getAlligment();
	bool getTextScrolling();
	int getLineSpace();

private slots:
	void openFontDialog();
	void openFontColorDialog();

private:

	Ui::CustomizePageLineWidget ui;
	QFont font_;
	QColor color_;
	QPalette palette_;
};