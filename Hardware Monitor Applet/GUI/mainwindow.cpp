#include "mainwindow.h"

MainWindow::MainWindow(KeyboardTypes type, Logitech * lcd, QWidget *parent)
	: QMainWindow(parent), temperatureActionGroup_(nullptr), monitorToolActionGroup_(nullptr), lcd_(lcd), mainWidget_(nullptr)
{
	ui.setupUi(this);

	temperatureActionGroup_ = new QActionGroup(this);
	monitorToolActionGroup_ = new QActionGroup(this);

	temperatureActionGroup_->addAction(ui.actionCelsius);
	temperatureActionGroup_->addAction(ui.actionFahrenheit);

	monitorToolActionGroup_->addAction(ui.actionHWiNFO);
	monitorToolActionGroup_->addAction(ui.actionOpen_Hardware_Monitor);

	connect(ui.addScreenButton, SIGNAL(clicked()), this, SLOT(openSelectionDialog()));
	connect(ui.removeScreenButton, SIGNAL(clicked()), this, SLOT(removeCurrentScreen()));
	connect(ui.screenComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBoxChanged()));

	keyboardChanged(type);
}

MainWindow::~MainWindow()
{
	if (temperatureActionGroup_ != nullptr)
	{
		delete temperatureActionGroup_;
		temperatureActionGroup_ = nullptr;
	}

	if (monitorToolActionGroup_ != nullptr)
	{
		delete monitorToolActionGroup_;
		monitorToolActionGroup_ = nullptr;
	}

	if (mainWidget_ != nullptr)
	{
		delete mainWidget_;
		mainWidget_ = nullptr;
	}
}

void MainWindow::keyboardChanged(KeyboardTypes type)
{
	if (type == KeyboardTypes::None)
	{
		ui.keyboardLabel->setText("No Logitech keyboard found!!");
	}
	else if (type == KeyboardTypes::Monochrome)
	{
		ui.keyboardLabel->setText("Logitech monochrome (G15, G15s, G510) keyboard found!!");
	}
	else
	{
		ui.keyboardLabel->setText("Logitech color (G19, G19s) keyboard found!!");
	}

}

void MainWindow::openSelectionDialog()
{
	ScreenSelectionDialog * dialog = new ScreenSelectionDialog(this, lcd_->getScreenList());
	dialog->exec();

	createScreen(dialog->getScreenName(), dialog->getScreenType());

	delete dialog;
}

void MainWindow::createScreen(QString name, ScreenType type)
{
	if (mainWidget_ != nullptr)
	{
		ui.widgetLayout->removeWidget(mainWidget_);
		delete mainWidget_;
		mainWidget_ = nullptr;
	}

	ui.screenComboBox->addItem(name);
	ui.screenComboBox->setCurrentIndex(ui.screenComboBox->count()-1);

	if (type == ScreenType::Normal)
	{
		lcd_->createPage(name, type);
		mainWidget_ = new NormalScreenWidget(name, lcd_);

		ui.widgetLayout->addWidget(mainWidget_);
	}

	else if(type == ScreenType::Graph)
	{
		mainWidget_ = new GraphScreenWidget(name, lcd_);

		ui.widgetLayout->addWidget(mainWidget_);
	}

	fillinAllScreens();
}

void MainWindow::removeCurrentScreen()
{
	if (mainWidget_ != nullptr)
	{
		ui.widgetLayout->removeWidget(mainWidget_);
		delete mainWidget_;
		mainWidget_ = nullptr;
	}

	lcd_->removePage(ui.screenComboBox->currentText());
	ui.screenComboBox->removeItem(ui.screenComboBox->currentIndex());

	fillinAllScreens();
	removeRemovedScreenOrder();
}

void MainWindow::comboBoxChanged()
{
	Screen * data = lcd_->getScreenData(ui.screenComboBox->currentText());

	if (data != nullptr)
	{
		if (mainWidget_ != nullptr)
		{
			ui.widgetLayout->removeWidget(mainWidget_);
			delete mainWidget_;
			mainWidget_ = nullptr;
		}

		if (data->getScreenType() == ScreenType::Normal)
		{
			mainWidget_ = new NormalScreenWidget(data, lcd_);

			ui.widgetLayout->addWidget(mainWidget_);
		}

		else if (data->getScreenType() == ScreenType::Graph)
		{
		mainWidget_ = new GraphScreenWidget(data, lcd_);

		ui.widgetLayout->addWidget(mainWidget_);
		}
	}
}

void MainWindow::fillinAllScreens()
{
	ui.allScreenListWidget->clear();

	for (int row = 0; row < ui.screenComboBox->count(); row++)
	{
		QString text = ui.screenComboBox->itemText(row);

		ui.allScreenListWidget->addItem(text);
	}
}

void MainWindow::removeRemovedScreenOrder()
{
	for (int i = 0; i < ui.mainScreenlistWidget->count(); i++)
	{
		QListWidgetItem * widgetitem = nullptr;

		for (int row = 0; row < ui.screenComboBox->count(); row++)
		{
			if (ui.mainScreenlistWidget->item(i)->text() == ui.screenComboBox->itemText(row))
			{
				widgetitem = ui.mainScreenlistWidget->item(i);
				break;
			}
		}

		if (widgetitem != nullptr)
		{
			ui.mainScreenlistWidget->removeItemWidget(widgetitem);
		}
	}
}