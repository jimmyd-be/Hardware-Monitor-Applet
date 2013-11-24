#include "stdafx.h"
#include "Settings.h"


Settings::Settings(void)
{
	file_ = getSettingsPath().append("\\Settings.ini");

	readFile();
}

Settings::~Settings(void)
{
	for(unsigned int i =0; i < lines_.size(); i++)
	{
		delete lines_[i];
	}
}

string Settings::getSettingsPath()
{
	WCHAR path[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, 0, path)))
	{
		//convert from wide char to narrow char array
		char ch[260];
		char DefChar = ' ';
		WideCharToMultiByte(CP_ACP,0,path,-1, ch,260,&DefChar, NULL);

		//A std:string  using the char* constructor.
		std::string ss(ch);

		return ss.append("\\AppData\\Roaming\\OHM Applet");
	}

	return "";
}

void Settings::readFile()
{
	ifstream iniFile(file_);

	if (iniFile.is_open())
	{
		string line;
		string region= "";

		while (getline(iniFile,line) )
		{
			if(line.find("[") != string::npos && line.find("]") != string::npos)
			{
				line.erase(line.find("["), 1);
				line.erase(line.find("]"), 1);
				region = line.append("/");
			}

			else if(line.length() != 0)
			{
				int pos = line.find("=");
				string key = region;
				key.append(line.substr(0, pos));
				string value = line.substr(pos+1, line.size() - pos);

				values_.insert(pair<string, string>(key, value));
			}
		}
		iniFile.close();
	}
}

string Settings::getValueString(string key, string region)
{
	region.append("/");
	region.append(key);
	map<string,string>::iterator it = values_.find(region);

	if(it != values_.end())
	{
		return it->second;
	}

	return "";
}

int Settings::getValueInt(string key, string region)
{
	int value = -1;

	region.append("/");
	region.append(key);
	map<string,string>::iterator it = values_.find(region);

	if(it != values_.end())
	{
		string temp = it->second;

		try
		{
			istringstream buffer(temp);
			buffer >> value;
		}
		catch(exception e)
		{

		}
	}

	return value;
}