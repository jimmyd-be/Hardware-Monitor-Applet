#include "stdafx.h"
#include "Settings.h"


Settings::Settings(void): totalPages_(0), fontSize_(0), font_(""), background_("")
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

string Settings::getValueString(string region, string key)
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

int Settings::getValueInt(string region, string key)
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


int Settings::totalPages()
{
	if(totalPages_ == 0)
	{
		totalPages_ = getValueInt("General", "TotalPages");
	}
	return totalPages_;
}

int Settings::fontSize()
{
	if(fontSize_ == 0)
	{
		fontSize_ =  getValueInt("General", "FontSize");
	}
	return fontSize_;
}

string Settings::font()
{
	if(font_ == "")
	{
		font_ = getValueString("General", "Font");
	}
	return font_;
}

vector<string> Settings::backgrounds()
{
	if(backgrounds_.size() == 0)
	{
		string general = getValueString("General", "Background");

		for(int i=0; i < totalPages(); i++)
		{
			string text = "Page";
			text.append(to_string(i+1));
			string background = getValueString(text, "Background");

			if(background == "")
			{
				background = general;
			}

			backgrounds_.push_back(background);
		}
	}

	return backgrounds_;
}

vector<string*> Settings::lines()
{
	if(lines_.size() == 0)
	{
		vector<int> lineNumbers = totalLines();

		for(int i=0; i < totalPages(); i++)
		{
			string * pageLine = new string[lineNumbers[i]];

			string pageText = "Page";
			pageText.append(to_string(i+1));

			for(int j=0; j < lineNumbers[i]; j++)
			{
				string lineText = "Line";
				lineText.append(to_string(j+1));

				pageLine[j] = getValueString(pageText, lineText);
			}

			lines_.push_back(pageLine);
		}
	}
	return lines_;
}

vector<int> Settings::totalLines()
{
	if(totalLines_.size() == 0)
	{
		for(int i=0; i < totalPages(); i++)
		{
			string text = "Page";
			text.append(to_string(i+1));
			int value = getValueInt(text, "TotalLines");

			totalLines_.push_back(value);
		}
	}

	return totalLines_;
}