#pragma once
#include "Defines.h"
#include "qdialog.h"
#include "Screen.h"
#include <QMessageBox>
#include "ui_DataDialog.h"
#include "../Tools/HWiNFO.h"

class DataDialog: public QDialog
{
	Q_OBJECT

public:
	DataDialog(QWidget *parent);
	virtual ~DataDialog();

private slots:
	void accept();
	void reject();

private:
	Ui::DataDialog ui;
};

