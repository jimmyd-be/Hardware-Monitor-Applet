//-----------------------------------------------------------------
// HWinfo File
// C++ Header - HWinfo.h - version v1.0 (2015-03-14)
//-----------------------------------------------------------------
#ifdef _WIN32
#pragma once

#include "../Defines.h"
#include <external/HWiNFO/hwisenssm2.h>
#include "MonitorTool.h"

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// HWinfo Class
//-----------------------------------------------------------------

class HwaSettings;

class HWinfo: public MonitorTool
{
public:
	//---------------------------
	// Constructor(s)
	//---------------------------
	HWinfo();

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~HWinfo();

	//---------------------------
	// General Methods
	//---------------------------
    QVector<Query> getAllSensors();
	MonitorSystem getMonitorSystem();
    double getData(Query);

private:
	// -------------------------
	// Datamembers
	// -------------------------
	QMap<QString, QPair<PHWiNFO_SENSORS_READING_ELEMENT, PHWiNFO_SENSORS_SENSOR_ELEMENT>> cacheMap_;
    HwaSettings * settings_;

	double transformData(double, SENSOR_READING_TYPE, QString);
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	HWinfo(const HWinfo& t);
	HWinfo& operator=(const HWinfo& t);
};
#endif
