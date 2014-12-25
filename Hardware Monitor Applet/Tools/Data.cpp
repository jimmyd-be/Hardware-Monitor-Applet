//-----------------------------------------------------------------
// Data File
// C++ Source - Data.cpp - version 0.1 (2013/06/13)
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Data.h"

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------
Data * Data::dataInstance = nullptr;

//-----------------------------------------------------------------
// Data methods
//-----------------------------------------------------------------
Data * Data::Instance()
{
	if (dataInstance == nullptr)   // Only allow one instance of class to be generated.
	{
		dataInstance = new Data();
	}
	return dataInstance;
}

void Data::removeInstance()
{
	if (dataInstance != nullptr)
	{
		delete dataInstance;
		dataInstance = nullptr;
	}
}

Data::Data()
{
	MonitorTool * wmi = new WMI();
	MonitorTool * hwinfo = new HWinfo();

	tools_.append(wmi);
	tools_.append(hwinfo);
}

Data::~Data()
{
	for (MonitorTool * monitorSystem : tools_)
	{
		if (monitorSystem != nullptr)
		{
			delete monitorSystem;
			monitorSystem = nullptr;
		}
	}

	tools_.clear();
}

QVector<HardwareSensor> Data::getAllData(MonitorSystem system)
{
	QVector<HardwareSensor> emptyVector;

	for (MonitorTool * monitorSystem : tools_)
	{
		if (monitorSystem->getMonitorSystem() == system)
		{
			return monitorSystem->getAllSensors();
			break;
		}
	}

	return emptyVector;
}