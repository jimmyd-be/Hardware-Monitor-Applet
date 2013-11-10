#include "tabwidget.h"
#include "ui_tabwidget.h"
#include "mainwindow.h"

TabWidget::TabWidget(WMI* wmi, MainWindow *mainWindow, QWidget *parent) :
    wmi_(wmi), QWidget(parent),
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

     LineWidget* lineWidget = new LineWidget(wmi_, this, layout->count()-2+1);
    layout->addWidget(lineWidget);

    lineWidgets.append(lineWidget);
    layout->removeItem(ui->verticalSpacer);
    layout->addItem(ui->verticalSpacer);
}

void TabWidget::removeLine(LineWidget *line)
{
    QLayout* layout = this->layout();
    layout->removeWidget(line);

    int lineIndex = lineWidgets.indexOf(line);

    lineWidgets.removeOne(line);
    delete line;

    for(int i = lineIndex; i < lineWidgets.size(); i++)
    {
        lineWidgets[i]->setId(i+1);
    }
}
