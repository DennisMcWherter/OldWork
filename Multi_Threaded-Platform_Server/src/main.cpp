/**
 * main.cpp
 * Main file
 *
 * File part of "Multithreaded Multiplatform Server"
 *
 * Dennis J. McWherter, Jr.
 * 12/28/10
 */

// Headers
#include "Threads/ThreadManager.h"
#include <iostream>
#include <sstream>

using namespace std;

int strToInt(std::string str)
{
	int i = 0;
	stringstream ss;
	ss << str;
	ss >> i;
	return i;
}

int main()
{
	ThreadManager *tm = new ThreadManager("localhost",1337);
	std::string err, in;
	while(1)
	{
		if(!(err = tm->getError()).empty()) // Fatal error!
			break;
		getline(std::cin,in); // Get entire line
		if(in == ".exit")
			break;
		else if(in == ".threadcount")
			cout<< "Thread count: "<< tm->getThreadCount() << endl << endl;
		else if(in == ".clientcount")
			cout<< "Clients connected: "<< tm->server->getConnected() << endl << endl;
		else if(in.substr(0,5) == ".all ")
			tm->server->writeSocket(-1,"From server: "+in.substr(5)+"\r\n");
		else if(in.substr(0,9) == ".getnick ")
			cout<< "Nickname of connection #"<< in.substr(9) << " is: "<< tm->server->irc->getNickName(strToInt(in.substr(5))) << endl << endl;
		Sleep(500);
	}
	delete tm;
	if(err.empty())
		cout<< "Server exited successfully!" << endl;
	else
		cout<< "Server exited with a fatal error: "<< err << endl;
	cin.get();
	return 0;
}
