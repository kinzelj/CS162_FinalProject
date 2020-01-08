/*******************************************************************
* Program name: menu function
* Author: Josh Kinzel
* Date: 04/14/201
* Function receives a vector of strings for each menu option, 
* and integer for the size of the menu option's vector, and a 
* string that will be output to the console to prompt the user 
* before displaying menu options. User will input their menu
* selection and the function will confirm a valid integers value
* was selected by calling intValidation function. If valid integer
* is selected, menu selection is returned.
******************************************************************/
#ifndef MENU_H
#define MENU_H
#include "intValidation.h"
#include <iostream>
#include <string>
#include <vector>
int menu(const std::vector<std::string> &menuOptions, int menuSize, const std::string &prompt);
#endif 
