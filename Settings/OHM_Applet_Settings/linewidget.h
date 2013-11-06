#ifndef LINEWIDGET_H
#define LINEWIDGET_H

#include <QWidget>

namespace Ui {
class LineWidget;
}

class LineWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LineWidget(int id, QWidget *parent = 0);
    ~LineWidget();

private:
    Ui::LineWidget *ui;

    int id_;
};

#endif // LINEWIDGET_H
