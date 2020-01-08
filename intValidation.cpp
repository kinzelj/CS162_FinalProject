/*******************************************************************
* Program name: intValidation function
* Author: Josh Kinzel
* Date: 04/14/2018
* Function checks to ensure an integer value input by the user
* meets the conditions specified. Function will prompt the user
* to input a valid integer value, check this value meets specified
* conditions, then returns the value if valid. If invalid value 
* input by user, function will continue to ask the user to input
* a valid integer.
******************************************************************/
#include "intValidation.h"

int intValidation(const std::string &promptOutput, bool negativesAllowed, bool zeroAllowed) {
	int returnInt;
	std::string extraChars;
	bool validInput = false;

	//display prompt message if passed to function
	if (promptOutput != "") {
		std::cout << promptOutput;
	}

	//loop until valid integer input is provided by user
	while (!validInput) {
		//read in integer, clear any errors, and read in any extra text after integer
		std::cin >> returnInt;
		std::cin.clear();
		std::getline(std::cin, extraChars);
		
		//set validInput to true then check all conditions to determine valid input
		validInput = true;
		if (extraChars.length() > 0) {
			validInput = false;
		}
		if (!negativesAllowed && returnInt < 0) {
			validInput = false;
		}
		if (!zeroAllowed && returnInt == 0) {
			validInput = false;
		}
		
		//if validInput reverted back to false, print invalid input error message
		if (!validInput) {
			std::cout << "Invalid input, please try again: ";
		}
	}

	//return valid integer
	return returnInt;
}