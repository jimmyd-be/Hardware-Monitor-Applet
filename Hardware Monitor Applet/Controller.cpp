//-----------------------------------------------------------------
// Controller File
// C++ Source - Controller.cpp - version 0.1 (2013/06/13)
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Controller.h"

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Controller methods
//-----------------------------------------------------------------
Controller::Controller(QApplication* app, SingleApplication* singleApp) : mainWindow_(nullptr), settings_(nullptr), app_(app), singleApp_(singleApp)
{
	connect(singleApp_, SIGNAL(messageReceivedSignal(QString)), this, SLOT(messageReceivedFromOtherInst(QString)));
	
	logitech_ = new Logitech();
	logitech_->initKeyboard();

	settings_ = Settings::getInstance();
	settings_->setLogitech(logitech_);

	settings_->loadSettings();
}

Controller::~Controller()
{
	if (mainWindow_ != nullptr)
	{
		delete mainWindow_;
		mainWindow_ = nullptr;
	}

	settings_->releaseResources();

	if (logitech_ != nullptr)
	{
		delete logitech_;
		logitech_ = nullptr;
	}
}

void Controller::messageReceivedFromOtherInst(QString message)
{
	if (message == "Settings")
	{
		openSettingsScreen();
	}
	else if (message == "Quit")
	{
		quitApplication();
	}
}

void Controller::openSettingsScreen()
{
	if (mainWindow_ == nullptr)
	{
		mainWindow_ = new MainWindow(app_, logitech_, this);
	}

	mainWindow_->showMaximized();
}

void Controller::closeSettingsScreen()
{
	mainWindow_->hide();

/*	if (mainWindow_ != nullptr)
	{	
		delete mainWindow_;
		mainWindow_  = nullptr;
	}*/
}

void Controller::quitApplication()
{
	app_->quit();
}