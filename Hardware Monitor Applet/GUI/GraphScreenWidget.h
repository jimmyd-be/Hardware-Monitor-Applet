#pragma once
#include "../Defines.h"
#include "ui_GraphScreenWidget.h"

class GraphScreenWidget :
	public QWidget, private Ui_GraphScreenWidget
{
	Q_OBJECT

public:
	GraphScreenWidget(QWidget *parent = 0);
	virtual ~GraphScreenWidget();
};

