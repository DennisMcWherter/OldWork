/**
 * Sockets/Sockets.cpp
 * Sockets class
 *
 * File part of "Multithreaded Multiplatform _server"
 *
 * Dennis J. McWherter, Jr.
 * 12/28/10
 */

#include "Sockets.h"

#ifdef _WIN32 // WIN32
Sockets::~Sockets()
{
	delete irc;
	for(int i=0;i<MAX_CONNECTIONS;++i)
	{
		shutdown(_client[i],SD_BOTH);
		closesocket(_client[i]);
	}
	closesocket(_server);
	WSACleanup();
}
#else // LINUX
Sockets::~Sockets()
{
	delete irc;
	for(int i=0;i<MAX_CONNECTIONS;++i)
	{
		shutdown(_client[i],SHUT_RDWR);
		close(_client[i]);
	}
	close(_server);
}
#endif

// Multiplatform declarations
Sockets::Sockets(std::string a,int p)
	: irc(new IRC), _server(-1), _addr(a), _port(p), _connected(0)
{
	for(int i=0;i<MAX_CONNECTIONS;++i)
		_client[i] = -1;
#ifdef _WIN32 // WIN32 fix
	WSAStartup(MAKEWORD(2,2),&_ws);
#endif
	memset(&sa,0,sizeof(sa));

	// Setup sa struct
	host = gethostbyname(a.c_str());
	memcpy(&sa.sin_addr.s_addr,host->h_addr,host->h_length);
	sa.sin_family = AF_INET;
	sa.sin_port = htons(p);

	// Setup poll struct
	for(int i=0;i<MAX_CONNECTIONS;++i)
	{
		_polls[i].fd = _client[i];
		_polls[i].events = POLLIN;
	}
}
#include <iostream>
int Sockets::init()
{
	_server = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(_server == INVALID_SOCKET || _server == SOCKET_ERROR)
		return 1;
	if(bind(_server,(sockaddr*)&sa,sizeof(sa)) != 0)
		return 1;
	if(listen(_server,5) != 0)
		return 1;
	return 0;
}

int Sockets::getPort()
{
	return _port;
}

int Sockets::getConnected()
{
	return _connected;
}

int Sockets::isFull()
{
	if(_connected >= MAX_CONNECTIONS) // Should not be >, but just in case
		return 1; // Result if _server is full - don't accept anymore _clients
	return 0;
}

int Sockets::acceptClient()
{
	while(1)
	{
		if(!isFull()) // If the server is full don't even go through the routine...
			for(int i=0;i<MAX_CONNECTIONS;++i)
				if(_client[i] == INVALID_SOCKET)
				{
					clen[i] = sizeof(ca[i]);
#ifdef _WIN32 // WIN32 accept
					u_long iMode = 1;
					_client[i] = accept(_server,(sockaddr*)&ca[i],&clen[i]);
					ioctlsocket(_client[i],FIONBIO,&iMode); // Non-blocking sockets
#else // LINUX accept
					_client[i] = accept(_server,(sockaddr*)&ca[i],(socklen_t*)&clen[i]);
					fcntl(_client[i],O_NONBLOCK);
#endif
					_polls[i].fd = _client[i];
					_connected++;
					return i; // Get ready for next _client
				}
#ifdef _WIN32
		Sleep(500); // Retry...
#else
		sleep(1);
#endif
	}
	return -1; // Error
}

SOCKET Sockets::getSocket(int i) // This is read-only data
{
	return _client[i];
}

SOCKET Sockets::getServerSock()
{
	return _server;
}

std::string Sockets::getAddr()
{
	return _addr;
}

char* Sockets::getClientAddr(int i)
{
	return inet_ntoa(ca[i].sin_addr);
}

void Sockets::clientExit(int i)
{
	if(_client[i] != -1) // Make sure we don't "close" a connection multiple times...
	{
#ifdef _WIN32
		closesocket(_client[i]);
#else
		close(_client[i]);
#endif
		_client[i] = -1;
		_connected--;
	}
}

std::queue<int> Sockets::pollRes() // Function should block until signaled
{
	std::queue<int> retval;
	int t = 0;
#ifdef _WIN32
	t = WSAPoll(_polls,MAX_CONNECTIONS,1500); // Check every 1.5 seconds we want to run through our main loop again
#else
	t = poll(_polls,MAX_CONNECTIONS,1500);
#endif
	if(t != 0) // Either timed-out or there was an error
		for(int i=0;i<MAX_CONNECTIONS;++i)
			if(_client[i] == -1) continue; // Couldn't have anything from this client since no one is connected
			else if(_polls[i].events & POLLIN)
				retval.push(i);
	return retval;
}

void Sockets::writeSocket(int i,std::string b)
{
	if(i >= 0) // Send message to specific client
#ifdef _WIN32
		send(_client[i],b.c_str(),b.size(),0);
#else
		write(_client[i],b.c_str(),b.size());
#endif
	else
		for(int i=0;i<MAX_CONNECTIONS;++i) // Send message to all clients
			if(_client[i] != -1)
#ifdef _WIN32
				send(_client[i],b.c_str(),b.size(),0);
#else
				write(_client[i],b.c_str(),b.size());
#endif
}
