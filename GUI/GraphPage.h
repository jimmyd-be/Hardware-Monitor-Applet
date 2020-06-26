#ifndef GRAPHPAGE_H
#define GRAPHPAGE_H

#include "qwizard.h"
#include "qguiapplication.h"
#include "ui_GraphPageWidget.h"
#include "GraphPageLineWidget.h"
#include <QBoxLayout>
#include "../Defines.h"
#include "DataPage.h"
#include "QFontDialog"

class GraphPage: public QWizardPage
{
	Q_OBJECT

public:
	GraphPage(DataPage* page, QWidget *parent = 0);
	GraphPage(DataPage* page, QList<GraphLine> lines, GraphSettings settings, QWidget *parent = 0);
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
	void yAxisBoxChanged();

private:
	void fillinData();
	void removeData();

	Ui::GraphPageWidget ui;
	QWidget * widget_;
	QVBoxLayout * layout_;
	DataPage* dataPage_;
	QVector<GraphPageLineWidget *> widgetItems_;	
	QFont titleFont_;
	QColor titleColor_;

	QList<GraphLine> oldLines_;
	GraphSettings oldSettings_;
};
#endif
