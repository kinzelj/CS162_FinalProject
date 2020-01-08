/**********************************************************************
* Item class represents each Item in the game. These include all
* objects that are picked up and moved around by the player, as well
* as any stationary item that the player can interact with.
* Each item will have a specific action method that will be called
* when selected by user.
**********************************************************************/
#include "Item.h"
Item::Item(std::string name, std::string type, bool walkOn,
	char unitChar, int itemKey, char marking, bool specialItem) :
	itemName(name),
	itemType(type),
	walkOn(walkOn),
	unitChar(unitChar),
	itemKey(itemKey),
	marking(marking),
	specialItem(specialItem) {

	this->nightstandPrompt = false;
	this->nightstandMove = false;
	this->doorOpen = false;
}

char Item::getUnitChar() {
	return this->unitChar;
}
bool Item::getWalkOn() {
	return this->walkOn;
}
std::string Item::getName() {
	return this->itemName;
}

//itemAction method will only be called when player is on top of an item
bool Item::itemAction() {
	if (!this->specialItem) {
		std::cout << "\nYou found a " << this->getType() << "!" << std::endl;
		std::string menuPrompt = "What would you like to do:";
		std::string menu1 = "Investigate Item";
		std::string menu2 = "Pickup Item";
		std::string menu3 = "Ignore Item";
		std::vector<std::string> itemMenu{ menu1, menu2, menu3 };
		bool endSelection = false;
		while (!endSelection) {
			int userMove = menu(itemMenu, itemMenu.size(), menuPrompt);
			switch (userMove) {
			case 1: {
				this->investigateItem();
				break;
			}
			case 2: {
				return true;
			}
			case 3: {
				return false;
			}
			}
		}
	}
	return false;
}

void Item::addItem(Item* newItem) {
	this->extraItems.push_back(newItem);
}

std::vector<Item*>& Item::getItemList(){
	return extraItems;
}

void Item::investigateItem() {
	switch (itemKey) {
	//main door
	case 0: {
		if (!doorOpen) {
			std::cout << "\nThis door is locked."
				<< "\nThat's strange, it looks like there are three keyholes for this door.\n"
				<< "Press enter to continue...";
			std::cin.get();
		}
		else {
			std::cout << "\nDoor is open.\n"
				<< "Press enter to continue...";
			std::cin.get();
		}
		break;
	}
	//nightstand
	case 1: {
		if (nightstandMove == false && ventPrompt == true) {
			std::cout << "Looks like a typical nightstand with a single drawer.\n"
				<< "It seems to be just tall enough that if you stood on top you could reach the vent cover.\n"
				<< "Press enter to continue...";
			std::cin.get();
			this->nightstandPrompt = true;
		} 
		else {
			std::cout << "Looks like a typical nightstand with a single drawer.\n"
				<< "Press enter to continue...";
			std::cin.get();
		}
		break;
	}
	//crossword puzzle
	case 2: {
		std::cout << "\nReviewing the crossword puzzle, all problems were solved.\n"
			<< "However there was one solution in the puzzle that stood out.\n"
			<< "#13 Down solution read \"ESCAPE\", but oddly the first three letters (\"ESC\") were circled.\n"
			<< "Press enter to continue...";
		std::cin.get();
		break;
	}
	//key C
	case 3: {
		std::cout << "\nItem is a key that is marked with the letter \"C\".\n"
			"Press enter to continue...";
		std::cin.get();
		break;
	}
	case 4: {
		std::cout << "There's a dim light in the corner of the room.\n"
			"Press enter to continue...";
		std::cin.get();
		break;
	}
	//Hallway door
	case 5: {
		if (!doorOpen) {
			std::cout << "\nThis door is locked.\n"
				<< "Press enter to continue...";
			std::cin.get();
		}
		else {
			std::cout << "\nDoor is open.\n"
				<< "Press enter to continue...";
			std::cin.get();
		}
		break;
	}
	//vent
	case 6: {
		if (this->nightstandMove == false) {
			std::cout << "You can see a large air vent above you. "
				"If only you had something to stand on to get access to the vent cover.\n"
				"Mabye you could then remove the cover and escape through the air ducts.\n"
				"Press enter to continue...";
			this->ventPrompt = true;
			std::cin.get();
		}
		else {
			std::cout << "You use the nightstand to get access to the vent cover. \n"
				"Unfortunately you see that the vent is fastened securley with several small screws.\n"
				"There's no way of getting through the vent without some type of screwdriver.\n"
				"Press enter to continue...";
			std::cin.get();
		}
		break;
	}
	//hammer
	case 7: {
		std::cout << "\nStandard carpenters hammer. This may become useful."
			<< "\nPress enter to continue...";
		std::cin.get();
		break;
	}
	//flashlight
	case 8: {
		std::cout << "\nJust a flashlight. Luckily batteries still have some power.\n"
			<< "Press enter to continue...";
		std::cin.get();
		break;
	}
	//key E
	case 9: {
		std::cout << "\nItem is a key that is marked with the letter \"E\".\n"
			"Press enter to continue...";
		std::cin.get();
		break;
	}
	case 10: {
		if (!doorOpen) {
			std::cout << "\nThis door is locked.\n"
				<< "Press enter to continue...";
			std::cin.get();
		}
		else {
			std::cout << "\nDoor is open.\n"
				<< "Press enter to continue...";
			std::cin.get();
		}
		break;
	}
	//screwdriver
	case 11: {
		std::cout << "\nSmall phillips head screwdriver. Could be useful."
			<< "\nPress enter to continue...";
		std::cin.get();
		break;
		break;
	}
	//key S
	case 12: {
		std::cout << "\nItem is a key that is marked with the letter \"S\".\n"
			"Press enter to continue...";
		std::cin.get();
		break;
	}
	case 13: {
		std::cout << "You found a toolbox. Wonder what's inside.\n"
			"Press enter to continue...";
		std::cin.get();
		break;
	}
	}
} 
//getter methods
int Item::getItemKey() {
	return this->itemKey;
}
std::string Item::getType() {
	return this->itemType;
}
bool Item::getSpecialItem() {
	return this->specialItem;
}
bool Item::getNightstandPrompt() {
	return this->nightstandPrompt;
}
bool Item::getVentPrompt() {
	return this->ventPrompt;
}
bool Item::getNightstandMove() {
	return this->nightstandMove;
}
bool Item::getDoorOpen() {
	return this->doorOpen;
}
//setter methods
void Item::setNightstandMove(bool moveStatus) {
	this->nightstandMove = moveStatus;
}
void Item::setDoorOpen(bool doorStatus) {
	this->doorOpen = doorStatus;
}
void Item::setVentPrompt(bool ventStatus) {
	this->ventPrompt = ventStatus;
}

//reset game mehtod
void Item::resetGame() {
	this->nightstandPrompt = false;
	this->nightstandMove = false;
	this->doorOpen = false;
}