//
// PrivateKeyHandler.cpp
//
// $Id: PrivateKeyHandler.cpp 96 2011-01-16 02:07:17Z raged $
//
// The private key handler to use real SSL certificates
//
// Main Developers: RageD (Dennis J. McWherter, Jr.), infernale890
//

#include "PrivateKeyHandler.h"

namespace TFD
{
	PrivateKeyHandler::PrivateKeyHandler(bool server,std::string key)
		: Poco::Net::PrivateKeyPassphraseHandler(server), _key(key)
	{
	}

	PrivateKeyHandler::~PrivateKeyHandler()
	{
	}

	void PrivateKeyHandler::onPrivateKeyRequested(const void* pSender,std::string& privateKey)
	{
		// Dont ask, just do - compile our key right in
		privateKey = _key;
	}
}
