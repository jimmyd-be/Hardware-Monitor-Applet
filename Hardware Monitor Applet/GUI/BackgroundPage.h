#pragma once

#include "qwizard.h"
#include "qguiapplication.h"
#include "ui_BackgroundPageWidget.h"
#include <QFileDialog>

class BackgroundPage: public QWizardPage
{
	Q_OBJECT

public:
	BackgroundPage(QWidget *parent = 0);
	virtual ~BackgroundPage();

	bool validatePage();

private:
	Ui::BackgroundPageWidget ui;
	QWidget *widget_;
	QVBoxLayout *layout_;

private slots:
	void radioButtonClicked();
	void browseButtonClicked();
};