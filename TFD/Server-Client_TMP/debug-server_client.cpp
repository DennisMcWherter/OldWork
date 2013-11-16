//
// Debug Client
//
// $Id$
//
// Debugging the server is a good thing :)
//
// Main Developers: RageD (Dennis J. McWherter, Jr.), infernale890
//

#include "ServerDefinitions.h"
#include <iostream>
#include <string>
#include "enetpp/ENet.h" // This includes all enetpp header files implicitly

using namespace std;
using namespace enetpp;

int main()
{
	// We're going to simply prepare a packet and see if we ever make it to the server xD
	int t = 0;
	ENet *net = new ENet;
	Event event;
	Host host = net->createClientHost(1,2,0,0);
	Address server = net->createAddress("localhost", SERVER_PORT_ENET);
	Peer peer = host.connect(server,2,(enet_uint32)1); // For game server, the data sent could be the user id? 
													  // This would obviously be after it passes login server checks
	cout<< "Awaiting connection...\n\n";
	
	// Handle <3
	switch(host.service(event,(enet_uint32)5000)) // 5 sec wait time
	{
	case ENET_EVENT_TYPE_CONNECT:
		cout<< "Connected!\n";
		t = 1;
		host.flush(); // Tell the host
		break;
	default:
		cout<< "Could not connect!\n";
		break;
	}
	if(t > 0) // Send our packet
	{
		cout<< "Sending packet..." << endl;
		string send = "What a beautiful day it is for our packetz!";
		Packet packet = net->createPacket((const void*)send.c_str(),send.size()+1,ENET_PACKET_FLAG_RELIABLE);
		peer.send(0,packet);
		cout<< "Packet sent!" << endl;
		host.flush();
	} else
		peer.reset();
	delete net;
	net = NULL;
	return 0;
}

