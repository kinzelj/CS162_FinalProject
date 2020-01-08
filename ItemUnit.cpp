/*********************************************************************
* ItemUnit class is an derived SpaceUnit class. This object represents
* each board space that is occupied by and Item object. These board
* spaces can be walked on by the player and will prompt the Item
* specific actions when player occupies these spaces.
**********************************************************************/
#include "ItemUnit.h"
ItemUnit::ItemUnit(char unitChar, bool walkOn, Item* newItem)
	: SpaceUnit(unitChar, walkOn) {
	this->unitItem = newItem;
	this->itemOccupied = true;
}

Item* ItemUnit::getItem() {
	return this->unitItem;
}
