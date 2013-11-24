#pragma once

#include <string>

using namespace std;

struct QueryCode
{
	string type;
	string id;
	string name;
	int round;
};

struct Sensor {
  	string identifier;
	string name;
	string parent;
	string processId;
	string sensorType;
	string instanceId;

	int index;

	float max;
	float min;
	float value;
};

struct Hardware{
	string hardwaretype;
	string identifier;
	string InstanceId;
	string name;
	string parent;
	string processId;
};