/**********************************************************************
* VentSpace class is a inherited class object that uses Space as
* it's base class. This class represents the vent room in the game.
**********************************************************************/
#ifndef VENTSPACE_H
#define VENTSPACE_H
#include "Space.h"
#include "Item.h"
class VentSpace : public Space {
private:
	static const int numRows = 3;
	static const int numCols = 6;
	static const int pStartRow = 1;
	static const int pStartCol = 5;
	static const int roomNumber = 6;
public:
	VentSpace();
	void customBoard();
	~VentSpace();
};
#endif // !VENTSPACE_H
