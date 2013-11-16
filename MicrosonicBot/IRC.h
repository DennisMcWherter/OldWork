/**
 * MicrosonicBot an IRC Bot
 *
 * (C) 2010 DENNIS J. MCWHERTER JR. All Rights Reserved.
 */

#ifndef __IRC_H__
#define __IRC_H__
#include <WinSock2.h>
#include <string>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include "BotCommands.h"
#include "ConfigParser.h"

#pragma comment(lib,"wsock32.lib")

class IRC : public ConfigParser
{
public:
	IRC();
	~IRC();

	// Main Functions
	bool ConnectToIRC();
	bool QuitIRC();
	void HandleIRCMsg();
	void SendMsg(const char* msg);
	void SendInfo();
	void login(std::string msg,std::string nick);
	void logout(std::string nick);
	void prune_dead();

	// Global vars
	SOCKET dataSock;
	char recvBuf[0x200];
	bool inChannel;

private:
	WSADATA WSADataStruct;
	struct hostent* ServerAddr;
	struct sockaddr_in structSock;

	// Checked our users who are logged in!
	std::vector<std::string> loggedin; // Stores login name which is logged in
	std::vector<std::string> usernick; // Stores chat nickname for user!

	// Info vars
	std::string USER;
	std::string NICK;
	std::string JOIN;
	std::string PART;
	std::string PRIVMSG;

	// Commands
	botCommands * CMD;
};
#endif
