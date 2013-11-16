#ifndef __LOGIN_DEFS_H__
#define __LOGIN_DEFS_H__

#include <stdint.h>
#include "GameDefinitions.h"

/* FLAG HI */
enum PacketRequestFlags
{
	//0x0000 to0x000F are used for Request packets
	LOGIN_REQ	= 0x0000, //Used by the client when it sends username and password to login into the game
	VERSION_REQ	= 0x0001, //Used by both client and server, used to get the game version 
	SRV_LIST_REQ	= 0x0002, //Used by the client, requests the login server to sends a list of all the available game servers
	REG_REQ		= 0x0003 // Login server should be handling registrations as well
};

enum PacketResponseFlags
{
	//0x0010 to 0x001F are use for response packets
	LOGIN_RESP_OK	= 0x0010, //Used when the task (login into the game, getting the server lists..) was succesful
	LOGIN_RESP_NOK	= 0x0011, //used when the task wasn't succesful
};


/* FLAG LO */

//These codes are used as "More information flag"
enum PacketInfoFlags
{
	// 0x0000 to 0x000F are used for invalid info sent by the client
	LOGIN_INV_ACC = 0x0000, //Account invalid
	LOGIN_INV_USR = 0x0001, //Incorrect username
	LOGIN_INV_PSW = 0x0002, //Incorrect password

	//0x0010 to 0x001F are used for information about the account
	LOGIN_ACC_BND = 0x0010, //Account banned
	LOGIN_ACC_BLK = 0x0011, //Account blocked by somebody
	LOGIN_ACC_FRZ = 0x0012, //Account freezed
	LOGIN_ACC_NAC = 0x0013, //Account not active
	LOGIN_ACC_ACT = 0x0014, //account active
	
	LOGIN_UNK_ERR = 0x00FF //unkown error, used when the server can not access user information in the database, etc..
};



/*********************************************************************************************/



#endif
