/**
 * Server.h
 * Minimal Cross-Platform Plaintext Server/Client
 *
 * Server class declaration
 *
 * (C) Copyright 2011 Dennis J. McWherter, Jr.
 *
 * 1/15/2011
 */

#ifndef __SERVER_H__
#define __SERVER_H__

#include "Sockets/Sockets.h"

class Server : public Sockets // Single client server class
{
public:
	Server(std::string host,int port);
	~Server();

	// Functions
	//void acceptClient();
	void acceptClient();
	void disconnectClient();
	void setShutdown();
	int getShutdown();

private:
	SOCKET _client;
	int _shutdown, _clen;
	struct sockaddr_in _ca;
};
#endif
