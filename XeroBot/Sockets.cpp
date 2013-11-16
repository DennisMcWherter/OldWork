/*======================================================================
 Sockets.cpp
 Small socket wrapper for XeroBot

 Copyright (C) 2011 Dennis J. McWherter, Jr.

 This software is provided 'as-is', without any express or implied
 warranty.  In no event will the authors be held liable for any damages
 arising from the use of this software.

 Permission is granted to anyone to use this software for any purpose,
 including commercial applications, and to alter it and redistribute it
 freely, subject to the following restrictions:

 1. The origin of this software must not be misrepresented; you must not
 claim that you wrote the original software. If you use this software
 in a product, an acknowledgment in the product documentation would be
 appreciated but is not required.
 2. Altered source versions must be plainly marked as such, and must not be
 misrepresented as being the original software.
 3. This notice may not be removed or altered from any source distribution.
 ========================================================================*/

#include "Sockets.h"

using namespace std;

Sockets::Sockets(const string& host, unsigned int port)
  : IsConnected(false), Socket(0), ErrorMsg()
{
  WSAStartup(MAKEWORD(2,0), &WsaData);
  Sa.sin_family = AF_INET;

  setHostName(host);
  setPort(port);

  if(!connectClient())
    ErrorMsg = "Could not connect to "+host;
}

Sockets::~Sockets()
{
  disconnectClient();
  WSACleanup();
}

void Sockets::read(string& data) const
{
  data.clear();
  if(!IsConnected)
    return;

  char buf[256];
  int read = recv(Socket, buf, 256, 0);

  if(read > 0) {
    buf[read] = '\0';
    data = buf;
  }
}

void Sockets::write(const string& data)
{
  if(!IsConnected)
    return;
  send(Socket, data.c_str(), data.length(), 0); // grep: I don't think this is working?
}

void Sockets::setHostName(const string& host)
{
  Host = host;
  Hent = gethostbyname(Host.c_str());
  Sa.sin_addr.s_addr = *((unsigned long*)Hent->h_addr_list[0]);
}

void Sockets::setPort(unsigned int port)
{
  Port = port;
  Sa.sin_port = htons(Port);
}

const string& Sockets::getErrorMsg() const
{
  return ErrorMsg;
}

bool Sockets::connectClient()
{
  if(IsConnected)
    return true; // Already connected

  Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(!Socket)
    return false; // Error - could not initialize socket

  return (IsConnected = (connect(Socket, (sockaddr*)&Sa, sizeof(sockaddr)) != SOCKET_ERROR));
}

void Sockets::disconnectClient()
{
  shutdown(Socket, 0);
  closesocket(Socket);
  Socket = 0;
  IsConnected = false;
}

void Sockets::disconnect()
{
  disconnectClient();
}

int Sockets::reconnect()
{
  if(IsConnected)
    disconnectClient();
  return connectClient();
}

int Sockets::reconnect(const string& host, unsigned int port)
{
  setHostName(host);
  setPort(port);
  return reconnect();
}

int Sockets::reconnect(const string& host)
{
  setHostName(host);
  return reconnect();
}

int Sockets::reconnect(unsigned int port)
{
  setPort(port);
  return reconnect();
}
