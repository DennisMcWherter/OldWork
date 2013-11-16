//
// ServerBase.h
//
// $Id: Server.h 96 2011-01-16 02:07:17Z raged $
//
// The server base
//
// Main Developers: RageD (Dennis J. McWherter, Jr.), infernale890
//

#ifndef __SERVER_H__
#define __SERVER_H__

// Using POCO for the login server - TCP + SSL = <3
#include <iostream>
#include <string>
#include <stdint.h>
#include "LocalDefinitions.h"
#include "ServerDefinitions.h"
#include "EventHandler.h"
#include "PrivateKeyHandler.h"
#include "Poco/AutoPtr.h"
#include "Poco/SharedPtr.h"
#include "Poco/Thread.h"
#include "Poco/ThreadPool.h"
#include "Poco/Net/Net.h"
#include "Poco/Net/Context.h"
#include "Poco/Net/TCPServer.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/TCPServerConnectionFactory.h"
#include "Poco/Net/TCPServerParams.h"
#include "Poco/Net/ConsoleCertificateHandler.h"
#include "Poco/Net/PrivateKeyPassphraseHandler.h"
#include "Poco/Net/SecureStreamSocket.h"
#include "Poco/Net/SecureServerSocket.h"
#include "Poco/Net/Session.h"
#include "Poco/Net/SSLException.h"
#include "Poco/Net/SSLManager.h"
#include "Poco/Util/Application.h"
#include "Poco/Util/AbstractConfiguration.h"

namespace TFD
{
	class Server
	{
	public:
		Server(std::string host, uint16_t port);
		~Server();
	private:
		std::string _spath;
		Poco::Net::SocketAddress _addr;
		Poco::SharedPtr<Poco::Net::PrivateKeyPassphraseHandler> _keyHandler;
		Poco::SharedPtr<Poco::Net::InvalidCertificateHandler> _invalidCertHandler;
		Poco::Net::Context::Ptr _pServer;
		Poco::AutoPtr<Poco::Net::TCPServerParams> _pParams;
		Poco::Net::SecureServerSocket _serverSock;
		Poco::Net::TCPServer _server;
	};
}
#endif
