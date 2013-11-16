/**
 * Sockets.cpp
 * Cross-platform socket implementation
 *
 * Last Update: 31 July 2011
 */

#include "SocketsImpl.h"

#include <stdexcept>

namespace MicroSockets
{

#ifdef _WIN32
    static inline int close(unsigned int sock)
    {
        return closesocket(sock);
    }
#endif // _WIN32

    SocketsImpl::SocketsImpl()
        : Hostname("localhost"), Port(7500), Socket(0), Connected(false), Buffer(0)
    {
        if(!setupSockets()) // Some arbitrary default
            throw std::exception("Could not initialize socket connection.\n");
    }

    SocketsImpl::SocketsImpl(const char* host, unsigned int port)
        : Hostname(host), Port(port), Socket(0), Connected(false), Buffer(0)
    {
        if(!setupSockets())
            throw std::exception("Could not initialize socket connection.\n");
    }

    SocketsImpl::~SocketsImpl()
    {
        clearBuffer();
        cleanupSockets();
    }

    int SocketsImpl::setupSockets()
    {
#ifdef _WIN32
        if(!WSAStartup(MAKEWORD(2,0), &WsaData))
            return 0;
#endif // _WIN32

        Socket = socket(AF_INET, SOCK_STREAM, 0);

        Host = gethostbyname(Hostname);

        Saddr.sin_family      = AF_INET;
        Saddr.sin_addr.s_addr = (unsigned long)Host->h_addr;
        Saddr.sin_port        = htons(Port);

        return 1;
    }

    bool SocketsImpl::isConnected() const
    {
        return Connected;
    }

    const char* SocketsImpl::getHostname() const
    {
        return Hostname;
    }

    unsigned int SocketsImpl::getPort() const
    {
        return Port;
    }

    int SocketsImpl::getSocket() const
    {
        return Socket;
    }

    void SocketsImpl::cleanupSockets()
    {
        shutdown(Socket, SD_BOTH);
        close(Socket);
#ifdef _WIN32
        WSACleanup();
#endif // _WIN32
    }

    void SocketsImpl::updateHostname(const char* host)
    {
        Hostname = host;
    }

    void SocketsImpl::updatePort(unsigned int port)
    {
        Port = port;
    }

    sockaddr* SocketsImpl::getSAddr() const
    {
        return (sockaddr*)&Saddr;
    }

    std::string SocketsImpl::Read(unsigned int length)
    {
        clearBuffer();
        Buffer = new char[length+1];

#ifdef _WIN32
        int r = recv(Socket, Buffer, length, 0);
        Buffer[r] = '\0';
#else
        read(Socket, Buffer, length);
#endif
        return std::string(Buffer);
    }

    void SocketsImpl::Write(const std::string& data)
    {
        Write(data.c_str(), data.size());
    }

    void SocketsImpl::Write(const char* data)
    {
        int size = sizeof(data)*sizeof(char*);
        Write(data, size);
    }

    void SocketsImpl::Write(const char* data, unsigned int length)
    {
#ifdef _WIN32
        send(Socket, data, length, 0);
#else
        write(Socket, data, length);
#endif
    }

    void SocketsImpl::clearBuffer()
    {
        if(!Buffer)
            return; // Buffer already cleared

        delete [] Buffer;

        Buffer = 0;
    }
}
