/**
 * Simple User Input by RageD
 * (C) RageD 2008.
 *
 * In this tutorial it is assumed you recall previously
 * covered material and all tutorials fromt here on forth
 * in this segment.
 *
 */

#include <iostream>
#include <string> // Allow us to declare things as "strings"

using namespace std;

int main()
{
	string name; // Declare variable as a "string" that comes from the #include <string> header file
		     // In all honest, you'll probably never use the "string" variable as it's eh. Not
		     // Very good programming really. But we'll go over that later this is just to start
		     // Grasping the concept of programming. Secure/efficient programming comes after this :P
	cout<< "To exit, please type 'exit' for your name.\n\nPlease enter your name: ";
	cin>> name; // This is the user input. The >> means to set the "name" variable to it
	if(name != "exit") // If is a conditional statement. It is explained below in the tutorial
	{
		cout<< "Nice, your name is " << name << endl << endl << "I like it..." << endl << endl;
		// Adding the name variable to be output is very similar to the endl as you can see :)
		return main();
	} else {
		return 0; // Loop to the main function over and over until "exit" is typed.
	}
}
