/**
 * MicrosonicBot an IRC Bot
 *
 * (C) 2010 DENNIS J. MCWHERTER JR. All Rights Reserved.
 */

#include "BotCommands.h"

botCommands::botCommands()
{
}

botCommands::~botCommands()
{
}

std::string botCommands::command_list(std::string nick,bool access,bool admin)
{
	// Global commands
	std::string sendTxt = "PRIVMSG "+nick+" :USER LEVEL COMMANDS\r\n"+
		"PRIVMSG "+nick+" :------------------------\r\n"+
		"PRIVMSG "+nick+" :!say_hello !channels\r\n"+
		"PRIVMSG "+nick+" : \r\n";

	// For users with access
	if(access == true)
	{
		sendTxt += "PRIVMSG "+nick+" :ACCESS LEVEL COMMANDS\r\n"+
		"PRIVMSG "+nick+" :------------------------\r\n"+
		"PRIVMSG "+nick+" :!op !deop !hop !dehop !voice !devoice !moderate\r\n"+
		"PRIVMSG "+nick+" :!unmoderate !kick !ban !unban !lock !unlock\r\n"+
		"PRIVMSG "+nick+" : \r\n";
	}

	// Let's show our admins some love :)
		// For users with access
	if(admin == true)
	{
		sendTxt += "PRIVMSG "+nick+" :ADMIN LEVEL COMMANDS\r\n"+
		"PRIVMSG "+nick+" :------------------------\r\n"+
		"PRIVMSG "+nick+" :!quit !leave !join !awho\r\n"+
		"PRIVMSG "+nick+" : \r\n";
	}

	return sendTxt;
}

std::string botCommands::hello_world(std::string chan)
{
	return "PRIVMSG "+chan+" :Hello World!!!\n";
}

std::string botCommands::list_channels(std::string nick,const std::vector<std::string> &channels)
{
	// Just go through the iteration and let the user know what's up via PM ;)
	std::string msg = "PRIVMSG "+nick+" :I am currently active on the following channel(s):\n"+
		"---------------------\n";
	for(unsigned int i=0; i < channels.size(); i++)
		msg += "PRIVMSG "+nick+" :"+channels.at(i)+"\n";

	return msg;
}

std::string botCommands::join(std::string nick,std::string msg,std::vector<std::string> &channels)
{
	std::string jchan;
	if(msg.find("#") != std::string::npos)
		jchan = msg.substr(msg.find("#")); // If there is more text, assume it's a key
	else
		return "PRIVMSG "+nick+" :I need a channel to join. I cannot join 'nothingness,' sorry.\n"; // Nope, forgot the channel doh!

	if(jchan != "")
	{
		std::string channame = jchan.substr(0,msg.find(" ")); // If we have a key, just parse it out so it doesn't save
		// Make sure we're not already on the channel
		for(unsigned int i = 0; i < channels.size(); i++)
		{
			if(memcmp(channels.at(i).data(),channame.data(),channels.at(i).length()) == 0)
			{
				return "PRIVMSG "+nick+" :I'm already on that channel!\n";
			}
		}
		channels.push_back(channame);
	}
	return "JOIN "+jchan+"\n";
}

std::string botCommands::part(std::string chan,std::string nick,std::string full,std::vector<std::string> &channels)
{
	if(chan != "")
	{
		bool is_on = false;

		// Remove from our active chan list! erm. well. make sure we're on the channel first :S
		for(unsigned int i = 0; i < channels.size(); i++)
		{
			// Found it! Erase the entry
			if(memcmp(channels.at(i).data(),chan.data(),channels.at(i).length()) == 0)
			{
				is_on = true;
				channels.erase(channels.begin()+i);
				break; // No reason to continue looping
			}
		}

		if(is_on == false)
		{
			return "NOTICE "+nick+" :I'm not on that channel.\r\n";
		}

		// We're on the channel so let's do it!
		std::string msg = full.substr(full.find("!leave")+7);

		return "PART "+chan+" "+msg+"\r\n";
	}
	return "NOTICE "+nick+" :We're not in a channel; this is PM.\r\n";
}

std::string botCommands::mode(std::string chan,std::string full,std::string nick,char* mode,std::string cmd)
{
	std::string privnick = full.substr(full.find(cmd)+(cmd.length()+1));
	if(privnick.empty())
		privnick = nick;
	return "MODE "+chan+" "+mode+" "+privnick+"\n";
}

std::string botCommands::kick(std::string chan,std::string full)
{
	std::string msg = full.substr(full.find("!kick")+6);
	return "KICK "+chan+" "+msg+"\n";
}

std::string botCommands::awho(std::string nick,std::vector<std::string> usernick,std::vector<std::string> loggedin)
{
	std::string sendTxt = "PRIVMSG "+nick+" :LOGGED IN USERS\n";
	sendTxt += "PRIVMSG "+nick+" :----------------------------\n";
	for(unsigned int i=0;i<usernick.size();i++)
		sendTxt += "PRIVMSG "+nick+" :Access: "+loggedin.at(i)+"/User: "+usernick.at(i)+"\n";

	return sendTxt;
}
