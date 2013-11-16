//
// EventHandler.h
//
// $Id: EventHandler.h 96 2011-01-16 02:07:17Z raged $
//
// The login server event handler
//
// Main Developers: RageD (Dennis J. McWherter, Jr.), infernale890
//

#ifndef __EVENTHANDLER_H__
#define __EVENTHANDLER_H__

#include "LoginDefinitions.h"
#include "PacketHandler.h"
#include "GeneralPacket.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/SecureStreamSocket.h"

namespace TFD
{
	class EventHandler : public Poco::Net::TCPServerConnection
	{
	public:
		EventHandler(const Poco::Net::SecureStreamSocket& s);
		~EventHandler() {}

		void run();
	};
}
#endif
