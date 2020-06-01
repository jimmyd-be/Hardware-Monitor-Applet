//-----------------------------------------------------------------
// GraphScreen File
// C++ Header - GraphScreen.h - version 0.1 (2013/06/13)
//-----------------------------------------------------------------
#ifndef GRAPHSCREEN_H
#define GRAPHSCREEN_H

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Screen.h"
#include "../external/QCustomPlot/qcustomplot.h"
#include "LegendScreen.h"

//-----------------------------------------------------------------
// GraphScreen Class
//-----------------------------------------------------------------
class GraphScreen : public Screen
{
public:
	//---------------------------
	// Constructor(s)
	//---------------------------

#ifdef __linux__
    GraphScreen(QString);
#elif _WIN32
    GraphScreen(CEzLcd *, QString);
#endif

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~GraphScreen();

	//---------------------------
	// General Methods
	//---------------------------
	void draw();
	void update();

	ScreenType getScreenType();

	void setData(QList<GraphLine>);

	QList<GraphLine> getData();

	void setBackground(QString background);

	void cleanData();
	void openCustomScreen();
	void setSettings(GraphSettings settings);

	GraphSettings getGraphSettings();

private:
	void createPlot();

	// -------------------------
	// Datamembers
	// -------------------------
	QList<GraphLine> graphData_;
	QCustomPlot * plot_;
	int Xpos_;
    #ifdef _WIN32
	HANDLE bitmapHandle_;
	HBITMAP bitmap_;
    #endif
	LegendScreen * legendScreen_;
	bool legendOpen_;
	GraphSettings settings_;
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	GraphScreen(const GraphScreen& t);
	GraphScreen& operator=(const GraphScreen& t);
};

#endif
