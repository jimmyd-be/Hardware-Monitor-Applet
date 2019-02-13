#pragma once

#include "qwizard.h"
#include "qguiapplication.h"
#include "ui_BackgroundPageWidget.h"
#include <QFileDialog>
#include "../Defines.h"

class BackgroundPage: public QWizardPage
{
	Q_OBJECT

public:
	BackgroundPage(QWidget *parent = 0);
	BackgroundPage(QString background, QWidget *parent = 0);
	virtual ~BackgroundPage();

	bool validatePage();

	QString getBackground();
	QString getSuffix();

protected:
	int nextId() const;

private:
	Ui::BackgroundPageWidget ui;
	QWidget *widget_;
	QVBoxLayout *layout_;

private slots:
	void radioButtonClicked();
	void browseButtonClicked();
};