/**
 * Sockets.cpp
 * Minimal Cross-Platform Plaintext Server/Client
 *
 * "Bare-bones" sockets
 *
 * (C) Copyright 2011 Dennis J. McWherter, Jr.
 *
 * 1/15/2011
 */

#include "Sockets/Sockets.h"
#include <iostream>

Sockets::Sockets(std::string host,int port,int type)
	: _hostname(host), _port(port), _type(type), _sock(INVALID_SOCKET)
{
#ifdef _WIN32
	WSAStartup(MAKEWORD(2,2),&_wsData);
#endif

	_host = gethostbyname(_hostname.c_str()); // Get host data

	// Setup sockaddr_in
	_sa.sin_family	    = AF_INET;
	_sa.sin_addr.s_addr = (unsigned long)_host->h_addr;
	_sa.sin_port	    = htons(_port);
}

#ifdef _WIN32
Sockets::~Sockets()
{
	shutdown(_sock,SD_BOTH);
	closesocket(_sock);
	WSACleanup();
}
#else // Linux
Sockets::~Sockets()
{
	shutdown(_sock,SD_BOTH);
	close(_sock);
}
#endif

/**
 * init function initializes socket based on type
 */
int Sockets::init()
{
	_sock = socket(AF_INET,SOCK_STREAM,0);
	if(_type > 0) // Client
		if(connect(_sock,(sockaddr*)&_sa,sizeof(_sa)) == SOCKET_ERROR)
			return 1; // Error
	else { // Server
		if(bind(_sock,(sockaddr*)&_sa,sizeof(_sa)) == SOCKET_ERROR)
			return 1; // Error
		if(listen(_sock,2) == SOCKET_ERROR)
			return 1; // Error
	}
	return 0; // Success
}

int Sockets::getPort()
{
	return _port;
}

std::string Sockets::getHost()
{
	return _hostname;
}

/**
 * Blocking function - receive data from client continuously
 *
 * Intended to run in a separate thread
 */
std::string Sockets::recvBytes()
{
	char buf[257];
#ifdef _WIN32
	int r = recv(_sock,buf,256,0);
	buf[r] = '\0';
#else
	read(_sock,buf,256);
#endif
	return buf;
}

// Send text data to server/client
void Sockets::sendBytes(std::string data)
{
#ifdef _WIN32
	send(_sock,data.c_str(),data.size(),0);
#else // Linux
	write(_sock,data.c_str(),data.size());
#endif
}
