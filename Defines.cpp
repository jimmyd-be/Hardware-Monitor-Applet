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
    QString directory;
    #ifdef _WIN32
    directory = QDir::homePath() + "/AppData/Roaming/Hardware Monitor Applet";
    #elif __linux__
    directory = QDir::home().absolutePath() + "/.config/HWA";
    #endif
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
     default:
        return "NONE";
	};
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
	case QueryValue::Hardware:
		return "Hardware";
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
	QueryValue value = QueryValue::Current;

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
		else if (string == "Hardware")
		{
			value = QueryValue::Hardware;
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

ScreenType Defines::translateScreenTypeEnum(QString type)
{
	if (type == "Graph")
	{
		return ScreenType::Graph;
	}
	else if (type == "Normal")
	{
		return ScreenType::Normal;
	}
	else if (type == "Start")
	{
		return ScreenType::Start;
	}

	return ScreenType::No;
}

QString Defines::translateAligmentEnum(Alignment aligment)
{
	if (aligment == Alignment::Center)
	{
		return "Center";
	}
	else if (aligment == Alignment::Left)
	{
		return "Left";
	}
	else if (aligment == Alignment::Right)
	{
		return "Right";
	}

	return "Left";
}

Alignment Defines::translateAligmentEnum(QString aligment)
{
	if (aligment == "Center")
	{
		return Alignment::Center;
	}
	else if (aligment == "Left")
	{
		return Alignment::Left;
	}
	else if (aligment == "Right")
	{
		return Alignment::Right;
	}

	return Alignment::Center;
}

QString Defines::translateTemperatureEnum(TemperatureType temp)
{
	switch (temp)
	{
	case Celsius:
		return "Celsius";
		break;
	case Fahrenheit:
		return "Fahrenheit";
		break;
	default:
		return "Celsius";
		break;
	}
}

TemperatureType Defines::translateTemperatureEnum(QString temp)
{
	if (temp == "Celsius")
	{
		return TemperatureType::Celsius;
	}
	else if (temp == "Fahrenheit")
	{
		return TemperatureType::Fahrenheit;
	}

	return TemperatureType::Celsius;
}
