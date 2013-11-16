//
// Server.h
//
// $Id: Server.h 96 2011-01-16 02:07:17Z raged $
//
// Rapresents a server object
//
// Main Developers: RageD (Dennis J. McWherter, Jr.), infernale890
//

#ifndef __SERVER_H__ // Include guards
#define __SERVER_H__

#include "enetpp/ENet.h"
#include "ConnectionHandler.h"
#include <stdint.h>
#include <string>

namespace TFD
{
#define MAX_CONNECTIONS     0x0FFF//Actually, this is the limit for enet(checked)
#define DEF_CHANNELS_NUMBER 0x02 //Maximum number of channels if no number is defined in the constructor
        class Server
	{
		enetpp::ENet      *Net;
		enetpp::Address   addr;
		enetpp::Host      *this_server;
		ConnectionHandler *CHandler;
		void Init(uint32_t MaxClientConnections, uint8_t Channels); //Initialize this_server and CHandler
		void Dealloc(); //Delete this_server and CHandler
	public:
		//Constructors
	        Server(std::string Host, uint16_t Port);
		Server(std::string Host, uint16_t Port, uint32_t MaxClientConnections);
		Server(std::string _Host, uint16_t Port, uint32_t MaxClientConnections, uint8_t Channels);
	        ~Server();

		ConnectionHandler* GetConnectionHandler() const;
	};
}
#endif
