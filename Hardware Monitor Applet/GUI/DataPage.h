#pragma once

#include "qwizard.h"
#include "qguiapplication.h"
#include "ui_DataPageWidget.h"
#include "../Tools/Data.h"
#include "../Defines.h"

class DataPage: public QWizardPage
{
	Q_OBJECT

	enum {
		Page_Intro, Page_Type, Page_Data, Page_LineEdit,
		Page_GraphEdit, Page_Customize
	};

public:
	DataPage(QWidget *parent = 0);
	virtual ~DataPage();

	bool validatePage();

	QMap<QString, Query> getData();

private:
	void loadData(MonitorSystem);
	bool isUnique(Query);
	QString foundNextSymbol();


	Ui::DataPageWidget ui;
	QWidget *widget_;
	QVBoxLayout *layout_;

	private slots:
	void addButtonClicked();
	void removeButtonClicked();
};