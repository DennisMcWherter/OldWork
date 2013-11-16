/**
 * Sockets.h
 * Cross-platform socket interface
 *
 * Last Update: 31 July 2011
 */

#ifndef __MICROSOCKETS_SOCKETS_H_
#define __MICROSOCKETS_SOCKETS_H_

#include <string>
#ifdef _WIN32
#include <WinSock2.h>
#pragma comment(lib, "wsock32.lib")
#elif defined(__linux__)
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#endif

namespace MicroSockets
{
    enum CONNECTION_TYPE
    {
        SERVER,
        CLIENT
    };

    class Sockets
    {
    public:
        Sockets(){}
        virtual ~Sockets(){}

        virtual const char* getHostname() const = 0;
        virtual unsigned int getPort() const = 0;
        virtual int getSocket() const = 0;
        virtual CONNECTION_TYPE getConnectionType() const = 0;

        virtual bool isConnected() const = 0;

        virtual std::string Read(unsigned int length) = 0;
        virtual void Write(const char* data) = 0;
        virtual void Write(const std::string& data) = 0;

    protected:
        virtual int setupSockets() = 0;
        virtual void cleanupSockets() = 0;
        virtual void updateHostname(const char* host) = 0;
        virtual void updatePort(unsigned int port) = 0;
        virtual sockaddr* getSAddr() const = 0;
    };
}

#endif // __MICROSOCKETS_SOCKETS_H_
