//
// ConnectionHandler.h
//
// $Id: ConnectionHandler.h 96 2011-01-16 02:07:17Z raged $
//
// Manages all the incoming connections~
//
// Main Developers: RageD (Dennis J. McWherter, Jr.), infernale890
//

#ifndef __CONNECTIONHANDLER_H__ // Include guards
#define __CONNECTIONHANDLER_H__

#include <arpa/inet.h>
#include "Connection.h"
#include "enetpp/ENet.h" // This implicitly includes everything else in the proper order
						// which allows us to avoid any "incomplete type" errors

namespace TFD
{
#define DEF_TIMEOUT 1000 //milliseconds

	class ConnectionHandler
	{
		enetpp::Host &Server;
	public:
		ConnectionHandler(enetpp::Host &Server);
		~ConnectionHandler();
		void EventsLoop(); //Receive incoming connection, data, etc...
	};
}
#endif
