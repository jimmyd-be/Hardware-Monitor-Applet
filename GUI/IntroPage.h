#pragma once

#include "qwizard.h"
#include "qguiapplication.h"
#include "ui_IntroPageWidget.h"
#include "../Screen/Screen.h"

class IntroPage: public QWizardPage
{
	Q_OBJECT

public:
	IntroPage(QList<Screen *> screenList, KeyboardTypes type, QWidget *parent = 0);
	IntroPage(QList<Screen *> screenList, KeyboardTypes type, QString name, QWidget *parent = 0);
	virtual ~IntroPage();

	bool validatePage();

	QString getPageName();

protected:
	int nextId() const;
	void copy();
	void cut();

private:
	Ui::IntroPageWidget ui;
	QWidget *widget_;
	QVBoxLayout *layout_;
	QList<Screen *> screenNames_;
	KeyboardTypes keyboardType_;
	QString oldPagename_;
};