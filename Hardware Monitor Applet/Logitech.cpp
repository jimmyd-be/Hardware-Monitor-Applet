//-----------------------------------------------------------------
// Logitech File
// C++ Source - Logitech.cpp - version 0.1 (2014/09/12)
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Logitech.h"
#include "Settings.h"
#include "AppletThread.h"

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Logitech methods
//-----------------------------------------------------------------
Logitech::Logitech() : keyboardType_(KeyboardTypes::None), time_(0), thread_(nullptr), startscreen_(nullptr), currentScreen_(nullptr), currentMainScreen_(nullptr)
{

}

Logitech::~Logitech()
{
	if (thread_ != nullptr)
	{
		thread_->terminate();
		delete thread_;
		thread_ = nullptr;
	}

	if (startscreen_ != nullptr)
	{
		delete startscreen_;
		startscreen_ = nullptr;
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
			startscreen_ = new StartScreen(&lcd_, "StartScreen");

			currentScreen_ = startscreen_;
		}

		else if (lcd_.IsDeviceAvailable(LG_MONOCHROME))
		{
			keyboardType_ = KeyboardTypes::Monochrome;

			startscreen_ = new StartScreen(&lcd_, "StartScreen");

			currentScreen_ = startscreen_;
		}

		thread_ = new AppletThread(&lcd_, this);

		thread_->start();

		return true;
	}

	return false;
}

KeyboardTypes Logitech::getKeyboardType()
{
	return keyboardType_;
}

QVector<Screen *> Logitech::getScreenList()
{
	return screenList_;
}

Screen * Logitech::getCurrentScreen()
{
	return currentScreen_;
}

void Logitech::createNormalScreen(QString name, QString background, ScreenType type, QMap<QString, Query> dataList, QStringList lines, QList<CustomSettings> settings)
{
	NormalScreen * screen = new NormalScreen(&lcd_, name);
	screen->setBackground(background);
	screen->setData(optimizeLines(optimizeData(lines, dataList)));
	screen->setSettings(settings);

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
	/*GraphScreen * screen = new GraphScreen(&lcd_, name);
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

	screenList_.append(screen);*/
}

void Logitech::creategraphScreen(QString name, QString background, ScreenType type, QList<LineText> linesList, QList<QColor> colors)
{
	/*GraphScreen * screen = new GraphScreen(&lcd_, name);
	screen->setBackground(background);

	screen->setData(linesList);
	screen->setColors(colors);

	screenList_.append(screen);*/
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
	mainOrder_.clear();
	subOrder_.clear();

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

	if (mainOrder_.size() > 0)
	{
		currentScreen_ = mainOrder_[0];
		currentMainScreen_ = mainOrder_[0];
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

	//Remove from mainOrder list
	int mainListPosition = mainOrder_.indexOf(oldScreen);

	if (mainListPosition != -1)
	{
		mainOrder_.removeAt(mainListPosition);
	}

	//Remove from subOrder list
	subOrder_.remove(name);

	for (int i = 0; i < subOrder_.keys().size(); i++)
	{
		QString key = subOrder_.keys()[i];
		QList<Screen*> subList = subOrder_.value(key);

		int subListPosition = subList.indexOf(oldScreen);

		if (subListPosition != -1)
		{
			subList.removeAt(subListPosition);
		}

		subOrder_.remove(key);
		subOrder_.insert(key, subList);
	}

	delete oldScreen;

	if (mainOrder_.size() == 0)
	{
		currentScreen_ = startscreen_;
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

void Logitech::changeCurrentScreen(PageDirection direction)
{
	if (direction == PageDirection::Next)
	{
		int position = mainOrder_.indexOf(currentMainScreen_) + 1;

		if (position >= mainOrder_.size())
		{
			position = 0;
		}

		currentScreen_ = mainOrder_.at(position);
		currentMainScreen_ = mainOrder_.at(position);
	}

	else if (direction == PageDirection::Previous)
	{
		int position = mainOrder_.indexOf(currentMainScreen_) - 1;

		if (position < 0)
		{
			position = mainOrder_.size()-1;
		}

		currentScreen_ = mainOrder_.at(position);
		currentMainScreen_ = mainOrder_.at(position);
	}

	else if (direction == PageDirection::Up)
	{
		QList<Screen *> subScreen = subOrder_.value(currentMainScreen_->getName());

		int currentPosition = subScreen.indexOf(currentScreen_) - 1;

		if (currentPosition < 0)
		{
			currentPosition = subScreen.size()-1;
		}

		currentScreen_ = subScreen.at(currentPosition);
	}

	else if (direction == PageDirection::Down)
	{
		QList<Screen *> subScreen = subOrder_.value(currentMainScreen_->getName());

		int currentPosition = subScreen.indexOf(currentScreen_) + 1;

		if (currentPosition >= subScreen.size())
		{
			currentPosition = 0;
		}

		currentScreen_ = subScreen.at(currentPosition);
	}
}