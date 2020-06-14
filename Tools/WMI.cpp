//-----------------------------------------------------------------
// WMI Object
// C++ Source - WMI.cpp - version v1.0 (2015-03-14)
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "WMI.h"
#include "../HwaSettings.h"

//-----------------------------------------------------------------
// WMI methods
//-----------------------------------------------------------------

/// <summary>
/// Initializes a new instance of the <see cref="WMI"/> class.
/// </summary>
WMI::WMI()
{
	pLoc_ = 0;
	pSvc_ = 0;
	pclsObj_ = 0;

    settings_ = HwaSettings::getInstance();

	connect();

}

/// <summary>
/// Finalizes an instance of the <see cref="WMI"/> class.
/// </summary>
WMI::~WMI(void)
{
	if (pSvc_ != 0)
	{
		pSvc_->Release();
		pSvc_ = 0;
	}

	if (pLoc_ != 0)
	{
		pLoc_->Release();
		pLoc_ = 0;
	}

	CoUninitialize();
}

/// <summary>
/// Connect the application with the Hardware Monitor WMI database
/// </summary>
void WMI::connect()
{
	// Initialize COM. ------------------------------------------

	hres_ = CoInitializeEx(0, COINIT_MULTITHREADED);

	if (!FAILED(hres_))
	{

		// Set general COM security levels --------------------------
		// Note: If you are using Windows 2000, you need to specify -
		// the default authentication credentials for a user by using
		// a SOLE_AUTHENTICATION_LIST structure in the pAuthList ----
		// parameter of CoInitializeSecurity ------------------------

		hres_ = CoInitializeSecurity(
			NULL,
			-1,                          // COM authentication
			NULL,                        // Authentication services
			NULL,                        // Reserved
			RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
			RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
			NULL,                        // Authentication info
			EOAC_NONE,                   // Additional capabilities 
			NULL                         // Reserved
			);


		if (!FAILED(hres_))
		{

			// Obtain the initial locator to WMI -------------------------

			hres_ = CoCreateInstance(
				CLSID_WbemLocator,
				0,
				CLSCTX_INPROC_SERVER,
				IID_IWbemLocator, (LPVOID *)&pLoc_);

			if (!FAILED(hres_))
			{

				// Connect to WMI through the IWbemLocator::ConnectServer method


				// Connect to the root\cimv2 namespace with
				// the current user and obtain pointer pSvc
				// to make IWbemServices calls.
				hres_ = pLoc_->ConnectServer(
					_bstr_t(L"ROOT\\OpenHardwareMonitor"), // Object path of WMI namespace
					NULL,                    // User name. NULL = current user
					NULL,                    // User password. NULL = current
					0,                       // Locale. NULL indicates current
					NULL,                    // Security flags.
					0,                       // Authority (e.g. Kerberos)
					0,                       // Context object 
					&pSvc_                    // pointer to IWbemServices proxy
					);

				if (!FAILED(hres_))
				{

					// Set security levels on the proxy -------------------------

					hres_ = CoSetProxyBlanket(
						pSvc_,                        // Indicates the proxy to set
						RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
						RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
						NULL,                        // Server principal name 
						RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
						RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
						NULL,                        // client identity
						EOAC_NONE                    // proxy capabilities 
						);

				}

			}

		}
	}
}

/// <summary>
/// Query all sensor information
/// </summary>
/// <returns>
/// QVector<HardwareSensor> list of all HardwareSensor
///</returns>
QVector<HardwareSensor> WMI::getAllSensors()
{
	QVector<HardwareSensor> sensors;

	string query = "select * from Sensor";

	if (pSvc_ != 0)
	{
		IEnumWbemClassObject* pEnumerator_;

		hres_ = pSvc_->ExecQuery(
			bstr_t("WQL"),
			bstr_t(query.c_str()),
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
			NULL,
			&pEnumerator_);

		if (!FAILED(hres_))
		{
			ULONG uReturn = 0;
			CIMTYPE pType;

			while (pEnumerator_)
			{
				HardwareSensor currentSensor;
				QString sensorType = "";
				QString hardwareIdentifier = "";

				HRESULT hr = pEnumerator_->Next(WBEM_INFINITE, 1,
					&pclsObj_, &uReturn);

				if (0 == uReturn)
				{
					break;
				}

				VARIANT vtProp;

				wstring stemp = _T("Identifier");

				hr = pclsObj_->Get(stemp.c_str(), 0, &vtProp, &pType, 0);

				if (!FAILED(hr))
				{
					wstring ws(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
					currentSensor.id = QString::fromStdString(string(ws.begin(), ws.end()));
					ws.clear();

					hr = 0;
				}

				stemp = _T("SensorType");

				hr = pclsObj_->Get(stemp.c_str(), 0, &vtProp, &pType, 0);

				if (!FAILED(hr))
				{
					wstring ws(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
					sensorType = QString::fromStdString(string(ws.begin(), ws.end()));
					ws.clear();

					hr = 0;
				}

				stemp = _T("Max");

				hr = pclsObj_->Get(stemp.c_str(), 0, &vtProp, &pType, 0);

				if (!FAILED(hr))
				{
					currentSensor.max = transformData(vtProp.fltVal, sensorType);

					hr = 0;
				}

				stemp = _T("Min");

				hr = pclsObj_->Get(stemp.c_str(), 0, &vtProp, &pType, 0);

				if (!FAILED(hr))
				{
					currentSensor.min = transformData(vtProp.fltVal, sensorType);

					hr = 0;
				}

				stemp = _T("Value");

				hr = pclsObj_->Get(stemp.c_str(), 0, &vtProp, &pType, 0);

				if (!FAILED(hr))
				{
					currentSensor.value = transformData(vtProp.fltVal, sensorType);

					hr = 0;
				}

				stemp = _T("Name");

				hr = pclsObj_->Get(stemp.c_str(), 0, &vtProp, &pType, 0);

				if (!FAILED(hr))
				{
					wstring ws(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
					currentSensor.name = QString::fromStdString(string(ws.begin(), ws.end())) + " " + sensorType;
					ws.clear();

					hr = 0;
				}

				stemp = _T("Parent");

				hr = pclsObj_->Get(stemp.c_str(), 0, &vtProp, &pType, 0);

				if (!FAILED(hr))
				{
					wstring ws(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
					hardwareIdentifier = QString::fromStdString(string(ws.begin(), ws.end()));
					ws.clear();

					hr = 0;
				}

				currentSensor.hardware = findHardware(hardwareIdentifier);

				VariantClear(&vtProp);
				uReturn = 0;
				pclsObj_->Release();

				currentSensor.unit = getUnit(sensorType);

				sensors.push_back(currentSensor);

			}
			pEnumerator_->Release();
		}
	}

	return sensors;
}

/// <summary>
/// Gets the monitor system.
/// </summary>
/// <returns>MonitorSystem</returns>
MonitorSystem WMI::getMonitorSystem()
{
	return MonitorSystem::OHM;
}

/// <summary>
/// Get the queried data from incomming query
/// </summary>
/// <param name="query">The query of the requested data.</param>
/// <returns>HardwareSensor</returns>
HardwareSensor WMI::getData(Query query)
{
    //TODO add support for new system without HardwareSensor OR Query
	HardwareSensor returnValue;

	string queryString = "select * from Sensor WHERE Identifier = '" + query.identifier.toStdString() + "'";

	if (pSvc_ != 0)
	{
		IEnumWbemClassObject* pEnumerator = nullptr;

		hres_ = pSvc_->ExecQuery(
			bstr_t("WQL"),
			bstr_t(queryString.c_str()),
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
			NULL,
			&pEnumerator);

		if (!FAILED(hres_))
		{
			ULONG uReturn = 0;
			CIMTYPE pType;

			while (pEnumerator)
			{
				QString sensorType = "";
				QString hardwareIdentifier = "";

				HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
					&pclsObj_, &uReturn);

				if (0 == uReturn)
				{
					break;
				}

				VARIANT vtProp;

				wstring stemp = _T("SensorType");

				hr = pclsObj_->Get(stemp.c_str(), 0, &vtProp, &pType, 0);

				if (!FAILED(hr))
				{
					wstring ws(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
					sensorType = QString::fromStdString(string(ws.begin(), ws.end()));
					ws.clear();

					hr = 0;
				}

				stemp = _T("Max");

				hr = pclsObj_->Get(stemp.c_str(), 0, &vtProp, &pType, 0);

				if (!FAILED(hr))
				{
					returnValue.max = transformData(vtProp.fltVal, sensorType);

					hr = 0;
				}

				stemp = _T("Min");

				hr = pclsObj_->Get(stemp.c_str(), 0, &vtProp, &pType, 0);

				if (!FAILED(hr))
				{
					returnValue.min = transformData(vtProp.fltVal, sensorType);

					hr = 0;
				}

				stemp = _T("Value");

				hr = pclsObj_->Get(stemp.c_str(), 0, &vtProp, &pType, 0);

				if (!FAILED(hr))
				{
					returnValue.value = transformData(vtProp.fltVal, sensorType);

					hr = 0;
				}

				stemp = _T("Name");

				hr = pclsObj_->Get(stemp.c_str(), 0, &vtProp, &pType, 0);

				if (!FAILED(hr))
				{
					wstring ws(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
					returnValue.name = QString::fromStdString(string(ws.begin(), ws.end()));
					ws.clear();

					hr = 0;
				}

				stemp = _T("Parent");

				hr = pclsObj_->Get(stemp.c_str(), 0, &vtProp, &pType, 0);

				if (!FAILED(hr))
				{
					wstring ws(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
					hardwareIdentifier = QString::fromStdString(string(ws.begin(), ws.end()));
					ws.clear();

					hr = 0;
				}

				returnValue.hardware = findHardware(hardwareIdentifier);

				VariantClear(&vtProp);
				uReturn = 0;
				pclsObj_->Release();

				returnValue.unit = getUnit(sensorType);


			}
			pEnumerator->Release();
		}
	}

	return returnValue;
}

/// <summary>
/// Get the unit for a sensor type
/// </summary>
/// <param name="sensorType">Type of the sensor.</param>
/// <returns>The unit for that specific type of sensor</returns>
QString WMI::getUnit(QString sensorType)
{
	if (sensorType == "Fan")
	{
		return  "RPM";
	}
	else if (sensorType == "Load")
	{
		return  "%";
	}
	else if (sensorType == "Clock")
	{
		return  "MHz";
	}
	else if (sensorType == "Power")
	{
		return "W";
	}
	else if (sensorType == "Control")
	{
		return  "%";
	}
	else if (sensorType == "Temperature")
	{
		if (settings_->getTemperature() == TemperatureType::Celsius)
		{
			return  QString("%1C").arg(degreeChar);
		}
		else
		{
			return  QString("%1F").arg(degreeChar);
		}
	}
	else if (sensorType == "Data")
	{
		return  "GB";
	}

	else if (sensorType == "Voltage")
	{
		return  "V";
	}

	return "";
}

/// <summary>
/// Transforms the data to the correct unit.
/// For example °C to °F and vice versa
/// </summary>
/// <param name="value">The value of that sensor type</param>
/// <param name="sensorType">Type of the sensor.</param>
/// <returns>Calculated value</returns>
float WMI::transformData(float value, QString sensorType)
{
	if (sensorType == "Temperature")
	{
		if (settings_->getTemperature() == TemperatureType::Fahrenheit)
		{
			value = ((value * 9) / 5) + 32;
		}
	}

	return value;
}

/// <summary>
/// Queried the hardware details from the WMI database by Identifier.
/// </summary>
/// <param name="identifier">The identifier of the hardware</param>
/// <returns>The name of the queried hardware</returns>
QString WMI::findHardware(QString identifier)
{
	string queryString = "select * from Hardware WHERE Identifier = '" + identifier.toStdString() + "'";

	QString hardware = "";

	if (pSvc_ != 0)
	{
		IEnumWbemClassObject* pEnumerator = nullptr;

		hres_ = pSvc_->ExecQuery(
			bstr_t("WQL"),
			bstr_t(queryString.c_str()),
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
			NULL,
			&pEnumerator);

		if (!FAILED(hres_))
		{
			ULONG uReturn = 0;
			CIMTYPE pType;

			while (pEnumerator)
			{
				HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
					&pclsObj_, &uReturn);

				if (0 == uReturn)
				{
					break;
				}

				VARIANT vtProp;

				wstring stemp = _T("Name");

				hr = pclsObj_->Get(stemp.c_str(), 0, &vtProp, &pType, 0);

				if (!FAILED(hr))
				{
					wstring ws(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
					hardware = QString::fromStdString(string(ws.begin(), ws.end()));
					ws.clear();

					hr = 0;
				}

				VariantClear(&vtProp);
				uReturn = 0;
			}
			pEnumerator->Release();
		}
	}

	return hardware;
}
