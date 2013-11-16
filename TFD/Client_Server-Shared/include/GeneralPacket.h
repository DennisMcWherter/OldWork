// Packets structure --> Actually GeneralPacket is not thread safe

#ifndef __GENERAL_PACKET_H__
#define __GENERAL_PACKET_H__

#include "GameDefinitions.h"


namespace TFD
{
	#define MAX_PACKET_SIZE 0x2000 //8k :(
	#define _FieldsSize (sizeof(uint16_t) + sizeof(uint16_t)) //+2 unecessary now //Flags + Size - +2 offset since we're losing 2-bytes off the buffer
	#define _MaxDataSize (MAX_PACKET_SIZE - _FieldsSize)
	#define _SERVER_SHIFT 0x008 // Shift 8
	#define _CLIENT_SHIFT 0x00C // Shift 12
	
	//Packet size field
	class PacketSize
	{
	public:
		PacketSize() : _Size(0) {}
		PacketSize(uint16_t Value) : _Size(Value) {}

		uint16_t Size()			 const { return this->_Size;  }
		void     Size(uint16_t value)	       { this->_Size = value; }
		
		uint16_t _Size;
	};
	
	//Packet flag field
	class PacketFlag
	{
	public:
		PacketFlag() : _Flag(0) {}
		PacketFlag(uint16_t Flag) : _Flag(Flag) {}
		PacketFlag(uint8_t FlagHi, uint8_t FlagLo) { Flag(FlagHi, FlagLo); }

		
		void     Flag(uint16_t Flag)				{ this->_Flag = Flag; }
		void     Flag(uint8_t _FlagHi, uint8_t _FlagLo) 	{ FlagHi(_FlagHi), FlagLo(_FlagLo); }
		uint16_t Flag() 			          const { return this->_Flag; }

		uint8_t  FlagHi()				  const { return this->Fn.FlagHi; }
		void     FlagHi(uint8_t FlagHi)	        		{ this->Fn.FlagHi = FlagHi; }

		uint8_t  FlagLo()  	          	  	  const { return this->Fn.FlagLo; }
		void     FlagLo(uint8_t FlagLo)				{ this->Fn.FlagLo = FlagLo; }


		union
		{
			uint16_t _Flag;
			struct {
				uint8_t FlagHi;
				uint8_t FlagLo;
			} Fn;
			uint8_t Fc[2];
		};
	};
	

	
	class AckPacket
	{
	public:
	};

	/* HAVEN'T TESTED MEMORY ALIGNMENT YET OF THIS ONE */
	class ListServerPacket
	{
	public:
	#define MAX_SERVERS 128
		struct ServerInfo
		{
			uint32_t Address;
			uint16_t Population;
			uint16_t Port;
			uint8_t  Nationality;
			int8_t   ServerName[SERVER_MAX_SIZE];
		} ServerInfo[MAX_SERVERS]; //ipotetically it can hold 199 servers info with a maximum packet size of 8k
	};

	//UserInfoPacket, used to exchange Account Information.
	class UserInfoPacket
	{
	public:
	#define MAX_USER_SIZE 16
	#define MAX_PWD_SIZE MAX_USER_SIZE
		uint8_t UsernameLength;
		uint8_t PasswordLength;
		char    Username[MAX_USER_SIZE];
		char    Password[MAX_PWD_SIZE];
	};

	//Data Packet, this is the basic data packet. Other type of packet mustn't exceed the size of DataPacket

	class DataPacket
	{
	public:
		uint8_t Data[_MaxDataSize];	
	};

	/* General Packet structure
	   Note by infernale890: pay attention to the memory alignment, if necessary uncomment the pragma packs
	*/

    //pragma pack(push)
    //pragma pack(1)
    template <typename T = DataPacket>
    class GeneralPacket : public PacketFlag, public PacketSize
    {
	public:
		GeneralPacket() : PacketFlag(0), PacketSize(0) { }
		
		void Data(const void *Data, uint16_t Size)
		{
			Data(Data, Size, this->_Flag);
		}

		void Data(const void *Data, uint16_t Size, uint16_t Flags)
		{
			uint16_t _len = 0;
			if (Data && Size > 0)
			{
				this->Flag(Flags);
				_len = (Size > sizeof(T) ? sizeof(T) : Size);
				memcpy(&_Data, Data, _len);
			}
			this->Size(_FieldsSize + _len);
		}


		T        _Data;
  };
  //pragma pack(pop)
}
#endif
