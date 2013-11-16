/**
 * Server.h
 * Server sockets interface for MicroSockets
 *
 * Last Update: 31 July 2011
 */

#ifndef __MICROSOCKETS_ServerSockImpl_H_
#define __MICROSOCKETS_ServerSockImpl_H_

#include "SocketsImpl.h"
#include "ServerSock.h"

namespace MicroSockets
{
    class ServerSockImpl : public ServerSock, SocketsImpl
    {
    public:
        ServerSockImpl(const char* host, unsigned int port);
        ServerSockImpl(const std::string& host, unsigned int port);
        virtual ~ServerSockImpl();

        virtual CONNECTION_TYPE getConnectionType() const;

        int reconnect(unsigned int backlog=4);
    private:
        int bindAndListen(unsigned int backlog);
    };
}

#endif // __MICROSOCKETS_ServerSockImpl_H_
