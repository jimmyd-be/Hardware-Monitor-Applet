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
AppletThread::AppletThread(CEzLcd* lcd, Logitech * logitech) : lcd_(lcd), logitech_(logitech), time_(0), OkButtonTime_(0)
{
	// nothing to create
}

AppletThread::~AppletThread()
{
	// nothing to destroy
}

void AppletThread::run()
{

	while (isRunning())
	{
		time_ += 30;

		if (logitech_->getCurrentScreen() != nullptr)
		{
			checkButtonPresses();

			if (time_ >= 1000)
			{
				updatePage();
				time_ = 0;
			}

			lcd_->ShowPage(logitech_->getCurrentScreen()->getPage());

			lcd_->Update();

		}
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
	if (logitech_->getCurrentScreen()->getScreenType() != ScreenType::Start)
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
	}
	
}

void AppletThread::checkbuttonPressesColor()
{
	if (logitech_->getCurrentScreen()->getScreenType() != ScreenType::Start)
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

		else if (lcd_->ButtonIsPressed(LG_BUTTON_OK))
		{
			OkButtonTime_ += 30;
		}

		else if (lcd_->ButtonReleased(LG_BUTTON_OK))
		{
			if (OkButtonTime_ < 1000)
			{
				Screen * currentScreen = logitech_->getCurrentScreen();

				currentScreen->openCustomScreen();
			}
			else
			{
				Screen * currentScreen = logitech_->getCurrentScreen();
				currentScreen->cleanData();
			}

			OkButtonTime_ = 0;
		}

	}
}

void AppletThread::updatePage()
{
	Screen * currentScreen = logitech_->getCurrentScreen();

	QList<Screen *> allScreens = logitech_->getScreenList();

	for (Screen * screen : allScreens)
	{
		screen->update();
	}
	currentScreen->draw();
}