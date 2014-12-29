#pragma once

#include "qwizard.h"
#include "qguiapplication.h"
#include "ui_CustomizePageWidget.h"
#include "LineEditPage.h"

class CustomizePage: public QWizardPage
{
	Q_OBJECT

	enum {
		Page_Intro, Page_Type, Page_Data, Page_LineEdit,
		Page_GraphEdit, Page_Customize
	};

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