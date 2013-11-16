/**
 * @file Microsonic_CFG_Framework.cpp
 * Microsonic Configuration Framework
 *
 * The framework was designed to help C++ developers
 * with their applications and save time in parsing
 * configuration. This particular file contains all the
 * main definitions.
 *
 * Framework developed by Dennis J. McWherter, Jr. 2010.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Version 0.1a
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include "Microsonic_CFG_Framework.h"

using namespace std;
using namespace MCFG;

// Define our variables
map<string,string> MCFG::Config;
string MCFG::configList = "Undefined"; // Undefined list
string MCFG::cFile = "";
const char* MCFG::err = "";
int MCFG::lineno = 1;

/**
 * -------------------
 *	   INIT CLASS
 * -------------------
 */

/**
 * Constructor()
 *
 * The constructor just initializes the function.
 * It requires an "overload" to choose which configuration file
 * will be read.
 */
INIT::INIT(string file)
	: tempKey(""), tempVal(""), multiline(false), quote(false)
{
	cFile = file;
	readConfig(file); // Do what we need to
}

/**
 * Destructor()
 *
 * What happens when we close? :)
 */
INIT::~INIT()
{
}

/**
 * readConfig()
 * 
 * Reads the specified configuration file and
 * stores the information to a variable buffer.
 *
 * @param file
 *   (std::string) Is the file which will be opened and read. Must have the full path.
 *
 * @return void
 */
void INIT::readConfig(string file)
{
	string line;
	ifstream theConfig(file.c_str());
	lineno = 1; // RESET <3

	// End pre-mature.. Ouch. That's never good in any context
	// Anyway, we'll check later if the config is false!
	if(!theConfig.is_open())
	{
		err = "Could not open file!\n";
		return;
	}

	// Great let's read each line and parse it <3
	while(getline(theConfig,line))
	{
		line = trim(line);
		if(!parseLine(line))
		{
			lineno++;
			if(strcmp(err,"") != 0)
				break; // Kill, this is a bad line: 
			else
				continue; // Doh! Bad line
		}

		// Don't waste our time if we have no values to store; that's wasted space >:|
		if(tempKey.size() > 0 && tempVal.size() > 0)
			Config[configList+'/'+tempKey] = tempVal;
		tempVal.clear();
		tempKey.clear();
		lineno++;
	}

	// Clean up a bit
	theConfig.close();

	return; // Bye-bye
}

/**
 * parseLine()
 *
 * Parses each line fed into
 * a proper configuration set.
 *
 * @param line
 *  (std::string) Line to be parsed into a config string
 *
 * @return bool
 */
bool INIT::parseLine(string line)
{
	if(line.empty() || line[0] == ';'|| line[0] == '#')	return false; // Blank lines or comments
	// Multi-line comments
	if(line[0] == '/' && line[1] == '*')
		multiline = true;

	// Check if part of the multiline comment, just ignore. Else
	// end it!
	if(multiline == true)
	{
		// Now since multiline is true check if we need to return or what.
		if(line.find("*/") != string::npos)
		{
			multiline = false;
			return false;
		} else { // eh.. no good.
			return false;
		}
	}

	// Set config list if found
	if(line[0] == '[')
	{
		configList = line.substr(1,line.find(']')-1);
		return false;
	}

	// Nothing found to break us.. Let's setup our key, etc.
	if(line.find("=\"") != string::npos)
	{
		if(line.find("\";") == string::npos)
		{
			err = "A parsing error occurred. Please make sure you end your statements properly with \";";
			return false;
		}
		tempKey = line.substr(0,line.find_first_of('='));
		tempVal = line.substr(line.find_first_of('=')+2,line.length()-line.find('=')-4);
	}

	// Configuration error? :S
	if(tempKey.empty() || tempVal.empty())
	{
		err = "A parsing error occurred";
		return false; // We didn't pick anything up... Improper config?
	}
	return true;
}

/**
 * Trim()
 *
 * This function trims whitespace from
 * any given line as long as the whitespace
 * is not "quoted."
 *
 * @param line
 *   (std::string) parameter which will be parsed
 *
 * @return string
 *   The parsed string's output.
 */
string INIT::trim(string line)
{
	quote = false; // reset
	size_t start = 0, end = 0;
	string c = ""; // init our single character check
	start = line.find("\"");
	end	  = line.find("\";",start);
	for(size_t i=0;i<line.length();i++)
	{
		if(i < start || i > end)
		{
			c = line.substr(i,1); // Set c to our current character
			// Well we made it passed our "quoted" text. Let's actually do some checking
			// then trimming <3 *vrooooom goes the motorized hedge clippers*
			if(c.find(' ') != string::npos && !quote) // spaces
				line.erase(line.begin()+i,line.begin()+i+1);
			if(c.find('\t') != string::npos && !quote) // tabs
				line.erase(line.begin()+i,line.begin()+i+1);
		}
	}
	return line;
}


/**
 * ---------------------------------
 *	  Begin non-class functions
 * ---------------------------------
 */

/**
 * getValue()
 *
 * Retrieve a value (in plain-text) of
 * any given key in any given list.
 *
 * @param list
 *   (std::string) The list (e.g. [list1]) that the key can be found in
 *
 * @param key
 *   (std::string) The actual key name
 *
 * @return const char*
 */
const char* MCFG::getValue(string list,string key)
{
	map<string,string>::const_iterator ci = Config.find(list+'/'+key);
	
	// Uh-oh, can't find it :(
	if(ci == Config.end())
		return "Variable not found!";

	return ci->second.c_str();
}

/**
 * writeValue()
 *
 * Function predefines or writes configuration
 * values. It does not save these values
 * to the physical configuration file.
 *
 * @return void
 */
void MCFG::writeValue(string list,string key,string value)
{
	Config[list+'/'+key] = value;
	return;
}

/**
 * rehashConfig()
 *
 * Function rehashes the configuration
 * file. It clears the current configuration
 * and loads the new one!
 *
 * !WARNING! In alpha stage, there is currently
 * no error checking. So rehashing an "invalid" config
 * file _MAY_CAUSE_ unexpected behavior (such as program
 * crashing or hanging). Please use this sparingly until
 * it is further developed.
 *
 * @return void
 */
void MCFG::rehashConfig()
{
	// Reload this beast... Grandma, here we come!
	INIT * init = new INIT(cFile);
	delete init;
	return;
}
