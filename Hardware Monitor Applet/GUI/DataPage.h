#pragma once

#include "qwizard.h"
#include "qguiapplication.h"
#include "ui_DataPageWidget.h"
#include "../Tools/Data.h"
#include "../Defines.h"

class DataPage: public QWizardPage
{
	Q_OBJECT

public:
	DataPage(ScreenType type, QWidget *parent = 0);
	virtual ~DataPage();

	bool validatePage();

	QMap<QString, Query> getData();

protected:
	int nextId() const;

private:
	void loadData(MonitorSystem);
	bool isUnique(Query);
	QString foundNextSymbol();

	ScreenType screenType_;
	Ui::DataPageWidget ui;
	QWidget *widget_;
	QVBoxLayout *layout_;

	private slots:
	void addButtonClicked();
	void removeButtonClicked();
};