#pragma once
#include "Defines.h"
#include "qdialog.h"
#include "Screen.h"
#include <QMessageBox>
#include "ui_DataDialog.h"
#include "../Tools/Data.h"

class DataDialog: public QDialog
{
	Q_OBJECT

public:
	DataDialog(QMap<QString, Query>, QWidget *parent);
	virtual ~DataDialog();
	QMap<QString, Query> getData();

private slots:
	void accept();
	void reject();
	void closeEvent(QCloseEvent * event);
	void radioButtonChanged(int);
	void addSensor();
	void removeSensor();
	void clearSelectionTable();

private:
	QString findSymbol();
	MonitorSystem getSelectedSystem();
	void fillinData();
	void fillinSelectedData(QMap<QString, Query>);
	void addHeaders();
	QString getSelectedSystemString();
	bool containsItems(QString, QString, QString);

	QMap<QString, Query> data_;

	Ui::DataDialog ui;
};