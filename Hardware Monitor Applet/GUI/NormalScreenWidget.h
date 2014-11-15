#pragma once
#include "../Defines.h"
#include "LineScreenWidget.h"
#include "ui_NormalScreenWidget.h"
#include "../Logitech.h"
#include "DataDialog.h"
#include "FontDialog.h"
#include "QFileDialog"

class NormalScreenWidget :
	public QWidget, private Ui_NormscreenWidget
{
	Q_OBJECT

public:
	NormalScreenWidget(QString name, Logitech *, QWidget *parent = 0);
	NormalScreenWidget(Screen * screen, Logitech *, QWidget *parent = 0);
	virtual ~NormalScreenWidget();

	void removeWidget(LineScreenWidget *);
	void lineScreenTextChanged();

private slots:
	void openDataScreen();
	void addLine();
	void openFontDialog();
	void openbackgroundDialog();

private:
	void addLine(QString);
	void addDataMap(Query);

	QVector<LineScreenWidget *> lineList_;
	DataDialog * dataDialog_;
	QString name_;
	QMap<QString, Query> dataMap_;

	Logitech * lcd_;
};

