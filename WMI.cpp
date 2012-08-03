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

	queryCPUName();
	queryGPUName();
	
	queryHDName();
	queryHDData();
	queryCPULoad();
	queryCPUTemp();
	queryCPUCLock();
	queryGPULoad();
	queryGPUTemp();
	queryGPUFan();
	queryGPUClock();


}

WMI::~WMI(void)
{
	pSvc->Release();
	pLoc->Release();
	//	pEnumerator->Release();
	//pclsObj->Release();
	CoUninitialize();
}

void WMI::refresh()
{
	CPUText.clear();
	GPUText.clear();
	HDDText.clear();

	queryCPUName();
	queryGPUName();

	queryHDName();
	queryHDData();

	queryCPULoad();
	queryCPUTemp();
	queryCPUCLock();
	queryGPULoad();
	queryGPUTemp();
	queryGPUFan();
	queryGPUClock();

	createtext();

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


void WMI::connectToWMI()
{


	// Initialize COM. ------------------------------------------

	hres =  CoInitializeEx(0, COINIT_MULTITHREADED);

	if (!FAILED(hres))
	{

		// Set general COM security levels --------------------------
		// Note: If you are using Windows 2000, you need to specify -
		// the default authentication credentials for a user by using
		// a SOLE_AUTHENTICATION_LIST structure in the pAuthList ----
		// parameter of CoInitializeSecurity ------------------------

		hres =  CoInitializeSecurity(
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

void WMI::queryCPUName()
{
	if(pSvc != 0 && pclsObj != 0)
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

				if(0 == uReturn)
				{
					break;
				}

				VARIANT vtProp;

				// Get the value of the Name property
				hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
				wstring ws(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
				CPUName = string( ws.begin(), ws.end() );


				hr = pclsObj->Get(L"Identifier", 0, &vtProp, 0, 0);
				ws = wstring(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
				CPUIdentifier = string( ws.begin(), ws.end() );

				VariantClear(&vtProp);

				pclsObj->Release();

			}
			pEnumerator->Release();

		}
	}
}

void WMI::queryGPUName()
{

	if(pSvc != 0 && pclsObj != 0)
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

				if(0 == uReturn)
				{
					break;
				}

				VARIANT vtProp;

				// Get the value of the Name property
				hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
				wstring ws(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
				GPUName.push_back(string( ws.begin(), ws.end() ));

				hr = pclsObj->Get(L"Identifier", 0, &vtProp, 0, 0);

				ws = wstring(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
				GPUIdentifier.push_back(string( ws.begin(), ws.end() ));

				VariantClear(&vtProp);

				pclsObj->Release();
			}
			pEnumerator->Release();

		}
	}

}

void WMI::queryHDName()
{
	if(pSvc != 0 && pclsObj != 0)
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

				if(0 == uReturn)
				{
					break;
				}

				VARIANT vtProp;

				// Get the value of the Name property
				hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
				wstring ws(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
				HDDName.push_back(string( ws.begin(), ws.end() ));

				hr = pclsObj->Get(L"Identifier", 0, &vtProp, 0, 0);
				ws = wstring(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));

				HDDIdentifier.push_back(string( ws.begin(), ws.end() ));
				VariantClear(&vtProp);

				pclsObj->Release();
			}
			pEnumerator->Release();

		}
	}
}

void WMI::queryCPULoad()
{
	if(pSvc != 0 && pclsObj != 0)
	{
		// Use the IWbemServices pointer to make requests of WMI ----

		// For example, get the name of the operating system
		string query = "select * from Sensor where Parent = '";
		query.append(CPUIdentifier);
		query.append("' and SensorType='Load' and Name != 'CPU Total'");

		char *a=new char[query.size()+1];
		a[query.size()]=0;
		memcpy(a,query.c_str(),query.size());

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

				if(0 == uReturn)
				{
					break;
				}

				VARIANT vtProp;

				// Get the value of the Name property
				hr = pclsObj->Get(L"Value", 0, &vtProp, 0, 0);

				int intValue = vtProp.fltVal;
				stringstream stringStream;
				stringStream << intValue;

				cpuLoad.push_back(stringStream.str());

				VariantClear(&vtProp);

				pclsObj->Release();
			}
			pEnumerator->Release();

		}
	}

}

void WMI::queryCPUTemp()
{
	if(pSvc != 0 && pclsObj != 0)
	{
		// Use the IWbemServices pointer to make requests of WMI ----

		// For example, get the name of the operating system
		string query = "select * from Sensor where Parent = '";
		query.append(CPUIdentifier);
		query.append("' and SensorType='Temperature'");

		char *a=new char[query.size()+1];
		a[query.size()]=0;
		memcpy(a,query.c_str(),query.size());

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

				if(0 == uReturn)
				{
					break;
				}

				VARIANT vtProp;

				// Get the value of the Name property
				hr = pclsObj->Get(L"Value", 0, &vtProp, 0, 0);

				int intValue = vtProp.fltVal;
				stringstream stringStream;
				stringStream << intValue;

				cpuTemp.push_back(stringStream.str());

				VariantClear(&vtProp);

				pclsObj->Release();
			}
			pEnumerator->Release();

		}
	}
}

void WMI::queryCPUCLock()
{
	if(pSvc != 0 && pclsObj != 0)
	{
		// Use the IWbemServices pointer to make requests of WMI ----

		// For example, get the name of the operating system
		string query = "select * from Sensor where Parent = '";
		query.append(CPUIdentifier);
		query.append("' and SensorType='Clock' and Name != 'Bus Speed'");

		char *a=new char[query.size()+1];
		a[query.size()]=0;
		memcpy(a,query.c_str(),query.size());

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

				if(0 == uReturn)
				{
					break;
				}

				VARIANT vtProp;

				// Get the value of the Name property
				hr = pclsObj->Get(L"Value", 0, &vtProp, 0, 0);

				stringstream stringStream;
				stringStream << vtProp.fltVal;

				CPUClock.push_back(stringStream.str());

				VariantClear(&vtProp);

				pclsObj->Release();
			}

			pEnumerator->Release();

		}
	}
}

void WMI::queryGPULoad()
{
	if(pSvc != 0 && pclsObj != 0)
	{
		for(int count =0; count < GPUIdentifier.size(); count++)
		{
		// Use the IWbemServices pointer to make requests of WMI ----

		// For example, get the name of the operating system
		string query = "select * from Sensor where Parent = '";
		query.append(GPUIdentifier[count]);
		query.append("' and SensorType='Load'");

		char *a=new char[query.size()+1];
		a[query.size()]=0;
		memcpy(a,query.c_str(),query.size());

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

				if(0 == uReturn)
				{
					break;
				}

				VARIANT vtProp;

				// Get the value of the Name property

				hr = pclsObj->Get(L"Value", 0, &vtProp, 0, 0);
				
				stringstream stringStream;
				stringStream << vtProp.fltVal;

				GPULoad.push_back(stringStream.str());
				VariantClear(&vtProp);

				pclsObj->Release();
			}
			pEnumerator->Release();
		}
		}
	}
}

void WMI::queryGPUTemp()
{
	if(pSvc != 0 && pclsObj != 0)
	{
		for(int count =0; count < GPUIdentifier.size(); count++)
		{
		// Use the IWbemServices pointer to make requests of WMI ----

		// For example, get the name of the operating system
		string query = "select * from Sensor where Parent = '";
		query.append(GPUIdentifier[count]);
		query.append("' and SensorType='Temperature'");

		char *a=new char[query.size()+1];
		a[query.size()]=0;
		memcpy(a,query.c_str(),query.size());

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

				if(0 == uReturn)
				{
					break;
				}

				VARIANT vtProp;

				// Get the value of the Name property

				hr = pclsObj->Get(L"Value", 0, &vtProp, 0, 0);
				
				stringstream stringStream;
				stringStream << vtProp.fltVal;

				GPUTemp.push_back(stringStream.str());
				VariantClear(&vtProp);

				pclsObj->Release();
			}
			pEnumerator->Release();
		}
		}
	}
}

void WMI::queryGPUFan()
{
if(pSvc != 0 && pclsObj != 0)
	{
		for(int count =0; count < GPUIdentifier.size(); count++)
		{
		// Use the IWbemServices pointer to make requests of WMI ----

		// For example, get the name of the operating system
		string query = "select * from Sensor where Parent = '";
		query.append(GPUIdentifier[count]);
		query.append("' and SensorType='Control'");

		char *a=new char[query.size()+1];
		a[query.size()]=0;
		memcpy(a,query.c_str(),query.size());

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

				if(0 == uReturn)
				{
					break;
				}

				VARIANT vtProp;

				// Get the value of the Name property

				hr = pclsObj->Get(L"Value", 0, &vtProp, 0, 0);
				
				stringstream stringStream;
				stringStream << vtProp.fltVal;

				GPUFan.push_back(stringStream.str());
				VariantClear(&vtProp);

				pclsObj->Release();
			}
			pEnumerator->Release();
		}
		}
	}
}

void WMI::queryGPUClock()
{
	if(pSvc != 0 && pclsObj != 0)
	{
		for(int count =0; count < GPUIdentifier.size(); count++)
		{
		// Use the IWbemServices pointer to make requests of WMI ----

		// For example, get the name of the operating system
		string query = "select * from Sensor where Parent = '";
		query.append(GPUIdentifier[count]);
		query.append("' and SensorType='Clock'");

		char *a=new char[query.size()+1];
		a[query.size()]=0;
		memcpy(a,query.c_str(),query.size());

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

				if(0 == uReturn)
				{
					break;
				}

				VARIANT vtProp;

				// Get the value of the Name property

				hr = pclsObj->Get(L"Index", 0, &vtProp, 0, 0);
				
				if(vtProp.intVal == 0)
				{
					hr = pclsObj->Get(L"Value", 0, &vtProp, 0, 0);
				
				stringstream stringStream;
				stringStream << vtProp.fltVal;

				GPUClock.push_back(stringStream.str());
				}
				
				else if(vtProp.intVal == 1)
				{
					hr = pclsObj->Get(L"Value", 0, &vtProp, 0, 0);
				
				stringstream stringStream;
				stringStream << vtProp.fltVal;

				GPUMemoryClock.push_back(stringStream.str());
				}
				VariantClear(&vtProp);

				pclsObj->Release();
			}
			pEnumerator->Release();
		}
		}
	}
}

void WMI::queryHDData()
{
	if(pSvc != 0 && pclsObj != 0)
	{
		for(int count =0; count < HDDIdentifier.size(); count++)
		{
		// Use the IWbemServices pointer to make requests of WMI ----

		// For example, get the name of the operating system
		string query = "select * from Sensor where Parent = '";
		query.append(HDDIdentifier[count]);
		query.append("' and (SensorType='Load' or SensorType='Temperature')");

		char *a=new char[query.size()+1];
		a[query.size()]=0;
		memcpy(a,query.c_str(),query.size());

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

				if(0 == uReturn)
				{
					break;
				}

				VARIANT vtProp;

				// Get the value of the Name property

				hr = pclsObj->Get(L"SensorType", 0, &vtProp, 0, 0);
				
				wstring ws(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
				string sensortype = string( ws.begin(), ws.end() );

				if(sensortype.compare("Load") ==0)
				{
					hr = pclsObj->Get(L"Value", 0, &vtProp, 0, 0);
					
					int load = vtProp.fltVal;
					stringstream stringStream;
				stringStream << load;

				HDDLoad.push_back(stringStream.str());
				}

				else if(sensortype.compare("Temperature") == 0)
				{
					hr = pclsObj->Get(L"Value", 0, &vtProp, 0, 0);
					int temperature = vtProp.fltVal;
					stringstream stringStream;
				stringStream << temperature;

				HDDTemperature.push_back(stringStream.str());
				}
				

				VariantClear(&vtProp);

				pclsObj->Release();
			}
			pEnumerator->Release();
		}

		if(HDDTemperature.size() != HDDLoad.size())
		{
			HDDTemperature.push_back("");
		}
		}
	}
}

void WMI::queryOther()
{

}

void WMI::createtext()
{
	CPUText.clear();
	GPUText.clear();
	HDDText.clear();

	CPUText.push_back(CPUName);

	for(int i =0; i < cpuTemp.size(); i++)
	{
		stringstream ss;//create a stringstream
		ss << i;//add number to the stream

		string tempText = "Core ";
		tempText = tempText.append(ss.str());
		tempText = tempText.append(": ").append(cpuTemp[i]).append("°C - ").append(cpuLoad[i]).append("% load - ").append(CPUClock[i]).append("MHz");
		CPUText.push_back(tempText);
	}
	
	for(int i =0; i< GPUIdentifier.size(); i++)
	{
		stringstream ss;//create a stringstream
		 ss << i;//add number to the stream
   
		GPUText.push_back(GPUName[i]);
		GPUText.push_back(string("CC: ").append(GPUClock[i]).append("MHz - MC: ").append(GPUMemoryClock[i]).append("MHz"));

		string gpuTemp ="GPU ";
		
		gpuTemp = gpuTemp.append(ss.str());
		gpuTemp = gpuTemp.append(": ");	
		gpuTemp = gpuTemp.append(GPUTemp[i]);
		gpuTemp = gpuTemp.append("°C - ");
		gpuTemp = gpuTemp.append(GPULoad[i]);
		gpuTemp = gpuTemp.append("% load - ");
		gpuTemp = gpuTemp.append(GPUFan[i]);
		gpuTemp = gpuTemp.append("% fan");

		GPUText.push_back(gpuTemp);
	}

	for(int i=0; i< HDDIdentifier.size(); i++)
	{
		if(HDDTemperature[i].empty())
		{
			HDDText.push_back(HDDIdentifier[i].append(": ").append(HDDLoad[i]).append("% load"));
		}

		else
		{
			HDDText.push_back(HDDIdentifier[i].append(": ").append(HDDTemperature[i]).append("°C - ").append(HDDLoad[i]).append("% load"));
		}
	}

	sort(HDDText.begin(), HDDText.end());
}

vector<string> WMI::getCPUText()
{
	return CPUText;
}

vector<string> WMI::getGPUText()
{
	return GPUText;
}

vector<string> WMI::getHDDText()
{
	return HDDText;
}