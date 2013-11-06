#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QWidget>

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

    void setId(int id);

private:
    Ui::TabWidget *ui;
    int id_;
};

#endif // TABWIDGET_H
