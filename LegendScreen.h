//-----------------------------------------------------------------
// LegendScreen File
// C++ Header - LegendScreen.h - version 0.1 (2013/06/13)
//-----------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Screen.h"
#include "../external/QCustomPlot/qcustomplot.h"


//-----------------------------------------------------------------
// LegendScreen Class
//-----------------------------------------------------------------
class LegendScreen : public Screen
{
public:
	//---------------------------
	// Constructor(s)
	//---------------------------
	LegendScreen(CEzLcd *, QString);

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~LegendScreen();

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

private:

	// -------------------------
	// Datamembers
	// -------------------------
	QList<GraphLine> graphData_;

	HANDLE bitmapHandle_;
	HBITMAP bitmap_;

	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	LegendScreen(const LegendScreen& t);
	LegendScreen& operator=(const LegendScreen& t);
};