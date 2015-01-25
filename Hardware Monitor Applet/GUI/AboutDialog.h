#pragma once

#include "qguiapplication.h"
#include "ui_AboutDialog.h"
#include "qdialog.h"

class AboutDialog : public QDialog
{
	Q_OBJECT

public:
	AboutDialog(QWidget *parent = 0);
	virtual ~AboutDialog();


	private slots:
	void accept();
	void reject();

private:
	Ui::AboutDialog ui;
	QWidget *widget_;

};