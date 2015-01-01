//-----------------------------------------------------------------
// Logitech File
// C++ Source - Logitech.cpp - version 0.1 (2014/09/12)
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Logitech.h"
#include "Settings.h"

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
	HRESULT hRes = lcd_.Initialize(_T("Hardware Monitor Applet"), LG_DUAL_MODE, TRUE, TRUE);

	if (hRes == S_OK)
	{

		if (lcd_.IsDeviceAvailable(LG_COLOR))
		{
			keyboardType_ = KeyboardTypes::Color;
			//startscreen_ = new StartScreen(&lcd_, "StartScreen");
			//screenList_.push_back(startscreen_);
		}

		else if (lcd_.IsDeviceAvailable(LG_MONOCHROME))
		{
			keyboardType_ = KeyboardTypes::Monochrome;

			//startscreen_ = new StartScreen(&lcd_, "StartScreen");

			//screenList_.push_back(startscreen_);
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
	/*if (!screenList_.isEmpty())
	{
		screenList_[currentPage_]->update();
	}
	else
	{

	}*/
}

KeyboardTypes Logitech::getKeyboardType()
{
	return keyboardType_;
}

QVector<Screen *> Logitech::getScreenList()
{
	return screenList_;
}

void Logitech::createNormalScreen(QString name, QString background, ScreenType type, QMap<QString, Query> dataList, QStringList lines)
{
	NormalScreen * screen = new NormalScreen(&lcd_, name);
	screen->setBackground(background);
	screen->setData(optimizeLines(optimizeData(lines, dataList)));

	screenList_.append(screen);
}

void Logitech::createNormalScreen(QString name, QString background, ScreenType type, QList<LineText> lines)
{
	NormalScreen * screen = new NormalScreen(&lcd_, name);
	screen->setBackground(background);
	screen->setData(lines);

	screenList_.append(screen);
}

void Logitech::creategraphScreen(QString name, QString background, ScreenType type, QMap<QString, Query> dataList, QList<QColor> colors)
{
	GraphScreen * screen = new GraphScreen(&lcd_, name);
	screen->setBackground(background);

	QList<LineText> linesList;

	QMap<QString, Query>::const_iterator i = dataList.constBegin();
	while (i != dataList.constEnd())
	{
		LineText newLine;

		newLine.text = i.key();

		QMap<QString, Query> map;
		map.insert(i.key(), i.value());

		newLine.queryMap = map;

		linesList.append(newLine);
		++i;
	}

	screen->setData(linesList);
	screen->setColors(colors);

	screenList_.append(screen);
}

void Logitech::creategraphScreen(QString name, QString background, ScreenType type, QList<LineText> linesList, QList<QColor> colors)
{
	GraphScreen * screen = new GraphScreen(&lcd_, name);
	screen->setBackground(background);

	screen->setData(linesList);
	screen->setColors(colors);

	screenList_.append(screen);
}

QList<LineText> Logitech::optimizeData(QStringList lines, QMap<QString, Query> dataList)
{
	QList<LineText> data;

	for (QString line : lines)
	{
		QMap<QString, Query> optimizedData;

		QMap<QString, Query>::const_iterator i = dataList.constBegin();

		while (i != dataList.constEnd())
		{
			if (line.contains(i.key()))
			{
				optimizedData.insert(i.key(), i.value());
			}
			++i;
		}
		LineText text;
		text.text = line;
		text.queryMap = optimizedData;

		data.append(text);
	}

	return data;
}

QList<LineText> Logitech::optimizeLines(QList<LineText> lines)
{
	while (!lines.isEmpty() && lines.last().text.isEmpty())
	{
		lines.removeLast();
	}

	return lines;
}

void Logitech::changeScreenOrder(QList<QString> mainOrder, QMap<QString, QList<QString>> subOrder)
{
	for (QString page : mainOrder)
	{
		mainOrder_.append(getScreenData(page));
	}

	QMap<QString, QList<Screen *>> subScreenOrder;

	QMap<QString, QList<QString>>::const_iterator i = subOrder.constBegin();
	while (i != subOrder.constEnd())
	{
		QList<QString> oldList = i.value();
		QList<Screen*> newList;

		for (QString page : oldList)
		{
			newList.append(getScreenData(page));
		}

		subOrder_.insert(i.key(), newList);
		++i;
	}
}

void Logitech::deleteScreen(QString name)
{
	Screen * oldScreen = getScreenData(name);

	int position = screenList_.indexOf(oldScreen);

	if (position != -1)
	{
		screenList_.removeAt(position);
	}
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

	return nullptr;
}

bool Logitech::isScreenActive(QString page)
{
	for (int i = 0; i < mainOrder_.size(); i++)
	{
		QString pageName = mainOrder_[i]->getName();
		if (pageName == page)
		{
			return true;
		}

		for (int j = 0; j < subOrder_.value(pageName).size(); j++)
		{
			if (subOrder_.value(pageName)[j]->getName() == page)
			{
				return true;
			}
		}
	}
	return false;
}

QList<Screen *> Logitech::getMainOrder()
{
	return mainOrder_;
}

QMap<QString, QList<Screen *>> Logitech::getSubOrder()
{
	return subOrder_;
}