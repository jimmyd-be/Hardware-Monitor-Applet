#ifndef DATAPAGE_H
#define DATAPAGE_H

#include "qwizard.h"
#include "qguiapplication.h"
#include "ui_DataPageWidget.h"
#include "../Tools/Data.h"
#include "../Defines.h"
#include "ScreenTypePage.h"
#include <QComboBox>

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
    void insertLineToSelectedData(int row, QString id, QString name, QString system, QString value, QString precision, QString symbol, QString unitString, QString hardware, QString field);

	QString foundNextSymbol();

	Ui::DataPageWidget ui;
	QWidget *widget_;
	QVBoxLayout *layout_;
	ScreenTypePage *  screenTypePage_;
    QVector<Query> data;

    void addLineToWidget(QTableWidget* tableWidget, QString system, int newRow, QList<QTableWidgetItem*> selectedItems);

private slots:
	void addButtonClicked();
	void removeButtonClicked();
};
#endif
