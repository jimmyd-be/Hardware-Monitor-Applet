#pragma once

#include "qwizard.h"
#include "qguiapplication.h"
#include "ui_GraphPageWidget.h"
#include "QBoxLayout.h"

class GraphPage: public QWizardPage
{
	Q_OBJECT

public:
	GraphPage(QWidget *parent = 0);
	virtual ~GraphPage();

private:
	Ui::GraphPageWidget ui;
	QWidget * widget_;

	QVBoxLayout * layout_;
};