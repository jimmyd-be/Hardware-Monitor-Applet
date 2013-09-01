//-----------------------------------------------------------------
// WMI Object
// C++ Source - WMI.cpp - version v1.0 (2012-08-01)
// 
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "stdafx.h"

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

	connectToWMI();

	CPUName = "";
	CPUIdentifier = "";
	CPUClock.clear();
	cpuLoad.clear();
	cpuTemp.clear();

	GPUName.clear();
	GPUIdentifier.clear();
	GPULoad.clear();
	GPUTemp.clear();
	GPUFan.clear();
	GPUClock.clear();
	GPUMemoryClock.clear();

	HDDName.clear();
	HDDIdentifier.clear();
	HDDTemperature.clear();
	HDDLoad.clear();
}

WMI::~WMI(void)
{
	pSvc->Release();
	pLoc->Release();
	CoUninitialize();
}

void WMI::connectToWMI()
{
	try
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
	catch (exception e)
	{
		Error::writeMessage("Can't open connection to WMI database. " + (string)e.what());
	}
}

void WMI::queryCPUName()
{
	try
	{
		if (pSvc != 0)
		{
			// Use the IWbemServices pointer to make requests of WMI ----

			// For example, get the name of the operating system

			hres = pSvc->ExecQuery(
				bstr_t("WQL"),
				bstr_t("select * from Hardware WHERE HardwareType = 'CPU'"),
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

					// Get the value of the Name property
					hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
					wstring ws(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
					CPUName = string(ws.begin(), ws.end());

					ws.clear();
					VariantClear(&vtProp);

					hr = pclsObj->Get(L"Identifier", 0, &vtProp, 0, 0);
					ws = wstring(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
					CPUIdentifier = string(ws.begin(), ws.end());

					ws.clear();
					VariantClear(&vtProp);

					pclsObj->Release();

				}
				pEnumerator->Release();
				uReturn = 0;
			}
		}
	}
	catch (exception e)
	{
		Error::writeMessage("Can't read CPU Name from WMI database.  " + (string) e.what());
	}
}

void WMI::queryGPUName()
{
	try
	{
		GPUName.clear();
		GPUIdentifier.clear();

		if (pSvc != 0)
		{
			// Use the IWbemServices pointer to make requests of WMI ----

			// For example, get the name of the operating system

			hres = pSvc->ExecQuery(
				bstr_t("WQL"),
				bstr_t("select * from Hardware WHERE HardwareType = 'GpuAti' or  HardwareType = 'GpuNvidia'"),
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

					// Get the value of the Name property
					hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
					wstring ws(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
					GPUName.push_back(string(ws.begin(), ws.end()));

					VariantClear(&vtProp);
					ws.clear();

					hr = pclsObj->Get(L"Identifier", 0, &vtProp, 0, 0);

					ws = wstring(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
					GPUIdentifier.push_back(string(ws.begin(), ws.end()));

					VariantClear(&vtProp);
					uReturn = 0;
					pclsObj->Release();
				}
				pEnumerator->Release();

			}
		}
	}
	catch (exception e)
	{
		Error::writeMessage("Can't read GPU Name from WMI database.  " + (string) e.what());
	}
}

void WMI::queryHDName()
{
	try
	{
		HDDName.clear();
		HDDIdentifier.clear();

		if (pSvc != 0)
		{
			// Use the IWbemServices pointer to make requests of WMI ----

			// For example, get the name of the operating system

			hres = pSvc->ExecQuery(
				bstr_t("WQL"),
				bstr_t("select * from Hardware WHERE HardwareType = 'HDD'"),
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

					// Get the value of the Name property
					hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
					wstring ws(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
					HDDName.push_back(string(ws.begin(), ws.end()));

					VariantClear(&vtProp);
					ws.clear();

					hr = pclsObj->Get(L"Identifier", 0, &vtProp, 0, 0);
					ws = wstring(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));

					HDDIdentifier.push_back(string(ws.begin(), ws.end()));

					VariantClear(&vtProp);
					uReturn = 0;
					pclsObj->Release();
				}
				pEnumerator->Release();

			}
		}
	}
	catch (exception e)
	{
		Error::writeMessage("Can't read HD Name from WMI database.  " + (string) e.what());
	}
}

void WMI::queryCPULoad()
{
	try
	{
		cpuLoad.clear();

		if (pSvc != 0)
		{
			// Use the IWbemServices pointer to make requests of WMI ----

			// For example, get the name of the operating system
			string query = "select * from Sensor where Parent = '";
			query.append(CPUIdentifier);
			query.append("' and SensorType='Load' and Name != 'CPU Total'");

			char *a = new char[query.size() + 1];
			a[query.size()] = 0;
			memcpy(a, query.c_str(), query.size());

			hres = pSvc->ExecQuery(
				bstr_t("WQL"),
				bstr_t(a),
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

					// Get the value of the Name property
					hr = pclsObj->Get(L"Value", 0, &vtProp, 0, 0);

					int intValue = (int) vtProp.fltVal;
					stringstream stringStream;
					stringStream << intValue;

					cpuLoad.push_back(stringStream.str());

					stringStream.clear();
					VariantClear(&vtProp);
					uReturn = 0;
					pclsObj->Release();
				}
				pEnumerator->Release();
			}
			delete a;
		}
	}
	catch (exception e)
	{
		Error::writeMessage("Can't read CPU Load from WMI database.  " + (string) e.what());
	}
}

void WMI::queryCPUTemp()
{
	try
	{
		cpuTemp.clear();

		if (pSvc != 0)
		{
			// Use the IWbemServices pointer to make requests of WMI ----

			// For example, get the name of the operating system
			string query = "select * from Sensor where Parent = '";
			query.append(CPUIdentifier);
			query.append("' and SensorType='Temperature'");

			char *a = new char[query.size() + 1];
			a[query.size()] = 0;
			memcpy(a, query.c_str(), query.size());

			hres = pSvc->ExecQuery(
				bstr_t("WQL"),
				bstr_t(a),
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

					// Get the value of the Name property
					hr = pclsObj->Get(L"Value", 0, &vtProp, 0, 0);

					int intValue = (int) vtProp.fltVal;
					stringstream stringStream;
					stringStream << intValue;

					cpuTemp.push_back(stringStream.str());

					stringStream.clear();
					VariantClear(&vtProp);
					uReturn = 0;
					pclsObj->Release();
				}
				pEnumerator->Release();

			}
			delete a;
		}
	}
	catch (exception e)
	{
		Error::writeMessage("Can't read CPU remperature from WMI database.  " + (string) e.what());
	}
}

void WMI::queryCPUClock()
{
	try
	{
		CPUClock.clear();

		if (pSvc != 0)
		{
			// Use the IWbemServices pointer to make requests of WMI ----

			// For example, get the name of the operating system
			string query = "select * from Sensor where Parent = '";
			query.append(CPUIdentifier);
			query.append("' and SensorType='Clock' and Name != 'Bus Speed'");

			char *a = new char[query.size() + 1];
			a[query.size()] = 0;
			memcpy(a, query.c_str(), query.size());

			hres = pSvc->ExecQuery(
				bstr_t("WQL"),
				bstr_t(a),
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

					// Get the value of the Name property
					hr = pclsObj->Get(L"Value", 0, &vtProp, 0, 0);

					stringstream stringStream;
					stringStream << floor(vtProp.fltVal + 0.5);

					CPUClock.push_back(stringStream.str());

					stringStream.clear();
					VariantClear(&vtProp);
					uReturn = 0;
					pclsObj->Release();
				}

				pEnumerator->Release();

			}
			delete a;
		}
	}
	catch (exception e)
	{
		Error::writeMessage("Can't read CPU Clock from WMI database.  " + (string) e.what());
	}
}

void WMI::queryGPULoad()
{
	try
	{
		GPULoad.clear();

		if (pSvc != 0)
		{
			for (int count = 0; count < GPUIdentifier.size(); count++)
			{
				// Use the IWbemServices pointer to make requests of WMI ----

				// For example, get the name of the operating system
				string query = "select * from Sensor where Parent = '";
				query.append(GPUIdentifier[count]);
				query.append("' and SensorType='Load'");

				char *a = new char[query.size() + 1];
				a[query.size()] = 0;
				memcpy(a, query.c_str(), query.size());

				hres = pSvc->ExecQuery(
					bstr_t("WQL"),
					bstr_t(a),
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

						// Get the value of the Name property

						hr = pclsObj->Get(L"Value", 0, &vtProp, 0, 0);

						stringstream stringStream;
						stringStream << vtProp.fltVal;

						GPULoad.push_back(stringStream.str());

						stringStream.clear();
						VariantClear(&vtProp);
						uReturn = 0;
						pclsObj->Release();
					}
					pEnumerator->Release();
				}
				delete a;
			}
		}
	}
	catch (exception e)
	{
		Error::writeMessage("Can't read GPU Load from WMI database.  " + (string) e.what());
	}
}

void WMI::queryGPUTemp()
{
	try
	{
		GPUTemp.clear();

		if (pSvc != 0)
		{
			for (int count = 0; count < GPUIdentifier.size(); count++)
			{
				// Use the IWbemServices pointer to make requests of WMI ----

				// For example, get the name of the operating system
				string query = "select * from Sensor where Parent = '";
				query.append(GPUIdentifier[count]);
				query.append("' and SensorType='Temperature'");

				char *a = new char[query.size() + 1];
				a[query.size()] = 0;
				memcpy(a, query.c_str(), query.size());

				hres = pSvc->ExecQuery(
					bstr_t("WQL"),
					bstr_t(a),
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

						// Get the value of the Name property

						hr = pclsObj->Get(L"Value", 0, &vtProp, 0, 0);

						stringstream stringStream;
						stringStream << vtProp.fltVal;

						GPUTemp.push_back(stringStream.str());

						stringStream.clear();
						VariantClear(&vtProp);
						uReturn = 0;
						pclsObj->Release();
					}
					pEnumerator->Release();
				}
				delete a;
			}
		}
	}
	catch (exception e)
	{
		Error::writeMessage("Can't read GPU temperature from WMI database.  " + (string) e.what());
	}
}

void WMI::queryGPUFan()
{
	try
	{
		GPUFan.clear();

		if (pSvc != 0)
		{
			for (int count = 0; count < GPUIdentifier.size(); count++)
			{
				// Use the IWbemServices pointer to make requests of WMI ----

				// For example, get the name of the operating system
				string query = "select * from Sensor where Parent = '";
				query.append(GPUIdentifier[count]);
				query.append("' and SensorType='Control'");

				char *a = new char[query.size() + 1];
				a[query.size()] = 0;
				memcpy(a, query.c_str(), query.size());

				hres = pSvc->ExecQuery(
					bstr_t("WQL"),
					bstr_t(a),
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

						// Get the value of the Name property

						hr = pclsObj->Get(L"Value", 0, &vtProp, 0, 0);

						stringstream stringStream;
						stringStream << vtProp.fltVal;

						GPUFan.push_back(stringStream.str());

						stringStream.clear();
						VariantClear(&vtProp);
						uReturn = 0;
						pclsObj->Release();
					}
					if (count != GPUFan.size() - 1)
					{
						GPUFan.push_back("");
					}
					pEnumerator->Release();
				}


				delete a;
			}
		}
	}
	catch (exception e)
	{
		Error::writeMessage("Can't read GPU Fan from WMI database.  " + (string) e.what());
	}
}

void WMI::queryGPUClock()
{
	try
	{
		GPUClock.clear();
		GPUMemoryClock.clear();

		if (pSvc != 0)
		{
			for (int count = 0; count < GPUIdentifier.size(); count++)
			{
				// Use the IWbemServices pointer to make requests of WMI ----

				// For example, get the name of the operating system
				string query = "select * from Sensor where Parent = '";
				query.append(GPUIdentifier[count]);
				query.append("' and SensorType='Clock'");

				char *a = new char[query.size() + 1];
				a[query.size()] = 0;
				memcpy(a, query.c_str(), query.size());

				hres = pSvc->ExecQuery(
					bstr_t("WQL"),
					bstr_t(a),
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

						// Get the value of the Name property

						hr = pclsObj->Get(L"Index", 0, &vtProp, 0, 0);

						if (vtProp.intVal == 0)
						{
							VariantClear(&vtProp);

							hr = pclsObj->Get(L"Value", 0, &vtProp, 0, 0);

							stringstream stringStream;
							stringStream << vtProp.fltVal;

							GPUClock.push_back(stringStream.str());
							stringStream.clear();
						}

						else if (vtProp.intVal == 1)
						{
							VariantClear(&vtProp);
							hr = pclsObj->Get(L"Value", 0, &vtProp, 0, 0);

							stringstream stringStream;
							stringStream << vtProp.fltVal;

							GPUMemoryClock.push_back(stringStream.str());
							stringStream.clear();
						}

						VariantClear(&vtProp);
						uReturn = 0;
						pclsObj->Release();
					}
					pEnumerator->Release();
				}
				delete a;
			}
		}
	}
	catch (exception e)
	{
		Error::writeMessage("Can't read GPU Clock from WMI database.  " + (string) e.what());
	}
}

void WMI::queryHDData()
{
	try
	{
		HDDTemperature.clear();
		HDDLoad.clear();

		if (pSvc != 0)
		{
			for (int count = 0; count < HDDIdentifier.size(); count++)
			{
				// Use the IWbemServices pointer to make requests of WMI ----

				// For example, get the name of the operating system
				string query = "select * from Sensor where Parent = '";
				query.append(HDDIdentifier[count]);
				query.append("' and (SensorType='Load' or SensorType='Temperature')");

				char *a = new char[query.size() + 1];
				a[query.size()] = 0;
				memcpy(a, query.c_str(), query.size());

				hres = pSvc->ExecQuery(
					bstr_t("WQL"),
					bstr_t(a),
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

						// Get the value of the Name property

						hr = pclsObj->Get(L"SensorType", 0, &vtProp, 0, 0);

						wstring ws(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
						string sensortype = string(ws.begin(), ws.end());

						VariantClear(&vtProp);
						ws.clear();

						if (sensortype.compare("Load") == 0)
						{
							hr = pclsObj->Get(L"Value", 0, &vtProp, 0, 0);

							int load = (int) vtProp.fltVal;
							stringstream stringStream;
							stringStream << load;

							HDDLoad.push_back(stringStream.str());

							stringStream.clear();
						}

						else if (sensortype.compare("Temperature") == 0)
						{
							hr = pclsObj->Get(L"Value", 0, &vtProp, 0, 0);
							int temperature = (int) vtProp.fltVal;
							stringstream stringStream;
							stringStream << temperature;

							HDDTemperature.push_back(stringStream.str());

							stringStream.clear();
						}


						VariantClear(&vtProp);
						uReturn = 0;
						pclsObj->Release();
					}
					pEnumerator->Release();
				}

				if (HDDTemperature.size() != HDDLoad.size())
				{
					HDDTemperature.push_back("");
				}

				delete a;
			}
		}
	}
	catch (exception e)
	{
		Error::writeMessage("Can't read HD data from WMI database.  " + (string) e.what());
	}
}

void WMI::queryMemory()
{
	try
	{
		memoryLoad = "";

		if (pSvc != 0)
		{
			// Use the IWbemServices pointer to make requests of WMI ----

			// For example, get the name of the operating system

			hres = pSvc->ExecQuery(
				bstr_t("WQL"),
				bstr_t("select * from sensor WHERE name='Memory' and SensorType = 'Load'"),
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

					// Get the value of the Name property
					hr = pclsObj->Get(L"Value", 0, &vtProp, 0, 0);

					int memory = (int) vtProp.fltVal;
					stringstream stringStream;
					stringStream << memory;

					memoryLoad = (string) stringStream.str();

					stringStream.clear();
					VariantClear(&vtProp);

					pclsObj->Release();

				}
				pEnumerator->Release();
				uReturn = 0;
			}
		}
	}
	catch (exception e)
	{
		Error::writeMessage("Can't read Memory Load from WMI database.  " + (string) e.what());
	}
}

vector<string> WMI::getmemoryText()
{
	try
	{
		if (pSvc == 0)
		{
			this->connectToWMI();
		}

		text.clear();
		queryMemory();

		if (!memoryLoad.empty())
		{
			text.push_back(string("Memory: ").append(memoryLoad).append("% Used"));
		}

		text.push_back(Error::getCurrentTime());

	}
	catch (exception e)
	{
		Error::writeMessage("Can't create Memory text.  " + (string) e.what());
	}
	return text;
}

vector<string> WMI::getCPUText()
{
	try
	{
		if (pSvc == 0)
		{
			this->connectToWMI();
		}

		text.clear();
		queryCPUName();
		queryCPULoad();
		queryCPUTemp();
		queryCPUClock();

		text.push_back(CPUName);

		int tempsize = (int)cpuTemp.size();

		for (int i = 0; i < cpuLoad.size(); i++)
		{
			stringstream ss;//create a stringstream
			ss << i;//add number to the stream

			string tempText = "";
			tempText = tempText.append(ss.str());

			if (i < tempsize)
			{
				tempText = tempText.append(": ").append(cpuTemp[i]).append("°C - ").append(cpuLoad[i]).append("% - ").append(CPUClock[i]).append("MHz");
			}

			else
			{
				tempText = tempText.append(": ").append(cpuTemp[tempsize - 1]).append("°C - ").append(cpuLoad[i]).append("% - ").append(CPUClock[i]).append("MHz");
			}

			text.push_back(tempText);

			ss.clear();
		}
	}
	catch (exception e)
	{
		Error::writeMessage("Can't create CPU text.  " + (string) e.what());
	}

	return text;
}

vector<string> WMI::getGPUText()
{
	try
	{
		if (pSvc == 0)
		{
			this->connectToWMI();
		}

		text.clear();

		queryGPUName();
		queryGPUClock();
		queryGPUFan();
		queryGPULoad();
		queryGPUTemp();

		for (int i = 0; i < GPUIdentifier.size(); i++)
		{
			stringstream ss;//create a stringstream
			ss << i;//add number to the stream

			text.push_back(GPUName[i]);
			text.push_back(string("CC/MC: ").append(GPUClock[i]).append(" / ").append(GPUMemoryClock[i]).append(" MHz"));

			string gpuTemp = "";

			gpuTemp = gpuTemp.append(GPUTemp[i]);
			gpuTemp = gpuTemp.append(" °C - ");
			gpuTemp = gpuTemp.append(GPULoad[i]);

			if (!GPUFan[i].empty())
			{
				gpuTemp = gpuTemp.append("% - ");
				gpuTemp = gpuTemp.append(GPUFan[i]);
				gpuTemp = gpuTemp.append("% fan");
			}
			else
			{
				gpuTemp = gpuTemp.append("%");
			}

			text.push_back(gpuTemp);

			ss.clear();
		}

	}
	catch (exception e)
	{
		Error::writeMessage("Can't create GPU text.  " + (string) e.what());
	}
	return text;
}

vector<string> WMI::getHDDText()
{
	try
	{
		if (pSvc == 0)
		{
			this->connectToWMI();
		}

		text.clear();
		queryHDName();
		queryHDData();

		for (int i = 0; i < HDDIdentifier.size(); i++)
		{
			if (HDDTemperature[i].empty())
			{
				text.push_back(HDDIdentifier[i].append(": ").append(HDDLoad[i]).append("% Used"));
			}

			else
			{
				text.push_back(HDDIdentifier[i].append(": ").append(HDDTemperature[i]).append("C - ").append(HDDLoad[i]).append("% Used"));
			}
		}

		sort(text.begin(), text.end());

	}
	catch (exception e)
	{
		Error::writeMessage("Can't create HD text.  " + (string) e.what());
	}
	return text;
}