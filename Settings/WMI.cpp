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
				sensor.instanceId = vtProp.intVal;
				VariantClear(&vtProp);

				hr = pclsObj->Get(L"Max", 0, &vtProp, 0, 0);
				sensor.max = vtProp.dblVal;
				VariantClear(&vtProp);

				hr = pclsObj->Get(L"Min", 0, &vtProp, 0, 0);
				sensor.min = vtProp.dblVal;
				VariantClear(&vtProp);

				hr = pclsObj->Get(L"Value", 0, &vtProp, 0, 0);
				sensor.value = vtProp.dblVal;
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
				hardware.InstanceId = vtProp.intVal;
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