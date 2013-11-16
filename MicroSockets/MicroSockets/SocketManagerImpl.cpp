/**
 * MicroSockets.cpp
 * Main entry point for MicroSockets light-weight cross-platform
 * socket library.
 *
 * Last Update: 31 July 2011
 */

#include "SocketManagerImpl.h"
#include "ServerSockImpl.h"

namespace MicroSockets
{
    SocketManagerImpl::SocketManagerImpl()
        : ServerSocket(0)
    {
    }

    SocketManagerImpl::~SocketManagerImpl()
    {
        if(ServerSocket)
            delete ServerSocket;
    }

    ServerSock * SocketManagerImpl::NewServerSock(const char* host, unsigned int port)
    {
        if(ServerSocket)
            delete ServerSocket;
        ServerSocket = new ServerSockImpl(host, port);
        return ServerSocket;
    }

    static SocketManager * NewSocketManager()
    {
        return new SocketManagerImpl;
    }
}
