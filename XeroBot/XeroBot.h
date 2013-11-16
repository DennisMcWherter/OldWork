/*======================================================================
 XeroBot.h
 XeroBot core

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

#ifndef XeroBot_XeroBot_H_
#define XeroBot_XeroBot_H_

#include "Sockets.h"

class XeroBot
{
public:
  XeroBot(const std::string& host="localhost", unsigned int port=6667);
  virtual ~XeroBot();

  void write(const std::string& data);
  void shutdown();
  bool getShutdown() const;

private:
  static void readThread(void * data);

  Sockets Sock;
  bool ShutDown;
  void * Thread;
};

#endif // XeroBot_XeroBot_H_
