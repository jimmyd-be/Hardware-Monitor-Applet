#pragma once
#include "../Defines.h"
#include "LineScreenWidget.h"
#include "ui_NormalScreenWidget.h"

class NormalScreenWidget :
	public QWidget, private Ui_NormscreenWidget
{
	Q_OBJECT

public:
	NormalScreenWidget(QWidget *parent = 0);
	virtual ~NormalScreenWidget();

	void removeWidget(LineScreenWidget *);

private slots:
	void openDataScreen();
	void addLine();

private:
	QVector<LineScreenWidget *> lineList_;
};

