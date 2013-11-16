/**
 * ServerBase.h
 * Server sockets interface for MicroSockets
 *
 * Last Update: 31 July 2011
 */

#ifndef __MICROSOCKETS_ServerSock_H_
#define __MICROSOCKETS_ServerSock_H_

#include "Sockets.h"

namespace MicroSockets
{
    class ServerSock
    {
    public:
        ServerSock(){}
        virtual ~ServerSock(){}

        virtual CONNECTION_TYPE getConnectionType() const = 0;

        virtual int reconnect(unsigned int backlog) = 0;
    };
}

#endif // __MICROSOCKETS_ServerSock_H_
