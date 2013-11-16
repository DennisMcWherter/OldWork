/**
 * Server.cpp
 * Minimal Cross-Platform Plaintext Server/Client
 *
 * Server class implementation
 *
 * (C) Copyright 2011 Dennis J. McWherter, Jr.
 *
 * 1/15/2011
 */

#include "Server.h"
#include <iostream>

Server::Server(std::string host,int port)
	: Sockets(host,port,0), _client(INVALID_SOCKET), _shutdown(0)
{
}

Server::~Server()
{
	setShutdown();
}

void Server::acceptClient()
{
	if(_client == INVALID_SOCKET) // Only one connection at a time
	{
		_client = socket(AF_INET,SOCK_STREAM,0);
		_clen = sizeof(_ca);
		_client = accept(_sock,(sockaddr*)&_ca,&_clen);
		if(_client < 0)
			std::cout<< "error\n";
		std::cout<< "Client connected!\n";
	}
}

void Server::disconnectClient()
{
#ifdef _WIN32
	shutdown(_client,SD_BOTH);
	closesocket(_client);
#else
	shutdown(_client,THIS);
	close(_client);
#endif
	_client = INVALID_SOCKET;
}

void Server::setShutdown()
{
	_shutdown = 1;
}

int Server::getShutdown()
{
	return _shutdown;
}
