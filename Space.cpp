/**********************************************************************
* Space class is an abstract class that is the base for each inherited
* Space object in the game that represents each room.
* The six Space objects will be linked together using Space pointers
* for top, bottom, left, and right. Each inherited object will have a
* unique 'board' that is created when the polymorphic customBoard()
* method is called.
**********************************************************************/
#include "Space.h"
//space constructor creates each room in the game
Space::Space(int roomNumber, int Rows, int Cols, int pRow, int pCol) :
	roomNumber(roomNumber),
	roomRows(Rows),
	roomCols(Cols),
	personRow(pRow),
	personCol(pCol)
	{
		this->top = nullptr;
		this->bottom = nullptr;
		this->left = nullptr;
		this->right = nullptr;
		this->setupBoard();
	}

void Space::addItemToList(Item* newItem) {
	this->itemList.push_back(newItem);
}

void Space::setupBoard() {
	//define initial board setup from roomRows & roomCols variables
	this->board = new SpaceUnit**[roomRows];
	for (int row = 0; row < roomRows; row++) {
		board[row] = new SpaceUnit*[roomCols];
	}

	//populate initial board space with boarders and empty spaces
	for (int row = 0; row < this->roomRows; row++) {
		for (int col = 0; col < this->roomCols; col++) {
			if (row == 0 || row == (roomRows - 1)) {
				board[row][col] = new HorizUnit();
			}
			else if ((col == 0 && (row > 0 && row < roomRows)) ||
				(col == (roomCols - 1) && (row > 0 && row < roomRows))) {
				board[row][col] = new VertUnit();
			}
			else {
				board[row][col] = new EmptyUnit();
			}
		}
	}
}

//print board of current room
void Space::printBoard() {
	std::cout << std::endl;
	if (this->board != NULL) {
		for (int row = 0; row < this->roomRows; row++) {
			for (int col = 0; col < this->roomCols; col++) {
				if (this->board[row][col]->checkPerson()) {
					std::cout << 'X' << ' ';
				}
				else {
					std::cout << this->board[row][col]->getUnitChar() << ' ';
				}
			}
			std::cout << std::endl;
		}
	}
}

//set person occupied condition to false for board positions passed to method
void Space::removePerson(int row, int col) {
	board[row][col]->setPersonOccupied(false);
}

//set person occupied condition to true for board positions passed to method
void Space::setPersonOccupied(int row, int col) {
	board[row][col]->setPersonOccupied(true);
}

//manual insert of SpaceUnit types to Space board
void Space::insertItem(int row, int col, Item* newItem) {
	delete board[row][col];
	board[row][col] = new ItemUnit(newItem->getUnitChar(), newItem->getWalkOn(), newItem);
}
void Space::insertEmpty(int row, int col) {
	delete board[row][col];
	board[row][col] = new EmptyUnit();
}
void Space::insertEmpty(int row, int col, int transferRoom) {
	delete board[row][col];
	board[row][col] = new EmptyUnit(transferRoom);
}
void Space::insertVertical(int row, int col) {
	delete board[row][col];
	board[row][col] = new VertUnit();
}
void Space::insertHorizontal(int row, int col) {
	delete board[row][col];
	board[row][col] = new HorizUnit();
}

//check to see if item is next to current person location
bool Space::checkForItem(int& itemRow, int& itemCol) {
	if (this->board[personRow][personCol]->getTransferRoom() == 0) {
		if (this->board[personRow - 1][personCol]->getItemOccupied()) {
			itemRow = personRow - 1;
			return true;
		}
		else if(this->board[personRow + 1][personCol]->getItemOccupied()) {
			itemRow = personRow + 1;
			return true;
		}
		else if(this->board[personRow][personCol - 1]->getItemOccupied()) {
			itemCol = personCol - 1;
			return true;
		}
		else if(this->board[personRow][personCol + 1]->getItemOccupied()) {
			itemCol = personCol + 1;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

//setter methods
void Space::setTop(Space* top) {
	this->top = top;
}
void Space::setBottom(Space* bottom) {
	this->bottom = bottom;
}
void Space::setLeft(Space* left) {
	this->left = left;
}
void Space::setRight(Space* right) {
	this->right = right;
}
void Space::setPersonRow(int rowModify, bool defineRow) {
	if (!defineRow) {
		this->removePerson(this->getPersonRow(), this->getPersonCol());
		this->personRow += rowModify;
		this->setPersonOccupied(this->getPersonRow(), this->getPersonCol());
	}
	else {
		this->removePerson(this->getPersonRow(), this->getPersonCol());
		this->personRow = rowModify;
		this->setPersonOccupied(this->getPersonRow(), this->getPersonCol());
	}

}
void Space::setPersonCol(int colModify, bool defineCol) {
	if (!defineCol) {
		this->removePerson(this->getPersonRow(), this->getPersonCol());
		this->personCol += colModify;
		this->setPersonOccupied(this->getPersonRow(), this->getPersonCol());
	}
	else {
		this->removePerson(this->getPersonRow(), this->getPersonCol());
		this->personCol = colModify;
		this->setPersonOccupied(this->getPersonRow(), this->getPersonCol());
	}
}

//getter methods
Space* Space::getTop() {
	return this->top;
}
Space* Space::getBottom() {
	return this->bottom;
}
Space* Space::getLeft() {
	return this->left;
}
Space* Space::getRight() {
	return this->right;
}
int Space::getPersonRow() {
	return this->personRow;
}
int Space::getPersonCol() {
	return this->personCol;
}
int Space::getRoomNumber() {
	return this->roomNumber;
}
SpaceUnit*** Space::getBoard() {
	return this->board;
}
std::vector<Item*>& Space::getItemList() {
	return this->itemList;
}

