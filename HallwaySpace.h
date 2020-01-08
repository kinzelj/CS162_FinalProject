/**********************************************************************
* HallwaySpace class is a inherited class object that uses Space as
* it's base class. This class represents the hallway room in the game.
**********************************************************************/
#ifndef HALLWAYSPACE 
#define HALLWAYSPACE_H 
#include "Space.h"
#include "Item.h"
class HallwaySpace : public Space {
private:
	static const int numRows = 7;
	static const int numCols = 8;
	static const int pStartRow = 1;
	static const int pStartCol = 0;
	static const int roomNumber = 2;
public:
	HallwaySpace();
	void customBoard();
	~HallwaySpace();
};
#endif // !HALLWAYSPACE_H
