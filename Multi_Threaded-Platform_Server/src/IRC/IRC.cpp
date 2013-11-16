/**
 * IRC/IRC.cpp
 * IRC class to create an IRC server - Main "manager" for IRC
 *
 * File part of "Multithreaded Multiplatform _server"
 *
 * - There is no real implementation of this; I am going to begin work on an IRCd   
 *
 * Dennis J. McWherter, Jr.
 * 12/31/10
 */

#include "IRC.h"

// Quick little trim functions
void trimWhiteSpace(std::string& str)
{
	while(size_t pos = str.find(" ") != std::string::npos)
		str.erase(pos,1);
}

int IRC::getClientNumber(std::string nick)
{
	for(unsigned int i=0;i<_nicknames.size();++i)
		if(_nicknames.at(i) == nick)
			return i;
	return -1; // Error, could not find socket #
}

int IRC::setNickName(int i,std::string nick)
{
	/*if(nick.find("%") != std::string::npos || nick.find("@") != std::string::npos || nick.find("&") == std::string::npos ||
		nick.find("~") != std::string::npos || nick.find("+") != std::string::npos ||
		nick.find("=") != std::string::npos || nick.find("*") != std::string::npos ||
		nick.find("!") != std::string::npos || nick.find("#") != std::string::npos)
	{
		return -1; // Erroneous nickname
	}*/
	for(unsigned int j=0;j<_nicknames.size();++i)
		if(_nicknames[j] == nick)
			return -2; // Nickname in use
	// Format name to only 16 characters and no spaces
	nick = nick.substr(0,15);
	_nicknames[i] = nick; // Otherwise, update nick!
	return 0;
}

std::string IRC::getNickName(int i)
{
	return _nicknames.at(i);
}

void IRC::joinChannel(int i,std::string chan)
{

}
