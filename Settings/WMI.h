//-----------------------------------------------------------------
// WMI Object
// C++ Header - WMI.h - version v1.0 (2012-08-01)
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <ctime>
#include <comdef.h>
#include <Wbemidl.h>

using namespace std;

struct Sensor {
  	string identifier;
	string name;
	string parent;
	string processId;
	string sensorType;
	
	int index;
	int instanceId;

	double max;
	double min;
	double value;
};

struct Hardware{
	string hardwaretype;
	string identifier;
	int InstanceId;
	string name;
	string parent;
	string processId;
};


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
	vector<string> getCPUText();
	vector<string> getGPUText();
	vector<string> getHDDText();
	vector<string> getmemoryText();

private:
	//---------------------------
	// Private Methods
	//---------------------------
	void connectToWMI();

	void querySensors();
	void queryHardware();


	//--------------------------
	// Datamembers
	//--------------------------
	IWbemLocator *pLoc;
	IWbemServices *pSvc;
	IEnumWbemClassObject* pEnumerator;
	IWbemClassObject *pclsObj;
	HRESULT hres;

	vector<Hardware> hardwareList;
	vector<Sensor> sensorList;

	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	WMI(const WMI& t);
	WMI& operator=(const WMI& t);
};