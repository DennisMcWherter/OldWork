//
// Server.cpp
//
// $Id: Server.cpp 96 2011-01-16 02:07:17Z raged $
//
// Main Server
//
// Main Developers: RageD (Dennis J. McWherter, Jr.), infernale890
//
#include "Server.h"

namespace TFD
{
  Server::Server(std::string Host, uint16_t Port) : Net(new enetpp::ENet), addr(Host.c_str(), Port), this_server(NULL)
  {
    Init(MAX_CONNECTIONS, DEF_CHANNELS_NUMBER);
  }

  Server::Server(std::string Host, uint16_t Port, uint32_t MaxConnections) : Net(new enetpp::ENet), addr(Host.c_str(), Port),
									     this_server(NULL)
  {
    Init(MaxConnections, DEF_CHANNELS_NUMBER);
  }

  Server::Server(std::string _Host, uint16_t Port, uint32_t MaxConnections, uint8_t Channels) : Net(new enetpp::ENet),
												addr(_Host.c_str(), Port),
												this_server(NULL)
  {
    Init(MaxConnections, Channels);
  }
  Server::~Server()
  {
    Dealloc();
    delete Net;
  }

  //dealloc this_server and CHandler
  void Server::Dealloc()
  {
    if (this_server)
    {
      this_server->destroy();
    }
    try
    {
      delete this_server;
    }catch(...) { }
    try
    {
      delete CHandler;
    } catch(...) { }
    
    this_server = NULL;
    CHandler    = NULL;
  }
  //Initialize this_server and Chandler
  void Server::Init(uint32_t MaxConnections, uint8_t Channels)
  {
    this_server = new enetpp::Host(Net, addr, MaxConnections, Channels, 0, 0);
    CHandler    = new ConnectionHandler(*this_server);
  }
  
  //Get the ConnectionHandler
  ConnectionHandler* Server::GetConnectionHandler() const
  {
    return CHandler;
  }
}
