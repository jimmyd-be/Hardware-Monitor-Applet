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
	CustomizePage(KeyboardTypes type, LineEditPage * page, QWidget *parent = 0);
	CustomizePage(KeyboardTypes type, LineEditPage * page, QList<CustomSettings> settings, QWidget *parent = 0);
	virtual ~CustomizePage();

	bool validatePage();

	QList<CustomSettings> getData();

protected:
	void initializePage();
	int nextId() const;

private slots:
	void generalSettingsChanged();
	void openFontDialog();
	void openFontColorDialog();
	void alligmentChanged();
	void textScrollingChanged();
	void lineSpaceChanged();

private:
	void initWindow();
	QStringList optimizeLines(QStringList);

	Ui::CustomizePageWidget ui;
	QWidget *widget_;
	QVBoxLayout *layout_;

	QList<CustomizePageLineWidget*> widgetList_;

	LineEditPage * linePage_;

	QList<CustomSettings> tempSettings_;

	KeyboardTypes lcdType_;

};