/**********************************************************************
* Space class is an abstract class that is the base for each inherited
* Space object in the game that represents each room.
* The six Space objects will be linked together using Space pointers
* for top, bottom, left, and right. Each inherited object will have a
* unique 'board' that is created when the polymorphic customBoard()
* method is called.
**********************************************************************/
#ifndef SPACE_H
#define SPACE_H
#include "SpaceUnit.h"
#include "HorizUnit.h"
#include "VertUnit.h"
#include "EmptyUnit.h"
#include "ItemUnit.h"
#include "Item.h"
#include "WIN_32_ClearScreen.h"

#include <string>
#include <iostream>
#include <stdio.h>
class Space {
protected:
	int roomNumber;
	int roomRows;
	int roomCols;
	int personRow;
	int personCol;

	Space* top;
	Space* bottom;
	Space* left;
	Space* right;

	SpaceUnit*** board;
	void setupBoard();

	std::vector<Item*> itemList;

public:
	Space(int roomNumber, int roomRows, int roomCols, int personRow, int personCol);
	void printBoard();

	Space* getTop();
	Space* getBottom();
	Space* getLeft();
	Space* getRight();
	SpaceUnit*** getBoard();
	int getPersonRow();
	int getPersonCol();
	int getRoomNumber();


	void setTop(Space*);
	void setBottom(Space*);
	void setLeft(Space*);
	void setRight(Space*);
	void setPersonRow(int, bool);
	void setPersonCol(int, bool);
	void removePerson(int row, int col);
	void setPersonOccupied(int row, int col);
	void addItemToList(Item*);
	std::vector<Item*>& getItemList();

	void insertVertical(int row, int col);
	void insertHorizontal(int row, int col);
	void insertEmpty(int row, int col);
	void insertEmpty(int row, int col, int transferRoom);
	void insertItem(int row, int col, Item* newItem);
	bool checkForItem(int&, int&);

	virtual void customBoard() = 0;
	virtual ~Space() {}

};
#endif // !SPACE_H
