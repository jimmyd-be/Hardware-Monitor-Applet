#pragma once

#include "qwizard.h"
#include "qguiapplication.h"
#include "Ui_LineEditPageWidget.h"
#include "LineEditPageLineWidget.h"
#include "DataPage.h"

class LineEditPage: public QWizardPage
{
	Q_OBJECT

public:
	LineEditPage(DataPage* page, QWidget *parent = 0);
	LineEditPage(DataPage* page, QList<LineText> lines, QWidget *parent = 0);
	virtual ~LineEditPage();

	bool validatePage();
	QStringList getData();

protected:
	void initializePage();
	int nextId() const;

private slots:
	void addLine();

private:
	void loadLines(QList<LineText> lines);
	void removeLines();
	
	Ui::LineEditPageWidget ui;
	QWidget *widget_;
	QVBoxLayout *layout_;

	QList<LineEditPageLineWidget*> widgetList_;

	DataPage * dataPage_;
};