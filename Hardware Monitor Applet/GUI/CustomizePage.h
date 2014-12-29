#pragma once

#include "qwizard.h"
#include "qguiapplication.h"
#include "ui_CustomizePageWidget.h"
#include "LineEditPage.h"

class CustomizePage: public QWizardPage
{
	Q_OBJECT

public:
	CustomizePage(LineEditPage * page, QWidget *parent = 0);
	virtual ~CustomizePage();

	bool validatePage();

protected:
	void initializePage();

private:
	Ui::CustomizePageWidget ui;
	QWidget *widget_;
	QVBoxLayout *layout_;

	LineEditPage * linePage_;

};