#ifndef SETTINGS_H
#define SETTINGS_H
//-----------------------------------------------------------------
// Settings File
// C++ Header - Settings.h - version 0.1 (2013/06/13)
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Defines.h"
#include <QSettings>
#include "Logitech.h"


//-----------------------------------------------------------------
// Settings Class
//-----------------------------------------------------------------
class HwaSettings
{
public:

    static HwaSettings* getInstance();
	static void releaseResources();

	//---------------------------
	// Destructor
	//---------------------------
    virtual ~HwaSettings();

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

    void setInfluxSettings(InfluxDbSettings);
    InfluxDbSettings getInfluxSettings();

protected:
	//---------------------------
	// Constructor(s)
	//---------------------------
    HwaSettings();

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

    static HwaSettings* singleton_;

	GeneralSettings generalSettings_;
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
    HwaSettings(const HwaSettings& t);
    HwaSettings& operator=(const HwaSettings& t);
};

#endif
