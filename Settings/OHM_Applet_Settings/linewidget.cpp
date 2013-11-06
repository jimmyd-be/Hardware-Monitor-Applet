#include "linewidget.h"
#include "ui_linewidget.h"

LineWidget::LineWidget(int id, QWidget *parent) :
    id_(id), QWidget(parent),
    ui(new Ui::LineWidget)
{
    ui->setupUi(this);
}

LineWidget::~LineWidget()
{
    delete ui;
}
