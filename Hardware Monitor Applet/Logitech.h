//-----------------------------------------------------------------
// Logitech File
// C++ Header - Logitech.h - version 0.1 (2013/06/13)
//-----------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "Defines.h"

#include "StartScreen.h"
#include "NormalScreen.h"
#include "GraphScreen.h"

class Settings;

//-----------------------------------------------------------------
// Logitech Class
//-----------------------------------------------------------------
class Logitech: public QObject
{
//	Q_OBJECT

public:
	//---------------------------
	// Constructor(s)
	//---------------------------
	Logitech();

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~Logitech();

	//---------------------------
	// General Methods
	//---------------------------
	bool initKeyboard();
	KeyboardTypes getKeyboardType();
	QVector<Screen *> getScreenList();

	void createNormalScreen(QString name, QString background, ScreenType type, QMap<QString, Query> dataList, QStringList lines);
	void createNormalScreen(QString name, QString background, ScreenType type, QList<LineText> lines);
	void creategraphScreen(QString name, QString background, ScreenType type, QMap<QString, Query> dataList, QList<QColor> colors);
	void creategraphScreen(QString name, QString background, ScreenType type, QList<LineText> linesList, QList<QColor> colors);
	void deleteScreen(QString name);
	
	Screen * getScreenData(QString);
	/*void createPage(QString name, ScreenType type);
	void addLine(QString pageName, QString text, QMap<QString, Query> dataMap);
	void addFont(QString pageName, AppletFont font);
	void addBackground(QString pageName, QString background);
	void clearPage(QString name);
	void removePage(QString name);*/

private:
	void initLCDObjectsMonochrome();
	void initLCDObjectsColor();
	void checkButtonPresses();
	void checkbuttonPressesMonochrome();
	void checkbuttonPressesColor();
	void updatePage();


	QList<LineText> optimizeData(QStringList lines, QMap<QString, Query> dataList);
	QList<LineText> optimizeLines(QList<LineText>);

	// -------------------------
	// Datamembers
	// -------------------------
	CEzLcd lcd_;
	QTimer * timer_;
	int time_;
	KeyboardTypes keyboardType_;
	QVector<Screen *> screenList_;
	StartScreen * startscreen_;
	int currentPage_;
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	Logitech(const Logitech& t);
	Logitech& operator=(const Logitech& t);

	private slots:
	void onTimer();
};