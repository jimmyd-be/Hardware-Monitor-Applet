#include "linewidget.h"
#include "ui_linewidget.h"
#include "tabwidget.h"

LineWidget::LineWidget(TabWidget * tabWidget, int id, QWidget *parent) :
    tabWidget_(tabWidget), id_(id), QWidget(parent),
    ui(new Ui::LineWidget)
{
    ui->setupUi(this);

    QString lineName = "Line ";
    lineName.append(QString::number(id));

    ui->label->setText(lineName);

    connect(ui->removeLineButton, SIGNAL(clicked()), this, SLOT(removeLine()));
}

LineWidget::~LineWidget()
{
    delete ui;
}

void LineWidget::removeLine()
{
    tabWidget_->removeLine(this);
}

int LineWidget::getId()
{
    return id_;
}

void LineWidget::setId(int id)
{
    id_ = id;

    QString lineName = "Line ";
    lineName.append(QString::number(id));

    ui->label->setText(lineName);
}
