/**********************************************************************
* VentSpace class is a inherited class object that uses Space as
* it's base class. This class represents the vent room in the game.
**********************************************************************/
#include "VentSpace.h"
VentSpace::VentSpace() : Space(roomNumber, numRows, numCols, pStartRow, pStartCol) {
	this->customBoard();
}

void VentSpace::customBoard() {
	//create items for main room
	Item* KeyS = new Item("Key S", "Key", true, 'K', 12, 'S', false);
	//add item to room item list
	this->addItemToList(KeyS);
	//insert empty spaces 
	this->insertEmpty(1, 5, 4);
	//insert items into board
	this->insertItem(1, 1, KeyS);
	//set personOccupied
	this->setPersonOccupied(this->getPersonRow(), this->getPersonCol());
}

VentSpace::~VentSpace() {
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