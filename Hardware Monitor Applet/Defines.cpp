//-----------------------------------------------------------------
// Defines File
// C++ Source - Defines.cpp - version 0.1 (2013/06/13)
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Defines.h"

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Defines methods
//-----------------------------------------------------------------
Defines::Defines()
{
}

Defines::~Defines()
{
}

QString Defines::getSettingsFolder()
{
	QString directory = QDir::homePath() + "/AppData/Roaming/HMApplet";

	QDir dir(directory);

	if (!dir.exists())
	{
		dir.mkpath(directory);
	}

	return directory;
}

QString Defines::translateMonitorSystemEnum(MonitorSystem system)
{
	switch (system)
	{
	case MonitorSystem::HWiNFO:
		return "HWiNFO";
		break;
	case MonitorSystem::OHM:
		return "OHM";
		break;
	};

	return "NONE";
}

QString Defines::translateQueryValueEnum(QueryValue value)
{
	switch (value)
	{
	case QueryValue::Current:
		return "Current";
		break;

	case QueryValue::Max:
		return "Max";
		break;
	case QueryValue::Min:
		return "Min";
		break;
	case QueryValue::Name:
		return "Name";
		break;
	};

	return "";
}

MonitorSystem Defines::translateMonitorSystemEnum(QString string)
{
	if (string == "HWiNFO")
	{
		return MonitorSystem::HWiNFO;
	}
	else if (string == "OHM")
	{
		return MonitorSystem::OHM;
	}

	return MonitorSystem::NONE;
}

QueryValue Defines::translateQueryValueEnum(QString string)
{
	QueryValue value;

		if (string == "Current")
		{
			value = QueryValue::Current;
		}
		else if (string == "Max")
		{
			value = QueryValue::Max;
		}
		else if (string == "Min")
		{
			value = QueryValue::Min;
		}
		else if (string == "Name")
		{
			value = QueryValue::Name;
		}

		return value;
}

QString Defines::translateScreenTypeEnum(ScreenType type)
{
	if (type == ScreenType::Graph)
	{
		return "Graph";
	}
	else if (type == ScreenType::Normal)
	{
		return "Normal";
	}
	else if (type == ScreenType::Start)
	{
		return "Start";
	}

	return "No";
}