#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QWidget>
#include "linewidget.h"

namespace Ui {

class TabWidget;
}

class MainWindow;

class TabWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TabWidget(MainWindow*, QWidget *parent = 0);
    ~TabWidget();

public slots:
    void addLine();
    void removeLine(LineWidget* line);


private:
    Ui::TabWidget *ui;
    QList<LineWidget*> lineWidgets;

};

#endif // TABWIDGET_H
