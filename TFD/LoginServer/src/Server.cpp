//
// ServerBase.cpp
//
// $Id: Server.cpp 96 2011-01-16 02:07:17Z raged $
//
// The login server base
//
// Main Developers: RageD (Dennis J. McWherter, Jr.), infernale890
//

#include "Server.h"

namespace TFD
{
	Server::Server(std::string host, uint16_t  port) : _spath(PATH_TO_LOGIN),
							   _addr(host,port),
							   _keyHandler(new TFD::PrivateKeyHandler(true,"ehNz3v1LJC")),
							   _invalidCertHandler(new Poco::Net::ConsoleCertificateHandler(true)),
							   _pServer(new Poco::Net::Context(Poco::Net::Context::SERVER_USE,
											   _spath+"/bin/ssl/server.key",
											   _spath+"/bin/ssl/server.crt",
											   "",
											   Poco::Net::Context::VERIFY_RELAXED, 9,
											   false,
											   "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH")), // All ciphers excepted the ones listed
							   _pParams(new Poco::Net::TCPServerParams),
							   _serverSock(_addr,64,_pServer),
							   _server(new Poco::Net::TCPServerConnectionFactoryImpl<EventHandler>(),
								   _serverSock,_pParams)
	{
		// Setup Params before we start!
		Poco::Net::SSLManager::instance().initializeServer(_keyHandler,_invalidCertHandler,_pServer);
		_pParams->setMaxQueued(100);
		_pParams->setMaxThreads(4);
		_pParams->setThreadIdleTime(100);
		try
		{
			_server.start();
		} catch(Poco::Exception& e) {
			std::cerr << "Server Exception Caught: " << e.displayText() << std::endl;
		}
	}

	Server::~Server()
	{
		_server.stop();
	}
}
