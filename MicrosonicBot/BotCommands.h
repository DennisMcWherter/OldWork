/**
 * MicrosonicBot an IRC Bot
 *
 * (C) 2010 DENNIS J. MCWHERTER JR. All Rights Reserved.
 */

#ifndef __BOT_COMMANDS_H__
#define __BOT_COMMANDS_H__
#include <string>
#include <vector>
#include "ConfigParser.h"

class botCommands
{
public:
	botCommands();
	~botCommands();

	// Process bot does without user input

	// Commands
	std::string hello_world(std::string chan);
	std::string list_channels(std::string nick,const std::vector<std::string> &channels);
	std::string command_list(std::string privnick,bool access,bool admin);
	std::string part(std::string chan,std::string nick,std::string full,std::vector<std::string> &channels);
	std::string join(std::string nick,std::string msg,std::vector<std::string> &channels);
	std::string mode(std::string chan,std::string full,std::string nick,char* mode,std::string cmd);
	std::string kick(std::string chan,std::string full);
	std::string awho(std::string nick,std::vector<std::string> usernick,std::vector<std::string> loggedin);
};
#endif
