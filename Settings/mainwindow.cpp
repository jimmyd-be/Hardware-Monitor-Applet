#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(WMI* wmi, QWidget *parent) :
    wmi_(wmi), QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    addPageButton = new QPushButton("Add page");

    connect(addPageButton, SIGNAL(clicked()), this, SLOT(addNewPage()));
	connect(ui->browseButton, SIGNAL(clicked()), this, SLOT(browseBackground()));
	connect(ui->actionReport_issue, SIGNAL(triggered()), this, SLOT(reportIssue()));

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

    TabWidget * newTab = new TabWidget(wmi_, this);
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

void MainWindow::browseBackground()
{
//	QStringList filters;
//	filters << "Image files (*.png *.jpg)";
//
//	//QFileDialog dialog;
//
//	//dialog.setNameFilters(filters);
//	//dialog.exec();
//
//	//QStringList fileList = dialog.selectedFiles();
//	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));

	//QString test = fileList.at(0);
	//ui->browseLine->setText();
}

void MainWindow::reportIssue()
{
	QUrl url("https://bitbucket.org/jimmyD/open-hardware-monitor-applet/issues?status=new&status=open");
	QDesktopServices::openUrl(url);
}