#ifndef LINEWIDGET_H
#define LINEWIDGET_H

#include <QWidget>
//#include "tabwidget.h"

namespace Ui {
class LineWidget;
}

class TabWidget;

class LineWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LineWidget(TabWidget*, int id, QWidget *parent = 0);
    ~LineWidget();

    void setId(int id);
    int getId();

private slots:
    void removeLine();

private:
    Ui::LineWidget *ui;
    int id_;
    TabWidget * tabWidget_;
};

#endif // LINEWIDGET_H
