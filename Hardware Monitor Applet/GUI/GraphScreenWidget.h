#pragma once
#include "../Defines.h"
#include "ui_GraphScreenWidget.h"

class GraphScreenWidget :
	public QWidget, private Ui_GraphScreenWidget
{
	Q_OBJECT

public:
	GraphScreenWidget(QString name, QWidget *parent = 0);
	virtual ~GraphScreenWidget();
private:
	QString name_;
};

