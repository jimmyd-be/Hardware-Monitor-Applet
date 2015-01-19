//-----------------------------------------------------------------
// WMI Object
// C++ Source - WMI.cpp - version v1.0 (2012-08-01)
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "WMI.h"
#include "../Settings.h"

//-----------------------------------------------------------------
// WMI methods
//-----------------------------------------------------------------
WMI::WMI()
{
	pEnumerator_ = NULL;
	pLoc_ = 0;
	pSvc_ = 0;
	pclsObj_ = 0;

	settings_ = Settings::getInstance();

	connect();

}

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

void WMI::connect()
{
	// Initialize COM. ------------------------------------------

	hres_ = CoInitializeEx(0, COINIT_APARTMENTTHREADED);

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

QVector<HardwareSensor> WMI::getAllSensors()
{
	QVector<HardwareSensor> sensors;

	string query = "select * from Sensor";

	if (pSvc_ != 0)
	{

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
					currentSensor.max = QString::number(transformData(vtProp.fltVal, sensorType), 'f', 2);

					hr = 0;
				}

				stemp = _T("Min");

				hr = pclsObj_->Get(stemp.c_str(), 0, &vtProp, &pType, 0);

				if (!FAILED(hr))
				{
					currentSensor.min = QString::number(transformData(vtProp.fltVal, sensorType), 'f', 2);

					hr = 0;
				}

				stemp = _T("Value");

				hr = pclsObj_->Get(stemp.c_str(), 0, &vtProp, &pType, 0);

				if (!FAILED(hr))
				{
					currentSensor.value = QString::number(transformData(vtProp.fltVal, sensorType), 'f', 2);

					hr = 0;
				}

				stemp = _T("Name");

				hr = pclsObj_->Get(stemp.c_str(), 0, &vtProp, &pType, 0);

				if (!FAILED(hr))
				{
					wstring ws(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
					currentSensor.name = QString::fromStdString(string(ws.begin(), ws.end()));
					ws.clear();

					hr = 0;
				}

				VariantClear(&vtProp);
				uReturn = 0;
				pclsObj_->Release();

				sensors.push_back(addUnit(currentSensor, sensorType));

			}
			pEnumerator_->Release();
		}
	}

	return sensors;
}

MonitorSystem WMI::getMonitorSystem()
{
	return MonitorSystem::OHM;
}

QString WMI::getData(Query query)
{

	return "";
}

HardwareSensor WMI::addUnit(HardwareSensor currentSensor, QString sensorType)
{
	if (sensorType == "Fan")
	{
		currentSensor.max += "RPM";
		currentSensor.min += "RPM";
		currentSensor.value += "RPM";
	}
	else if (sensorType == "Load")
	{
		currentSensor.max += "%";
		currentSensor.min += "%";
		currentSensor.value += "%";
	}
	else if (sensorType == "Clock")
	{
		currentSensor.max += "MHz";
		currentSensor.min += "MHz";
		currentSensor.value += "MHz";
	}
	else if (sensorType == "Power")
	{
		currentSensor.max += "W";
		currentSensor.min += "W";
		currentSensor.value += "W";
	}
	else if (sensorType == "Control")
	{
		currentSensor.max += "%";
		currentSensor.min += "%";
		currentSensor.value += "%";
	}
	else if (sensorType == "Temperature")
	{
		if (settings_->getTemperature() == TemperatureType::Celsius)
		{
			currentSensor.max += QString("%1C").arg(degreeChar);
			currentSensor.min += QString("%1C").arg(degreeChar);
			currentSensor.value += QString("%1C").arg(degreeChar);
		}
		else
		{
			currentSensor.max += QString("%1F").arg(degreeChar);
			currentSensor.min += QString("%1F").arg(degreeChar);
			currentSensor.value += QString("%1F").arg(degreeChar);
		}
	}
	else if (sensorType == "Data")
	{
		currentSensor.max += "GB";
		currentSensor.min += "GB";
		currentSensor.value += "GB";
	}

	else if (sensorType == "Voltage")
	{
		currentSensor.max += "V";
		currentSensor.min += "V";
		currentSensor.value += "V";
	}

	return currentSensor;
}

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