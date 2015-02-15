#pragma once

#include "qwizard.h"
#include "qguiapplication.h"
#include "ui_GraphPageWidget.h"
#include "GraphPageLineWidget.h"
#include "QBoxLayout.h"
#include "../Defines.h"
#include "DataPage.h"
#include "QFontDialog"

class GraphPage: public QWizardPage
{
	Q_OBJECT

public:
	GraphPage(DataPage* page, QWidget *parent = 0);
	GraphPage(DataPage* page, QList<LineText> lines, QList<QColor> colors, QWidget *parent = 0);
	virtual ~GraphPage();

	QMap<QString, Query> getValues();
	QList<QColor> getColors();
	GraphSettings getGraphSettings();

protected:
	int nextId() const;
	void initializePage();

private slots:
	void openFontDialog();
	void openColorDialog();
	void titleCheckBoxChanged();

private:
	void loadData(QList<LineText>, QList<QColor>);
	void fillinData();
	void removeData();

	Ui::GraphPageWidget ui;
	QWidget * widget_;
	QVBoxLayout * layout_;
	DataPage* dataPage_;
	QVector<GraphPageLineWidget *> widgetItems_;	
	QFont titleFont_;
	QColor titleColor_;
};