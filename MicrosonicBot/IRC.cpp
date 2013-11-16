/**
 * MicrosonicBot an IRC Bot
 *
 * (C) 2010 DENNIS J. MCWHERTER JR. All Rights Reserved.
 */

#include "IRC.h"

/**
 * Constructor
 */
IRC::IRC()
	: inChannel(false), dataSock(NULL), CMD(NULL)
{
	parseConfig(); // Give necessary access and join channels!
}

/**
 * Destructor
 */
IRC::~IRC()
{
	delete CMD;
}

/**
 * Connect to IRC Function
 */
bool IRC::ConnectToIRC()
{
	// Save channels - INSTAJOIN <3
	for(unsigned int i = 0; i < channels.size(); i++)
		JOIN += "JOIN "+channels.at(i)+"\n";

	// Set up our info we need to send at the beginning :)
	USER = "USER " + botnick + " 8 * :" + botnick + "\n";
	NICK = "NICK " + botnick + "\n";

	WSAStartup(MAKEWORD(2,2),&WSADataStruct); // init WinSock

	dataSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // Make socket

	// Connect struct so we know what's going on
	ServerAddr = gethostbyname(server.c_str());
	// Don't continue until we're sure that our host resolves
	if(ServerAddr == NULL)
	{
		std::string err = "\r\nUnable to resolve connection to host: "+server+" on port "+sport+"\r\n";
		parseError(err.c_str());
		return false;
	}
	structSock.sin_family = AF_INET; // Family
	structSock.sin_port   = htons(port); // Port
	structSock.sin_addr.s_addr = *((unsigned long*)ServerAddr->h_addr_list[0]); // Server address
	memset(structSock.sin_zero,0,sizeof(structSock.sin_zero)); // 0 out zero xD

	// Connect to the server - obviously need some error checking xD
	if(connect(dataSock, (sockaddr*)&structSock, sizeof(sockaddr)) == SOCKET_ERROR)
	{
		std::string err = "\r\nUnable to resolve connection to host: "+server+" on port "+sport+"\r\n";
		parseError(err.c_str());
		return false;
	}

	// Let things happen
	Sleep(1200);
	SendInfo(); // Send our user data :)

	return true;
}

bool IRC::QuitIRC()
{
	shutdown(dataSock, 2);
	closesocket(dataSock);
	WSACleanup();

	return true;
}

void IRC::HandleIRCMsg()
{
	std::string tempBuf, sendTxt, chan, privnick;
	bool has_access = false, is_admin = false;

	// Static buffer of 512 (0x200) so we'll do that now!
	// Truncate the end of the line <3
	for(int i=0;i<512;i++)
		if(recvBuf[i] == '\n') recvBuf[i++] = '\0';

	tempBuf = recvBuf; // It's parsed, so store it!

	// Break up our msg a bit!
	std::string raw,msg;
	size_t pos1 = tempBuf.find_first_of(":");
	raw = tempBuf.substr((pos1+1),tempBuf.find(":",pos1+1)); // The RAW middle (between first two :'s)
	size_t pos2 = raw.find_last_of(":"); // Where to start for our msg
	msg = tempBuf.substr(pos2+1); // Take only the message if one exists!

	if(raw.find("#") != std::string::npos)
	{
		chan = raw.substr(raw.find_first_of("#"),raw.find_last_of(":")-1); // Our channel
		chan = chan.substr(0,chan.find(" :")); // Remove the " :", it breaks things!
	}

	if(raw.find("!") != std::string::npos)
		privnick = raw.substr(0,raw.find_first_of("!")); // Nickname of msg sender

	// Parse and print the output to BASIC IRC stuff
	if(tempBuf.find("PRIVMSG") == std::string::npos) // RAW IRC to simply display
		printf("%s\n",tempBuf.c_str());
	else if(raw.find("PRIVMSG #") != std::string::npos) // Chan msgs
		printf("[%s @ %s] %s\n",privnick.c_str(),chan.c_str(),msg.c_str());
	else if(raw.find("PRIVMSG") != std::string::npos) // PRIVMSG
	{
		printf("[%s] %s\n",privnick.c_str(),msg.c_str());

		// Handle login/logout
		if(msg.find(".login") != std::string::npos){
			login(msg,privnick);
		} else if(msg.find(".logout") != std::string::npos) {
			logout(privnick);
		}
	}

	if(tempBuf.find("PING :") != std::string::npos && tempBuf.find("PRIVMSG") == std::string::npos)
	{
		sendTxt = "PONG :" + tempBuf.substr((tempBuf.find_last_of(":")+1), (tempBuf.find_last_of('\r')-1)) + "\n";
		SendMsg(sendTxt.c_str());

		// Not in a channel? :(
		// Rejoin
		if(!inChannel)
		{
			Sleep(2000);
			SendMsg(JOIN.c_str());
			printf("%s",JOIN.c_str());
			inChannel = true;
		}
	}
	
	// Check logged in users!
	// grep: need to make a way to auto logout users if inactive for too long
	for(unsigned int i=0;i<usernick.size();i++)
	{
		if(usernick.at(i) == privnick)
		{
			has_access = true;
			// Has access? Let's check if they are admin!
			for(unsigned int ii=0;ii<admin.size();ii++)
			{
				if(admin.at(ii) == loggedin.at(i))
				{
					is_admin = true;
				}
			}
			break;
		}
	}

	// Our command loop for everyone
	if(msg.find(":!say_hello") != std::string::npos)
	{
		if(!chan.empty())
		{
			SendMsg(CMD->hello_world(chan).c_str());
			printf("%s",CMD->hello_world(chan).c_str());
		}
	} else if(msg.find(":!help") != std::string::npos || msg.find(":!cmd") != std::string::npos
		|| msg.find(":!commands") != std::string::npos) {
			SendMsg(CMD->command_list(privnick,has_access,is_admin).c_str());
			printf("%s",CMD->command_list(privnick,has_access,is_admin).c_str());
	} else if(msg.find(":!channels") != std::string::npos) {
		SendMsg(CMD->list_channels(privnick,(const std::vector<std::string>&)channels).c_str());
		printf("%s",CMD->list_channels(privnick,(const std::vector<std::string>&)channels).c_str());
	}

	// Commands that require access
	if(has_access == true)
	{
		if(msg.find(":!op") != std::string::npos) {
			if(!chan.empty())
			{
				if(has_access == true)
				SendMsg(CMD->mode(chan,tempBuf,privnick,"+o","!op").c_str());
				printf("%s",CMD->mode(chan,tempBuf,privnick,"+o","!op").c_str());
			}
		} else if(msg.find(":!deop") != std::string::npos) {
			if(!chan.empty())
			{
				SendMsg(CMD->mode(chan,tempBuf,privnick,"-o","!deop").c_str());
				printf("%s",CMD->mode(chan,tempBuf,privnick,"-o","!deop").c_str());
			}
		} else if(msg.find(":!hop") != std::string::npos) {
			if(!chan.empty())
			{
				SendMsg(CMD->mode(chan,tempBuf,privnick,"+h","!hop").c_str());
				printf("%s",CMD->mode(chan,tempBuf,privnick,"+h","!hop").c_str());
			}
		} else if(msg.find(":!dehop") != std::string::npos) {
			if(!chan.empty())
			{
				SendMsg(CMD->mode(chan,tempBuf,privnick,"-h","!dehop").c_str());
				printf("%s",CMD->mode(chan,tempBuf,privnick,"-h","!dehop").c_str());
			}
		} else if(msg.find(":!voice") != std::string::npos) {
			if(!chan.empty())
			{
				SendMsg(CMD->mode(chan,tempBuf,privnick,"+v","!voice").c_str());
				printf("%s",CMD->mode(chan,tempBuf,privnick,"+v","!voice").c_str());
			}
		} else if(msg.find(":!devoice") != std::string::npos) {
			if(!chan.empty())
			{
				SendMsg(CMD->mode(chan,tempBuf,privnick,"-v","!devoice").c_str());
				printf("%s",CMD->mode(chan,tempBuf,privnick,"-v","!devoice").c_str());
			}
		} else if(msg.find(":!moderate") != std::string::npos) {
			if(!chan.empty())
			{
				SendMsg(CMD->mode(chan,tempBuf,"Moderated","+m","!moderate").c_str());
				printf("%s",CMD->mode(chan,tempBuf,"Moderated","+m","!moderate").c_str());
			}
		} else if(msg.find(":!unmoderate") != std::string::npos) {
			if(!chan.empty())
			{
				SendMsg(CMD->mode(chan,tempBuf,"Moderated","-m","!unmoderate").c_str());
				printf("%s",CMD->mode(chan,tempBuf,"Moderated","-m","!unmoderate").c_str());
			}
		} else if(msg.find(":!lock") != std::string::npos) {
			if(!chan.empty())
			{
				std::string key = msg.substr(msg.find("!lock")+6);
				SendMsg(CMD->mode(chan,tempBuf,key,"+k","!lock").c_str());
				printf("%s",CMD->mode(chan,tempBuf,key,"+k","!lock").c_str());
			}
		} else if(msg.find(":!unlock") != std::string::npos) {
			if(!chan.empty())
			{
				std::string key = msg.substr(msg.find("!unlock")+6);
				SendMsg(CMD->mode(chan,tempBuf,key,"-k","!unlock").c_str());
				printf("%s",CMD->mode(chan,tempBuf,key,"-k","!unlock").c_str());
			}
		} else if(msg.find(":!ban") != std::string::npos) {
			if(!chan.empty())
			{
				std::string user = msg.substr(msg.find("!ban")+5);
				SendMsg(CMD->mode(chan,tempBuf,user,"+b","!ban").c_str());
				printf("%s",CMD->mode(chan,tempBuf,user,"+b","!ban").c_str());
			}
		} else if(msg.find(":!unban") != std::string::npos) {
			if(!chan.empty())
			{
				std::string user = msg.substr(msg.find("!unban")+7);
				SendMsg(CMD->mode(chan,tempBuf,user,"-b","!unban").c_str());
				printf("%s",CMD->mode(chan,tempBuf,user,"-b","!unban").c_str());
			}
		} else if(msg.find(":!kick") != std::string::npos) {
			if(!chan.empty())
			{
				std::string user = msg.substr(msg.find("!kick")+6);
				SendMsg(CMD->kick(chan,tempBuf).c_str());
				printf("%s",CMD->kick(chan,tempBuf).c_str());
			}
		}
		
		// Check if user has admin access!
		if(is_admin == true)
		{
			if(msg.find(":!quit") != std::string::npos) // Force bot to quit
			{
				if(!chan.empty())
				{
					SendMsg("QUIT MicrosonicBot v1.0.0.0 - http://microsonic.org\n");
					FatalError = true;
				}
			} else if(msg.find(":!awho") != std::string::npos) { // Check which users are logged in!
				SendMsg(CMD->awho(privnick,usernick,loggedin).c_str());
				printf("%s",CMD->awho(privnick,usernick,loggedin).c_str());
			} else if(msg.find(":!leave") != std::string::npos)	{
				std::string cmd = CMD->part(chan,privnick,tempBuf,(std::vector<std::string>&)channels); // This should only be run once per command
				SendMsg(cmd.c_str());
				printf("%s",cmd.c_str());
			} else if(msg.find(":!join") != std::string::npos) {
				std::string cmd = CMD->join(privnick,msg,(std::vector<std::string>&)channels);
				SendMsg(cmd.c_str());
				printf("%s",cmd.c_str());
			}
		}
	}

	Sleep(350); // 350 ms rest
	prune_dead(); // Cleanup any channels we may no longer be on
}

void IRC::SendMsg(const char* msg)
{
	send(dataSock, msg, strlen(msg), 0);
}

void IRC::SendInfo()
{
	SendMsg(NICK.c_str());
	SendMsg(USER.c_str());
}

void IRC::login(std::string msg,std::string nick)
{
	std::string sendTxt = "PRIVMSG "+nick+" :";
	std::string login = "",passwd = "";
	// Check if we're already logged in... no sense in duplicating our "session"
	for(unsigned int i=0;i<usernick.size();i++)
	{
		if(usernick.at(i) == nick)
		{
			sendTxt += "You are already logged in!\n";
			SendMsg(sendTxt.c_str());
			printf("%s\n",sendTxt.c_str());
			return;
		}
	}

	// Not logged in? Check the credentials..
	size_t pos = msg.find(".login");
	login	   = msg.substr(pos+7,(msg.find(" ",pos+7)-(pos+7)));
	// Make sure the user put both a login and pass, if not let's not crash xD
	if(msg.length() >= (strlen(".login")+login.length()+3))
		passwd = msg.substr(strlen(".login")+login.length()+3);
	else
		passwd = "";

	for(unsigned int i=0;i<access.size();i++)
	{
		if((memcmp(access.at(i).data(),login.data(),access.at(i).length()) == 0) && (memcmp(pass.at(i).data(),passwd.data(),pass.at(i).length()) == 0))
		{
			loggedin.push_back(login);
			usernick.push_back(nick);
			sendTxt += "You have successfully logged in!\n";
			SendMsg(sendTxt.c_str());
			printf("%s",sendTxt.c_str());
			return;
		}
	}

	// Uh-oh.. no good. user didn't know what was up lolz tell them sorry
	sendTxt += "Sorry, you had invalid credentials. You were not logged in.\n";
	SendMsg(sendTxt.c_str());
	printf("%s",sendTxt.c_str());
}

void IRC::logout(std::string nick)
{
	// Check if we're already logged in... if not we can't logout? o_O
	bool is_loggedin = false;
	int e;
	std::string sendTxt = "PRIVMSG "+nick+" :";
	for(unsigned int i=0;i<usernick.size();i++)
	{
		if(usernick.at(i) == nick)
		{
			is_loggedin = true;
			e = i;
			break; // Good work, the user is actually logged in haha
		}
	}

	if(is_loggedin == true)
	{
		usernick.erase(usernick.begin()+e);
		loggedin.erase(loggedin.begin()+e);
		sendTxt += "Successfully logged out!\n";
	} else {
		sendTxt += "You are not logged in.\n";
	}
	SendMsg(sendTxt.c_str());
	printf("%s",sendTxt.c_str());
}

void IRC::prune_dead()
{
	// Find dead channels
}
