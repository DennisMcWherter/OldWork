/*======================================================================
 XeroBot.cpp
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

#include <iostream>
#include <process.h>

#include "XeroBot.h"

using namespace std;

XeroBot::XeroBot(const string& host, unsigned int port)
  : Sock(host, port), ShutDown(false), Thread(0)
{
  Thread = (void*)_beginthread(XeroBot::readThread, 0, this);
}

XeroBot::~XeroBot()
{
  TerminateThread(Thread, 0);
  CloseHandle(Thread);
}

void XeroBot::write(const string& data)
{
  Sock.write(data);
}

void XeroBot::shutdown()
{
  ShutDown = true;
  Sleep(500); // Give 500ms to allow readThread to terminate
}

bool XeroBot::getShutdown() const
{
  return ShutDown;
}

void XeroBot::readThread(void * data)
{
  XeroBot * bot = static_cast<XeroBot*>(data);
  std::string read;
  while(!bot->ShutDown) {
    bot->Sock.read(read);
    if(read.length() > 0)
      cout<< read << endl;
    Sleep(100);
  }
}
