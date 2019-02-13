//-----------------------------------------------------------------
// Settings File
// C++ Header - Settings.h - version 0.1 (2013/06/13)
//-----------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Defines.h"
#include <QSettings>
#include "Logitech.h"

//-----------------------------------------------------------------
// Settings Class
//-----------------------------------------------------------------
class Settings
{
public:

	static Settings* getInstance();
	static void releaseResources();

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~Settings();

	//---------------------------
	// General Methods
	//---------------------------
	void setLogitech(Logitech * logitech);
	void loadSettings();
	void saveSettings();

	void setTemperature(TemperatureType);
	TemperatureType getTemperature();

	void setAutoStart(bool);
	bool getAutoStart();

	void setLanguage(QString);
	QString getLanguage();

protected:
	//---------------------------
	// Constructor(s)
	//---------------------------
	Settings();

private:
	void saveNormalScreenSettings(NormalScreen *);
	void saveGraphScreenSettings(GraphScreen *);
	void saveScreenOrder();
	void saveMainScreenOrder();
	void saveSubScreenOrder();
	void saveCustomSettings(NormalScreen *);
	void saveGeneralSettings();

	void loadGeneralSettings();
	QList<CustomSettings> loadCustomSettings();
	void loadNormalScreenSettings(QString, QString, ScreenType);
	void loadGraphScreenSettings(QString, QString, ScreenType);
	void loadScreenOrder();
	QList<QString> loadMainScreenOrder();
	QMap<QString, QList<QString>> loadSubScreenOrder();

	// -------------------------
	// Datamembers
	// -------------------------
	QSettings * settings_;
	Logitech * logitech_;

	static Settings* singleton_;

	GeneralSettings generalSettings_;
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	Settings(const Settings& t);
	Settings& operator=(const Settings& t);
};