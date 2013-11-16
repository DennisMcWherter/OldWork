//
// LogonDB.cpp
//
// $Id: LogonDB.cpp 104 2011-01-18 12:40:37Z infernale890 $
//
// The LogonDB wrapper for TFD Servers 
// note: From previous tests looks like that you can't intialize more than 152 connections
//
// Main Developers: RageD (Dennis J. McWherter, Jr.), infernale890
//

#include "LogonDB.h"
#include <iostream>
ISTANTIATE_SINGLETON(LogonDB)

LogonDB::LogonDB(std::string host,std::string user,std::string pass,std::string db)
	: BaseSQL(host,user,pass,db)
{
}

LogonDB::LogonDB()
	: BaseSQL(LOGIN_HOST, LOGIN_USER,LOGIN_PASS,LOGIN_DB)
{
}

/**
 * Haven't made the DB structure for the login table yet, so this is just temporary
 * as an example
 *
 * grep: Security checks need to be added into this - this is just an example. Will need
 *       to escape strings, etc. to avoid any sort of user hacking attempts.
 *		Additionally, we're currently only using a MD5 encryption, but
 *		can/will generate salts, etc. later on.
 */
int LogonDB::registerUser(std::string user,std::string pass,std::string email)
{
	if(user.empty() || pass.empty() || email.empty())
		return 1; // ERR CODE 1: Did not fill out user, pass, or e-mail

	// Vector to check data
	std::vector<int> check;

	getData<int>(check,"select id from tfd_login where user='"+user+"'");
	if(check.size() > 0)
		return 2; // ERR CODE 2: Username in use

	getData<int>(check,"select id from tfd_login where email='"+email+"'");
	if(check.size() > 0)
		return 3; // ERR CODE 3: E-mail in use

	runQuery("insert into tfd_login set user='"+user+"', pass=MD5('"+pass+"'), email='"+email+"'");
	return 0; // Success
}

// Login to user
int LogonDB::userLogin(std::string user,std::string pass)
{
	if(user.empty() || pass.empty())
		return 1; // ERR CODE 1: Did not fill out form properly

	std::vector<int> check;
	std::cout << std::endl << "User: " << user.c_str() << " - pass: " << pass.c_str() << std::endl;
	getData(check,"select id from tfd_login where user='"+user+"' and pass=MD5('"+pass+"') limit 1");
	if(check.size() <= 0)
		return 2; // ERR CODE 2: Invalid credentials

	return 0; // Success
}
