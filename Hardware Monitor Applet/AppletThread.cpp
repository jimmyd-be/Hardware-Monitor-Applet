//-----------------------------------------------------------------
// AppletThread File
// C++ Source - AppletThread.cpp - version 0.1 (2013/06/13)
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "AppletThread.h"

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// AppletThread methods
//-----------------------------------------------------------------
AppletThread::AppletThread(CEzLcd* lcd, Logitech * logitech) : lcd_(lcd), logitech_(logitech), time_(0)
{
	// nothing to create
}

AppletThread::~AppletThread()
{
	// nothing to destroy
}

void AppletThread::run()
{
	//WMI * wmiThread = new WMI(ThreadType::Thread);
	//Data::Instance()->addMonitorTool(wmiThread);

	while (isRunning())
	{
		time_ += 30;

		checkButtonPresses();

		if (time_ >= 1000)
		{
			updatePage();
			time_ = 0;
		}

		lcd_->Update();

		msleep(30);
	}
}

void AppletThread::initLCDObjectsMonochrome()
{


}

void AppletThread::initLCDObjectsColor()
{


}

void AppletThread::checkButtonPresses()
{
	if (lcd_->IsDeviceAvailable(LG_COLOR))
	{
		checkbuttonPressesColor();
	}

	else if (lcd_->IsDeviceAvailable(LG_MONOCHROME))
	{
		checkbuttonPressesMonochrome();
	}
}

void AppletThread::checkbuttonPressesMonochrome()
{
	lcd_->ModifyDisplay(LG_MONOCHROME);

	if (lcd_->ButtonTriggered(LG_BUTTON_1))
	{
		logitech_->changeCurrentScreen(PageDirection::Previous);
	}

	else if (lcd_->ButtonTriggered(LG_BUTTON_2))
	{
		logitech_->changeCurrentScreen(PageDirection::Down);
	}

	else if (lcd_->ButtonTriggered(LG_BUTTON_3))
	{
		logitech_->changeCurrentScreen(PageDirection::Up);
	}

	else if (lcd_->ButtonTriggered(LG_BUTTON_4))
	{
		logitech_->changeCurrentScreen(PageDirection::Next);
	}

	lcd_->ShowPage(logitech_->getCurrentScreen()->getIndex());

}

void AppletThread::checkbuttonPressesColor()
{
	lcd_->ModifyDisplay(LG_COLOR);

	if (lcd_->ButtonTriggered(LG_BUTTON_RIGHT))
	{
		logitech_->changeCurrentScreen(PageDirection::Next);
	}

	else if (lcd_->ButtonTriggered(LG_BUTTON_LEFT))
	{
		logitech_->changeCurrentScreen(PageDirection::Previous);
	}

	else if (lcd_->ButtonTriggered(LG_BUTTON_UP))
	{
		logitech_->changeCurrentScreen(PageDirection::Up);
	}

	else if (lcd_->ButtonTriggered(LG_BUTTON_DOWN))
	{
		logitech_->changeCurrentScreen(PageDirection::Down);
	}

	else if (lcd_->ButtonTriggered(LG_BUTTON_OK))
	{

	}

	lcd_->ShowPage(logitech_->getCurrentScreen()->getIndex());
}

void AppletThread::updatePage()
{
	Screen * currentScreen = logitech_->getCurrentScreen();


//	currentScreen->update();
	currentScreen->draw();

}