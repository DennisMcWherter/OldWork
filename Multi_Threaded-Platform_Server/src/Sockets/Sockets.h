/**
 * Sockets/Sockets.h
 * Sockets class
 *
 * File part of "Multithreaded Multiplatform _server"
 *
 * Dennis J. McWherter, Jr.
 * 12/28/10
 */

#ifndef __SOCKETS_SOCKETS_H__
#define __SOCKETS_SOCKETS_H__

// Includes
#include <stdio.h>
#include <queue>
#include "../IRC/IRC.h"
#ifdef _WIN32 // WIN32
#include <WinSock2.h>
#pragma comment(lib,"wsock32.lib")
#pragma comment(lib,"ws2_32.lib")
typedef WSAPOLLFD POLL_T;
#else // LINUX
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/poll.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define INVALID_SOCKET ~0
#define SOCKET_ERROR -1
typedef int SOCKET;
typedef struct pollfd POLL_T;
#endif

// Max connections
#define MAX_CONNECTIONS 2

class Sockets
{
public:
	Sockets(std::string a,int p);
	~Sockets();

	// Functions
	int init();
	int getPort();
	int getConnected();
	int acceptClient();
	int isFull();
	SOCKET getSocket(int i);
	SOCKET getServerSock();
	std::string getAddr();
	char* getClientAddr(int i);
	std::queue<int> pollRes();
	void writeSocket(int i,std::string b);
	void clientExit(int i);

	// To make this baby an IRC server
	IRC *irc;

private:
	struct sockaddr_in sa, ca[MAX_CONNECTIONS];
	struct hostent *host;
	POLL_T _polls[MAX_CONNECTIONS];
	SOCKET _server;
	SOCKET _client[MAX_CONNECTIONS];
	int clen[MAX_CONNECTIONS];
	std::string _addr;
	int _port;
	int _connected;

#ifdef _WIN32 // WIN32
	WSAData _ws;
#endif
};
#endif
