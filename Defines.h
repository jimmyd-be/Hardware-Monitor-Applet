//-----------------------------------------------------------------
// Defines File
// C++ Header - Defines.h - version 0.1 (2014/08/31)
//-----------------------------------------------------------------
#ifndef DEFINES_H
#define DEFINES_H

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#ifdef _WIN32
#include <external\Logitech\EZ_LCD.h>
#include <QtWinExtras\qwinfunctions.h>
#endif

#include <qdir.h>
#include <qpixmap.h>
#include <QVector>
#include <qactiongroup.h>
#include <qobject.h>
#include <qtimer.h>
#include <qfont.h>
#include <qmap.h>
#include <QDir>

enum KeyboardTypes {Color, Monochrome, None};
enum ScreenType {Normal, Graph, Start, Legend, No};
enum QueryValue {Name, Current, Max, Min, Hardware};
enum MonitorSystem { OHM, HWiNFO, NONE };
enum Page{ Page_Intro, Page_Background, Page_Type, Page_Data, Page_LineEdit, Page_GraphEdit, Page_Customize };
enum TemperatureType { Celsius, Fahrenheit };
enum Alignment { Left, Center, Right };
enum PageDirection {Next, Previous, Up, Down};

struct Query{
	MonitorSystem system;
	QString identifier;
	QString name;
	QueryValue value;
	int precision;
	bool addUnit;

	bool operator == (const Query& rhs)
	{
		return system == rhs.system &&
			identifier == rhs.identifier &&
			name == rhs.name &&
			value == rhs.value &&
			precision == rhs.precision &&
			addUnit == rhs.addUnit;
	}
};

struct LineText{
	QString text;
	QMap<QString, Query> queryMap;
    #ifdef _WIN32
    HANDLE textHandle;
    #endif
};

struct GraphLine{
	QString text;
	Query query;
	QColor color;
};

struct GraphSettings{
	int range;
	int yMinRange;
	int yMaxRange;
	bool yAutoRange;
	bool addTitle;
	QFont titleFont;
	QColor titleColor;
};

struct AppletFont{
	QFont name;
	int height;
	double lineSpace;
	QColor color;
};

struct HardwareSensor{
	QString id;
	QString name;
	double value;
	double max;
	double min;
	QString unit;
	QString hardware;
};

struct CustomSettings
{
	Alignment aligment;
	bool textScrolling;
	QFont font;
	QColor fontColor;
	int lineSpacing;
};

struct GeneralSettings
{
	TemperatureType temperature;
	bool autoStart;
	QString language;
};

const QChar degreeChar(0260);

//-----------------------------------------------------------------
// Defines Class
//-----------------------------------------------------------------
class Defines
{
	public:
		static QString getSettingsFolder();
		static QString translateMonitorSystemEnum(MonitorSystem);
		static QString translateQueryValueEnum(QueryValue);
		static QString translateScreenTypeEnum(ScreenType);

		static MonitorSystem translateMonitorSystemEnum(QString);
		static QueryValue translateQueryValueEnum(QString);
		static ScreenType translateScreenTypeEnum(QString);

		static QString translateAligmentEnum(Alignment);
		static Alignment translateAligmentEnum(QString);

		static QString translateTemperatureEnum(TemperatureType);
		static TemperatureType translateTemperatureEnum(QString);

	private:
		//---------------------------
		// Constructor(s)
		//---------------------------
		Defines();
		//---------------------------
		// Destructor
		//---------------------------
		~Defines();
};
#endif
