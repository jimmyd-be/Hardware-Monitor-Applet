#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    addPageButton = new QPushButton("Add page");

    connect(addPageButton, SIGNAL(clicked()), this, SLOT(addNewPage()));

    ui->tabWidget->setCornerWidget(addPageButton);

    addNewPage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addNewPage()
{
    int totalTabs = ui->tabWidget->count()+1;

    QString tabName = "Page ";
    tabName.append(QString::number(totalTabs));

    TabWidget * newTab = new TabWidget(this);
    int id = ui->tabWidget->addTab(newTab, tabName);
}

void MainWindow::removePage()
{
    int currentTab = ui->tabWidget->currentIndex();
    int totalTabs = ui->tabWidget->count();

    if(totalTabs > 1)
    {
        for(int i= currentTab; i< totalTabs-1; i++)
        {
            QString tabName = "Page ";
            tabName.append(QString::number(i+1));

            ui->tabWidget->setTabText(i+1, tabName);
        }

         ui->tabWidget->removeTab(currentTab);
    }
}
