/*======================================================================
 Sockets.h
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

#ifndef XeroBot_Sockets_H_
#define XeroBot_Sockets_H_

#include <WinSock2.h>
#include <string>

class Sockets
{
public:
  Sockets(const std::string& host, unsigned int port);
  virtual ~Sockets();

  void read(std::string& data) const;
  void write(const std::string& data);
  void disconnect();

  int reconnect();
  int reconnect(const std::string& host, unsigned int port);
  int reconnect(const std::string& host);
  int reconnect(unsigned int port);

  void setHostName(const std::string& host);
  void setPort(unsigned int port);

  const std::string& getErrorMsg() const;

protected:
  bool connectClient();
  void disconnectClient();

private:
  bool IsConnected;
  unsigned int Socket;
  std::string ErrorMsg;

  std::string Host;
  unsigned int Port;
  WSAData WsaData;

  struct sockaddr_in Sa;
  hostent * Hent;
};

#endif // XeroBot_Sockets_H_
