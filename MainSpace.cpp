/**********************************************************************
* MainSpace class is a inherited class object that uses Space as
* it's base class. This class represents the main room in the game.
* This room is where the player starts and is the central room in the
* game.
**********************************************************************/
#include "MainSpace.h"
MainSpace::MainSpace() : Space(roomNumber, numRows, numCols, pStartRow, pStartCol) {
	this->customBoard();
}
void MainSpace::customBoard() {
	//create items for main room
	Item* mainDoor = new Item("Main Door", "Door", false, 'D', 0, ' ', true);				//#0 Item in room
	Item* nightstand = new Item("Nightstand", "Nightstand", false, '=', 1, ' ', true);	//#1 Item in room
	Item* note = new Item("Crossword", "Note", true, 'N', 2, ' ', false);					//#2 Item in room
	Item* keyC = new Item("Key C", "Key", true, 'K', 3, 'C', false);							//#3 Item in room
	Item* vent = new Item("Vent", "Vent", false, 'V', 6, ' ', false);							//#4 Item in room
	Item* hallDoor = new Item("Hallway Door", "Door", false, 'D', 5, ' ', true);			//#5 Item in room
	Item* light = new Item("Light", "Light", true, '*', 4, ' ', true);						//#6 Item in room

	//add all items to Space itemList
	this->addItemToList(mainDoor);		//#0 Item in room
	this->addItemToList(nightstand);		//#1 Item in room
	this->addItemToList(note);				//#2 Item in room
	this->addItemToList(keyC);				//#3 Item in room
	this->addItemToList(vent);				//#4 Item in room
	this->addItemToList(hallDoor);		//#5 Item in room
	this->addItemToList(light);			//#6 Item in room

	//add note to nightstand item
	nightstand->addItem(note);

	//insert empty spaces 
	this->insertEmpty(11, 5);
	this->insertEmpty(7, 11, 4);

	//insert vertical spaces
	this->insertVertical(10, 4);
	this->insertVertical(10, 6);
	this->insertVertical(1, 7);
	this->insertVertical(2, 7);
	this->insertVertical(3, 7);
	this->insertVertical(4, 7);
	this->insertVertical(1, 9);
	this->insertVertical(2, 9);
	this->insertVertical(3, 9);
	this->insertVertical(4, 9);

	//insert horizontal spaces
	this->insertHorizontal(1, 8);
	this->insertHorizontal(4, 8);
	this->insertHorizontal(6, 10);
	this->insertHorizontal(8, 10);

	//insert items into board
	this->insertItem(10, 5, mainDoor);
	this->insertItem(1, 6, nightstand);
	this->insertItem(3, 0, vent);
	this->insertItem(7, 10, hallDoor);
	this->insertItem(1, 10, light);

	//set occupied person space
	this->setPersonOccupied(this->getPersonRow(), this->getPersonCol());

	//set win game space
	this->board[11][5]->setWinGame(true);
}

MainSpace::~MainSpace() {
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