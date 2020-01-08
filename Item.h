/**********************************************************************
* Item class represents each Item in the game. These include all 
* objects that are picked up and moved around by the player, as well
* as any stationary item that the player can interact with. 
* Each item will have a specific action method that will be called 
* when selected by user.
**********************************************************************/
#ifndef ITEMS_H
#define ITEMS_H
#include <string>
#include <iostream>
#include "menu.h"
#include "intValidation.h"
class Item {
protected:
	std::string itemName;
	std::string itemType;
	bool walkOn;
	char unitChar;
	int itemKey;
	char marking;
	bool specialItem;
	std::vector<Item*> extraItems;
	bool nightstandPrompt;
	bool ventPrompt;
	bool nightstandMove;
	bool doorOpen;

public:
	Item(std::string name, std::string type, bool walkOn, 
		char unitChar, int itemKey, char marking, bool specialItem);
	void investigateItem();
	bool itemAction();

	std::string getType();
	std::string getName();
	bool getWalkOn();
	char getUnitChar();
	int getItemKey();
	bool getSpecialItem();
	void addItem(Item*);
	std::vector<Item*>& getItemList();
	bool getNightstandPrompt();
	bool getVentPrompt();
	bool getNightstandMove();
	bool getDoorOpen();
	void setNightstandMove(bool);
	void setDoorOpen(bool);
	void setVentPrompt(bool);
	void resetGame();
};
#endif // !ITEMS_H
