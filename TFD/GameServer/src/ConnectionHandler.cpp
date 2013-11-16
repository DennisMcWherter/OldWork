//
// ConnectionHandler
//
// $Id: ConnectionHandler.cpp 96 2011-01-16 02:07:17Z raged $
//
// Manage all the incoming connections
//
// Main Developers: RageD (Dennis J. McWherter, Jr.), infernale890
//

#include "ConnectionHandler.h"
#include <iostream>

namespace TFD
{
  ConnectionHandler::ConnectionHandler(enetpp::Host &_server) : Server(_server) 
  {
  }

  ConnectionHandler::~ConnectionHandler()
  {
  }

  // NOTE: Need to debug this later - perhaps the server reference isn't working properly?
  void ConnectionHandler::EventsLoop()
  {
    enetpp::Event _event;
    switch(Server.service(_event,(enet_uint32)DEF_TIMEOUT)) // DEF_TIMEOUT should probably be between 1 and 5 secs
    {
      case ENET_EVENT_TYPE_CONNECT:
    	  // Quick IP conversion
    	  struct in_addr addr;
    	  addr.s_addr = _event.peer().address().host();
    	std::cout<< "Client ID #"<< _event.data() <<" connected from address: "<< inet_ntoa(addr) <<"\n\n";
	break;
      case ENET_EVENT_TYPE_DISCONNECT:
	break;
      case ENET_EVENT_TYPE_RECEIVE:
     	  std::cout<< "Receiving packet...\nPacket Data: "<< _event.packet().data() << "\n\n";
	break;
      case ENET_EVENT_TYPE_NONE:
      default:
	break;
    }
  }
}

