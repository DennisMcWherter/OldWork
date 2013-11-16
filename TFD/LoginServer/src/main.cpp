//
// main.cpp
//
// $Id: main.cpp 97 2011-01-16 05:26:26Z infernale890 $
//
// The login server main function - tie everything together ;)
//
// Main Developers: RageD (Dennis J. McWherter, Jr.), infernale890
//

#include "Configuration.h"
#include "ServerDefinitions.h"
#include "Server.h"
#include "Poco/Util/PropertyFileConfiguration.h"
#include "Poco/AutoPtr.h"

void sleepMs(int ms)
{
	usleep(ms*1000);
}

int main()
{
	_config.setSource("../../ConfigurationLogin");
	TFD::Server* server = new TFD::Server("localhost",SERVER_PORT_SSL); // Arbitrary testing port
	std::cout<< "Login server running...\n";
	std::string in;
	std::cout<< "The Forgotten Darkness login server: Prototype 0.1a" << std::endl
			<< "\tThe server should be able to effectively receive data from client and will automatically "
			<< "echo the data back. Since this is a multi-threaded TCP server, there is a maximum "
			<< "of 4 simultaneous connections (4 threads). However, there is a maximum queue "
			<< "of 100. That means 104 users can attempt to login at the same time and will be "
			<< "properly handled. This should not be an issue as the client will will wait until "
			<< "signaled by the server to connect - processing a user login/registration should "
			<< "take < 1 second of connection time so there should be no issues." << std::endl << std::endl;
	while(1) // Just keep server alive and listen for clients...
	{
		getline(std::cin,in);
		if(in == "exit")
			break;
		sleepMs(100);
	}
	delete server;
	server = NULL;
	return 0;
}
