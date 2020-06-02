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

Settings::Settings() : logitech_(nullptr), generalSettings_(GeneralSettings{ TemperatureType::Celsius })
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

void Settings::setTemperature(TemperatureType temp)
{
	generalSettings_.temperature = temp;

	saveSettings();
}

TemperatureType Settings::getTemperature()
{
	loadGeneralSettings();

	return generalSettings_.temperature;
}

void Settings::setAutoStart(bool autostart)
{
	generalSettings_.autoStart = autostart;

	saveSettings();
}

bool Settings::getAutoStart()
{
	loadGeneralSettings();

	return generalSettings_.autoStart;
}

void Settings::loadSettings()
{
	loadGeneralSettings();

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

			QList<CustomSettings> list = loadCustomSettings();
			NormalScreen* currentScreen = static_cast<NormalScreen*>(logitech_->getScreenData(name));
			currentScreen->setSettings(list);
		}

		else if(type == ScreenType::Graph)
		{
			loadGraphScreenSettings(name, background, type);
		}
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
			query.precision = settings_->value("precision").toInt();
			query.addUnit = settings_->value("addUnit").toBool();

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
	QList<GraphLine> graphData;

	GraphSettings graphSetting;

	graphSetting.addTitle = settings_->value("AddTitle").toBool();
	graphSetting.range = settings_->value("Range").toInt();
	graphSetting.yMinRange = settings_->value("YMinRange").toInt();
	graphSetting.yMaxRange = settings_->value("YMaxRange").toInt();
	graphSetting.yAutoRange = settings_->value("YAutoRange").toBool();

	QColor fontcolor;
	fontcolor.setRed(settings_->value("TitleColorRed").toInt());
	fontcolor.setBlue(settings_->value("TitleColorBlue").toInt());
	fontcolor.setGreen(settings_->value("TitleColorGreen").toInt());

	QFont titleFont;
	titleFont.setPointSize(settings_->value("FontSize").toInt());
	titleFont.setFamily(settings_->value("FontFamily").toString());

	graphSetting.titleColor = fontcolor;
	graphSetting.titleFont = titleFont;

	int graphCount = settings_->beginReadArray("graphData");

	for (int i = 0; i < graphCount; i++)
	{
		settings_->setArrayIndex(i);

		GraphLine line;
		Query query;
		QColor color;

		line.text = settings_->value("Text").toString();

		query.system = Defines::translateMonitorSystemEnum(settings_->value("system").toString());
		query.identifier = settings_->value("id").toString();
		query.name = settings_->value("name").toString();
		query.value = Defines::translateQueryValueEnum(settings_->value("value").toString());
		query.precision = settings_->value("precision").toInt();
		query.addUnit = settings_->value("addUnit").toBool();

		line.query = query;

		color.setRed(settings_->value("ColorRed").toInt());
		color.setGreen(settings_->value("ColorGreen").toInt());
		color.setBlue(settings_->value("ColorBlue").toInt());

		line.color = color;

		graphData.append(line);
	}

	settings_->endArray();

	logitech_->creategraphScreen(name, background, type, graphData, graphSetting);
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

void Settings::saveGeneralSettings()
{
	settings_->beginGroup("General");

	settings_->setValue("Temperature", Defines::translateTemperatureEnum(generalSettings_.temperature));
	settings_->setValue("AutoStart", generalSettings_.autoStart);
	settings_->setValue("Language", generalSettings_.language);

    settings_->setValue("influxPort", generalSettings_.influxDbSettings.port);
    settings_->setValue("influxUsername", generalSettings_.influxDbSettings.username);
    settings_->setValue("influxPassword", generalSettings_.influxDbSettings.password);
    settings_->setValue("influxHostname", generalSettings_.influxDbSettings.hostname);

	settings_->endGroup();
}

void Settings::loadGeneralSettings()
{
	generalSettings_.temperature = Defines::translateTemperatureEnum(settings_->value("General/Temperature").toString());
	generalSettings_.autoStart = settings_->value("General/AutoStart").toBool();
	generalSettings_.language = settings_->value("General/Language").toString();

    InfluxDbSettings influxSettings;

    influxSettings.port =  settings_->value("influxPort").toInt();
    influxSettings.username = settings_->value("influxUsername").toString();
    influxSettings.password = settings_->value("influxPassword").toString();
    influxSettings.hostname = settings_->value("influxHostname").toString();

    generalSettings_.influxDbSettings = influxSettings;
}

void Settings::saveSettings()
{
	if (logitech_ != nullptr)
	{
		settings_->clear();

		saveGeneralSettings();

		QList<Screen*> screens = logitech_->getScreenList();

		settings_->beginWriteArray("pages");

		for (int i = 0; i < screens.size(); i++)
		{
			settings_->setArrayIndex(i);

			settings_->setValue("pageName", screens[i]->getName());
			settings_->setValue("background", screens[i]->getBackground());

			settings_->setValue("type", Defines::translateScreenTypeEnum(screens[i]->getScreenType()));

			if (screens[i]->getScreenType() == ScreenType::Normal)
			{
				saveNormalScreenSettings(static_cast<NormalScreen*>(screens[i]));
				saveCustomSettings(static_cast<NormalScreen*>(screens[i]));
			}
			else if (screens[i]->getScreenType() == ScreenType::Graph)
			{
				saveGraphScreenSettings(static_cast<GraphScreen*>(screens[i]));
			}

		}

		settings_->endArray();

		saveScreenOrder();
	}
}

void Settings::saveNormalScreenSettings(NormalScreen * screen)
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
			settings_->setValue("addUnit", k.value().addUnit);

			index++;
			++k;
		}

		settings_->endArray();
	}
	settings_->endArray();
}

void Settings::saveGraphScreenSettings(GraphScreen * screen)
{
	QList<GraphLine> graphData = screen->getData();

	settings_->setValue("AddTitle", screen->getGraphSettings().addTitle);
	settings_->setValue("Range", screen->getGraphSettings().range);
	settings_->setValue("YMinRange", screen->getGraphSettings().yMinRange);
	settings_->setValue("YMaxRange", screen->getGraphSettings().yMaxRange);
	settings_->setValue("YAutoRange", screen->getGraphSettings().yAutoRange);

	settings_->setValue("TitleColorRed", screen->getGraphSettings().titleColor.red());
	settings_->setValue("TitleColorBlue", screen->getGraphSettings().titleColor.blue());
	settings_->setValue("TitleColorGreen", screen->getGraphSettings().titleColor.green());

	settings_->setValue("FontSize", screen->getGraphSettings().titleFont.pointSize());
	settings_->setValue("FontFamily", screen->getGraphSettings().titleFont.family());


	settings_->beginWriteArray("graphData");

	for (int i = 0; i < graphData.size(); i++)
	{
		settings_->setArrayIndex(i);

		settings_->setValue("Text", graphData[i].text);

		settings_->setValue("system", Defines::translateMonitorSystemEnum(graphData[i].query.system));
		settings_->setValue("id", graphData[i].query.identifier);
		settings_->setValue("name", graphData[i].query.name);
		settings_->setValue("value", graphData[i].query.value);
		settings_->setValue("precision", graphData[i].query.precision);
		settings_->setValue("addUnit", graphData[i].query.addUnit);

		settings_->setValue("ColorRed", graphData[i].color.red());
		settings_->setValue("ColorGreen", graphData[i].color.green());
		settings_->setValue("ColorBlue", graphData[i].color.blue());
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

void Settings::saveCustomSettings(NormalScreen * screen)
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

void Settings::setLanguage(QString language)
{
	generalSettings_.language = language;

	saveSettings();
}

QString Settings::getLanguage()
{
	return generalSettings_.language;
}

void Settings::setInfluxSettings(InfluxDbSettings influxSettings)
{
    generalSettings_.influxDbSettings = influxSettings;

    saveSettings();

}

InfluxDbSettings Settings::getInfluxSettings()
{
    return generalSettings_.influxDbSettings;
}
