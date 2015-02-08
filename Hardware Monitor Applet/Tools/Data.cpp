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

QList<double> Data::translateLines(QList<GraphLine> lines)
{
	QList<double> returnValue;

	for (GraphLine line : lines)
	{
		Query query = line.query;

		HardwareSensor sensor = getMonitorTool(query.system)->getData(query);

		switch (query.value)
		{
		case Name:
			returnValue.append(0);
		case Current:
			returnValue.append(sensor.value);
			break;
		case Max:
			returnValue.append(sensor.max);
			break;
		case Min:
			returnValue.append(sensor.min);
			break;
		}

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

		HardwareSensor sensor = getMonitorTool(query.system)->getData(query);

		switch (query.value)
		{
		case Name:
			value = sensor.name;
		case Current:
			value = QString::number(sensor.value, 'f', query.precision);
			break;
		case Max:
			value = QString::number(sensor.max, 'f', query.precision);
			break;
		case Min:
			value = QString::number(sensor.min, 'f', query.precision);
			break;
		}

		if (query.addUnit && query.value != QueryValue::Name)
		{
			value += sensor.unit;
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