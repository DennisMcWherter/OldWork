/**
 * Server.cpp
 * Server sockets for MicroSockets
 *
 * Last Update: 31 July 2011
 */

#include "ServerSockImpl.h"

namespace MicroSockets
{
    ServerSockImpl::ServerSockImpl(const char* host, unsigned int port)
        : SocketsImpl(host, port)
    {
    }

    ServerSockImpl::ServerSockImpl(const std::string& host, unsigned int port)
        : SocketsImpl(host.c_str(), port)
    {
    }

    ServerSockImpl::~ServerSockImpl()
    {
    }

    CONNECTION_TYPE ServerSockImpl::getConnectionType() const
    {
        return SERVER;
    }

    int ServerSockImpl::reconnect(unsigned int backlog)
    {
        cleanupSockets();
        setupSockets();
        return bindAndListen(backlog);
    }

    int ServerSockImpl::bindAndListen(unsigned int back)
    {
        int Socket = getSocket();
        sockaddr * sa = getSAddr();
        if(bind(Socket, sa, sizeof(*sa)) == -1)
            return 0;
        if(listen(Socket, back))
            return 0;
        return 1;
    }
}
