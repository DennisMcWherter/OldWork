//
// PrivateKeyHandler.h
//
// $Id: PrivateKeyHandler.h 96 2011-01-16 02:07:17Z raged $
//
// The private key handler to use secure SSL certificates
//
// Main Developers: RageD (Dennis J. McWherter, Jr.), infernale890
//

#ifndef __PRIVATE_KEY_HANDLER_H__
#define __PRIVATE_KEY_HANDLER_H__

#include "Poco/Net/NetSSL.h"
#include "Poco/Net/PrivateKeyPassphraseHandler.h"
#include <string>

namespace TFD
{
	class PrivateKeyHandler : public Poco::Net::PrivateKeyPassphraseHandler
	{
	public:
		PrivateKeyHandler(bool server,std::string key);
		~PrivateKeyHandler();

		void onPrivateKeyRequested(const void* pSender, std::string& privateKey);
	private:
		std::string _key;
	};
}
#endif
