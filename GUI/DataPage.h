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
	DataPage(ScreenTypePage* type, QList<GraphLine>, QWidget *parent = 0);
	virtual ~DataPage();

	bool validatePage();

	QMap<QString, Query> getData();
	QList<Query> getDataList();

protected:
	int nextId() const;
	void initializePage();

private:
	void makeWindow();
	void loadSelecteddata(QList<LineText>);
	void loadSelecteddata(QList<GraphLine>);
	void loadData(MonitorSystem);
	void clearData(MonitorSystem system);
	bool isUnique(Query, HardwareSensor);
	void insertLineToSelectedData(int row, QString id, QString name, QString system, QString value, QString precision, QString symbol, QString unit, QString unitString, QString hardware);

	QString foundNextSymbol();

	Ui::DataPageWidget ui;
	QWidget *widget_;
	QVBoxLayout *layout_;
	ScreenTypePage *  screenTypePage_;

	private slots:
	void addButtonClicked();
	void removeButtonClicked();
};