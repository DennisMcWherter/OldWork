//
// Server.cpp
//
// $Id: main.cpp 96 2011-01-16 02:07:17Z raged $
//
// Main server file which unifies all the structures. This is the main
// program.
//
// Main Developers: RageD (Dennis J. McWherter, Jr.), infernale890
//
#include "ServerDefinitions.h"
#include "ConnectionHandler.h"
#include "enetpp/ENet.h"
#include "Server.h"
#include <iostream>
#include <string>
//using namespace enetpp;
/**
 *  NOTE: We will probably be sending this into a much bigger class very soon
 *  	as this would all be much better managed in a set of classes. Right now
 *  	the intent of this program is to get some sort of prototype running to see
 *  	the steps it will take in order to bind, listen, recv packets, and interpret packets
 *  	effectively for the end result of the server.
 */

void sleepMs(int ms) // Sleep for x milliseconds
{
	usleep(ms*1000); // usleep is in microseconds so... microseconds*1000 = milliseconds
}

int main()
{
    TFD::Server server("127.0.0.1", SERVER_PORT_ENET);
	TFD::ConnectionHandler *ch = server.GetConnectionHandler();
	std::cout<< "Prototype server running...\nPlease use \"CTRL+C\" key command to exit\n\n" << std::endl;
	int i = 0;
	while(1) // We'll obviously have to thread this later
	{
		if(i > 40) // A little over 40 seconds - just let us know the server isn't hanging
		{
			std::cout<< "Server is still alive...\n\n";
			i = 0; // Reset
		}
		// Run our loop
		if (ch)
		  ch->EventsLoop();
		sleepMs(100); // CPU saver
		i++;
	}
	return 0;
}

