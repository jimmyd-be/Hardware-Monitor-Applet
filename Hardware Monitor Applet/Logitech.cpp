//-----------------------------------------------------------------
// Logitech File
// C++ Source - Logitech.cpp - version 0.1 (2014/09/12)
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Logitech.h"

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Logitech methods
//-----------------------------------------------------------------
Logitech::Logitech() : keyboardType_(KeyboardTypes::None), time_(0), timer_(nullptr), currentPage_(0)
{
}

Logitech::~Logitech()
{
	if (timer_ != nullptr)
	{
		timer_->stop();
		delete timer_;
		timer_ = nullptr;
	}

	for (int i = 0; i < screenList_.length(); i++)
	{
		lcd_.RemovePage(i);
		delete screenList_[i];
	}	
}

bool Logitech::initKeyboard()
{
	HRESULT hRes = lcd_.Initialize(_T("Open Hardware Monitor"), LG_DUAL_MODE, TRUE, TRUE);

	if (hRes == S_OK)
	{

		if (lcd_.IsDeviceAvailable(LG_COLOR))
		{
			keyboardType_ = KeyboardTypes::Color;

			screenList_.push_back(new StartScreen(&lcd_, "StartScreen"));
		}

		else if (lcd_.IsDeviceAvailable(LG_MONOCHROME))
		{
			keyboardType_ = KeyboardTypes::Monochrome;

			screenList_.push_back(new StartScreen(&lcd_, "StartScreen"));
		}

		timer_ = new QTimer(this);
		connect(timer_, SIGNAL(timeout()), this, SLOT(onTimer()));
		timer_->start(30);

		return true;
	}

	return false;
}

void Logitech::onTimer()
{
	time_ += 30;

	checkButtonPresses();

	if (time_ >= 1000)
	{
		updatePage();
		time_ = 0;
	}

	lcd_.Update();
}


VOID Logitech::initLCDObjectsMonochrome()
{
	
	
}

VOID Logitech::initLCDObjectsColor()
{
	

 
}

VOID Logitech::checkButtonPresses()
{
	if (lcd_.IsDeviceAvailable(LG_COLOR))
	{
		checkbuttonPressesColor();
	}

	else if (lcd_.IsDeviceAvailable(LG_MONOCHROME))
	{
		checkbuttonPressesMonochrome();
	}
}

VOID Logitech::checkbuttonPressesMonochrome()
{
	lcd_.ModifyDisplay(LG_MONOCHROME);

	if (lcd_.ButtonTriggered(LG_BUTTON_4))
	{

	}

	else if (lcd_.ButtonTriggered(LG_BUTTON_1))
	{

	}
}

VOID Logitech::checkbuttonPressesColor()
{
	lcd_.ModifyDisplay(LG_COLOR);

	if (lcd_.ButtonTriggered(LG_BUTTON_RIGHT))
	{

	}

	else if (lcd_.ButtonTriggered(LG_BUTTON_LEFT))
	{

	}
}

void Logitech::updatePage()
{
	if (!screenList_.isEmpty())
	{
		screenList_[currentPage_]->update();
	}
	else
	{

	}
}

KeyboardTypes Logitech::getKeyboardType()
{
	return keyboardType_;
}

QVector<Screen *> Logitech::getScreenList()
{
	return screenList_;
}

void Logitech::createPage(QString name, ScreenType type)
{
	if (type == ScreenType::Normal)
	{
		Screen * newScreen = new NormalScreen(&lcd_, name);

		screenList_.push_back(newScreen);
	}
	else if (type == ScreenType::Graph)
	{
		Screen * newScreen = new GraphScreen(&lcd_, name);

		screenList_.push_back(newScreen);
	}

	currentPage_ = screenList_.size() - 1;
}

Screen * Logitech::getScreenData(QString name)
{
	for (Screen * screen : screenList_)
	{
		if (screen->getName() == name)
		{
			return screen;
		}
	}
}

void Logitech::addLine(QString pageName, QString text)
{
	Screen * editScreen = getScreenData(pageName);

	editScreen->addLine(text);
}

void Logitech::clearPage(QString name)
{
	Screen * editScreen = getScreenData(name);

	editScreen->clearLines();
}

void Logitech::removePage(QString name)
{
	Screen * editScreen = getScreenData(name);

}