#pragma once
#include "../Defines.h"
#include "ui_NormalLineWidget.h"

class NormalScreenWidget;

class LineScreenWidget :
	public QWidget, private Ui_NormalLineWidget
{
	Q_OBJECT

public:
	LineScreenWidget(NormalScreenWidget * widget, QWidget *parent = 0);
	LineScreenWidget(QString text, NormalScreenWidget * widget, QWidget *parent = 0);
	virtual ~LineScreenWidget();

	QString getText();

private:
	NormalScreenWidget * normalScreenWidget_;

private slots:
	void removeLine();
	void textChanged(QString);
};

