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
	}

	settings_->endArray();
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

void Settings::saveSettings()
{
	if (logitech_ != nullptr)
	{
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

			settings_->endArray();
		}

		settings_->endArray();
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

void Settings::setLogitech(Logitech * logitech)
{
	logitech_ = logitech;
}