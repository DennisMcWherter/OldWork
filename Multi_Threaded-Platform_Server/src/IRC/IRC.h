/**
 * IRC/IRC.h
 * IRC class to create an IRC server - This is simply a "manager" based off the current server architecture
 *
 * - There is no real implementation of this; I am going to begin work on an IRCd
 *
 * File part of "Multithreaded Multiplatform _server"
 *
 * Dennis J. McWherter, Jr.
 * 12/28/10
 */

#ifndef __IRC_IRC_H__
#define __IRC_IRC_H__
#include <string>
#include <map>
#include <vector>

class IRC
{
public:
	// Constructors and destructors aren't being used at this time
	IRC(){}
	~IRC(){}

	// Functions
	int getClientNumber(std::string nick);
	int setNickName(int i,std::string nick);
	std::string getNickName(int i);
	void joinChannel(int i,std::string chan);

private:
	// Well... if we're an IRC server, let's do this stuff...
	std::map<int,std::string> _nicknames; // Only one nickname per user
	std::map<int,std::vector<std::string> > _channels; // We can have multiple channels however...
	std::map<std::string,std::vector<std::string> > _chanList; // Names list
};
#endif
