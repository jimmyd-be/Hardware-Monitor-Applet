//-----------------------------------------------------------------
// Settings File
// C++ Source - Settings.cpp - version 0.1 (2013/06/13)
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Settings.h"

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------
Settings* Settings::singleton_ = nullptr;

//-----------------------------------------------------------------
// Settings methods
//-----------------------------------------------------------------
Settings* Settings::getInstance()
{
	if (singleton_ == nullptr)
		singleton_ = new Settings();

	return singleton_;
}

void Settings::releaseResources()
{
	if (singleton_ != nullptr)
	{
		delete singleton_;
		singleton_ = nullptr;
	}
}

Settings::Settings() : logitech_(nullptr)
{
	QString fileName = Defines::getSettingsFolder() + "/settings.ini";
	settings_ = new QSettings(fileName, QSettings::IniFormat);
}

Settings::~Settings()
{
	if (settings_ != nullptr)
	{
		delete settings_;
		settings_ = nullptr;
	}
}

void Settings::loadSettings()
{
	int screenTotal = settings_->beginReadArray("pages");

	for (int i = 0; i < screenTotal; i++)
	{
		settings_->setArrayIndex(i);
		QString name = settings_->value("pageName").toString();
		QString background = settings_->value("background").toString();
		ScreenType type = Defines::translateScreenTypeEnum(settings_->value("type").toString());

		if (type == ScreenType::Normal)
		{
			loadNormalScreenSettings(name, background, type);
		}

		else if(type == ScreenType::Graph)
		{
			loadGraphScreenSettings(name, background, type);
		}

		QList<CustomSettings> list = loadCustomSettings();
		logitech_->getScreenData(name)->setSettings(list);
	}

	settings_->endArray();

	loadScreenOrder();
}

void Settings::loadNormalScreenSettings(QString name, QString background, ScreenType type)
{
	QList<LineText> lines;
	LineText text;

	int totalLines = settings_->beginReadArray("lines");

	for (int j = 0; j < totalLines; j++)
	{
		settings_->setArrayIndex(j);

		QString linesText = settings_->value("text").toString();

		int totalData = settings_->beginReadArray("data");

		QMap<QString, Query> queryMap;

		for (int k = 0; k < totalData; k++)
		{
			settings_->setArrayIndex(k);

			QString key = settings_->value("key").toString();

			Query query;

			query.system = Defines::translateMonitorSystemEnum(settings_->value("system").toString());
			query.identifier = settings_->value("id").toString();
			query.name = settings_->value("name").toString();
			query.value = Defines::translateQueryValueEnum(settings_->value("value").toString());
			settings_->value("precision").toInt();

			queryMap.insert(key, query);
		}

		text.queryMap = queryMap;
		text.text = linesText;

		lines.append(text);

		settings_->endArray();
	}

	logitech_->createNormalScreen(name, background, type, lines);

	settings_->endArray();
}

void Settings::loadGraphScreenSettings(QString name, QString background, ScreenType type)
{
	QList<LineText> lines;
	LineText text;

	int totalLines = settings_->beginReadArray("lines");

	for (int j = 0; j < totalLines; j++)
	{
		settings_->setArrayIndex(j);

		QString linesText = settings_->value("text").toString();

		int totalData = settings_->beginReadArray("data");

		QMap<QString, Query> queryMap;

		for (int k = 0; k < totalData; k++)
		{
			settings_->setArrayIndex(k);

			QString key = settings_->value("key").toString();

			Query query;

			query.system = Defines::translateMonitorSystemEnum(settings_->value("system").toString());
			query.identifier = settings_->value("id").toString();
			query.name = settings_->value("name").toString();
			query.value = Defines::translateQueryValueEnum(settings_->value("value").toString());
			settings_->value("precision").toInt();

			queryMap.insert(key, query);
		}

		text.queryMap = queryMap;
		text.text = linesText;

		lines.append(text);
		settings_->endArray();
	}

	settings_->endArray();

	QList<QColor> colorList;

	int size = settings_->beginReadArray("graphColorData");

	for (int i = 0; i < size; i++)
	{
		settings_->setArrayIndex(i);

		int red = settings_->value("ColorRed").toInt();
		int green = settings_->value("ColorGreen").toInt();
		int bleu = settings_->value("ColorBlue").toInt();

		QColor color(red, green, bleu);

		colorList.append(color);
	}
	
	settings_->endArray();

	logitech_->creategraphScreen(name, background, type, lines, colorList);
}

void Settings::loadScreenOrder()
{
	logitech_->changeScreenOrder(loadMainScreenOrder(), loadSubScreenOrder());
}

QList<QString> Settings::loadMainScreenOrder()
{
	QList<QString> mainList;

	int size = settings_->beginReadArray("MainOrder");

	for (int i = 0; i < size; i++)
	{
		settings_->setArrayIndex(i);

		mainList.append(settings_->value("Page").toString());
	}

	settings_->endArray();

	return mainList;
}

QMap<QString, QList<QString>> Settings::loadSubScreenOrder()
{
	QMap<QString, QList<QString>> subList;

	int size = settings_->beginReadArray("SubOrder");

	for (int i = 0; i < size; i++)
	{
		settings_->setArrayIndex(i);

		QString mainPage = settings_->value("MainPage").toString();

		QList<QString> subSubList;

		int subSize = settings_->beginReadArray("SubSubOrder");

		for (int j = 0; j < subSize; j++)
		{
			settings_->setArrayIndex(j);

			subSubList.append(settings_->value("Page").toString());
		}

		settings_->endArray();

		subList.insert(mainPage, subSubList);
	}
	settings_->endArray();

	return subList;
}

void Settings::saveSettings()
{
	if (logitech_ != nullptr)
	{
		settings_->clear();
		QVector<Screen*> screens = logitech_->getScreenList();

		settings_->beginWriteArray("pages");

		for (int i = 0; i < screens.size(); i++)
		{
			settings_->setArrayIndex(i);

			settings_->setValue("pageName", screens[i]->getName());
			settings_->setValue("background", screens[i]->getBackground());
			settings_->setValue("type", Defines::translateScreenTypeEnum(screens[i]->getScreenType()));

			if (screens[i]->getScreenType() == ScreenType::Normal)
			{
				saveNormalScreenSettings(screens[i]);
			}
			else if (screens[i]->getScreenType() == ScreenType::Graph)
			{
				saveNormalScreenSettings(screens[i]);
				saveGraphScreenSettings(screens[i]);
			}

			saveCustomSettings(screens[i]);
		}

		settings_->endArray();

		saveScreenOrder();
	}
}

void Settings::saveNormalScreenSettings(Screen * screen)
{
	QList<LineText> lines = screen->getLines();

	settings_->beginWriteArray("lines");

	for (int j = 0; j < lines.size(); j++)
	{
		settings_->setArrayIndex(j);
		settings_->setValue("text", lines[j].text);

		settings_->beginWriteArray("data");

		QMap<QString, Query> queryMap = lines[j].queryMap;

		QMap<QString, Query>::const_iterator k = queryMap.constBegin();

		int index = 0;

		while (k != queryMap.constEnd()) {

			settings_->setArrayIndex(index);

			settings_->setValue("key", k.key());

			settings_->setValue("system", Defines::translateMonitorSystemEnum(k.value().system));
			settings_->setValue("id", k.value().identifier);
			settings_->setValue("name", k.value().name);
			settings_->setValue("value", k.value().value);
			settings_->setValue("precision", k.value().precision);

			index++;
			++k;
		}

		settings_->endArray();
	}
	settings_->endArray();
}

void Settings::saveGraphScreenSettings(Screen * screen)
{
	QList<QColor> graphColors = screen->getGraphColors();

	settings_->beginWriteArray("graphColorData");

	for (int i = 0; i < graphColors.size(); i++)
	{
		settings_->setArrayIndex(i);

		settings_->setValue("ColorRed", graphColors[i].red());
		settings_->setValue("ColorGreen", graphColors[i].green());
		settings_->setValue("ColorBlue", graphColors[i].blue());
	}

	settings_->endArray();
}

void Settings::saveScreenOrder()
{
	saveMainScreenOrder();
	saveSubScreenOrder();
}

void Settings::saveMainScreenOrder()
{
	QList<Screen*> mainList = logitech_->getMainOrder();

	settings_->beginWriteArray("MainOrder");

	for (int i = 0; i < mainList.size(); i++)
	{
		settings_->setArrayIndex(i);

		settings_->setValue("Page", mainList[i]->getName());
	}

	settings_->endArray();
}

void Settings::saveSubScreenOrder()
{
	QMap<QString, QList<Screen*>> subList = logitech_->getSubOrder();

	settings_->beginWriteArray("SubOrder");

	QMap<QString, QList<Screen*>>::const_iterator i = subList.constBegin();

	int index = 0;
	
	while (i != subList.constEnd())
	{
		settings_->setArrayIndex(index);

		settings_->setValue("MainPage", i.key());

		QList<Screen*> subSubList = i.value();

		settings_->beginWriteArray("SubSubOrder");

		for (int j = 0; j < subSubList.size(); j++)
		{
			settings_->setArrayIndex(j);

			settings_->setValue("Page", subSubList[j]->getName());
		}

		settings_->endArray();

		index++;
		++i;
	}
	settings_->endArray();
}

void Settings::saveCustomSettings(Screen * screen)
{
	QList<CustomSettings> settingsList = screen->getSettings();

	settings_->beginWriteArray("CustomSettings");

	for (int i = 0; i < settingsList.size(); i++)
	{
		settings_->setArrayIndex(i);

		CustomSettings custom = settingsList[i];

		settings_->setValue("Aligment", Defines::translateAligmentEnum(custom.aligment));
		settings_->setValue("Scrolling", custom.textScrolling);
		settings_->setValue("LineSpacing", custom.lineSpacing);

		settings_->setValue("FontFamily", custom.font.family());
		settings_->setValue("FontSize", custom.font.pointSize());
		settings_->setValue("FontBold", custom.font.bold());
		settings_->setValue("FontItalic", custom.font.italic());

		settings_->setValue("FontColorRed", custom.fontColor.red());
		settings_->setValue("FontColorBlue", custom.fontColor.blue());
		settings_->setValue("FontColorGreen", custom.fontColor.green());		
	}

	settings_->endArray();
}

QList<CustomSettings> Settings::loadCustomSettings()
{
	int size = settings_->beginReadArray("CustomSettings");

	QList<CustomSettings> customList;

	for (int i = 0; i < size; i++)
	{
		settings_->setArrayIndex(i);

		CustomSettings custom;

		custom.aligment = Defines::translateAligmentEnum(settings_->value("Aligment").toString());
		
		custom.textScrolling = settings_->value("Scrolling").toBool();
		custom.lineSpacing = settings_->value("LineSpacing").toInt();

		QFont font;
		font.setFamily(settings_->value("FontFamily").toString());
		font.setPointSize(settings_->value("FontSize").toInt());
		font.setBold(settings_->value("FontBold").toBool());
		font.setItalic(settings_->value("FontItalic").toBool());

		QColor color;
		color.setRed(settings_->value("FontColorRed").toInt());
		color.setBlue(settings_->value("FontColorBlue").toInt());
		color.setGreen(settings_->value("FontColorGreen").toInt());
		
		custom.font = font;
		custom.fontColor = color;

		customList.append(custom);
	}

	settings_->endArray();

	return customList;
}

void Settings::setLogitech(Logitech * logitech)
{
	logitech_ = logitech;
}