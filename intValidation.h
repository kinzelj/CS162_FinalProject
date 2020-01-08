/*******************************************************************
* Program name: intValidation function
* Author: Josh Kinzel
* Date: 04/14/201
* Function checks to ensure an integer value input by the user
* meets the conditions specified. Function will prompt the user
* to input a valid integer value, check this value meets specified
* conditions, then returns the value if valid. If invalid value 
* input by user, function will continue to ask the user to input
* a valid integer.
******************************************************************/
#ifndef INTVALIDATION_H
#define INTVALIDATION_H
#include <iostream>
#include <string>
int intValidation(const std::string &promptOutput, bool negativesAllowed, bool zeroAllowed);
#endif 