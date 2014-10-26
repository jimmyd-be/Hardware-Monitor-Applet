#pragma once
#include "Defines.h"
#include "qdialog.h"
#include "Screen.h"
#include "qcolordialog.h"
#include "ui_FontDialog.h"

class FontDialog: public QDialog
{
	Q_OBJECT

public:
	FontDialog(Screen *, QWidget *parent);
	virtual ~FontDialog();
	AppletFont getFont();

private slots:
	void accept();
	void reject();
	void closeEvent(QCloseEvent * event);
	void openColorPicker();

private:
	Screen * screenData_;
	Ui::FontDialog ui;
	AppletFont font_;
};