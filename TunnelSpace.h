/**********************************************************************
* TunnelSpace class is a inherited class object that uses Space as
* it's base class. This class represents the tunnel room in the game.
**********************************************************************/
#ifndef TUNNELSPACE_H
#define TUNNELSPACE_H
#include "Space.h"
#include "Item.h"
class TunnelSpace : public Space {
private:
	static const int numRows = 4;
	static const int numCols = 10;
	static const int pStartRow = 0;
	static const int pStartCol = 8;
	static const int roomNumber = 4;
public:
	TunnelSpace();
	void customBoard();
	~TunnelSpace();
};
#endif // !TUNNELSPACE_H
