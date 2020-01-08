/**********************************************************************
* ShopSpace class is a inherited class object that uses Space as
* it's base class. This class represents the shop room in the game.
**********************************************************************/
#ifndef SHOPSPACE_H 
#define SHOPSPACE_H 
#include "Space.h"
#include "Item.h"
class ShopSpace : public Space {
private:
	static const int numRows = 7;
	static const int numCols = 8;
	static const int pStartRow = 0;
	static const int pStartCol = 6;
	static const int roomNumber = 3;
public:
	ShopSpace();
	void customBoard();
	~ShopSpace();
};
#endif // !SHOPSPACE_H
