//-----------------------------------------------------------------
// WMI Object
// C++ Source - WMI.cpp - version v1.0 (2012-08-01)
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
	pEnumerator_ = NULL;
	pLoc_ = 0;
	pSvc_ = 0;
	pclsObj_ = 0;

	connectToWMI();

}

WMI::~WMI(void)
{
	pSvc_->Release();
	pLoc_->Release();
	CoUninitialize();
}

void WMI::connectToWMI()
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
				IID_IWbemLocator, (LPVOID *) &pLoc_);

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

QueryCode WMI::convertCodeToLine(string code)
{
	vector<QueryCode> codes;

	int index =0;
	int startPosition = -1;
	QueryCode query;

	for(unsigned int i=0; i < code.size(); i++)
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
	return query;
}

string WMI::queryCode(QueryCode code)
{
	string returnValue = "";

	string query = "select ";
	query.append(code.name);
	query.append(" from ");
	query.append(code.type);
	query.append(" where InstanceId = ");
	query.append(code.id);

	if (pSvc_ != 0)
	{
		// Use the IWbemServices pointer to make requests of WMI ----

		// For example, get the name of the operating system

		hres_ = pSvc_->ExecQuery(
			bstr_t("WQL"),
			bstr_t(query.c_str()),
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
			NULL,
			&pEnumerator_);

		if (!FAILED(hres_))
		{

			// Get the data from the query

			ULONG uReturn = 0;

			while (pEnumerator_)
			{
				HRESULT hr = pEnumerator_->Next(WBEM_INFINITE, 1,
					&pclsObj_, &uReturn);

				if (0 == uReturn)
				{
					break;
				}

				VARIANT vtProp;

				wstring stemp = std::wstring(code.name.begin(), code.name.end());

				hr = pclsObj_->Get(stemp.c_str(), 0, &vtProp, 0, 0);

				wstring ws(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));
				returnValue = string(ws.begin(), ws.end());
				ws.clear();
				
				VariantClear(&vtProp);
				uReturn = 0;
				pclsObj_->Release();

			}
			pEnumerator_->Release();

		}
	}

	return returnValue;
}

string WMI::convertLine(string line)
{
	int position = line.find_first_of("{");
	int position2 = line.find_first_of("}");

	while (position != -1 || position2 != -1)
	{
		string code = line.substr(position, position2 - position + 1);
		QueryCode queryCode1 = convertCodeToLine(code);
		string result = queryCode(queryCode1);

		line.replace(position, position2 - position + 1, result);
		position = line.find_first_of("{");
		position2 = line.find_first_of("}");
	}


	return line;
}