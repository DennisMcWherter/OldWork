//
// Manage all the incoming connections
//
// Main Developers: RageD (Dennis J. McWherter, Jr.), infernale890
//

#include "Connection.h"

namespace TFD
{
  Connection::Connection(ENetPeer *peer): Peer(peer) 
  {
  }

  Connection::~Connection()
  {
  }
}

