#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QWidget>
#include "linewidget.h"
#include "WMI.h"

namespace Ui {

class TabWidget;
}

class MainWindow;

class TabWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TabWidget(WMI* wmi, MainWindow*, QWidget *parent = 0);
    ~TabWidget();
	
	void disableBrowse(bool);

public slots:
    void addLine();
    void removeLine(LineWidget* line);


private:
    Ui::TabWidget *ui;
    QList<LineWidget*> lineWidgets;

	WMI * wmi_;
};

#endif // TABWIDGET_H
