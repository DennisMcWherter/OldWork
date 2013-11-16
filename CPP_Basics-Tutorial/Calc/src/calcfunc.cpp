/**
 * This is where the framework is at
 *
 */

#include <iostream>
//#include <ctypes> // For the isdigit(); function

using namespace std;
using namespace Calculator; // ours <3

/**
 * Create the class for the main function
 * to loop to, etc.
 * 
 */

class Calc
{
public:
  int main();
  int add(int x, int y);
  int sub(int x, int y);
  int div(int x, int y);
  int mult(int x, int y);
};

/**
 * Begin the real work now :)
 *
 */

int Calc::main()
{
	char x;
	int s1, s2;
	cout<< "Welcome to the test calculator by RageD!\n\nPlease let us know which operation you would like to do:\n\na.) Add\nb.) Subtract\nc.) Divide\nd.) Multiply\n\nx.) Exit calculator\n\nYour operation: ";
	cin>> x;
	switch(x)
	{
		case 'a':
			cout<< "Please enter your first number to add: ";
			cin>> s1;
			cout<< endl << "Now your second: ";
			cin>> s2;
			return Calc::add(s1,s2);
		break;
		case 'b':
			cout<< "Please enter your first number to subtract: ";
			cin>> s1;
			cout<< endl << "Now your second: ";
			cin>> s2;
			return Calc::sub(s1,s2);
		break;
		case 'c':
			cout<< "Please enter your first number to divide: ";
			cin>> s1;
			cout<< endl << "Now your second: ";
			cin>> s2;
			return Calc::div(s1,s2);
		break;
		case 'd':
			cout<< "Please enter your first number to multiply: ";
			cin>> s1;
			cout<< endl << "Now your second: ";
			cin>> s2;
			return Calc::mult(s1,s2);
		break;
		case 'x':
			cout<< endl << endl << "Exiting Calculator!" << endl;
			return 0;
		break;
		default:
			cout<< endl << "Invalid option, please try again!" << endl;
			return Calc::main();
		break;
	}
	return 0; // Shouldn't get to this point.
}

int Calc::add(int x, int y)
{
	cout<< "Your numbers you wished to add together were "<< x << " and "<< y << endl;
	cout<< "The answer is: "<< endl << addition(x,y) << endl; // because we defined namespace we don't need
	return Calc::main();  			                 // to use Calculator::add(x,y);
}

int Calc::sub(int x, int y)
{
	cout<< "Your numbers you wished to subtract were "<< x << " and "<< y << endl;
	cout<< "The answer is: "<< endl << subtraction(x,y) << endl;
	return Calc::main();
}

int Calc::div(int x, int y)
{
	cout<< "Your numbers you wished to divide were "<< x << " and "<< y << endl;
	cout<< "The answer is: "<< endl << division(x,y) << endl;
	return Calc::main();
}

int Calc::mult(int x, int y)
{
	cout<< "Your numbers you wished to multiply together were "<< x << " and "<< y << endl;
	cout<< "The answer is: "<< endl << multiplication(x,y);
	return Calc::main();
}
