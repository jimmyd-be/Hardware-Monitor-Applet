#include "tabwidget.h"
#include "ui_tabwidget.h"
#include "mainwindow.h"

TabWidget::TabWidget(MainWindow *mainWindow, QWidget *parent) :
    /*mainWindow_(mainWindow),*/ QWidget(parent),
    ui(new Ui::TabWidget)
{
    ui->setupUi(this);

    connect(ui->removePageButton, SIGNAL(clicked()), mainWindow, SLOT(removePage()));
}

TabWidget::~TabWidget()
{
    delete ui;
}

void TabWidget::setId(int id)
{
    id_ = id;
}
