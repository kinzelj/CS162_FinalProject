/**********************************************************************
* TunnelSpace class is a inherited class object that uses Space as
* it's base class. This class represents the tunnel room in the game.
**********************************************************************/
#include "TunnelSpace.h"
TunnelSpace::TunnelSpace() : Space(roomNumber, numRows, numCols, pStartRow, pStartCol) {
	this->customBoard();
}
void TunnelSpace::customBoard() {
	//create items for main room
	Item* KeyE = new Item("Key E", "Key", true, 'K', 9, 'E', false);
	//add items to room itemList
	this->addItemToList(KeyE);
	//insert empty spaces 
	this->insertEmpty(0, 8, 2);
	this->insertEmpty(0, 0);
	this->insertEmpty(0, 1);
	this->insertEmpty(0, 2);
	this->insertEmpty(0, 3);
	this->insertEmpty(0, 4);
	this->insertEmpty(0, 5);
	this->insertEmpty(0, 6);
	//insert vertical spaces
	this->insertVertical(0, 7);
	this->insertVertical(0, 9);
	//insert horizontal spaces
	this->insertHorizontal(1, 0);
	this->insertHorizontal(1, 1);
	this->insertHorizontal(1, 2);
	this->insertHorizontal(1, 3);
	this->insertHorizontal(1, 4);
	this->insertHorizontal(1, 5);
	this->insertHorizontal(1, 6);
	this->insertHorizontal(1, 7);
	//insert items into board
	this->insertItem(2, 1, KeyE);
	//set personOccupied
	this->setPersonOccupied(this->getPersonRow(), this->getPersonCol());
}

TunnelSpace::~TunnelSpace() {
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