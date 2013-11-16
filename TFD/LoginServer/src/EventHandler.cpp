//
// EventHandler.cpp
//
// $Id: EventHandler.cpp 98 2011-01-16 13:03:16Z infernale890 $
//
// The login server event handler
//
// Main Developers: RageD (Dennis J. McWherter, Jr.), infernale890
//

#include "EventHandler.h"
#include "BaseSQL.h" // Eventually going to need to handle the buffer and query the db
#include <iostream>

namespace TFD
{
	EventHandler::EventHandler(const Poco::Net::SecureStreamSocket& s)
		: TCPServerConnection(s)
	{
	}

	void EventHandler::run()
	{
	  Poco::Net::SecureStreamSocket& _sock = (Poco::Net::SecureStreamSocket&)socket();
	  printf("New Connection\n");
	  if(!_sock.secure())
			printf("Socket unsecure!\n");
		try
		{
		    	char buffer[MAX_PACKET_SIZE];
			uint32_t n = 0;
            		while ((n = _sock.receiveBytes(buffer, MAX_PACKET_SIZE)) > 0)
			{
				GeneralPacket<DataPacket> *p = (GeneralPacket<DataPacket> *) buffer;
				GeneralPacket<DataPacket> r;
				printf("Size: %u\n", p->Size());
				printf("Data: %s\n", p->_Data.Data);
				PacketHandler cp(p, &r, true);
				//_sock.sendBytes(p, p->Size); // Simple echo
				_sock.sendBytes(&r,r.Size()); // Send response
			    	memset(buffer, 0, MAX_PACKET_SIZE);
		    	}
		}
		catch (Poco::Exception& e)
		{
			std::cerr << "EventHandler Exception Caught: " << e.displayText() << std::endl;
		}
	}
}
