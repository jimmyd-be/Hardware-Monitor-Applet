#pragma once

#include "qwizard.h"
#include "qguiapplication.h"
#include "ui_ScreenTypePageWidget.h"

class ScreenTypePage: public QWizardPage
{
	Q_OBJECT

	enum {
		Page_Intro, Page_Type, Page_Data, Page_LineEdit,
		Page_GraphEdit, Page_Customize
	};

public:
	ScreenTypePage(QWidget *parent = 0);
	virtual ~ScreenTypePage();

private:
	Ui::ScreenTypePageWidget ui;
	QWidget *widget_;
	QVBoxLayout *layout_;

};