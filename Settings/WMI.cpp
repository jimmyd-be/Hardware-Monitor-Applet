//-----------------------------------------------------------------
// WMI Object
// C++ Source - WMI.cpp - version v1.0 (2012-08-01)
// 
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "WMI.h"

//-----------------------------------------------------------------
// WMI methods
//-----------------------------------------------------------------
WMI::WMI()
{
	pEnumerator = NULL;
	pLoc = 0;
	pSvc = 0;
	pclsObj = 0;

	hardwareList.clear();
	sensorList.clear();

	connectToWMI();

//	querySensors();
//	queryHardware();
}

WMI::~WMI(void)
{
	pSvc->Release();
	pLoc->Release();
	CoUninitialize();
}

void WMI::connectToWMI()
{
	// Initialize COM. ------------------------------------------

	hres = CoInitializeEx(0, COINIT_MULTITHREADED);

	if (!FAILED(hres))
	{

		// Set general COM security levels --------------------------
		// Note: If you are using Windows 2000, you need to specify -
		// the default authentication credentials for a user by using
		// a SOLE_AUTHENTICATION_LIST structure in the pAuthList ----
		// parameter of CoInitializeSecurity ------------------------

		hres = CoInitializeSecurity(
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


		if (!FAILED(hres))
		{

			// Obtain the initial locator to WMI -------------------------

			hres = CoCreateInstance(
				CLSID_WbemLocator,
				0,
				CLSCTX_INPROC_SERVER,
				IID_IWbemLocator, (LPVOID *) &pLoc);

			if (!FAILED(hres))
			{

				// Connect to WMI through the IWbemLocator::ConnectServer method


				// Connect to the root\cimv2 namespace with
				// the current user and obtain pointer pSvc
				// to make IWbemServices calls.
				hres = pLoc->ConnectServer(
					_bstr_t(L"ROOT\\OpenHardwareMonitor"), // Object path of WMI namespace
					NULL,                    // User name. NULL = current user
					NULL,                    // User password. NULL = current
					0,                       // Locale. NULL indicates current
					NULL,                    // Security flags.
					0,                       // Authority (e.g. Kerberos)
					0,                       // Context object 
					&pSvc                    // pointer to IWbemServices proxy
					);

				if (!FAILED(hres))
				{

					// Set security levels on the proxy -------------------------

					hres = CoSetProxyBlanket(
						pSvc,                        // Indicates the proxy to set
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

void WMI::querySensors()
{
	sensorList.clear();

	if (pSvc != 0)
	{
		// Use the IWbemServices pointer to make requests of WMI ----

		// For example, get the name of the operating system

		hres = pSvc->ExecQuery(
			bstr_t("WQL"),
			bstr_t("select * from Sensor"),
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
			NULL,
			&pEnumerator);

		if (!FAILED(hres))
		{

			// Get the data from the query

			ULONG uReturn = 0;

			while (pEnumerator)
			{
				HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
					&pclsObj, &uReturn);

				if (0 == uReturn)
				{
					break;
				}

				VARIANT vtProp;
				Sensor sensor;

				// Get the value of the Name property
				hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
				wstring ws(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
				sensor.name = string(ws.begin(), ws.end());

				ws.clear();
				VariantClear(&vtProp);

				hr = pclsObj->Get(L"Identifier", 0, &vtProp, 0, 0);
				ws = wstring(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
				sensor.identifier = string(ws.begin(), ws.end());
				ws.clear();
				VariantClear(&vtProp);

				hr = pclsObj->Get(L"Parent", 0, &vtProp, 0, 0);
				ws = wstring(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
				sensor.parent = string(ws.begin(), ws.end());
				ws.clear();
				VariantClear(&vtProp);


				hr = pclsObj->Get(L"ProcessId", 0, &vtProp, 0, 0);
				ws = wstring(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
				sensor.processId = string(ws.begin(), ws.end());
				ws.clear();
				VariantClear(&vtProp);

				hr = pclsObj->Get(L"SensorType", 0, &vtProp, 0, 0);
				ws = wstring(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
				sensor.sensorType = string(ws.begin(), ws.end());
				ws.clear();
				VariantClear(&vtProp);

				hr = pclsObj->Get(L"Index", 0, &vtProp, 0, 0);
				sensor.index = vtProp.intVal;
				VariantClear(&vtProp);

				hr = pclsObj->Get(L"InstanceId", 0, &vtProp, 0, 0);
				ws = wstring(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
				sensor.instanceId = string(ws.begin(), ws.end());
				ws.clear();
				VariantClear(&vtProp);

				hr = pclsObj->Get(L"Max", 0, &vtProp, 0, 0);
				sensor.max = vtProp.fltVal;
				VariantClear(&vtProp);

				hr = pclsObj->Get(L"Min", 0, &vtProp, 0, 0);
				sensor.min = vtProp.fltVal;
				VariantClear(&vtProp);

				hr = pclsObj->Get(L"Value", 0, &vtProp, 0, 0);
				sensor.value = vtProp.fltVal;
				VariantClear(&vtProp);

				pclsObj->Release();

				sensorList.push_back(sensor);

			}
			pEnumerator->Release();
			uReturn = 0;
		}
	}

}

void WMI::queryHardware()
{
	hardwareList.clear();

	if (pSvc != 0)
	{
		// Use the IWbemServices pointer to make requests of WMI ----

		// For example, get the name of the operating system

		hres = pSvc->ExecQuery(
			bstr_t("WQL"),
			bstr_t("select * from Hardware"),
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
			NULL,
			&pEnumerator);

		if (!FAILED(hres))
		{

			// Get the data from the query

			ULONG uReturn = 0;

			while (pEnumerator)
			{
				HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
					&pclsObj, &uReturn);

				if (0 == uReturn)
				{
					break;
				}

				VARIANT vtProp;
				Hardware hardware;

				hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
				wstring ws(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
				hardware.name = string(ws.begin(), ws.end());

				ws.clear();
				VariantClear(&vtProp);

				hr = pclsObj->Get(L"Identifier", 0, &vtProp, 0, 0);
				ws = wstring(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
				hardware.identifier = string(ws.begin(), ws.end());
				ws.clear();
				VariantClear(&vtProp);

				hr = pclsObj->Get(L"Parent", 0, &vtProp, 0, 0);
				ws = wstring(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
				hardware.parent = string(ws.begin(), ws.end());
				ws.clear();
				VariantClear(&vtProp);

				hr = pclsObj->Get(L"ProcessId", 0, &vtProp, 0, 0);
				ws = wstring(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
				hardware.processId = string(ws.begin(), ws.end());
				ws.clear();
				VariantClear(&vtProp);

				hr = pclsObj->Get(L"InstanceId", 0, &vtProp, 0, 0);
				ws = wstring(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
				hardware.InstanceId = string(ws.begin(), ws.end());
				ws.clear();
				VariantClear(&vtProp);
				
				hr = pclsObj->Get(L"HardwareType", 0, &vtProp, 0, 0);
				ws = wstring(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
				hardware.hardwaretype = string(ws.begin(), ws.end());
				ws.clear();
				VariantClear(&vtProp);

				uReturn = 0;
				pclsObj->Release();

				hardwareList.push_back(hardware);
			}
			pEnumerator->Release();

		}
	}
}

void WMI::refresh()
{
	queryHardware();
	querySensors();
}

vector<Sensor> WMI::getSensors(vector<string> hardwareCode)
{
	if (hardwareCode.empty())
	{
		querySensors();
		return sensorList;
	}
	else
	{
		vector<Sensor> sensorListNew;

		if (pSvc != 0)
		{
			string temp = "Parent = '";
			for (int i = 0; i < hardwareCode.size(); i++)
			{
				temp += hardwareCode.at(i);
				temp += "'";

				if (i < hardwareCode.size()-1)
				{
					temp += " or Parent = '";
				}
			}

			string query = "select * from Sensor where " + temp;

			hres = pSvc->ExecQuery(
				bstr_t("WQL"),
				bstr_t(query.c_str()),
				WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
				NULL,
				&pEnumerator);

			if (!FAILED(hres))
			{

				// Get the data from the query

				ULONG uReturn = 0;

				while (pEnumerator)
				{
					HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
						&pclsObj, &uReturn);

					if (0 == uReturn)
					{
						break;
					}

					VARIANT vtProp;
					Sensor sensor;

					// Get the value of the Name property
					hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
					wstring ws(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
					sensor.name = string(ws.begin(), ws.end());

					ws.clear();
					VariantClear(&vtProp);

					hr = pclsObj->Get(L"Identifier", 0, &vtProp, 0, 0);
					ws = wstring(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
					sensor.identifier = string(ws.begin(), ws.end());
					ws.clear();
					VariantClear(&vtProp);

					hr = pclsObj->Get(L"Parent", 0, &vtProp, 0, 0);
					ws = wstring(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
					sensor.parent = string(ws.begin(), ws.end());
					ws.clear();
					VariantClear(&vtProp);


					hr = pclsObj->Get(L"ProcessId", 0, &vtProp, 0, 0);
					ws = wstring(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
					sensor.processId = string(ws.begin(), ws.end());
					ws.clear();
					VariantClear(&vtProp);

					hr = pclsObj->Get(L"SensorType", 0, &vtProp, 0, 0);
					ws = wstring(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
					sensor.sensorType = string(ws.begin(), ws.end());
					ws.clear();
					VariantClear(&vtProp);

					hr = pclsObj->Get(L"Index", 0, &vtProp, 0, 0);
					sensor.index = vtProp.intVal;
					VariantClear(&vtProp);

					hr = pclsObj->Get(L"InstanceId", 0, &vtProp, 0, 0);
					ws = wstring(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
					sensor.instanceId = string(ws.begin(), ws.end());
					ws.clear();
					VariantClear(&vtProp);

					hr = pclsObj->Get(L"Max", 0, &vtProp, 0, 0);
					sensor.max = vtProp.fltVal;
					VariantClear(&vtProp);

					hr = pclsObj->Get(L"Min", 0, &vtProp, 0, 0);
					sensor.min = vtProp.fltVal;
					VariantClear(&vtProp);

					hr = pclsObj->Get(L"Value", 0, &vtProp, 0, 0);
					sensor.value = vtProp.fltVal;
					VariantClear(&vtProp);

					pclsObj->Release();

					sensorListNew.push_back(sensor);

				}
				pEnumerator->Release();
				uReturn = 0;
			}
		}
		return sensorListNew;
	}	
}

vector<Hardware> WMI::getHardware()
{
	if (hardwareList.empty())
	{
		queryHardware();
	}

	return hardwareList;
}

QString WMI::generateCode(QString type, QString id, QString name, int round)
{
	QString code = "{";

	if(type == "Hardware")
	{
		code.append("H,");
	}
	else if(type == "Sensor")
	{
		code.append("S,");
	}

	code.append(id);
	code.append(",");

	code.append(name);
	
	if(round != 0)
	{
		code.append(",");
		code.append(QString::number(round));
	}

	code.append("}");

	return code;
}

string WMI::convertCodeToLine(string code)
{
	int index =0;
	int startPosition = -1;
	QueryCode query;

	for(int i=0; i < code.size(); i++)
	{
		if(code[i] == '{')
		{
			startPosition = i;
		}

		else if(code[i] == '}')
		{
			string test = code.substr(startPosition+1, i-1-startPosition);

			switch(index)
			{
			case 0:	query.type = test;
				break;
			case 1: query.id = test;
				break;
			case 2: query.name = test;
				break;
			case 3: int value = atoi(test.c_str());
				query.round = value;
				break;
			}

			if(query.type == "S")
			{
				query.type = "Sensor";
			}
			else if(query.type == "H")
			{
				query.type = "Hardware";
			}

			if(index < 3)
			{
				query.round = 0;
			}
			codes.push_back(query);

			startPosition = -1;
			index = 0;
		}

		else if(code[i] == ',')
		{
			string test = code.substr(startPosition+1, i-1-startPosition);
			startPosition = i;

			switch(index)
			{
			case 0:	query.type = test;
				break;
			case 1: query.id = test;
				break;
			case 2: query.name = test;
				break;
			case 3:	int value = atoi(test.c_str());
				query.round = value;
				break;
			}

			index++;
		}
	}

	return "";
}

string WMI::queryCode(QueryCode code)
{
	string returnValue = "";

	string query = "select ";
	query.append(code.name);
	query.append(" from ");
	query.append(code.type);
	query.append("where InstanceId = ");
	query.append(code.id);

	if (pSvc != 0)
	{
		// Use the IWbemServices pointer to make requests of WMI ----

		// For example, get the name of the operating system

		hres = pSvc->ExecQuery(
			bstr_t("WQL"),
			bstr_t(query.c_str()),
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
			NULL,
			&pEnumerator);

		if (!FAILED(hres))
		{

			// Get the data from the query

			ULONG uReturn = 0;

			while (pEnumerator)
			{
				HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
					&pclsObj, &uReturn);

				if (0 == uReturn)
				{
					break;
				}

				VARIANT vtProp;

				wstring stemp = std::wstring(code.name.begin(), code.name.end());

				hr = pclsObj->Get(stemp.c_str(), 0, &vtProp, 0, 0);
				wstring ws(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
				returnValue = string(ws.begin(), ws.end());

				ws.clear();
				VariantClear(&vtProp);
				uReturn = 0;
				pclsObj->Release();

			}
			pEnumerator->Release();

		}
	}

	return returnValue;
}

vector<string> WMI::getHardwareIdentifier(QString hardwareName)
{
	vector<string> name;

	if (pSvc != 0)
	{
		// Use the IWbemServices pointer to make requests of WMI ----

		string query = "select * from Hardware where name = '" + hardwareName.toStdString() + "'";

		hres = pSvc->ExecQuery(
			bstr_t("WQL"),
			bstr_t(query.c_str()),
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
			NULL,
			&pEnumerator);

		if (!FAILED(hres))
		{

			// Get the data from the query

			ULONG uReturn = 0;

			while (pEnumerator)
			{
				HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
					&pclsObj, &uReturn);

				if (0 == uReturn)
				{
					break;
				}

				VARIANT vtProp;

				hr = pclsObj->Get(L"Identifier", 0, &vtProp, 0, 0);
				wstring ws(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
				name.push_back(string(ws.begin(), ws.end()));

				ws.clear();
				VariantClear(&vtProp);

				uReturn = 0;
				pclsObj->Release();

			}
			pEnumerator->Release();

		}
	}

	return name;
}