#pragma once

#include "qwizard.h"
#include "qguiapplication.h"
#include "ui_CustomizePageWidget.h"
#include "LineEditPage.h"
#include "CustomizePageLineWidget.h"

class CustomizePage: public QWizardPage
{
	Q_OBJECT

public:
	CustomizePage(LineEditPage * page, QWidget *parent = 0);
	virtual ~CustomizePage();

	bool validatePage();

	QList<CustomSettings> getData();

protected:
	void initializePage();
	int nextId() const;

private:
	QStringList optimizeLines(QStringList);

	Ui::CustomizePageWidget ui;
	QWidget *widget_;
	QVBoxLayout *layout_;

	QList<CustomizePageLineWidget*> widgetList_;

	LineEditPage * linePage_;

};