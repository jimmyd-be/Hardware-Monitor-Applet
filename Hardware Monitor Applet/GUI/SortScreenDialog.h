#pragma once
#include "Defines.h"
#include "qdialog.h"
#include "Screen\Screen.h"
#include <QMessageBox>
#include "ui_SortScreenDialog.h"

class SortScreenDialog: public QDialog
{
	Q_OBJECT

public:
	SortScreenDialog(QWidget *parent);
	virtual ~SortScreenDialog();

private slots:
	void accept();
	void reject();

private:
	Ui::SortScreenDialog ui;
};

