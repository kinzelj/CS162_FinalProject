/**********************************************************************
* ShopSpace class is a inherited class object that uses Space as
* it's base class. This class represents the shop room in the game.
**********************************************************************/
#include "ShopSpace.h"
ShopSpace::ShopSpace() : Space(roomNumber, numRows, numCols, pStartRow, pStartCol) {
	this->customBoard();
}

void ShopSpace::customBoard() {
	//create items for shop space
	Item* closetDoor = new Item("Hallway Door", "Door", false, 'D', 10, ' ', true);			//#0 Item in room
	Item* toolBox = new Item("Tool Box", "Tool Box", false, '#', 13, ' ', false);				//#1 Item in room
	Item* hammer = new Item("Hammer", "Hammer", true, 'H', 7, ' ', false);						//#2 Item in room
	Item* flashlight = new Item("Flashlight", "Flashlight", true, 'F', 8, ' ', false);		//#3 Item in room
	//add all items to Space itemList
	this->addItemToList(closetDoor);		//#0 Item in room
	this->addItemToList(toolBox);			//#1 Item in room
	this->addItemToList(hammer);			//#2 Item in room
	this->addItemToList(flashlight);		//#3 Item in room
	//add note to nightstand item
	toolBox->addItem(hammer);
	toolBox->addItem(flashlight);
	//insert empty spaces 
	this->insertEmpty(0, 6, 2);	//transfer to hallway space
	this->insertEmpty(5, 0, 1);	//transfer to closet space
	//insert vertical spaces
	this->insertVertical(0, 5);
	this->insertVertical(0, 7);
	//insert horizontal spaces
	this->insertHorizontal(4, 1);
	//insert items into board
	this->insertItem(5, 1, closetDoor);
	this->insertItem(4, 5, toolBox);
	this->insertItem(5, 5, toolBox);
	this->insertItem(4, 6, toolBox);
	this->insertItem(5, 6, toolBox);
	//set personOccupied
	this->setPersonOccupied(this->getPersonRow(), this->getPersonCol());
}

ShopSpace::~ShopSpace() {
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