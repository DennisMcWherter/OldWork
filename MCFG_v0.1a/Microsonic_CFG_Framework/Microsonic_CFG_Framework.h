/**
 * @file Microsonic_CFG_Framework.h
 * Microsonic Configuration Framework
 *
 * The framework was designed to help C++ developers
 * with their applications and save time in parsing
 * configuration. This particular file contains all the
 * main declarations.
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

#pragma once
#ifndef __MICROSONIC_CF_MAIN_H__
#define __MICROSONIC_CF_MAIN_H__
#include <iostream>
#include <string>
#include <map>

/**
 * @namespace MCFG
 *
 * The main namespace for the Microsonic Configuration Framework.
 * Contains most of the important stuff!
 */
namespace MCFG
{
	// Global namespace variables
	extern std::map<std::string,std::string> Config;
	extern std::string configList; // Configuration list to be looking through (this allows to have multiple config lists stored at one runtime)
	extern std::string cFile;
	extern const char* err;
	extern int lineno;

	/**
	 * @class MCFG
	 *
	 * Main MCFG Parsing and control
	 */
	class INIT
	{
	public:
		INIT(std::string file);
		~INIT();
		void readConfig(std::string file);
		std::string trim(std::string line);
	private:
		bool parseLine(std::string line);
		// Vars
		std::string tempKey;
		std::string tempVal;
		bool multiline;
		bool quote;
	};

	// Main functions
	extern const char* getValue(std::string list,std::string key);
	extern void writeValue(std::string list,std::string key,std::string value);
	extern void rehashConfig();
}
#endif
