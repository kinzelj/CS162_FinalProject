/*******************************************************************
* Program name: CS162 Final Project - Escape Room Game
* Author: Josh Kinzel
* Date: 06/12/201
* This program simulates an escape sequence game. The objective
* of the game is for the player to find clues and items needed
* to escape the room before they run out of oxygen. The purpose
* of this program is to utilize the object oriented tools that
* were taught in CS162: abstract data types, inheritance, 
* polymorphism, dynamic pointers, etc.
******************************************************************/
#include "Game.h"
#ifdef _WIN32
#include <stdlib.h>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC 
#endif
int main() {
	Game newGame;
	newGame.startGame();
	return 0;
#ifdef _WIN32
	_CrtDumpMemoryLeaks();
#endif // _WIN32
}