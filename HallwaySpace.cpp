/**********************************************************************
* HallwaySpace class is a inherited class object that uses Space as
* it's base class. This class represents the hallway room in the game.
**********************************************************************/
#include "HallwaySpace.h"
HallwaySpace::HallwaySpace() : Space(roomNumber, numRows, numCols, pStartRow, pStartCol) {
	this->customBoard();
}

void HallwaySpace::customBoard() {
	//insert empty spaces 
	this->insertEmpty(1, 0, 1); //transfer to main space 
	this->insertEmpty(6, 6, 3); //transfer to shop space
	this->insertEmpty(3, 0);
	this->insertEmpty(4, 0);
	this->insertEmpty(5, 0);
	this->insertEmpty(6, 0);
	this->insertEmpty(6, 1);
	this->insertEmpty(6, 2);
	this->insertEmpty(6, 3);
	this->insertEmpty(6, 4);
	//insert vertical spaces
	this->insertVertical(3, 5);
	this->insertVertical(4, 5);
	this->insertVertical(5, 5);
	this->insertVertical(6, 5);
	this->insertVertical(6, 7);
	//insert horizontal spaces
	this->insertHorizontal(2, 0);
	this->insertHorizontal(2, 1);
	this->insertHorizontal(2, 2);
	this->insertHorizontal(2, 3);
	this->insertHorizontal(2, 4);
	this->insertHorizontal(2, 5);
	//set personOccupied
	this->setPersonOccupied(this->getPersonRow(), this->getPersonCol());
}

HallwaySpace::~HallwaySpace() {
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