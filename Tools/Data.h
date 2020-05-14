//-----------------------------------------------------------------
// Data File
// C++ Header - Data.h - version v1.0 (2015-03-14)
//-----------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "../Defines.h"
#include "HWiNFO.h"
#include "WMI.h"

//-----------------------------------------------------------------
// Data Class
//-----------------------------------------------------------------
class Data
{
public:
	static Data * Instance();
	static void removeInstance();

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~Data();

	//---------------------------
	// General Methods
	//---------------------------
	QVector<HardwareSensor> getAllData(MonitorSystem system);
	QStringList translateLines(QList<LineText>);
	QList<double> translateLines(QList<GraphLine>);

	HardwareSensor translateLine(Query);

private:
	//---------------------------
	// Constructor(s)
	//---------------------------
	Data();
	// -------------------------
	// Datamembers
	// -------------------------
	QList<MonitorTool *> tools_;
	GeneralSettings settings_;

	QMap<QString, QString> queryMapData(QMap<QString, Query>);
	MonitorTool * getMonitorTool(MonitorSystem);

	static Data* dataInstance;
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	Data(const Data& t);
	Data& operator=(const Data& t);
};