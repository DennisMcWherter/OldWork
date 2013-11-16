/**
 * MicrosonicBot an IRC Bot
 *
 * (C) 2010 DENNIS J. MCWHERTER JR. All Rights Reserved.
 */

#include <fstream>
#include <stdlib.h>
#include "ConfigParser.h"
#include "IRC.h"

ConfigParser::ConfigParser()
	: FatalError(false)
{
	// Keep things cleaned up before we use them
	access.clear();
	pass.clear();
	admin.clear();
	channels.clear();
}

ConfigParser::~ConfigParser()
{
}

void ConfigParser::parseConfig()
{
	std::ifstream cFile("mbot.conf");
	std::string line;
	bool acc = false, chan = false, admins = false, bPort = false, bServer = false, bNick = false, die = false;
	int ePos;
	int ccount = 0, ucount = 0, acount = 0;

	if(!cFile)
	{
		parseError("Fatal Error: Could not open config file (mbot.conf)\n\n");
		return;
	} else {
		printf("Parsing config file...\r\n");
	}

	while(std::getline(cFile,line,'\n'))
	{
		if(!line.length()) continue; // Skip blank lines

		// Parse comments & line breaks
		if(line[0] == ';') continue;
		if(line[0] == '//') continue;

		// Parse var blocks
		if(line[0] == '[' && line[1] == 'a' && line[2] == 'c')
		{
			acc = true;
			continue;
		} else if(line[0] == '[' && line[1] == 'c') {
			chan = true;
			continue;
		} else if(line[0] == '[' && line[1] == 'a' && line[2] == 'd') {
			admins = true;
			continue;
		}

		if(acc == true)
		{
			// If we're still reading, take the vars then <3
			if(line.find("[/access]") == std::string::npos)
			{
				ePos = line.find("=");
				access.push_back(line.substr(0,ePos));
				pass.push_back(line.substr(ePos+1));
				ucount++;
			} else {
				acc = false;
				printf("Parsed %d users with access...\n",ucount);
				continue;
			}
		} else if(chan == true) {
			// Channels
			if(line.find("[/channels]") == std::string::npos)
			{
				channels.push_back(line);
				ccount++;
			} else {
				chan = false;
				printf("Parsed %d channels to join...\n",ccount);
				continue;
			}
		} else if(admins == true) {
			// Find admins
			if(line.find("[/admins]") == std::string::npos)
			{
				admin.push_back(line);
				acount++;
			} else {
				admins = false;
				printf("Parsed %d bot admins...\n",acount);
				continue;
			}
		}

		// Find our nickname, server, etc.
		if(bServer == false)
		{
			if(size_t pos = line.find("server=") != std::string::npos)
			{
				server = line.substr(pos+6);
				bServer = true;
			}
		}
		if(bPort == false)
		{
			if(size_t pos = line.find("port=") != std::string::npos)
			{
				sport = line.substr(pos+4);
				port = strtoul(line.substr(pos+4).c_str(),NULL,0);
				bPort = true;
			}
		}
		if(bNick == false)
		{
			if(size_t pos = line.find("botnick=") != std::string::npos)
			{
				botnick = line.substr(pos+7);
				bNick = true;
			}
		}

		// Make sure we edited our config file like good little boys and girls :)
		if(line.find("die") != std::string::npos)
			die = true;

		// If access and chan are false we're not going to do anything o_O
	}
	cFile.close();

	// Do some final error checking make sure we have necessary info
	if(bServer == false || bPort == false || bNick == false)
	{
		parseError("\r\nFatal Error: Could not find required information! (Server, port, or nickname)\n\nPlease check that you have properly set your config.\n\n");
		return;
	}

	// Grr.. EDIT YOUR CONFIG!
	if(die == true)
	{
		parseError("Fatal Error: Edit your config file!\n\n");
		return;
	}

	printf("Done!\r\n----------------\r\n");
}

void ConfigParser::parseError(const char* err)
{
	printf("%s",err);
	FatalError = true;
}
