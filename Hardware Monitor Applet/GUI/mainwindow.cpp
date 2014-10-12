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

	QObject::connect(ui.addScreenButton, SIGNAL(clicked()), this, SLOT(openSelectionDialog()));

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

		ui.backgroundBrowseButton->hide();
		ui.backgroundLabel->hide();
		ui.backgroundLine->hide();
	}
	else
	{
		ui.keyboardLabel->setText("Logitech color (G19, G19s) keyboard found!!");
		
		ui.backgroundBrowseButton->show();
		ui.backgroundLabel->show();
		ui.backgroundLine->show();
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
	if (type == ScreenType::Normal)
	{
		mainWidget_ = new NormalScreenWidget();

		ui.widgetLayout->addWidget(mainWidget_);
	}

	else if(type == ScreenType::Graph)
	{
		mainWidget_ = new GraphScreenWidget();

		ui.widgetLayout->addWidget(mainWidget_);
	}
}