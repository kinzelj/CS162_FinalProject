/*******************************************************************
* Program name: menu function
* Author: Josh Kinzel
* Date: 04/14/2018
* Function receives a vector of strings for each menu option, 
* and integer for the size of the menu option's vector, and a 
* string that will be output to the console to prompt the user 
* before displaying menu options. User will input their menu
* selection and the function will confirm a valid integers value
* was selected by calling intValidation function. If valid integer
* is selected, menu selection is returned.
******************************************************************/
#include "menu.h"
int menu(const std::vector<std::string> &menuOptions, int menuSize, const std::string &prompt) {
	int choiceNumber = 1;		//integer to designate menu option number
	int choiceInput;			//integer for user menu choice
	bool validChoice = false;	//condition for valid menu choice

	//display menu prompt string passed to function
	std::cout << prompt << std::endl;

	//lopp through menu option vector to display string of all option
	for (int i = 0; i < menuSize; i++) {
		std::cout << choiceNumber << ": " << menuOptions[i] << std::endl;
		choiceNumber++;
	}

	//until valid menu option is selected, prompt user to define menu selection
	while (!validChoice) {
		//call inValidation function to confirm valid integer was input by user
		choiceInput = intValidation("", false, false);

		//check to confirm user selected integer between menu options
		if (choiceInput >= 1 && choiceInput < choiceNumber) {
			validChoice = true;
		}
		else {
			std::cout << "Invalid Input, please try again: ";
		}
	}
	//return integer of valid menu option
	return choiceInput;
}