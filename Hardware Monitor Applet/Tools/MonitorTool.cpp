//-----------------------------------------------------------------
// MonitorTool File
// C++ Source - MonitorTool.cpp - version 0.1 (2013/06/13)
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "MonitorTool.h"

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// MonitorTool methods
//-----------------------------------------------------------------
MonitorTool::MonitorTool()
{
	// nothing to create
}

MonitorTool::~MonitorTool()
{
	// nothing to destroy
}

QVector<HardwareSensor> MonitorTool::getAllSensors()
{
	QVector<HardwareSensor> sensors;

	return sensors;
}

MonitorSystem MonitorTool::getMonitorSystem()
{
	return MonitorSystem::NONE;
}

QString MonitorTool::getData(Query query)
{
	return "";
}