#pragma once

#include "qwizard.h"
#include "qguiapplication.h"
#include "Ui_LineEditPageWidget.h"
#include "DataPage.h"

class LineEditPage: public QWizardPage
{
	Q_OBJECT

	enum {
		Page_Intro, Page_Type, Page_Data, Page_LineEdit,
		Page_GraphEdit, Page_Customize
	};

public:
	LineEditPage(DataPage* page, QWidget *parent = 0);
	virtual ~LineEditPage();

	bool validatePage();

protected:
	void initializePage();

private:
	Ui::LineEditPageWidget ui;
	QWidget *widget_;
	QVBoxLayout *layout_;

	DataPage * dataPage_;
};