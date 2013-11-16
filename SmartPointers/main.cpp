/**
 * Quick implementation of simple smart pointer
 * class.
 *
 * Author: Dennis J. McWherter, Jr.
 * 8 Mar 2011
 */

#include <iostream>
#include <string>
#include "smartPointer.h"

#define _DEBUG_
#ifdef _DEBUG_
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

using namespace std;

void playWithSP()
{
	// Create smart pointer objects
	smartPointer<int> test, test2;
	smartPointer<std::string> sweet;
	*test = 10;
	test2 = test;
	cout<< *test2 << endl;
	test = 71239401;
	cout<< *test << endl;
	*sweet = "This is pretty cool!";
	cout<< *sweet << endl;
	sweet = "Yep - no mem leaks <3";
	cout<< *sweet << endl;

	smartPointer<char*> cool;
	*cool = "w00t";
	cout<< *cool << endl;
}

int main()
{
	playWithSP();
#ifdef _DEBUG_
	_CrtDumpMemoryLeaks();
#endif
	cin.get();
	return 0;
}
