#ifndef LOGITECH_H
#define LOGITECH_H
//-----------------------------------------------------------------
// Logitech File
// C++ Header - Logitech.h - version 0.1 (2013/06/13)
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "Defines.h"

#include "Screen/StartScreen.h"
#include "Screen/NormalScreen.h"
#include "Screen/GraphScreen.h"


class HwaSettings;
class AppletThread;

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
	QList<Screen *> getScreenList();

	void createNormalScreen(QString name, QString background, ScreenType type, QMap<QString, Query> dataList, QStringList lines, QList<CustomSettings> settings);
	void createNormalScreen(QString name, QString background, ScreenType type, QList<LineText> lines);
	void creategraphScreen(QString name, QString background, ScreenType type, QMap<QString, Query> dataList, QList<QColor> colors, GraphSettings settings);
	void creategraphScreen(QString name, QString background, ScreenType type, QList<GraphLine> graphData, GraphSettings settings);

	void changeScreenOrder(QList<QString> mainOrder, QMap<QString, QList<QString>> subOrder);
	void deleteScreen(QString name);
	
	Screen * getScreenData(QString);
	Screen * getCurrentScreen();

	QList<Screen *> getMainOrder();
	QMap<QString, QList<Screen *>> getSubOrder();
	
	bool isScreenActive(QString);

	void changeCurrentScreen(PageDirection);

private:
	QList<LineText> optimizeData(QStringList lines, QMap<QString, Query> dataList);
	QList<LineText> optimizeLines(QList<LineText>);

	void openStartScreen();

	// -------------------------
	// Datamembers
	// -------------------------
	KeyboardTypes keyboardType_;
	int time_;
	AppletThread * thread_;
	StartScreen * startscreen_;
	Screen * currentScreen_;
	Screen * currentMainScreen_;
	
    #ifdef _WIN32
	CEzLcd lcd_;
#endif

	QList<Screen *> screenList_;
	QList<Screen *> mainOrder_;
	QMap<QString, QList<Screen *>> subOrder_;
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	Logitech(const Logitech& t);
	Logitech& operator=(const Logitech& t);
};

#endif
