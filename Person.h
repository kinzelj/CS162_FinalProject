/**********************************************************************
* Person class represents the player in the game and contains a vector
* for all items captured by player.
**********************************************************************/
#ifndef PERSON_H
#define PERSON_H
#include "Item.h"
#include <vector>
class Person {
private:
	std::vector<Item*> itemList;
	bool allKeys;
	const unsigned int MAX_ITEMS = 7;
public:
	Person();
	void addItem(Item*);
	Item* selectItem();
	void capturedAllKeys();
	std::vector<Item*>& getItemList();
	unsigned int getMaxItems();
};
#endif // !PERSON_H
