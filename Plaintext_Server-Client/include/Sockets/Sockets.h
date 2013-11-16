/**
 * Sockets.h
 * Minimal Cross-Platform Plaintext Server/Client
 *
 * "Bare-bones" sockets
 *
 * (C) Copyright 2011 Dennis J. McWherter, Jr.
 *
 * 1/15/2011
 */

#ifndef __SOCKETS_SOCKETS_H__
#define __SOCKETS_SOCKETS_H__

#include <string>
#ifdef _WIN32
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#else // Linux
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
// Update some things to comply with winsock - just keeps things cleaner
typedef int SOCKET;
#define INVALID_SOCKET ~0
#define SOCKET_ERROR -1
#endif

class Sockets
{
public:
	// Constructor/destructor set
	Sockets(std::string host,int port,int type);
	~Sockets();

	// Functions
	int init();
	int getPort();
	std::string getHost();
	std::string recvBytes();
	void sendBytes(std::string data);

private:
	std::string _hostname;
	int _port, _type; // Server port & type
#ifdef _WIN32
	WSAData _wsData;
#endif
	struct sockaddr_in _sa;
	struct hostent *_host;
	SOCKET _sock; // Not multi-threaded, so direct connection TCP for this
	friend class Server;
};
#endif
