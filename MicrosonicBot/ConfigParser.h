/**
 * MicrosonicBot an IRC Bot
 *
 * (C) 2010 DENNIS J. MCWHERTER JR. All Rights Reserved.
 */

#ifndef __CONFIG_PARSER_H__
#define __CONFIG_PARSER_H__
#include <string>
#include <vector>

class ConfigParser
{
public:
	ConfigParser();
	~ConfigParser();

	// Parse config file
	void parseConfig();
	void parseError(const char* err);

	// Our vars we need to hold in memory
	std::vector<std::string> access; // Users who have access
	std::vector<std::string> pass; // Access passwords
	std::vector<std::string> admin; // Users with ADMIN access
	std::vector<std::string> channels; // Store our channels
	std::string server, botnick, sport;
	unsigned short port;
	bool FatalError;
};
#endif
