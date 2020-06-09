//-----------------------------------------------------------------
// WMI Object
// C++ Header - WMI.h - version v1.0 (2015-03-14)
//-----------------------------------------------------------------
#ifdef _WIN32

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <comdef.h>
#include <Wbemidl.h>

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <ctime>
#include "../Defines.h"
#include <iomanip>
#include "MonitorTool.h"

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------
#define _WIN32_DCOM
# pragma comment(lib, "wbemuuid.lib")
using namespace std;

class HwaSettings;

//-----------------------------------------------------------------
// WMI Class
//-----------------------------------------------------------------
class WMI : public MonitorTool
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
	QVector<HardwareSensor> getAllSensors();
	MonitorSystem getMonitorSystem();
	HardwareSensor getData(Query);

private:
	//---------------------------
	// Private Methods
	//---------------------------
	void connect();
	float transformData(float, QString);
	QString getUnit(QString);
	QString findHardware(QString);

	//--------------------------
	// Datamembers
	//--------------------------
	IWbemLocator *pLoc_;
	IWbemServices *pSvc_;
	IWbemClassObject *pclsObj_;
	HRESULT hres_;
    HwaSettings * settings_;

	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	WMI(const WMI& t);
	WMI& operator=(const WMI& t);
};
#endif
