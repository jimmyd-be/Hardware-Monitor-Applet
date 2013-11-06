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

private slots:
    void addLine();


private:
    Ui::TabWidget *ui;

};

#endif // TABWIDGET_H
