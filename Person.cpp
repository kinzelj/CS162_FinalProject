/**********************************************************************
* Person class represents the player in the game and contains a vector
* for all items captured by player.
**********************************************************************/
#include "Person.h"
Person::Person() : allKeys(false) {}

void Person::addItem(Item* newItem) {
	if (this->itemList.size() < this->MAX_ITEMS) {
		this->itemList.push_back(newItem);
	}
	else {
		std::cout << "You cannot carry any more items.\n"
			"Press enter to continue...";
		std::cin.get();
	}
}

Item* Person::selectItem() {
	if (!itemList.empty()) {
		std::string itemListPrompt = "Select an item and press enter:";
		std::vector<std::string> itemMenu;
		for (size_t i = 0; i < itemList.size(); i++) {
			itemMenu.push_back(itemList[i]->getName());
		}
		itemMenu.push_back("Never Mind");
		unsigned int itemSelection = menu(itemMenu, itemMenu.size(), itemListPrompt);
		if (itemSelection == itemMenu.size()) {
			return nullptr;
		}
		return itemList[itemSelection - 1];
	}
	else {
		std::cout << "\nYou have no items." << std::endl;
		std::cout << "Pres enter to continue...";
		std::cin.get();
		return nullptr;
	}

}

void Person::capturedAllKeys() {
	this->allKeys = true;
}

std::vector<Item*>& Person::getItemList() {
	return this->itemList;
}

unsigned int Person::getMaxItems() {
	return this->MAX_ITEMS;
}