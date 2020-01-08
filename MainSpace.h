/**********************************************************************
* MainSpace class is a inherited class object that uses Space as
* it's base class. This class represents the main room in the game.
* This room is where the player starts and is the central room in the
* game.
**********************************************************************/
#ifndef MAINSPACE_H
#define MAINSPACE_H
#include "Space.h"
#include "Item.h"
class MainSpace : public Space {
	static const int numRows = 12;
	static const int numCols = 12;
	static const int pStartRow = 8;
	static const int pStartCol = 5;
	static const int roomNumber = 1;
public:
	MainSpace();
	void customBoard();
	~MainSpace();
};
#endif // !MAINSPACE_H
