/**
 * MicroSockets.h
 * Cross-platform socket interface
 *
 * Last Update: 31 July 2011
 */

#ifndef __MICROSOCKETS_SOCKETMANAGER_H_
#define __MICROSOCKETS_SOCKETMANAGER_H_

#include "Sockets.h"
#include "ServerSock.h"

#ifdef _WIN32
#define MICROSOCKAPI __declspec(dllexport)
#else
#define MICROSOCKAPI
#endif

namespace MicroSockets
{
    class SocketManager
    {
    public:
        SocketManager(){}
        virtual ~SocketManager(){}

        virtual ServerSock * NewServerSock(const char* host, unsigned int port) = 0;
    };
    typedef SocketManager * SMPTR;
    SMPTR MICROSOCKAPI NewSocketManager();
}

#endif // __MICROSOCKETS_SOCKETMANAGER_H_
