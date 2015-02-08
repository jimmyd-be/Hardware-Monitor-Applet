//-----------------------------------------------------------------
// MonitorTool File
// C++ Header - MonitorTool.h - version 0.1 (2013/06/13)
//-----------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "../Defines.h"

//-----------------------------------------------------------------
// MonitorTool Class
//-----------------------------------------------------------------
class MonitorTool
{
public:
	//---------------------------
	// Constructor(s)
	//---------------------------
	MonitorTool();

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~MonitorTool();

	//---------------------------
	// General Methods
	//---------------------------
	virtual QVector<HardwareSensor> getAllSensors();
	virtual MonitorSystem getMonitorSystem();
	virtual HardwareSensor getData(Query);

private:
	// -------------------------
	// Datamembers
	// -------------------------
	
	
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	MonitorTool(const MonitorTool& t);
	MonitorTool& operator=(const MonitorTool& t);
};