/**
 * Example class script by RageD
 * (C) 2008 RageD.
 *
 */

#include <iostream>

using namespace std;

/**
 * Create the class structure here
 *
 * Not too difficult and pretty self explanatory but take a look anyway :) 
 *
 */

class Main
{
public:
  int loop();
  int a();
  int b();
  int c();
private:
  bool w00t(); // Not coded in example :P
}; // Yes, semi-colon is supposed to be here in this one. Even with the "}"

/**
 * Now let's make the structure useful :P
 *
 */

int Main::loop()
{
	char opt, pause; // Define both opt and pause as "char"
	cout<< "Welome to the main menu!\n\nPlease select one of the following options:"<< endl << endl << "a\nb\nc\n\nx to exit" << endl << endl << "Your option: ";
	//cout<< argv[0];
	cin>> opt;
	switch(opt)
	{
		case 'a':
			return Main::a();
		break;
		case 'b':
			return Main::b();
		break;
		case 'c':
			return Main::c();
		break;
		case 'x':
			cout<< "Exiting...\n\n";
			return 0;
		break;
		default:
			cout<< "Your option '"<< opt <<"' is not a valid option!" << endl;
			return Main::loop();
		break;
	}
}

int Main::a()
{
	cout<< "Great, you selected option A!\n\nPlease hit return to continue..." << endl << endl;
	Main::loop();
}

int Main::b()
{
	cout<< "Sweet, you picked option B!\n\nPlease hit return to continue..." << endl << endl;
	Main::loop();
}

int Main::c()
{
	cout<< "Erm.. Why C? C++ FTW! :D\n\nPlease hit return to continue..." << endl << endl;
	Main::loop();
}
