#pragma once
#include "Defines.h"
#include "qdialog.h"
#include "Screen.h"
#include <QMessageBox>
#include "ui_ScreenSelectionDialog.h"

class ScreenSelectionDialog: public QDialog
{
	Q_OBJECT

public:
	ScreenSelectionDialog(QWidget *parent, QVector<Screen *> screenList);
	virtual ~ScreenSelectionDialog();

	QString getScreenName();
	ScreenType getScreenType();

private slots:
	void accept();
	void reject();

private:
	Ui::Dialog ui;

	QString name_;
	ScreenType type_;
	QVector<Screen *> screenList_;
};

