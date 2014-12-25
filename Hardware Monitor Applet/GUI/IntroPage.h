#pragma once

#include "qwizard.h"
#include "qguiapplication.h"
#include "ui_IntroPageWidget.h"

class IntroPage: public QWizardPage
{
	Q_OBJECT

	enum {
		Page_Intro, Page_Type, Page_Data, Page_LineEdit,
		Page_GraphEdit, Page_Customize
	};

public:
	IntroPage(QWidget *parent = 0);
	virtual ~IntroPage();

	bool validatePage();

private:
	Ui::IntroPageWidget ui;
	QWidget *widget_;
	QVBoxLayout *layout_;

};