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
	DataDialog(QWidget *parent);
	virtual ~DataDialog();

private slots:
	void accept();
	void reject();
	void closeEvent(QCloseEvent * event);
	void radioButtonChanged(int);
	void addSensor();
	void removeSensor();
	void clearSelectionTable();

private:

	MonitorSystem getSelectedSystem();
	void fillinData();
	void addHeaders();
	QString getSelectedSystemString();

	Ui::DataDialog ui;
};