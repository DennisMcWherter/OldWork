//
// BaseSQL.h
//
// $Id: BaseSQL.h 96 2011-01-16 02:07:17Z raged $
//
// The BaseSQL wrapper for TFD Servers
//
// Main Developers: RageD (Dennis J. McWherter, Jr.), infernale890
//

#ifndef __BASE_SQL_H__
#define __BASE_SQL_H__

// Main includes
#include "Poco/Data/MySQL/MySQL.h"
#include "Poco/Data/MySQL/Connector.h"
#include "Poco/Data/MySQL/SessionImpl.h"
#include "Poco/Data/Session.h"
#include "Poco/Exception.h"
#include <vector>
#include <string>

// NOTE: This is a base class - this class should _NEVER_ be accessed directly


class BaseSQL
{
#define DB_TYPE "MySQL"
private:
	Poco::Data::Session *_dbSession; //Database session

	void regConnector();
	void unregConnector();
public:
	BaseSQL(std::string host,std::string user,std::string pass,std::string db);
	~BaseSQL();

	// Functions
	inline bool isSessionOk() { return (_dbSession ? true : false); }                      //this checks if _dbsession is allocated
	inline int  canConnect()  { return (isSessionOk() ? _dbSession->isConnected() : -1); } //checks if _dbSession is connected
	void        runQuery(std::string query);
	template<typename T> void getData(std::vector<T>& res,std::string query)
	{
		if (isSessionOk())
		{
			res.clear(); // We only want these results... Make sure nothing else is hanging around
			*_dbSession << query, Poco::Data::into(res), Poco::Data::now;
		}
	}
	template<typename T> void insertData(std::vector<T> data,std::string query)
	{
		if (isSessionOk())
		{
			//Actually i don't know if it's better to use a Statement or _dbSession directly, but for now we'll use the Statement until we do some researches
			Poco::Data::Statement insert(_dbSession);
			insert << query, Poco::Data::use(data), Poco::Data::now;
			insert.execute();
		}
	}
};
#endif
