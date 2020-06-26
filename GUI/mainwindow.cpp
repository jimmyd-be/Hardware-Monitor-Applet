#include "mainwindow.h"

MainWindow::MainWindow(Logitech * logitech,QWidget *parent)
    : QMainWindow(parent), logitech_(logitech), degreeGroup_(nullptr)
{
	ui.setupUi(this);

#ifdef __linux__
    ui.menuAutostart->setDisabled(true);
    ui.actionClose->setDisabled(true);
#endif

	keyboardChanged(logitech->getKeyboardType());

	degreeGroup_ = new QActionGroup(this);
	degreeGroup_->addAction(ui.actionFahrenheit);
	degreeGroup_->addAction(ui.actionCelsius);

	autoStartGroup_ = new QActionGroup(this);
	autoStartGroup_->addAction(ui.actionEnable);
	autoStartGroup_->addAction(ui.actionDisable);

	if (HwaSettings::getInstance()->getTemperature() == TemperatureType::Fahrenheit)
	{
		ui.actionFahrenheit->setChecked(true);
	}

	ui.actionEnable->setChecked(HwaSettings::getInstance()->getAutoStart());
	ui.actionDisable->setChecked(!HwaSettings::getInstance()->getAutoStart());

	connect(ui.AddScreen_Button, SIGNAL(clicked()), this, SLOT(openScreenWizard()));
	connect(ui.Order_pushButton, SIGNAL(clicked()), this, SLOT(openOrderWindow()));
	connect(ui.actionClose, SIGNAL(triggered()), this, SLOT(closeWindow()));
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(closeProgram()));
	connect(ui.actionFahrenheit, SIGNAL(triggered()), this, SLOT(settingsChanged()));
	connect(ui.actionCelsius, SIGNAL(triggered()), this, SLOT(settingsChanged()));
	connect(ui.actionReport_a_bug, SIGNAL(triggered()), this, SLOT(reportIssue()));
	connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(openAboutWindow()));
	connect(ui.actionEnable, SIGNAL(triggered()), this, SLOT(settingsChanged()));
	connect(ui.actionDisable, SIGNAL(triggered()), this, SLOT(settingsChanged()));
    connect(ui.actionChange_InfluxDb_settings, SIGNAL(triggered()), this, SLOT(openInfluxDialog()));

	fillinPages();
}

MainWindow::~MainWindow()
{
	removePages();

	if (degreeGroup_ != nullptr)
	{
		delete degreeGroup_;
		degreeGroup_ = nullptr;
	}

	if (autoStartGroup_ != nullptr)
	{
		delete autoStartGroup_;
		autoStartGroup_ = nullptr;
	}

}

void MainWindow::keyboardChanged(KeyboardTypes type)
{
	if (type == KeyboardTypes::None)
	{
		ui.statusBar->showMessage(tr("No Logitech keyboard found!!"));
	}
	else if (type == KeyboardTypes::Monochrome)
	{
		ui.statusBar->showMessage(tr("Connected to: Logitech monochrome (G15, G15s, G510) keyboard"));
	}
	else if (type == KeyboardTypes::Color)
	{
		ui.statusBar->showMessage(tr("Connected to: Logitech color (G19, G19s) keyboard"));
	}

	ui.statusBar->show();
}

void MainWindow::openInfluxDialog()
{
    InfluxDbDialog * dialog = new InfluxDbDialog();
    dialog->exec();

    delete dialog;
}

void MainWindow::closeEvent(QCloseEvent * event)
{
	closeWindow();
	event->ignore();
}

void MainWindow::closeWindow()
{
    //controller_->closeSettingsScreen();

#ifdef __linux__
    QApplication::quit();
#elif _WIN32
    hide();
#endif
}

void MainWindow::closeProgram()
{
    QApplication::quit();
    //controller_->quitApplication();
}

void MainWindow::reportIssue()
{
    QUrl url("https://github.com/lonelobo0070/Hardware-Monitor-Applet/issues");
	QDesktopServices::openUrl(url);
}

void MainWindow::openAboutWindow()
{
	AboutDialog * dialog = new AboutDialog();

	dialog->exec();

	delete dialog;
}

void MainWindow::openScreenWizard()
{
	CreateScreenWizard * wizard = new CreateScreenWizard(logitech_, this);
	wizard->exec();
	
	delete wizard;

	refreshPages();
}

void MainWindow::settingsChanged()
{
	if (ui.actionCelsius->isChecked())
	{
		HwaSettings::getInstance()->setTemperature(TemperatureType::Celsius);
	}
	else if (ui.actionFahrenheit->isChecked())
	{
		HwaSettings::getInstance()->setTemperature(TemperatureType::Fahrenheit);
	}

	if (ui.actionEnable->isChecked())
	{
		HwaSettings::getInstance()->setAutoStart(true);
	}
	else if (ui.actionDisable->isChecked())
	{
		HwaSettings::getInstance()->setAutoStart(false);
	}

}

void MainWindow::fillinPages()
{
	QList<Screen *> pages = sortScreenList(logitech_->getScreenList());

	for (int i = 0; i < pages.size(); i++)
	{
        MainScreenWidget * widget = new MainScreenWidget(logitech_, pages[i]->getName(), pages[i]->getScreenType(), logitech_->isScreenActive(pages[i]->getName()));

        connect(widget, SIGNAL(refreshMainWindow()), this, SLOT(refreshPages()));

		ui.ScreenList_Layout->addWidget(widget);

		widgetList_.append(widget);
	}
}

QList<Screen *> MainWindow::sortScreenList(QList<Screen*> list)
{
	for (int i = 0; i < list.size(); i++)
	{
		int min = i;

		for (int j = i + 1; j < list.size(); j++)
		{
			QString test = list[min]->getName();
			QString test2 = list[j]->getName();

			if (QString::compare(list[min]->getName(), list[j]->getName(), Qt::CaseInsensitive) > 0)
			{
				min = j;
			}
		}

		Screen * temp = list[i];
		list[i] = list[min];
		list[min] = temp;
	}

	return list;
}

void MainWindow::removePages()
{
	for (QWidget * widget : widgetList_)
	{
		ui.ScreenList_Layout->removeWidget(widget);
		delete widget;
	}

	widgetList_.clear();
}

void MainWindow::refreshPages()
{
	removePages();
	fillinPages();
}


void MainWindow::openOrderWindow()
{
	OrderWindow * window = new OrderWindow(logitech_);

	window->exec();

	refreshPages();

	delete window;
}

