// calculation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;



int main()
{
	bool c = true;
	string answer = "";
	int firstNumber;
	int secondNumber;
	
	while (c) {
		cout << "give me a number: ";
		cin >> firstNumber;
		cout << "give me a second number: ";
		cin >> secondNumber;
		cout << "The sum of the numbers is: " << firstNumber + secondNumber << endl;
		cout << "the difference of the two numbers is: " << firstNumber - secondNumber << endl;
		cout << "the product of the two numbers: " << firstNumber*secondNumber << endl;
		cout << "the quotient of the the two  numbers: " << firstNumber / secondNumber << endl;
		cout << "continue? (y/n): ";
		cin >> answer;
		if (answer == "no" || answer == "n") { c = false; }
	}
    return 0;
}

