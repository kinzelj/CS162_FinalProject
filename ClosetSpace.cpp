/*********************************************************************
* ClosetSpace class is a inherited class object that uses Space as
* it's base class. This class represents the closet room in the game.
*********************************************************************/
#include "ClosetSpace.h"
ClosetSpace::ClosetSpace() : Space(roomNumber, numRows, numCols, pStartRow, pStartCol) {
	this->customBoard();
}

void ClosetSpace::customBoard() {
	//create items for Closet Space 
	Item* screwdriver = new Item("Screwdriver", "Screwdriver", true, 'S', 11, ' ', false);
	//add item to itemList
	this->addItemToList(screwdriver);
	//insert empty spaces 
	this->insertEmpty(1, 2, 4);	//transfer to shop space
	//insert items into board
	this->insertItem(2, 1, screwdriver);
	//set personOccupied
	this->setPersonOccupied(this->getPersonRow(), this->getPersonCol());
}

ClosetSpace::~ClosetSpace() {
	//delete dynamic for all items in room
	for (Item* spaceItem : itemList) {
		delete spaceItem;
	}

	//delete dynamic memory of all room loactions
	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numCols; col++) {
			delete board[row][col];
		}
		delete[] board[row];
	}
	delete[] board;
}


