//
// PacketHandler.h
//
// $Id: PacketHandler.h 98 2011-01-16 13:03:16Z infernale890 $
//
// Handles all the packets
// 
// Main Developers: RageD (Dennis J. McWherter, Jr.), infernale890
//

#ifndef __PACKETHANDLER_H__
#define __PACKETHANDLER_H__

#include "LoginDefinitions.h"
#include "GeneralPacket.h"
#include "LogonDB.h"
#include <cstring>
#include <string>

namespace TFD
{
	class PacketHandler
	{
	private:
		GeneralPacket<DataPacket> *_RPacket, *_RUserPacket; //response
		GeneralPacket<DataPacket> *_SPacket; //Packet to handle
	public:
		PacketHandler(GeneralPacket<DataPacket> *_Packet, bool Compute = true);
		PacketHandler(GeneralPacket<DataPacket> *_Packet, GeneralPacket<DataPacket> *_RUserPacket, bool Compute = true);
		~PacketHandler();
		GeneralPacket<DataPacket> *Compute();
		GeneralPacket<DataPacket> *GetResponse() const;

		void LoginRequest();
		void VersionRequest();
	};
}
#endif
