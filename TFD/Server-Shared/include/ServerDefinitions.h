// General defines/enums

#ifndef __SERVER_DEFS_H__
#define __SERVER_DEFS_H__
#include "Configuration.h"
/**
 * This is just an easy way to store this data
 */


#ifdef LOGIN_SERVER
	#define LOGIN_HOST _config.getValue("LoginDB.host") //maybe we should define  a std::string
	#define LOGIN_PORT _config.getValue("LoginDB.port")
	#define LOGIN_USER _config.getValue("LoginDB.username")
	#define LOGIN_PASS _config.getValue("LoginDB.password")
	#define LOGIN_DB   _config.getValue("LoginDB.database")
#elif GAME_SERVER
	#define GAME_HOST "localhost"
	#define GAME_USER "root"
	#define GAME_PASS "pass"
	#define GAME_DB "database"
#endif

enum _ServerPortUsed
{
	SERVER_PORT_SSL   = 7590,
	SERVER_PORT_ENET  = 7600
};

#endif
