#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(WMI* wmi, QWidget *parent) :
	wmi_(wmi), QMainWindow(parent), addPageButton(nullptr),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	addPageButton = new QPushButton("Add page");

	connect(addPageButton, SIGNAL(clicked()), this, SLOT(addNewPage()));
	connect(ui->browseButton, SIGNAL(clicked()), this, SLOT(browseBackground()));
	connect(ui->actionReport_issue, SIGNAL(triggered()), this, SLOT(reportIssue()));
	connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(openAboutWindow()));
	connect(ui->keyboardGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(keyboardLayoutChanged(QAbstractButton*)));
	connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
	connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveSettings()));
	connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveSettings()));
	connect(ui->undoButton, SIGNAL(clicked()), this, SLOT(loadSettings()));

	ui->tabWidget->setCornerWidget(addPageButton);
	ui->browseLine->setDisabled(true);

	addNewPage();

	loadSettings();
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
	QStringList	selectedFiles;

	dialog.setFileMode(QFileDialog::AnyFile);
	dialog.setNameFilter("Images (*.png *.jpg)");
	dialog.setOption(QFileDialog::DontUseNativeDialog);

	if (dialog.exec())
	{
		selectedFiles = dialog.selectedFiles();

		QImage image(selectedFiles.at(0));

		if(image.height() != 240 && image.width() != 320)
		{
			QMessageBox messageBox;
			messageBox.setText("File is not an image or the dimension is not 320x240");
			messageBox.exec();
		}

		else
		{
			ui->browseLine->setText(selectedFiles.at(0));
		}
	}	

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

		for(int i= 0; i< ui->tabWidget->count(); i++)
		{
			QWidget* widget = ui->tabWidget->widget(i);
			TabWidget* tab =static_cast<TabWidget*>(widget);

			tab->disableBrowse(true);
		}
	}
	else
	{
		ui->browseButton->setDisabled(false);

		for(int i= 0; i< ui->tabWidget->count(); i++)
		{
			QWidget* widget = ui->tabWidget->widget(i);
			TabWidget* tab =static_cast<TabWidget*>(widget);

			tab->disableBrowse(false);
		}
	}
}

void MainWindow::close()
{
	QApplication::quit();
}

void MainWindow::loadSettings()
{
	QSettings settings(QSettings::IniFormat, QSettings::UserScope, "OHM Applet", "Settings");


	//Read General settigns
	settings.beginGroup("General");
	int totalPages = settings.value("TotalPages").toInt();

	if(totalPages > 0)
	{
		ui->fontComboBox->setCurrentFont(QFont(settings.value("Font").toString()));
		ui->fontSpinBox->setValue(settings.value("FontSize").toInt());
		ui->browseLine->setText(settings.value("Background").toString());

		settings.endGroup();

		for(int i = 0; i < ui->tabWidget->count(); i++)
		{
			ui->tabWidget->removeTab(i);
		}

		for(int i= 0; i< totalPages; i++)
		{
			QString pageText = "Page";
			pageText.append(QString::number(i+1));

			settings.beginGroup(pageText);

			int totalLines = settings.value("TotalLines").toInt();

			if(ui->tabWidget->count() <= i)
			{
				addNewPage();
			}

			QWidget* widget = ui->tabWidget->widget(i);
			TabWidget* tab =static_cast<TabWidget*>(widget);

			tab->setBackground(settings.value("Background").toString());

			QVector<QString> lines;

			for(int j=0; j < totalLines; j++)
			{
				if(tab->getLines().size() <= j)
				{
					tab->addLine();
				}
				QString lineText = "Line";
				lineText.append(QString::number(j+1));

				lines.push_back(settings.value(lineText).toString());
			}

			tab->setLines(lines);

			settings.endGroup();
		}
	}
}

void MainWindow::saveSettings()
{
	QString dir = QDir::homePath();

	dir.append("/AppData/Roaming/OHM Applet/Images/");

	QDir directory(dir);

	if(!directory.exists())
	{
		directory.mkpath(dir);
	}

	QFile file(ui->browseLine->text());

	QSettings settings(QSettings::IniFormat, QSettings::UserScope, "OHM Applet", "Settings");

	settings.beginGroup("General");
	settings.setValue("TotalPages", ui->tabWidget->count());
	settings.setValue("Font", ui->fontComboBox->currentFont().toString());
	settings.setValue("FontSize", ui->fontSpinBox->value());

	if(file.exists())
	{
		QString dir2 = dir;

		QFileInfo info(file);

		bool test = file.copy(dir2.append(info.fileName()));
		settings.setValue("Background", info.fileName());
	}


	settings.endGroup();

	for(int i= 0; i< ui->tabWidget->count(); i++)
	{
		QWidget* widget = ui->tabWidget->widget(i);
		TabWidget* tab =static_cast<TabWidget*>(widget);

		QString pageText = "Page";
		pageText.append(QString::number(i+1));

		QFile tabFile(tab->getbackground());

		settings.beginGroup(pageText);

		if(tabFile.exists())
		{
			QString dir2 = dir;
			QFileInfo info2(tabFile);

			tabFile.copy(dir2.append(info2.fileName()));
			settings.setValue("Background", info2.fileName());
		}
		else
		{
			settings.setValue("Background", "");
		}

		pageText.append(QString::number(i+1));

		settings.setValue("TotalLines", tab->getLines().size());

		for(int j=0; j < tab->getLines().size(); j++)
		{
			QString lineText = "Line";
			lineText.append(QString::number(j+1));
			settings.setValue(lineText, tab->getLines().at(j));
		}

		settings.endGroup();
	}	
}