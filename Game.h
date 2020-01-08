/*******************************************************************
* Game class controls all object instantiation and overall game
* structure. The Game class will handle all game scenarios and 
* sequences. It is the central control for the entire game.
******************************************************************/
#ifndef GAME_H
#define GAME_H
#include "Space.h"
#include "SpaceUnit.h"
#include "MainSpace.h"
#include "TunnelSpace.h"
#include "VentSpace.h"
#include "HallwaySpace.h"
#include "ShopSpace.h"
#include "ClosetSpace.h"
#include "Person.h"
#include "menu.h"
#include "intValidation.h"
#include "WIN_32_ClearScreen.h"

#ifdef __unix__ 
#include <unistd.h>
#include <termios.h> 
#elif _WIN32
#include <conio.h>
#else
#endif

#include <string>
#include <vector>
#include <algorithm>
class Game {
private:
	static const int numRooms = 6;
	Space* allRooms[numRooms];
	Space* currentRoom;
	Person* player;
	void useItem(Item* itemSecletion);
	void dropItem(Item* itemSelection);
	bool usedFlashlight;
	int itemRow;
	int itemCol;
	void setupRooms();
	bool allKeys;
	bool nextToItem;
	bool reachVent;
	bool itemDropped;
	bool puzzlePickup;
	bool nightstandPrompt;
	bool winGame;
	bool allDoorsOpen;
	bool getAllKeys;
	double oxygen;
	const double OXYGEN_PER_MOVE = 0.2;

public:
	Game();
	~Game();
	void startGame();
	void promptIntro();
	void promptOutro();
	void printCurrentBoard(Space* currentRoom);
	bool simulateGame();
	void nextMove(int personRow, int personCol, SpaceUnit*** currentBoard);
	void setCurrentRoom(Space* currentRoom);
	void setRoomPointers();
	void itemFound(int personRow, int personCol, SpaceUnit*** currentBoard);
	int checkDoor();
	void openFinalDoor();
	void openAllDoors();
	void resetGame();
	char getchar();
	void checkAllKeys();
};
#endif // !GAME_H
