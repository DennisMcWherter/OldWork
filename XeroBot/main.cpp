/*======================================================================
 main.cpp
 XeroBot IRC Bot main entry point

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
#include "XeroBot.h"

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
  XeroBot bot("irc.freenode.net", 6667);
  // Load modules (should eventually be modular)
  std::string input;
  while(!bot.getShutdown()) {
    cin >> input;

    if(input == "exit")
      bot.shutdown();
    else
      bot.write(input);

    Sleep(200);
  }
  return 0;
}
