#ifndef GRAPHPAGELINEWIDGET_H
#define GRAPHPAGELINEWIDGET_H

#include "../Defines.h"
#include <QColorDialog>
#include "ui_GraphPageLineWidget.h"
#include <QPair>

class GraphPageLineWidget :
	public QWidget, private Ui_GraphPageLineWidget
{
	Q_OBJECT

public:
	GraphPageLineWidget(QString, Query, QWidget *parent = 0);
	GraphPageLineWidget(GraphLine, QWidget *parent = 0);

	virtual ~GraphPageLineWidget();

	QColor getColor();
	QPair<QString, Query> getValue();

private slots:
	void openColorPicker();

private:
	int randInt(int low, int high);

    Query query_;
	QPalette palette_;
	QColor color_;
};

#endif
