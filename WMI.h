//-----------------------------------------------------------------
// WMI Object
// C++ Header - WMI.h - version v1.0 (2012-08-01)
// 
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include <iostream>
#include <comdef.h>
#include <Wbemidl.h>
#include <string>
#include <vector>
#include <sstream>
#include "stdafx.h"

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------
#define _WIN32_DCOM
# pragma comment(lib, "wbemuuid.lib")
using namespace std;

//-----------------------------------------------------------------
// WMI Class
//-----------------------------------------------------------------
class WMI
{
public:
	//---------------------------
	// Constructor(s)
	//---------------------------
	WMI();

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~WMI(void);
	
	//---------------------------
	// General Methods
	//---------------------------
	void refresh();
	vector<string> getCPUText();
	vector<string> getGPUText();
	vector<string> getHDDText();

private:
	//---------------------------
	// Private Methods
	//---------------------------
	void connectToWMI();

	void queryCPUName();
	void queryCPUCLock();
	void queryCPULoad();
	void queryCPUTemp();

	void queryGPUName();
	void queryGPULoad();
	void queryGPUTemp();
	void queryGPUFan();
	void queryGPUClock();

	void queryHDName();
	void queryOther();

	void createtext();
	//--------------------------
	// Datamembers
	//--------------------------
	IWbemLocator *pLoc;
	IWbemServices *pSvc;
	IEnumWbemClassObject* pEnumerator;
	IWbemClassObject *pclsObj;
	HRESULT hres;

	vector<string> CPUText;
	vector<string> GPUText;
	vector<string> HDDText;

	string CPUName;
	string CPUIdentifier;
	vector<string> CPUClock;
	vector<string> cpuLoad;
	vector<string> cpuTemp;

	vector<string> GPUName;
	vector<string> GPUIdentifier;
	vector<string> GPULoad;
	vector<string> GPUTemp;
	vector<string> GPUFan;
	vector<string> GPUClock;
	vector<string> GPUMemoryClock;

	vector<string> HDDName;
	vector<string> HDDIdentifier;
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	WMI(const WMI& t);
	WMI& operator=(const WMI& t);
};

