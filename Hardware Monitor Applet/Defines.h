#pragma once

#include <external\Logitech\EZ_LCD.h>
#include <qdir.h>
#include <qpixmap.h>
#include <QtWinExtras\qwinfunctions.h>
#include <QVector>
#include <qactiongroup.h>
#include <qobject.h>
#include <qtimer.h>
#include <qfont.h>
#include <qmap.h>

enum KeyboardTypes {Color, Monochrome, None};
enum ScreenType {Normal, Graph, Start, No};
enum QueryType {Sensor, Hardware};
enum QueryValue {Name, Current, Max, Min};

struct Query{
	QString identifier;
	QueryType type;
	QueryValue value;
};

struct LineText{
	QString text;
	QFont font;
	QMap<QString, Query> queryMap;
	HANDLE textHandle;
};