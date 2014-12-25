#pragma once

#include "qwizard.h"
#include "IntroPage.h"
#include "ScreenTypePage.h"
#include "DataPage.h"


class CreateScreenWizard : public QWizard
{
	//Q_OBJECT

	enum {
		Page_Intro, Page_Type, Page_Background, Page_Data, Page_LineEdit,
		Page_GraphEdit, Page_Customize
	};

public:
	CreateScreenWizard(QWidget *parent = 0);
	virtual ~CreateScreenWizard();

	//void accept();
};