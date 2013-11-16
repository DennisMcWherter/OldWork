//
// EventHandler.cpp
//
// $Id: PacketHandler.cpp 98 2011-01-16 13:03:16Z infernale890 $
//
// The login server event handler
//
// Main Developers: RageD (Dennis J. McWherter, Jr.), infernale890
//

#include "PacketHandler.h"

namespace TFD
{
	PacketHandler::PacketHandler(GeneralPacket<DataPacket> *_Packet, bool compute) : _RPacket(NULL),
											 _RUserPacket(NULL), 
											 _SPacket(NULL)
	{	//check that the packet to handle is ok
		if (_Packet)
		{
			_SPacket = _Packet;
			_RPacket = new GeneralPacket<DataPacket>; //alloc the resp packet
			if (compute)
				this->Compute();				
		}
	}
	
	PacketHandler::PacketHandler(GeneralPacket<DataPacket> *_Packet, GeneralPacket<DataPacket> *_RUserPacket, bool compute) : _RPacket(NULL),  
																  _RUserPacket(NULL),
																  _SPacket(NULL)
	{
		if (_Packet && _RUserPacket)
		{
			_SPacket = _Packet;
			this->_RPacket = new GeneralPacket<DataPacket>;
			this->_RUserPacket = _RUserPacket;
			if (compute)
				this->Compute();				
		}
	}
	
	PacketHandler::~PacketHandler()
	{
		if (_RPacket)
		{
			try
			{
				delete _RPacket;
			} catch (...) { }
		}
		_SPacket = NULL;
	}

	GeneralPacket<DataPacket> *PacketHandler::Compute()
	{
		if (_SPacket && _RPacket)
		{
			switch(_SPacket->FlagHi())
			{
			case LOGIN_REQ:
				this->LoginRequest(); break;
			case VERSION_REQ:
				this->VersionRequest(); break;
			case REG_REQ: // Going to put reg system on site
			case SRV_LIST_REQ:
			default:
				break;
			}
			if (_RUserPacket)
				memcpy(_RUserPacket, _RPacket, (_RPacket->_Size > MAX_PACKET_SIZE ? MAX_PACKET_SIZE : _RPacket->_Size));
		}
		return _RPacket;
	}
	
	GeneralPacket<DataPacket> *PacketHandler::GetResponse() const
	{
		return _RPacket;
	}

	void PacketHandler::LoginRequest()
	{
		if (_RPacket && _SPacket)
		{
			GeneralPacket<UserInfoPacket> *p = (GeneralPacket<UserInfoPacket> *) _SPacket;
			p->_Data.Username[p->_Data.UsernameLength] = '\0';
			p->_Data.Password[p->_Data.PasswordLength] = '\0';
			if (!_loginDB.userLogin(p->_Data.Username, p->_Data.Password))
			{
				_RPacket->FlagHi(LOGIN_RESP_OK);
				_RPacket->FlagLo(LOGIN_ACC_ACT);
			}
			else
			{
				_RPacket->FlagHi(LOGIN_RESP_NOK);
				_RPacket->FlagLo(LOGIN_INV_ACC);
			}
			_RPacket->Size(_FieldsSize);
		}
	}

	void PacketHandler::VersionRequest()
	{
		if (_RPacket)
		{
			_RPacket->FlagHi(LOGIN_RESP_OK);
			_RPacket->FlagLo(0);
			_RPacket->Size(_FieldsSize + sizeof(float));
			memcpy(_RPacket->_Data.Data, &GAME_VERSION, sizeof(float));
		}
	}
}
