/*********************************************************************
* ItemUnit class is an derived SpaceUnit class. This object represents
* each board space that is occupied by and Item object. These board
* spaces can be walked on by the player and will prompt the Item
* specific actions when player occupies these spaces.
**********************************************************************/
#ifndef ITEMUNIT_H
#define ITEMUNIT_H
#include "SpaceUnit.h"
#include "Item.h"
class ItemUnit : public SpaceUnit {
private:
	Item* unitItem;
public:
	ItemUnit(char unitChar, bool walkOn, Item* newItem);
	~ItemUnit() {}
	Item* getItem();
};
#endif // !ITEMUNIT_H
