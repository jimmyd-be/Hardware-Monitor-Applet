#include "tabwidget.h"
#include "ui_tabwidget.h"
#include "mainwindow.h"

TabWidget::TabWidget(MainWindow *mainWindow, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabWidget)
{
    ui->setupUi(this);

    connect(ui->removePageButton, SIGNAL(clicked()), mainWindow, SLOT(removePage()));
    connect(ui->addLineButton, SIGNAL(clicked()), this, SLOT(addLine()));
}

TabWidget::~TabWidget()
{
    delete ui;
}

void TabWidget::addLine()
{
    QLayout* layout = this->layout();

    layout->addWidget(new LineWidget(layout->count()-2+1));

    layout->removeItem(ui->verticalSpacer);
    layout->addItem(ui->verticalSpacer);
}
