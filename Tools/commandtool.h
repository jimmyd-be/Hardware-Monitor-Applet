#ifndef COMMANDTOOL_H
#define COMMANDTOOL_H

#include "MonitorTool.h"
#include <QDebug>
#include <QProcess>
#include <QProcess>
#include <QStringList>

class CommandTool : public MonitorTool
{
public:
    CommandTool();

    //---------------------------
    // Destructor
    //---------------------------
    virtual ~CommandTool();

    //---------------------------
    // General Methods
    //---------------------------
    QVector<Query> getAllSensors();
    MonitorSystem getMonitorSystem();
    double getData(Query);
};

#endif // COMMANDTOOL_H
