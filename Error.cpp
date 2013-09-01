//-----------------------------------------------------------------
// Error File
// C++ Source - Error.cpp - version 0.1 (2013/06/13)
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "stdafx.h"
#include "Error.h"

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Error methods
//-----------------------------------------------------------------

Error::Error()
{

}

Error::~Error()
{
	// nothing to destroy
}


ofstream Error::openLogFile()
{
	ofstream logFile;

	string filePath = "C:\\OHM.log";
	logFile.open(filePath, ios::app);

	return logFile;
}

void Error::writeMessage(string message)
{
	Error* error = new Error();

	ofstream logFile = error->openLogFile();

	if (logFile.is_open())
	{
		logFile << Error::getCurrentTime() << ": " << message << endl;
	}

	logFile.close();
}


string Error::getCurrentTime()
{
	struct tm newtime;
	__time64_t long_time;
	char timebuf[26];
	errno_t err;

	// Get time as 64-bit integer.
	_time64(&long_time);
	// Convert to local time.
	err = _localtime64_s(&newtime, &long_time);

	//asctime_s(timebuf, 26, &newtime);

	strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %X", &newtime);

	string temp = timebuf;

	if (!temp.empty() && temp[temp.size() - 1] == '\n')
	{
		temp.erase(temp.size() - 1);
	}
	return temp;
}