//
// Connection.h
//
// $Id: Connection.h 96 2011-01-16 02:07:17Z raged $
//
// Rapresents a single connection
//
// Main Developers: RageD (Dennis J. McWherter, Jr.), infernale890
//

#ifndef __CONNECTION_H__ // Include guards
#define __CONNECTION_H__

#include "enetpp/Peer.h"

namespace TFD
{
        class Connection : public enetpp::Peer
	{
	public:
	        Connection(ENetPeer *peer);
	        ~Connection();
	};
}
#endif
