/**
 * Sockets.h
 * Cross-platform socket interface
 *
 * Last Update: 31 July 2011
 */

#ifndef __MICROSOCKETS_SOCKETSIMPL_H_
#define __MICROSOCKETS_SOCKETSIMPL_H_

#include "Sockets.h"

namespace MicroSockets
{
    class SocketsImpl : public Sockets
    {
    public:
        SocketsImpl();
        SocketsImpl(const char* host, unsigned int port);
        virtual ~SocketsImpl();

        virtual const char* getHostname() const;
        virtual unsigned int getPort() const;
        virtual int getSocket() const;
        virtual CONNECTION_TYPE getConnectionType() const = 0;

        virtual bool isConnected() const;

        virtual std::string Read(unsigned int length=256);
        virtual void Write(const char* data);
        virtual void Write(const std::string& data);

    protected:
        int setupSockets();
        void cleanupSockets();
        void updateHostname(const char* host);
        void updatePort(unsigned int port);
        sockaddr* getSAddr() const;

    private:
        inline void clearBuffer();
        void Write(const char* data, unsigned int length);

#ifdef _WIN32
        WSAData WsaData;
#endif // _WIN32

        const char* Hostname;
        unsigned int Port;
        int Socket;
        bool Connected;
        struct sockaddr_in Saddr;
        struct hostent * Host;
        char* Buffer;
    };
}

#endif // __MICROSOCKETS_SOCKETSIMPL_H_
