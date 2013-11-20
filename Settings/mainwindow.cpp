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
	connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(openAboutWindow()));
	connect(ui->keyboardGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(keyboardLayoutChanged(QAbstractButton*)));

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
	QFileDialog dialog;
	dialog.setFileMode(QFileDialog::AnyFile);
	dialog.setNameFilter("Images (*.png *.jpg)");

	dialog.exec();

	QStringList	selectedFiles = dialog.selectedFiles();
}

void MainWindow::reportIssue()
{
	QUrl url("https://bitbucket.org/jimmyD/open-hardware-monitor-applet/issues?status=new&status=open");
	QDesktopServices::openUrl(url);
}

void MainWindow::openAboutWindow()
{
	AboutWindow window;
	window.exec();
}

void MainWindow::keyboardLayoutChanged(QAbstractButton* button)
{
	if(ui->monochromeRadioButton == button)
	{
		ui->browseButton->setDisabled(true);
		ui->browseLine->setDisabled(true);
	}
	else
	{
		ui->browseButton->setDisabled(false);
		ui->browseLine->setDisabled(false);
	}
}