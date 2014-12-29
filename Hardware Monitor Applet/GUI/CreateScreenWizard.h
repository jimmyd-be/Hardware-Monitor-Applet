#pragma once

#include "qwizard.h"
#include "IntroPage.h"
#include "ScreenTypePage.h"
#include "DataPage.h"
#include "BackgroundPage.h"
#include "LineEditPage.h"
#include "CustomizePage.h"
#include "GraphPage.h"
#include "../Logitech.h"

class CreateScreenWizard : public QWizard
{
	//Q_OBJECT

public:
	CreateScreenWizard(Logitech *, QWidget *parent = 0);
	virtual ~CreateScreenWizard();

	void accept();

private:
	DataPage *dataPage_;
	LineEditPage * lineEditPage_;
	IntroPage * introPage_;
	BackgroundPage * backgroundPage_;
	ScreenTypePage * screenTypePage_;
	CustomizePage * customizePage_;
	GraphPage * graphPage_;
	Logitech * logitech_;
};