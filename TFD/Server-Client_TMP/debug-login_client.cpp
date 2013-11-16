// Debugging login client

#include "LocalDefinitions.h"
#include "ServerDefinitions.h"
#include "LoginDefinitions.h"
#include "GeneralPacket.h"
#include "Poco/SharedPtr.h"
#include "Poco/Net/KeyConsoleHandler.h"
#include "Poco/Net/Net.h"
#include "Poco/Net/NetSSL.h"
#include "Poco/Net/Context.h"
#include "Poco/Net/SecureStreamSocket.h"
#include "Poco/Net/KeyConsoleHandler.h"
#include "Poco/Net/InvalidCertificateHandler.h"
#include "Poco/Net/PrivateKeyPassphraseHandler.h"
#include "Poco/Net/SSLManager.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void sleepMs(int ms)
{
	usleep(ms*1000);
}

/**
 * We will move this to some class in client later
 */
class CertificateErrorHandler : public Poco::Net::InvalidCertificateHandler
{
public:
	CertificateErrorHandler(bool server)
		: InvalidCertificateHandler(server)
	{
	}

	~CertificateErrorHandler()
	{
	}

	void onInvalidCertificate(const void* pSender,Poco::Net::VerificationErrorArgs& errorCert)
	{
		//const Poco::Net::X509Certificate& aCert = errorCert.certificate(); // The error
		// handle errors - right now, simply ignoring them. May be able to do this anyway since it will be connecting to _OUR_ server
	}
};

uint8_t DoLogin(std::string user, std::string pass, Poco::Net::SecureStreamSocket& sock)
{
	uint8_t ret = LOGIN_UNK_ERR;
	char buffer[MAX_PACKET_SIZE];
	TFD::GeneralPacket<TFD::UserInfoPacket> packet;

	packet._Data.UsernameLength = (user.length() > MAX_USER_SIZE ? MAX_USER_SIZE : user.length());
	packet._Data.PasswordLength = (pass.length() > MAX_PWD_SIZE ? MAX_PWD_SIZE : pass.length());
	strncpy(packet._Data.Username, user.c_str(), packet._Data.UsernameLength);
	strncpy(packet._Data.Password, pass.c_str(), packet._Data.PasswordLength);
	packet.FlagHi(LOGIN_REQ);
	packet.Size(_FieldsSize + sizeof(TFD::UserInfoPacket));

	sock.sendBytes(&packet, packet.Size());
	if (sock.receiveBytes(buffer, MAX_PACKET_SIZE) > 0)
	{
		TFD::GeneralPacket<TFD::AckPacket> *p = (TFD::GeneralPacket<TFD::AckPacket>*)buffer;
		ret = p->FlagLo();
	}
	return ret;
}

float GetVersion(Poco::Net::SecureStreamSocket& sock)
{
	float ret = 0.0;
	char buffer[MAX_PACKET_SIZE];
	TFD::GeneralPacket<TFD::DataPacket> packet;
	
	packet.Size(_FieldsSize);
	packet.FlagHi(VERSION_REQ);
	
	sock.sendBytes(&packet, packet.Size());
	if (sock.receiveBytes(buffer, MAX_PACKET_SIZE) > 0)
	{
		TFD::GeneralPacket<TFD::DataPacket> *p = (TFD::GeneralPacket<TFD::DataPacket>*)buffer;
		memcpy(&ret, p->_Data.Data, sizeof(float));
	}
	return ret;
}


int main()
{
	printf("Flag size\t\t\t = %u\n", sizeof(TFD::PacketFlag));
	printf("ListServerPacket size\t\t = %u -\t GeneralPacket = %u\n", sizeof(TFD::ListServerPacket), sizeof(TFD::GeneralPacket<TFD::ListServerPacket>));
	printf("UserInfoPacket size\t\t = %u -\t\t GeneralPacket = %u\n", sizeof(TFD::UserInfoPacket), sizeof(TFD::GeneralPacket<TFD::UserInfoPacket>));
	printf("Data Packet size\t\t = %u -\t GeneralPacket = %u\n", sizeof(TFD::DataPacket), sizeof(TFD::GeneralPacket<TFD::DataPacket>));
	string dir(PATH_TO_LOGIN);
	string data;
	cout<< "Awaiting Connection Slot..." << endl << endl;

	// Initialize connection
	Poco::SharedPtr<Poco::Net::PrivateKeyPassphraseHandler> pHandler = new Poco::Net::KeyConsoleHandler(false);
	Poco::SharedPtr<Poco::Net::InvalidCertificateHandler> pInvalid = new CertificateErrorHandler(false);
	Poco::Net::Context::Ptr pClient = new Poco::Net::Context(Poco::Net::Context::CLIENT_USE,
								 "","", "client.ca",
								 Poco::Net::Context::VERIFY_RELAXED, 0, false,
								 "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
	Poco::Net::SSLManager::instance().initializeClient(pHandler,pInvalid,pClient);
	Poco::Net::SocketAddress sa("localhost",SERVER_PORT_SSL);
	Poco::Net::SecureStreamSocket ss1(sa,pClient);
	std::cout<< "Connected!\n\nThe Forgotten Darkness login server: Prototype 0.1a (debug client)" << std::endl
		<< "----------------------------------------------------------------------" << std::endl
		<< "(1). Type login to attempt a login with your username and password" << std::endl
		<< "(2). Type reg to attempt a registration " << std::endl
		<< "(3). Type srvlist to get the list of the game servers" << std::endl
		<< "(4). Type version to get the game version" << std::endl
		<< "(5). Type exit to exit" << std::endl << std::endl;
		
	while(1)
	{
		getline(cin,data);
		if (data == "login")
		{
			std::string user, pass;
			std::cout<< "Please type your account information in the following format:\nuser pass\n\n";
			std::cin >> user >> pass; //it's just an example, i don 't like this very much
			std::string resp;
			switch(DoLogin(user, pass, ss1))
			{
			case LOGIN_INV_ACC:
			case LOGIN_INV_USR:
			case LOGIN_INV_PSW:
				resp = "--- Invalid information baby ---"; break;
			case LOGIN_ACC_BND:
			case LOGIN_ACC_BLK:
			case LOGIN_ACC_FRZ:
			case LOGIN_ACC_NAC:
				resp = "--- You account has something bad! ---"; break;
			case LOGIN_ACC_ACT:
				resp = "--- Login successful! ---"; break;
			case LOGIN_UNK_ERR:
			default:
				resp = "--- Unkown error ---"; break;
			}
			std::cout << resp << std::endl;
		}
		else if (data == "reg")
		{
			std::cout << "--- Not implemented yet! ---" << std::endl;
		}
		else if (data == "srvlist")
		{
			std::cout << "--- Not implemented yet! ---" << std::endl;
		}
		else if (data == "version")
		{
			float version = GetVersion(ss1);
			std::cout << "--- Game version: " << version << " ---" << std::endl;
		}
		else if (data == "exit")
		{
			break;
		}

		/*// Send data to server
		TFD::GeneralPacket<> lp;

		// Removed the "MakePacket()" function and using the class members to set data
		lp.Data(data.data(),data.size(),0);
		if(data == "reg")
		{
			std::cout<< "Please type your registration in the following format:\nuser:pass:e-mail\n\n";
			getline(cin,data);
			lp.Data(data.data(),data.size(),0);
			lp.FlagHi(REG_REQ); // Setting .Flag() loses two bytes on the response - using FlagHi()/FlagLo()
			//lp.Flag(REG_REQ);
		} else
			lp.FlagHi(LOGIN_REQ);
			//lp.Flag(LOGIN_REQ);

		// Packet is made.. Send it and block for server response...
		int s = ss1.sendBytes(&lp,lp._Size);
		printf("Sent: %d bytes\n",s);
        int n = ss1.receiveBytes(buffer,MAX_PACKET_SIZE);
		printf("Received: %d bytes\n", n);

		// Now interpret the packe:t
		TFD::GeneralPacket<TFD::DataPacket> *p = (TFD::GeneralPacket<TFD::DataPacket>*)buffer;
		printf("Data: %s\n",p->_Data.Data);
		if(p->FlagLo() == LOGIN_RESP_OK)
			printf("Logged in!\n");
		else if(p->FlagLo() == LOGIN_RESP_NOK)
			printf("Login failed...\n");*/
		sleepMs(100);
	}
	return 0;
}
