#include <fstream>
#include <string>
#include "include/Stats.h"

Stats::Stats()
{
	m_health = 0;
}

Stats::~Stats()
{
}

void Stats::loadFromFile(std::string filename)
{
	std::ifstream input(filename.c_str());

	std::string str;
	while(input >> str)
	{
		if(str == "Name") { 
			input >> m_name;
			continue;
		}
		if(str == "Level")
		{
			input >> m_level;
			continue;
		}
		if(str == "Experience")
		{
			input >> m_experience;
			continue;
		}

	}



}

void Stats::saveToFile(std::string filename)
{

}

std::string Stats::toString()
{
	return " Name " + m_name + "\n";
}



