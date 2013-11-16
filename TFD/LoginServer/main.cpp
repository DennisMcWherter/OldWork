// Sample implementation
//
// $Id$
//
// @author: RageD (Dennis J. McWherter, Jr.)
//

#include <iostream>
#include "LogonDB.h"
#include <cmath>
#include <stdint.h>
#include <ctime>

using namespace std;

void processUserResult(int res)
{
	switch(res)
	{
	case 0:
		cout<< "Successfully registered character!\n";
		break;
	case 1:
		cout<< "You did not properly fill-out the registration! Please try again.\n";
		break;
	case 2:
		cout<< "That username is already registered.\n";
		break;
	case 3:
		cout<< "Someone has already registered with that e-mail.\n";
		break;
	default:
		cout<< "An unexpected error occurred.\n";
		break;
	}
}

int main()
{
  	vector<int> values;
       	LogonDB *logondb = new LogonDB("localhost","root","paxxword","db"); // This can be hardcoded for security on our servers
	if(logondb->canConnect())
		cout<< "Success!" << endl;
	else // An exception will probably be thrown by poco before this - we can handle our own later if we want though
		cout<< "Failed! :(" << endl;

	// setup our datamanager - run this query based off of infernale's test
	logondb->getData<int>(values,"select * from foo");
	for(unsigned int i=0;i<values.size();++i) cout<< "Value "<< (i+1)<< ": "<< values[i] << endl;

	// Awesome, that worked! Now, let's register a user...
	logondb->runQuery("DROP TABLE IF EXISTS tfd_login");
	logondb->runQuery("CREATE TABLE `tfd_login` (`id` BIGINT( 10 ) NOT NULL AUTO_INCREMENT PRIMARY KEY , `user` VARCHAR( 16 ) NOT NULL , `pass` VARCHAR( 32 ) NOT NULL , `email` VARCHAR( 32 ) NOT NULL ) ENGINE = MYISAM");

	// FEATURE DEBUG
	// Try registering a user - This is more for debugging than practical application
	// Actual implementation will probably be to send back the result code to the client and we'll handle it there with text
	cout<< endl << "Attempting to register user...\nThis test should cycle through all possible results...\n" << endl;
	processUserResult(logondb->registerUser("raged","test","admin@microsonic.org"));
	processUserResult(logondb->registerUser("raged","test","admin@microsonic.org"));
	processUserResult(logondb->registerUser("w00t","test","admin@microsonic.org"));
	processUserResult(logondb->registerUser("raged","test",""));
	// END FEATURE DEBUG

	// Cleanup
	delete logondb;
	logondb = NULL;
	return 0;
}
