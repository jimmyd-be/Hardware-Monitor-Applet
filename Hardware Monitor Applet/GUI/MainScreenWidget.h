#pragma once
#include "../Defines.h"
#include "ui_MainScreenWidget.h"
#include "../Logitech.h"

#include "CreateScreenWizard.h"

class MainScreenWidget :
	public QWidget, private Ui_MainScreenWidget
{
	Q_OBJECT

public:
	MainScreenWidget(QWidget *parent = 0);
	virtual ~MainScreenWidget();

private slots:
	

private:
	
};

