/*********************************************************************
* ClosetSpace class is a inherited class object that uses Space as 
* it's base class. This class represents the closet room in the game.
*********************************************************************/
#ifndef CLOSETSPACE_H 
#define CLOSETSPACE_H 
#include "Space.h"
#include "Item.h"
class ClosetSpace : public Space {
private:
	static const int numRows = 4;
	static const int numCols = 3;
	static const int pStartRow = 1;
	static const int pStartCol = 2;
	static const int roomNumber = 5;
public:
	ClosetSpace();
	void customBoard();
	~ClosetSpace();
};
#endif // !CLOSETSPACE_H
