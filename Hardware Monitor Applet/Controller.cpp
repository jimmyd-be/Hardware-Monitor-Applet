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
Controller::Controller(QtSingleApplication* app) : mainWindow_(nullptr), settings_(nullptr)
{
	QObject::connect(app, SIGNAL(messageReceived(const QString &)), this, SLOT(vMessageReceivedFromOtherInst(const QString &)));
	
	logitech_ = new Logitech();
	bool success = logitech_->initKeyboard();

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

void  Controller::vMessageReceivedFromOtherInst(const QString &  msg)
{
	openSettingsScreen();
}

void Controller::openSettingsScreen()
{
	if (mainWindow_ == nullptr)
	{
		mainWindow_ = new MainWindow(logitech_);
	}

	mainWindow_->showMaximized();
}