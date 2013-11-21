#ifndef LINEWIDGET_H
#define LINEWIDGET_H

#include <QWidget>
#include "datawindow.h"
#include "WMI.h"

namespace Ui {
class LineWidget;
}

class TabWidget;

class LineWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LineWidget(WMI* wmi, TabWidget*, int id, QWidget *parent = 0);
    ~LineWidget();

    void setId(int id);
    int getId();
	QString getText();

private slots:
    void removeLine();
	void openDataWindow();

private:
    Ui::LineWidget *ui;
    int id_;
    TabWidget * tabWidget_;
	WMI * wmi_;
};

#endif // LINEWIDGET_H
