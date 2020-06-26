//-----------------------------------------------------------------
// MonitorTool File
// C++ Header - MonitorTool.h - version v1.0 (2015-03-14)
//-----------------------------------------------------------------
#ifndef MONITORTOOL_H
#define MONITORTOOL_H
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
    virtual QVector<Query> getAllSensors();
	virtual MonitorSystem getMonitorSystem();
    virtual double getData(Query);

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
#endif
