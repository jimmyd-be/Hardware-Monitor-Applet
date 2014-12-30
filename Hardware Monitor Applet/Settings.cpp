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

			QList<LineText> lines = screens[i]->getLines();

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

		settings_->endArray();
	}
}

void Settings::setLogitech(Logitech * logitech)
{
	logitech_ = logitech;
}