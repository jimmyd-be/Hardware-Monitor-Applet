#pragma once

#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <map>
using namespace std;


class Settings
{
public:
	Settings(void);
	virtual ~Settings(void);

	string getValueString(string key, string region);
	int getValueInt(string key, string region);

private:
	string getSettingsPath();
	void readFile();

	map<string, string> values_;

	string file_;

	int totalPages_;
	int fontSize_;

	string font_;
	string background_;

	vector<string> backgrounds_;
	vector<int> totalLines_;
	vector<string*> lines_;
};

