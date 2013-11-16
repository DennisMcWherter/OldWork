/**
 * Random Seed Script by RageD
 * (C) RageD 2008.
 *
 */

#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
	unsigned seed;
	char quit;
	cout<< "Please enter seed: ";
	cin>> seed;
	srand(seed);
	for(int i=0;i<8;i++)
	{
		cout<< "Your seed: " << rand() << endl;
	}
	cout<< endl << "Would you like to quit? (y/n)\n\nYour option: ";
	cin>> quit;
	switch(quit)
	{
		case 'y':
			cout<< endl << endl << "Exiting..." << endl;
			return 0;
		break;
		case 'n':
			return main();
		break;
		default:
			cout<< "Exiting..." << endl;
			return 0;
		break;
	}
}

