// primefactor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>

void doFactor(int numToFactorize, int i) {
	if (i <= numToFactorize) {
		if (numToFactorize % i == 0)
			std::cout << i << " ";

		doFactor(numToFactorize, i + 1);
	}
}

int main()
{
	std::cout << "Please input your number to factorize: ";

	int input;
	std::cin >> input;

	std::cout << "You inputted " << input << ". Was that correct?\n";
	doFactor(input, 1);
}
