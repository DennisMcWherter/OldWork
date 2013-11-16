//
// BaseSQL.cpp
//
// $Id: BaseSQL.cpp 96 2011-01-16 02:07:17Z raged $
//
// The BaseSQL wrapper for TFD Servers
//
// Main Developers: RageD (Dennis J. McWherter, Jr.), infernale890
//

#include "BaseSQL.h"
#include <stdint.h>

namespace
{
  static uint32_t MySQLInits = 0; //Used to track how many sessions are alive
}

BaseSQL::BaseSQL(std::string host,std::string user,std::string pass,std::string db) : _dbSession(NULL)
{
       regConnector(), MySQLInits++;
       //Cannot put _dbSession in costructor because we have to call registerConnector before :( that's why _dbSession is a pointer
       _dbSession = new Poco::Data::Session(DB_TYPE, "host="+host+";user="+user+";password="+pass+";db="+db+";compress=true;auto-reconnect=true");
}

BaseSQL::~BaseSQL()
{
        if (isSessionOk())
	  _dbSession->close();
        try
	{
	  delete _dbSession;
        } catch (...) {}
	if (MySQLInits) 
	  --MySQLInits,  unregConnector();
}

void BaseSQL::regConnector()
{ 
  /*Regconnector should be called only from constructor. If it's the first
   *session then this will call registerConnector */
        if (!MySQLInits)
	  Poco::Data::MySQL::Connector::registerConnector();
}

void BaseSQL::unregConnector()
{
  /*unregConnector should be called only from deconstructor. If it's the last
    session then this will call unregisterConnector */
        if (!MySQLInits)
	  Poco::Data::MySQL::Connector::unregisterConnector();
}

/**
 * Run a general query - no templated format, but no way to return results
 */
void BaseSQL::runQuery(std::string query)
{
        if (isSessionOk())
	  *_dbSession << query, Poco::Data::now;
}

