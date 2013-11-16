//
// LogonDB.h
//
// $Id: LogonDB.h 104 2011-01-18 12:40:37Z infernale890 $
//
// The LogonDB wrapper for TFD Servers
//
// Main Developers: RageD (Dennis J. McWherter, Jr.), infernale890
//

#ifndef __LOGONDB_H__
#define __LOGONDB_H__
#include "LocalDefinitions.h"
#include "Singleton.h"
#include "Configuration.h"
#include "BaseSQL.h"
#include "ServerDefinitions.h" // Always have this implicitly included for a default setup of DB

class LogonDB : public BaseSQL
{
public:
	LogonDB(std::string host,std::string user,std::string pass,std::string db);
	LogonDB();
	~LogonDB(){}

	// Functions important to the logondb
	int registerUser(std::string user,std::string pass,std::string email);
	int userLogin(std::string user,std::string pass);

private:
	// No private members currently
};

#define _loginDB Singleton<LogonDB>::Instance()
#endif
