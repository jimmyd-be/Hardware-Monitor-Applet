#pragma once

#include "qwizard.h"
#include "qguiapplication.h"
#include "ui_IntroPageWidget.h"
#include "../Screen/Screen.h"

class IntroPage: public QWizardPage
{
	Q_OBJECT

public:
	IntroPage(QVector<Screen *> screenList, KeyboardTypes type, QWidget *parent = 0);
	IntroPage(QVector<Screen *> screenList, KeyboardTypes type, QString name, QWidget *parent = 0);
	virtual ~IntroPage();

	bool validatePage();

	QString getPageName();

protected:
	int nextId() const;

private:
	Ui::IntroPageWidget ui;
	QWidget *widget_;
	QVBoxLayout *layout_;
	QVector<Screen *> screenNames_;
	KeyboardTypes keyboardType_;
	QString oldPagename_;
};