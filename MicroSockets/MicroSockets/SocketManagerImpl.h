/**
 * SocketManagerImpl.h
 *
 * Last Update: 31 July 2011
 */

#ifndef __MICROSOCKETS_SOCKETMANAGERIMPL_H_
#define __MICROSOCKETS_SOCKETMANAGERIMPL_H_

#include "SocketManager.h"

namespace MicroSockets
{
    class SocketManagerImpl : public SocketManager
    {
    public:
        SocketManagerImpl();
        virtual ~SocketManagerImpl();

        virtual ServerSock * NewServerSock(const char* host, unsigned int port);
    private:
        ServerSock * ServerSocket;
    };
}

#endif // __MICROSOCKETS_SOCKETMANAGERIMPL_H_
