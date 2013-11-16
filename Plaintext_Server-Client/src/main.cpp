/**
 * main.cpp
 * Minimal Cross-Platform Plaintext Server/Client
 *
 * Main application which allows the program to properly function
 *
 * (C) Copyright 2011 Dennis J. McWherter, Jr.
 *
 * 1/15/2011
 */

#include "Server.h"
#include "Client.h"
// Thread stuff - Note this is _NOT_ a multi-threaded server. These are just threads to allow handling of sending/receiving messages concurrently
#ifdef _WIN32
#include <process.h> // _beginthread/_endthread reside here
#else // Linux
#include <pthread.h>
#endif
#include <iostream>

using namespace std;

void serverThread(void* lParam);
void clientThread(void* lParam);

static int threadExit = 0;

#ifdef __linux__
// Sleep in milliseconds
void Sleep(int ms)
{
	usleep(ms*1000);
}
#endif

int main()
{
	int type = 0, port = 1234;
	std::string host("127.0.0.1"), input("");

	// Quick setup parameters
	/*cout<< "Please select the behavior of the program.\n\nType '0' to run a server or '1' to access a server" << endl << endl << "Selection: ";
	cin >> type;
	
	cout<< "Please enter the hostname: ";
	cin >> host;

	cout<< "Please enter the port number: ";
	cin >> port;*/

	// Determine what to do
	if(type > 0) // Client
	{
		// Nothing right now
	} else { // Server
		Server *server = new Server(host,port);
		if(server->init() != 0)
			cerr << "Could not initialize server!";
		else {
			server->acceptClient();
			_beginthread(serverThread,0,(void*)server);
			while(!server->getShutdown())
			{
				getline(cin,input);
				if(input == "exit"){
					threadExit = 1;
					server->setShutdown();
				}
				Sleep(100);
			}
		}
		delete server;
		server = NULL;
	}
	system("pause");
	return 0;
}

void serverThread(void* lParam)
{
	Server *server = (Server*)lParam;
	while(!threadExit)
	{
		//server->acceptClient();
		Sleep(100);
	}
	_endthread();
}
