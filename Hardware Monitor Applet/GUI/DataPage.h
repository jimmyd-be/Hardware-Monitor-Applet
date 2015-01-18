#pragma once

#include "qwizard.h"
#include "qguiapplication.h"
#include "ui_DataPageWidget.h"
#include "../Tools/Data.h"
#include "../Defines.h"
#include "ScreenTypePage.h"

class DataPage: public QWizardPage
{
	Q_OBJECT

public:
	DataPage(ScreenTypePage* type, QWidget *parent = 0);
	DataPage(ScreenTypePage* type, QList<LineText>, QWidget *parent = 0);
	virtual ~DataPage();

	bool validatePage();

	QMap<QString, Query> getData();

protected:
	int nextId() const;
	void initializePage();

private:
	void loadSelecteddata(QList<LineText>);
	void loadData(MonitorSystem);
	void clearData(MonitorSystem system);
	bool isUnique(Query);

	QString foundNextSymbol();

	Ui::DataPageWidget ui;
	QWidget *widget_;
	QVBoxLayout *layout_;
	ScreenTypePage *  screenTypePage_;

	private slots:
	void addButtonClicked();
	void removeButtonClicked();
};