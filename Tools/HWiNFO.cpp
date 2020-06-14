//-----------------------------------------------------------------
// HWinfo File
// C++ Source - HWinfo.cpp - version v1.0 (2015-03-14)
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "HWinfo.h"
#include "../HwaSettings.h"

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// HWinfo methods
//-----------------------------------------------------------------

/// <summary>
/// Initializes a new instance of the <see cref="HWinfo"/> class.
/// </summary>
HWinfo::HWinfo()
{
    settings_ = HwaSettings::getInstance();
}

/// <summary>
/// Finalizes an instance of the <see cref="HWinfo"/> class.
/// </summary>
HWinfo::~HWinfo()
{
	// nothing to destroy
}

/// <summary>
/// Query all the sensor details.
/// </summary>
/// <returns>List of HardwareSensor details</returns>
QVector<HardwareSensor> HWinfo::getAllSensors()
{
	QVector<HardwareSensor> sensors;

	HANDLE hHWiNFOMemory = OpenFileMapping(FILE_MAP_READ, FALSE, _T(HWiNFO_SENSORS_MAP_FILE_NAME2));
	if (hHWiNFOMemory)
	{
		PHWiNFO_SENSORS_SHARED_MEM2 pHWiNFOMemory =
			(PHWiNFO_SENSORS_SHARED_MEM2)MapViewOfFile(hHWiNFOMemory, FILE_MAP_READ, 0, 0, 0);

		// loop through all available readings
		for (DWORD dwReading = 0; dwReading < pHWiNFOMemory->dwNumReadingElements; dwReading++)
		{
			HardwareSensor sensor;
			PHWiNFO_SENSORS_READING_ELEMENT reading = (PHWiNFO_SENSORS_READING_ELEMENT)((BYTE*)pHWiNFOMemory +
				pHWiNFOMemory->dwOffsetOfReadingSection +
				(pHWiNFOMemory->dwSizeOfReadingElement * dwReading));

			PHWiNFO_SENSORS_SENSOR_ELEMENT sensorHW = (PHWiNFO_SENSORS_SENSOR_ELEMENT)((BYTE*)pHWiNFOMemory +
					pHWiNFOMemory->dwOffsetOfSensorSection +
					(pHWiNFOMemory->dwSizeOfSensorElement * reading->dwSensorIndex));

			sensor.id = QString::fromStdString(to_string(sensorHW->dwSensorID) + "/" + to_string(reading->dwReadingID) + "/" + to_string(sensorHW->dwSensorInst));
			sensor.name = reading->szLabelUser;
			sensor.hardware = sensorHW->szSensorNameUser;

			sensor.unit = reading->szUnit;

			if (reading->tReading == SENSOR_READING_TYPE::SENSOR_TYPE_TEMP)
			{
				if (settings_->getTemperature() == TemperatureType::Celsius)
				{
					sensor.unit = QString("%1C").arg(degreeChar);
				}
				else if (settings_->getTemperature() == TemperatureType::Fahrenheit)
				{
					sensor.unit = QString("%1F").arg(degreeChar);
				}
			}

			sensor.max = reading->ValueMax;
			sensor.min = reading->ValueMin;
			sensor.value = reading->Value;

			sensors.push_back(sensor);
		}


	}

	return sensors;
}

/// <summary>
/// Gets the monitor system.
/// </summary>
/// <returns>MonitorSystem::HWiNFO</returns>
MonitorSystem HWinfo::getMonitorSystem()
{
	return MonitorSystem::HWiNFO;
}

/// <summary>
/// Query the sensor data by providing the query.
/// </summary>
/// <param name="query">The query</param>
/// <returns>HardwareSensor details</returns>
HardwareSensor HWinfo::getData(Query query)
{
    //TODO add support for new system without HardwareSensor OR Query

	HardwareSensor returnValue;

	if (cacheMap_.contains(query.identifier))
	{
		QPair<PHWiNFO_SENSORS_READING_ELEMENT, PHWiNFO_SENSORS_SENSOR_ELEMENT> reading = cacheMap_.value(query.identifier);

		returnValue.value = transformData(reading.first->Value, reading.first->tReading, reading.first->szUnit);
		returnValue.max = transformData(reading.first->ValueMax, reading.first->tReading, reading.first->szUnit);
		returnValue.min = transformData(reading.first->ValueMin, reading.first->tReading, reading.first->szUnit);
		returnValue.name = reading.first->szLabelUser;
		returnValue.hardware = reading.second->szSensorNameUser;

		if (reading.first->tReading == SENSOR_READING_TYPE::SENSOR_TYPE_TEMP)
		{
			if (settings_->getTemperature() == TemperatureType::Celsius)
			{
				returnValue.unit = QString("%1C").arg(degreeChar);
			}
			else if (settings_->getTemperature() == TemperatureType::Fahrenheit)
			{
				returnValue.unit = QString("%1F").arg(degreeChar);
			}
		}
		else
		{
			returnValue.unit = reading.first->szUnit;
		}
	}
	else
	{
		HANDLE hHWiNFOMemory = OpenFileMapping(FILE_MAP_READ, FALSE, _T(HWiNFO_SENSORS_MAP_FILE_NAME2));
		if (hHWiNFOMemory)
		{
			PHWiNFO_SENSORS_SHARED_MEM2 pHWiNFOMemory =
				(PHWiNFO_SENSORS_SHARED_MEM2)MapViewOfFile(hHWiNFOMemory, FILE_MAP_READ, 0, 0, 0);

			// loop through all available readings
			for (DWORD dwReading = 0; dwReading < pHWiNFOMemory->dwNumReadingElements; dwReading++)
			{
				PHWiNFO_SENSORS_READING_ELEMENT reading = (PHWiNFO_SENSORS_READING_ELEMENT)((BYTE*)pHWiNFOMemory +
					pHWiNFOMemory->dwOffsetOfReadingSection +
					(pHWiNFOMemory->dwSizeOfReadingElement * dwReading));

				PHWiNFO_SENSORS_SENSOR_ELEMENT sensorHW = (PHWiNFO_SENSORS_SENSOR_ELEMENT)((BYTE*)pHWiNFOMemory +
					pHWiNFOMemory->dwOffsetOfSensorSection +
					(pHWiNFOMemory->dwSizeOfSensorElement * reading->dwSensorIndex));

				if (QString::fromStdString(to_string(sensorHW->dwSensorID) + "/" + to_string(reading->dwReadingID) + "/" + to_string(sensorHW->dwSensorInst)) == query.identifier)
				{
					cacheMap_.insert(query.identifier, QPair<PHWiNFO_SENSORS_READING_ELEMENT, PHWiNFO_SENSORS_SENSOR_ELEMENT>(reading, sensorHW));

					returnValue.value = transformData(reading->Value, reading->tReading, reading->szUnit);
					returnValue.max = transformData(reading->ValueMax, reading->tReading, reading->szUnit);
					returnValue.min = transformData(reading->ValueMin, reading->tReading, reading->szUnit);
					returnValue.name = reading->szLabelUser;

					returnValue.hardware = sensorHW->szSensorNameUser;

					if (reading->tReading == SENSOR_READING_TYPE::SENSOR_TYPE_TEMP)
					{
						if (settings_->getTemperature() == TemperatureType::Celsius)
						{
							returnValue.unit = QString("%1C").arg(degreeChar);
						}
						else if (settings_->getTemperature() == TemperatureType::Fahrenheit)
						{
							returnValue.unit = QString("%1F").arg(degreeChar);
						}
					}
					else
					{
						returnValue.unit = reading->szUnit;
					}
					break;
				}

			}
		}
	}

	return returnValue;
}

/// <summary>
/// Transforms the data into a specific unit.
/// For example transform °C to °F and vice versa.
/// </summary>
/// <param name="value">The value.</param>
/// <param name="type">The type.</param>
/// <param name="unit">The unit.</param>
/// <returns>The tranformed value</returns>
double HWinfo::transformData(double value, SENSOR_READING_TYPE type, QString unit)
{
	if (type == SENSOR_READING_TYPE::SENSOR_TYPE_TEMP)
	{
		if (settings_->getTemperature() == TemperatureType::Celsius)
		{
			if (unit.contains("F"))
			{
				value = ((value - 32) * 5) / 9;
			}
		}
		else
		{
			if (unit.contains("C"))
			{
				value = ((value * 9) / 5) + 32;
			}
		}
	}

	return value;
}
