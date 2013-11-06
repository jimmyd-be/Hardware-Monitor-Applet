#include "linewidget.h"
#include "ui_linewidget.h"

LineWidget::LineWidget(int id, QWidget *parent) :
    id_(id), QWidget(parent),
    ui(new Ui::LineWidget)
{
    ui->setupUi(this);

    QString lineName = "Line ";
    lineName.append(QString::number(id));

    ui->label->setText(lineName);
}

LineWidget::~LineWidget()
{
    delete ui;
}
