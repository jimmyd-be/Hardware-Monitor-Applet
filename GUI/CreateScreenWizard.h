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
#include "../Settings.h"

class CreateScreenWizard : public QWizard
{
	//Q_OBJECT

public:
	CreateScreenWizard(Logitech *, QWidget *parent = 0);
	CreateScreenWizard(Logitech *, QString, QWidget *parent = 0);
	virtual ~CreateScreenWizard();

	void accept();

private:
	void copyBackground();
	void removeBackground(QString);

	Logitech * logitech_;

	QString oldPageName_;
	
	IntroPage * introPage_;
	BackgroundPage * backgroundPage_;
	ScreenTypePage * screenTypePage_;
	DataPage *dataPage_;
	LineEditPage * lineEditPage_;
	GraphPage * graphPage_;
	CustomizePage * customizePage_;
	

	int width_ = 900;
	int height_ = 800;
};