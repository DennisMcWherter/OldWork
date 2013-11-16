/**
 * @file MCFG_Example.cpp
 * Microsonic Configuration Framework
 *
 * The framework was designed to help C++ developers
 * with their applications and save time in parsing
 * configuration. This particular file is an example
 * on how to properly and effectively use the configuration framework!
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

#include <cstring>
#include "Microsonic_CFG_Framework.h"

using namespace std;
using namespace MCFG;

int main()
{
	INIT::INIT("example.conf"); // Init our config
	writeValue("block1","Testvar","Predefined_Config_Var"); // Shows the ability to create "pre-defined" vars

	// Loose error handling
	// Check if the framework returned any error.
	if(strcmp(err,"") != 0)
	{
		printf("An error occurred: %s\nLine: %d\n",err,lineno-1);
		std::getchar();
		return 0;
	}

	// No errors, let's read our config vars 
	printf("Reading 'block1' configuration block\nTestvar: %s\nTest1: %s\n\n",getValue("block1","Testvar"),getValue("block1","Test1"));
	printf("Rehashing config...\n\nHit Enter to Continue...\n\n");
	
	fflush(stdin);
	std::getchar(); // Pause

	// Rehash & re-read
	rehashConfig();
	printf("Reading 'block1' configuration block (after rehash)\nTestvar: %s\nTest1: %s\nTest5: %s\n\n",getValue("block1","Testvar"),getValue("block1","Test1"),getValue("block1","Test5"));
	printf("Read 'block2' configuration block\nTestvar: %s\n\n",getValue("block2","Testvar"));

	fflush(stdin);
	std::getchar(); // Pause

	fflush(stdin);
	return 0;
}
