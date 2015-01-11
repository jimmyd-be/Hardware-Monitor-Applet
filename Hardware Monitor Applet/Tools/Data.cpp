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

QStringList Data::translateLines(QList<LineText> lines)
{
	QStringList returnValue;

	for (LineText text : lines)
	{
		QString temp = text.text;

		QMap<QString, QString> values = queryMapData(text.queryMap);

		QMap<QString, QString>::const_iterator i = values.constBegin();

		while (i != values.constEnd())
		{
			temp = temp.replace(i.key(), i.value());
			++i;
		}

		returnValue.append(temp);
	}

	return returnValue;
}

QMap<QString, QString> Data::queryMapData(QMap<QString, Query> map)
{
	QMap<QString, QString> returnmap;

	QMap<QString, Query>::const_iterator i = map.constBegin();
	
	while (i != map.constEnd())
	{
		Query query = i.value();

		QString value = "";

		if (query.system == MonitorSystem::HWiNFO)
		{
			value = getMonitorTool(MonitorSystem::HWiNFO)->getData(query);
		}
		else if (query.system == MonitorSystem::OHM)
		{
			value = getMonitorTool(MonitorSystem::OHM)->getData(query);
		}

		returnmap.insert(i.key(), value);

		++i;
	}

	return returnmap;
}

MonitorTool * Data::getMonitorTool(MonitorSystem system)
{
	for (MonitorTool * tool : tools_)
	{
		if (tool->getMonitorSystem() == system)
		{
			return tool;
		}
	}

	return nullptr;
}