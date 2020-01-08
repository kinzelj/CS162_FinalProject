/*******************************************************************
* Game class controls all object instantiation and overall game
* structure. The Game class will handle all game scenarios and
* sequences. It is the central control for the entire game.
******************************************************************/
#include "Game.h"
Game::Game() {
	this->usedFlashlight = true;
	this->allKeys = false;
	this->nextToItem = false;
	this->reachVent = false;
	this->itemDropped = false;
	this->puzzlePickup = false;
	this->winGame = false;
	this->nightstandPrompt = false;


	//for testing
	this->allDoorsOpen = false;
	this->getAllKeys = false;
}

void Game::startGame() {
	this->promptIntro();
	bool quitGame = false;
	//promptStartGame();
	while (!quitGame) {
		setupRooms();
		setRoomPointers();
		setCurrentRoom(allRooms[0]);
		this->oxygen = 100;

		//print board
		#ifdef __unix__ 
				printf("\033c");
		#elif _WIN32
				WIN_32_ClearScreen();
		#else
		#endif
		std::cout << "OXYGEN REMAINING: " << int(this->oxygen) << "%";
		printCurrentBoard(currentRoom);

		//open all doors for testing
		if (allDoorsOpen == true) { this->openAllDoors(); }

		//start game simulation
		winGame = simulateGame();

		//after game over, prompt user for end of game options
		if (winGame) {
			this->promptOutro();
			#ifdef __unix__ 
				printf("\033c");
			#elif _WIN32
				WIN_32_ClearScreen();
			#else
			#endif
			std::string endGamePrompt = "YOU ESCAPED!\nChoose option and press enter:";
			std::string menu1 = "Play again";
			std::string menu2 = "Quit game";
			std::vector<std::string> endGameMenu = { menu1, menu2 };
			int menuChoice = menu(endGameMenu, endGameMenu.size(), endGamePrompt);
			switch (menuChoice) {
			case 1: {
				resetGame();
				break;
			}
			case 2: {
				quitGame = true;
				break;
			}
			}
		}
		else {
			#ifdef __unix__ 
				printf("\033c");
			#elif _WIN32
				WIN_32_ClearScreen();
			#else
			#endif
			std::string endGamePrompt = "YOU RAN OUT OF OXYGEN AND PASSED OUT.\nGAME OVER!\n\nChoose option and press enter:";
			std::string menu1 = "Try again";
			std::string menu2 = "Quit game";
			std::vector<std::string> endGameMenu = { menu1, menu2 };
			int menuChoice = menu(endGameMenu, endGameMenu.size(), endGamePrompt);
			switch (menuChoice) {
			case 1: {
				resetGame();
				break;
			}
			case 2: {
				quitGame = true;
				break;
			}
			}
		}
	}
}

void Game::promptIntro() {
#ifdef __unix__ 
	printf("\033c");
#elif _WIN32
	WIN_32_ClearScreen();
#else
#endif
	std::cout << "...Waking up in a cold dark room, you are laying on a cement floor. Your head is throbbing with pain.\n"
		"\n\"Where am I?\" you mumble.\n"
		"\n\"How did I get here?\"...\"Was I kidnapped?\"\n"
		"\nThe last thing you remember is driving home from work, parking your car in the driveway, then...nothing.\n"
		"After that you memory is blank...\n"
		"\nAs your eyes begin to come back into focus, all you can see is a dim light in the far corner of the room, "
		"\nand the only things visible are a bed and nightstand next to a single steel door.\nThe rest of the room is pitch black.\n"
		"\nYou sit up and rest your back against a hard metal surface. You look up and notice you are leaning against\na second "
		"door. \nWithout much hope, you reach up and attempt to open the door...as expected it's locked.\n"
		"\n\"Hello!\" you yell without any response. \"Someone Help!\"...\n"
		"\nListening for a response, all you hear is the hum of the air vent towards the back corner of the room.\n"
		"\nWithout any response you slowly stand up to inspect the room. As you walk into the light you suddenly\nhear the fan "
		"from the air vent power down to a complete stop.\n\"Well that's just great\" you sarcastically say to yourself.\n\nYou can't "
		"imagine you have that much time before your run out of oxygen. Trying to limit\nyour breathing, you frantically "
		"begin to search for anything to get you out of this room..."
		"\n\n[PRESS ENTER]";
	std::cin.get();
	std::cout << std::endl;
}

void Game::promptOutro() {
#ifdef __unix__ 
	printf("\033c");
#elif _WIN32
	WIN_32_ClearScreen();
#else
#endif
	std::cout << "As you open the door you feel a rush of fresh air enter the room.\n"
		"Just before you exit you notice a flashing red light in the upper corner of the room.\n"
		"\"Is that a camera?\" you say to yourself...\"What is happeining to me?\"\n"
		"\nYou take a deep breath and exit the room, terrified of what will happen next..."
		"\n[PRESS ENTER]";
	std::cin.get();
	std::cout << std::endl;
}

void Game::setupRooms() {
	allRooms[0] = new MainSpace();
	allRooms[1] = new VentSpace();
	allRooms[2] = new ShopSpace();
	allRooms[3] = new TunnelSpace();
	allRooms[4] = new HallwaySpace();
	allRooms[5] = new ClosetSpace();
}

void Game::setRoomPointers() {
	/***************************
	allRooms[0] = main space
	allRooms[1] = vent space
	allRooms[2] = shop space
	allRooms[3] = tunnel space
	allRooms[4] = hallway space 
	allRooms[5] = closet space
	***************************/

	//link main room pointers
	allRooms[0]->setLeft(allRooms[1]);
	allRooms[0]->setBottom(allRooms[3]);
	allRooms[0]->setRight(allRooms[4]);

	//link vent room pointers
	allRooms[1]->setRight(allRooms[0]);

	//link shop room pointers	
	allRooms[2]->setTop(allRooms[4]);
	allRooms[2]->setLeft(allRooms[5]);

	//link tunnel room pointers
	allRooms[3]->setTop(allRooms[0]);
	
	//link hallway room pointers
	allRooms[4]->setLeft(allRooms[0]);
	allRooms[4]->setBottom(allRooms[2]);

	//link closet room pointers
	allRooms[5]->setRight(allRooms[2]);
}

bool Game::simulateGame() {
	player = new Person();

	//get all keys for testing purposes
	if (getAllKeys == true) { this->allKeys = true; }

	//set initial endGame condition
	bool endGame = false;
	SpaceUnit*** currentBoard = this->currentRoom->getBoard();
	//loop through simulation until player reaches end square or runs out of life
	while (!endGame) {
		//get current board and position
		currentBoard = this->currentRoom->getBoard();
		int personRow = this->currentRoom->getPersonRow();
		int personCol = this->currentRoom->getPersonCol();

		//check allKeys condition met
		this->checkAllKeys();

		//call next move
		this->nextMove(personRow, personCol, currentBoard);
		this->oxygen -= this->OXYGEN_PER_MOVE;

		//get current board and position
		currentBoard = this->currentRoom->getBoard();
		personRow = this->currentRoom->getPersonRow();
		personCol = this->currentRoom->getPersonCol();

		//print current board
		#ifdef __unix__ 
				printf("\033c");
		#elif _WIN32
				WIN_32_ClearScreen();
		#endif
		std::cout << "OXYGEN REMAINING: " << int(this->oxygen) << "%";
		this->printCurrentBoard(currentRoom);

		//call itemFound method to check if player is on top of item
		if (!this->itemDropped) {
			this->itemFound(personRow, personCol, currentBoard);
		}
		else {
			this->itemDropped = false;
		}

		//if current position is win position return true
		if (currentBoard[personRow][personCol]->getWinGame()) {
			delete player;
			return true;
		}
		//if player dies, set endGame to true 
		if (this->oxygen <= 1) {
			endGame = true;
		}
	}
	delete player;
	return false;
}

void Game::printCurrentBoard(Space* currentBoard) {
	currentBoard->printBoard();
}

void Game::nextMove(int personRow, int personCol, SpaceUnit*** currentBoard) {
	SpaceUnit* currentSpace = currentBoard[personRow][personCol];
	std::vector<std::string> moveMenu = { "VIEW PLAYER ITEMS" };

	//check if player is next to item and add prompt to menu if true
	this->itemRow = currentRoom->getPersonRow();
	this->itemCol = currentRoom->getPersonCol();
	this->nextToItem = currentRoom->checkForItem(itemRow, itemCol);
	if (nextToItem && ((currentBoard[itemRow][itemCol]->getWalkOn() == false)
		|| (currentBoard[itemRow][itemCol]->getItem()->getSpecialItem() == true))) {
		std::string menu6 = "INSPECT ROOM ITEM";
		moveMenu.push_back(menu6);
	}

	//prompt next move
	std::cout << "User arrow keys to move, or select one of the following:\n";
	for (size_t i = 0; i < moveMenu.size(); i++) {
		std::cout << (i + 1) << ": " << moveMenu[i] << std::endl;
	}

	//get user input
	int userMove;
	#ifdef __unix__ 
	int move = getchar();
	if (move == 27) { // if the first value is esc
		getchar(); // skip the [
		userMove = getchar();
	}
	else {
		userMove = move;
	}
	switch (userMove) {
		//Up
	case 'A': {
		//if current space is transfer room space, go to room if correct direction moved
		int moveDirection = 2;
		if (moveDirection == currentSpace->getTransferRoom()) {
			//if going from tunnel to main room, subtract oxygen
			if (this->currentRoom->getRoomNumber() == 4) {
				this->oxygen -= 10;
				std::cout << "You used alot of oxygen crawling through the tunnel. Need to be careful to not use so much energy.\n"
					<< "Press enter to continue...";
				std::cin.get();
			}
			this->setCurrentRoom(currentRoom->getTop());
			break;
		}
		//else move player to next spot. Check first if next space walkOn equals true
		if (currentBoard[personRow - 1][personCol]->getWalkOn()) {
			this->currentRoom->setPersonRow(-1, false);
		}
		break;
	}
	//Down
	case 'B': {
		//if current space is transfer room space, go to room if correct direction moved
		int moveDirection = 3;
		if (moveDirection == currentSpace->getTransferRoom()) {
			this->setCurrentRoom(currentRoom->getBottom());
			break;
		}
		//else move player to next spot. Check first if next space walkOn equals true
		if (currentBoard[personRow + 1][personCol]->getWalkOn()) {
			this->currentRoom->setPersonRow(1, false);
		}
		break;
	}
	//Right
	case 'C': {
		//if current space is transfer room space, go to room if correct direction moved
		int moveDirection = 4;
		if (moveDirection == currentSpace->getTransferRoom()) {
			this->setCurrentRoom(currentRoom->getRight());
			break;
		}
		//else move player to next spot. Check first if next space walkOn equals true
		if (currentBoard[personRow][personCol + 1]->getWalkOn()) {
			this->currentRoom->setPersonCol(1, false);
		}
		break;
	}
				 //Left
	case 'D': {
		//if current space is transfer room space, go to room if correct direction moved
		int moveDirection = 1;
		if (moveDirection == currentSpace->getTransferRoom()) {
			this->setCurrentRoom(currentRoom->getLeft());
			break;
		}
		//else move player to next spot. Check first if next space walkOn equals true
		if (currentBoard[personRow][personCol - 1]->getWalkOn()) {
			this->currentRoom->setPersonCol(-1, false);
		}
		break;
	}

				 //Check items
	case '1': {
		Item* itemSelection = this->player->selectItem();
		if (itemSelection != nullptr) {
			std::string menuPrompt = "Choose option and press enter:";
			std::string menu1 = "Use Item";
			std::string menu2 = "Drop Item";
			std::string menu3 = "Never Mind";
			std::vector<std::string> menuOptions = { menu1, menu2, menu3 };
			int menuChoice = menu(menuOptions, menuOptions.size(), menuPrompt);
			switch (menuChoice) {
			case 1: {
				this->useItem(itemSelection);
				break;
			}
			case 2: {
				this->dropItem(itemSelection);
				break;
			}
			case 3: {
				break;
			}
			}
		}
		break;
	}
				 //Inspect item
	case '2': {
		if (moveMenu.size() == 2) {
			//check for vent prompt in main room
			if (allRooms[0]->getItemList()[4]->getVentPrompt() == true) {
				//if true set current item ventPrompt to true. This will be used to determine which nightstand prompt to use
				currentBoard[itemRow][itemCol]->getItem()->setVentPrompt(true);
			}
			//check for nightStand move condition
			if (allRooms[0]->getItemList()[1]->getNightstandMove() == true) {
				//if true set current item nightstand move condition to true 
				currentBoard[itemRow][itemCol]->getItem()->setNightstandMove(true);
			}
			std::string chooseItemPrompt = "Choose option and press enter:";
			std::string menu1 = "Investigate Item";
			std::string menu2 = "Use/Open Item";
			std::vector<std::string> menuOptions = { menu1, menu2 };
			int menuChoice = menu(menuOptions, menuOptions.size(), chooseItemPrompt);
			switch (menuChoice) {
			case 1: {
				//investigate item
				currentBoard[itemRow][itemCol]->getItem()->investigateItem();
				break;
			}
			case 2: {
				Item* itemSelection = currentBoard[itemRow][itemCol]->getItem();
				if (itemSelection != nullptr) {
					this->useItem(itemSelection);
				}
				break;
			}
			}
			break;
		}
	}
	default: {
		std::cout << "Invalid Input. Press enter to continue...";
		std::cin.get();
		break;
	}
	}

	#elif _WIN32
	int move = _getch();
	if (move == 224) { // if the first value is esc
		userMove = _getch();
	}
	else {
		userMove = move;
		_getch();
	}

	switch (userMove) {
		//Up
	case 72: {
		//if current space is transfer room space, go to room if correct direction moved
		int moveDirection = 2;
		if (moveDirection == currentSpace->getTransferRoom()) {
			//if going from tunnel to main room, subtract oxygen
			if (this->currentRoom->getRoomNumber() == 4) {
				this->oxygen -= 10;
				std::cout << "You used alot of oxygen crawling through the tunnel. Need to be careful to not use so much energy.\n"
					<< "Press enter to continue...";
				std::cin.get();
			}
			this->setCurrentRoom(currentRoom->getTop());
			break;
		}
		//else move player to next spot. Check first if next space walkOn equals true
		if (currentBoard[personRow - 1][personCol]->getWalkOn()) {
			this->currentRoom->setPersonRow(-1, false);
		}
		break;
	}
				//Down
	case 80: {
		//if current space is transfer room space, go to room if correct direction moved
		int moveDirection = 3;
		if (moveDirection == currentSpace->getTransferRoom()) {
			this->setCurrentRoom(currentRoom->getBottom());
			break;
		}
		//else move player to next spot. Check first if next space walkOn equals true
		if (currentBoard[personRow + 1][personCol]->getWalkOn()) {
			this->currentRoom->setPersonRow(1, false);
		}
		break;
	}
				//Right
	case 77: {
		//if current space is transfer room space, go to room if correct direction moved
		int moveDirection = 4;
		if (moveDirection == currentSpace->getTransferRoom()) {
			this->setCurrentRoom(currentRoom->getRight());
			break;
		}
		//else move player to next spot. Check first if next space walkOn equals true
		if (currentBoard[personRow][personCol + 1]->getWalkOn()) {
			this->currentRoom->setPersonCol(1, false);
		}
		break;
	}
				//Left
	case 75: {
		//if current space is transfer room space, go to room if correct direction moved
		int moveDirection = 1;
		if (moveDirection == currentSpace->getTransferRoom()) {
			this->setCurrentRoom(currentRoom->getLeft());
			break;
		}
		//else move player to next spot. Check first if next space walkOn equals true
		if (currentBoard[personRow][personCol - 1]->getWalkOn()) {
			this->currentRoom->setPersonCol(-1, false);
		}
		break;
	}

	//Check items
	case '1': {
		Item* itemSelection = this->player->selectItem();
		if (itemSelection != nullptr) {
			std::string menuPrompt = "Choose option and press enter:";
			std::string menu1 = "Use Item";
			std::string menu2 = "Drop Item";
			std::string menu3 = "Never Mind";
			std::vector<std::string> menuOptions = { menu1, menu2, menu3 };
			int menuChoice = menu(menuOptions, menuOptions.size(), menuPrompt);
			switch (menuChoice) {
			case 1: {
				this->useItem(itemSelection);
				break;
			}
			case 2: {
				this->dropItem(itemSelection);
				break;
			}
			case 3: {
				break;
			}
			}
		}
		break;
	}
	//Inspect item
	case '2': {
		if (moveMenu.size() == 2) {
			//check for vent prompt in main room
			if (allRooms[0]->getItemList()[4]->getVentPrompt() == true) {
				//if true set current item ventPrompt to true. This will be used to determine which nightstand prompt to use
				currentBoard[itemRow][itemCol]->getItem()->setVentPrompt(true);
			}
			//check for nightStand move condition
			if (allRooms[0]->getItemList()[1]->getNightstandMove() == true) {
				//if true set current item nightstand move condition to true 
				currentBoard[itemRow][itemCol]->getItem()->setNightstandMove(true);
			}
			std::string chooseItemPrompt = "Choose option and press enter:";
			std::string menu1 = "Investigate Item";
			std::string menu2 = "Use/Open Item";
			std::vector<std::string> menuOptions = { menu1, menu2 };
			int menuChoice = menu(menuOptions, menuOptions.size(), chooseItemPrompt);
			switch (menuChoice) {
			case 1: {
				//investigate item
				currentBoard[itemRow][itemCol]->getItem()->investigateItem();
				break;
			}
			case 2: {
				Item* itemSelection = currentBoard[itemRow][itemCol]->getItem();
				if (itemSelection != nullptr) {
					this->useItem(itemSelection);
				}
				break;
			}
			default: {
				break;
			}
			}
			break;
		}
	}
	default: {
		std::cout << "Invalid Input. Press enter to continue...";
		std::cin.get();
		break;
	}
	}
#endif
}

void Game::itemFound(int personRow, int personCol, SpaceUnit*** currentBoard) {
	SpaceUnit* currentUnit = currentBoard[personRow][personCol];
	Item* currentItem = currentUnit->getItem();
	if (currentUnit->getItemOccupied()) {
		bool itemKeyPickup = currentItem->itemAction();
		if (itemKeyPickup) {
			this->player->addItem(currentItem);
			std::cout << "\nItem picked up.\nPress enter to continue...";
			std::cin.get();
			//replace current ItemUnit with EmptyUnit
			currentRoom->insertEmpty(personRow, personCol);
			currentUnit = currentBoard[personRow][personCol];
			//set new EmptyUnit to current person location
			currentUnit->setPersonOccupied(true);
		}
		if (!currentItem->getSpecialItem()) {
			#ifdef __unix__ 
						printf("\033c");
			#elif _WIN32
						WIN_32_ClearScreen();
			#endif
			this->printCurrentBoard(currentRoom);
		}
	}
}

void Game::useItem(Item* itemToUse) {
	switch (itemToUse->getItemKey()) {
	//Main door
	case 0: {
		if (this->allKeys) {
			this->openFinalDoor();
		}
		else {
			std::cout << "If you want to unlock this door it looks like you will need three keys.\n"
				<< "Press enter to continue...";
			std::cin.get();
		}
		break;
	}
	//Nightstand
	case 1: {
		//check nightstand prompt condition
		if (this->currentRoom->getItemList()[1]->getNightstandPrompt() == true
			|| this->currentRoom->getItemList()[4]->getVentPrompt() == true) {
			this->nightstandPrompt = true;
		}

		//if nightstand itemList is not empty and crossword hasn't been picked up
		if (itemToUse->getItemList().size() != 0 && puzzlePickup == false) {
			std::string chooseItemPrompt = "\nChoose option and press enter:";
			std::string menu1 = "Open drawer";
			std::vector<std::string> menuOptions = { menu1 };
			if (this->nightstandPrompt == true && itemToUse->getNightstandMove() == false) {
				std::string menu2 = "Move nightstand to vent";
				menuOptions.push_back(menu2);
			}
			std::string menu3 = "Do nothing";
			menuOptions.push_back(menu3);
			int menuChoice = menu(menuOptions, menuOptions.size(), chooseItemPrompt);;
			switch (menuChoice) {
			case 1: {
				std::cout << "\nOpening the nightstand drawer, you see there's a crossword puzzle:";
				std::string chooseItemPrompt = "\nChoose option and press enter:";
				std::string menu1 = "Pickup crossword puzzle";
				std::string menu2 = "Ignore crossword puzzle";
				std::vector<std::string> menuOptions = { menu1, menu2 };
				int menuChoice = menu(menuOptions, menuOptions.size(), chooseItemPrompt);
				switch (menuChoice) {
				case 1: {
					//add item to player inventory
					this->player->addItem(itemToUse->getItemList()[0]);
					this->puzzlePickup = true;
					//remove item from extraItems vector
					itemToUse->getItemList().erase(itemToUse->getItemList().begin());

					std::cout << "\nAs you pickup the crossword puzzle, something shiny is revealed in"
						" the back of the nightstand drawer.";

					//add key to nightstand itemList
					Item* keyC = this->currentRoom->getItemList()[3];
					itemToUse->addItem(keyC);

					//prompt user to pickup key
					std::string chooseKeyPrompt = "\nChoose option and press enter:";
					std::string keyMenu1 = "Pickup item";
					std::string keyMenu2 = "Ignore item";
					std::vector<std::string> menuOptions = { keyMenu1, keyMenu2, };
					int menuChoice = menu(menuOptions, menuOptions.size(), chooseKeyPrompt);
					switch (menuChoice) {
						case 1: {
							itemToUse->getItemList()[0]->investigateItem();
							//add item to player inventory
							this->player->addItem(itemToUse->getItemList()[0]);
							//remove item from extraItems vector
							itemToUse->getItemList().erase(itemToUse->getItemList().begin());

							std::cout << "\nKey picked up.";
							break;
						}
						case 2: {
							break;
						}
					}
					std::cout << "\nCrossword picked up.\nPress enter to continue...";
					std::cin.get();
					break;
				}
				case 2: {
					break;
				}
				}
				break;
			}
			case 2: {
				if (menuOptions.size() == 3) {
					this->currentRoom->insertItem(3, 1, this->currentRoom->getItemList()[1]);
					this->currentRoom->getBoard()[3][1]->setWalkOn(true);
					this->currentRoom->insertEmpty(1, 6);
					this->currentRoom->setPersonRow(3, true);
					this->currentRoom->setPersonCol(2, true);
					this->reachVent = true;
					itemToUse->setNightstandMove(true);
					this->oxygen -= 10;
					std::cout << "The Nightstand has been moved in front of vent.\n"
						<< "You used alot of oxygen moving the nighstand to the vent. Need to be careful to not use so much energy.\n"
						<< "Press enter to continue...";
					std::cin.get();
				}
			}
			case 3: {
				break;
			}
			}
		}

		//else if nightstand itemList is not empty and crossword has been picked up
		else if (itemToUse->getItemList().size() != 0 && puzzlePickup == true) {
			std::string chooseItemPrompt = "\nChoose option:";
			std::string menu1 = "Open drawer";
			std::vector<std::string> menuOptions = { menu1 };
			if (this->nightstandPrompt == true && itemToUse->getNightstandMove() == false) {
				std::string menu2 = "Move nightstand to vent";
				menuOptions.push_back(menu2);
			}
			std::string menu3 = "Do nothing";
			menuOptions.push_back(menu3);
			int menuChoice = menu(menuOptions, menuOptions.size(), chooseItemPrompt);
			switch (menuChoice) {
			case 1: {
				std::cout << "\nSomething shiny is revealed in the back of the nightstand drawer";
				std::string chooseItemPrompt = "\nChoose option:";
				std::string menu1 = "Pickup item";
				std::string menu2 = "Ignore item";
				std::vector<std::string> menuOptions = { menu1, menu2 };
				int menuChoice = menu(menuOptions, menuOptions.size(), chooseItemPrompt);
				switch (menuChoice) {
				case 1: {
					itemToUse->getItemList()[0]->investigateItem();
					//add item to player inventory
					this->player->addItem(itemToUse->getItemList()[0]);
					//remove item from extraItems vector
					itemToUse->getItemList().erase(itemToUse->getItemList().begin());

					std::cout << "\nKey picked up.\nPress enter to continue...";
					std::cin.get();
					break;
				}
				case 2: {
					break;
				}
				}
				break;
			}
			case 2: {
				if (menuOptions.size() == 3) {
					this->currentRoom->insertItem(3, 1, this->currentRoom->getItemList()[1]);
					this->currentRoom->getBoard()[3][1]->setWalkOn(true);
					this->currentRoom->insertEmpty(1, 6);
					this->currentRoom->setPersonRow(3, true);
					this->currentRoom->setPersonCol(2, true);
					this->reachVent = true;
					itemToUse->setNightstandMove(true);
					this->oxygen -= 10;
					std::cout << "The Nightstand has been moved in front of vent.\n"
						<< "You used alot of oxygen moving the nighstand to the vent. Need to be careful to not use so much energy.\n"
						<< "Press enter to continue...";;
					std::cin.get();
				};
			}
			case 3: {
				break;
			}
			}
		}

		//else if nightstand itemList is empty but nightstand has yet to be moved to vent
		else if (itemToUse->getItemList().size() == 0 && itemToUse->getNightstandMove() == false) {
			std::string chooseItemPrompt = "\nChoose option and press enter:";
			std::string menu1 = "Open drawer";
			std::vector<std::string> menuOptions = { menu1 };
			if (this->nightstandPrompt == true && itemToUse->getNightstandMove() == false) {
				std::string menu2 = "Move nightstand to vent";
				menuOptions.push_back(menu2);
			}
			std::string menu3 = "Do nothing";
			menuOptions.push_back(menu3);
			int menuChoice = menu(menuOptions, menuOptions.size(), chooseItemPrompt);
			switch (menuChoice) {
			case 1: {
				std::cout << "Drawer is empty.\nPress enter to continue...";
				std::cin.get();
				break;
			}
			case 2: {
				if (menuOptions.size() == 3) {
					this->currentRoom->insertItem(3, 1, this->currentRoom->getItemList()[1]);
					this->currentRoom->getBoard()[3][1]->setWalkOn(true);
					this->currentRoom->insertEmpty(1, 6);
					this->currentRoom->setPersonRow(3, true);
					this->currentRoom->setPersonCol(2, true);
					this->reachVent = true;
					itemToUse->setNightstandMove(true);
					this->oxygen -= 10;
					std::cout << "The Nightstand has been moved in front of vent.\n"
						<< "You used alot of oxygen moving the nighstand to the vent. Need to be careful to not use so much energy.\n"
						<< "Press enter to continue...";;
					std::cin.get();
				}
				break;
			}
			case 3: {
				break;
			}
			}
		}

		//else just prompt user that nightstand is empty
		else {
			std::string chooseItemPrompt = "\nChoose option and press enter:";
			std::string menu1 = "Open drawer";
			std::string menu2 = "Do nothing";
			std::vector<std::string> menuOptions = { menu1, menu2 };
			int menuChoice = menu(menuOptions, menuOptions.size(), chooseItemPrompt);
			switch (menuChoice) {
			case 1: {
				std::cout << "Drawer is empty.\nPress enter to continue...";
				std::cin.get();
				break;
			}
			case 2: {
				break;
			}
			}
		}
		break;
	}
	
	//Crossword puzzle
	case 2: {
		itemToUse->investigateItem();
		break;
	}
	//Key C
	case 3: {
		//first check if next to item
		if (this->nextToItem) {
			//to use key, check if currently next to door
			int doorNumber = this->checkDoor();
			switch (doorNumber) {
				//if next to main door, call openFinalDoor method if player has all three keys
			case 0: {
				if (this->allKeys) {
					this->openFinalDoor();
				}
				else {
					std::cout << "You do not have all three keys to open this door.\n"
						<< "Press enter to continue...";
					std::cin.get();
				}
				break;
			}
			case 5: {
				//key 3 will unlock door 5
				this->currentRoom->getBoard()[7][10]->setWalkOn(true);
				this->currentRoom->getItemList()[5]->setDoorOpen(true);
				std::cout << "Door unlocked!\n" 
					<< "Press enter to continue...";
				std::cin.get();
				break;
			}
			case 10: {
				//key does not unlock door
				std::cout << "Key does not unlock this door.\n"
					<< "Press enter to continue...";
				std::cin.get();
				break;
			}
			case -1: {
				//not next to door
				std::cout << "You are not next to a door to unlock\n"
					<< "Press enter to continue...";
				std::cin.get();
				break;
			}
			}
		}
		else {
			std::cout << "You are not next to a door to unlock\n"
				<< "Press enter to continue...";
			std::cin.get();
		}
		break;
	}
	//Light
	case 4: {
		itemToUse->investigateItem();
		break;
	}
	//Hallway door
	case 5: {
		itemToUse->investigateItem();
		break;
	}
	//Vent
	case 6: {
		itemToUse->investigateItem();
		break;
	}
	//Hammer
	case 7: {
		itemToUse->investigateItem();
		break;
	}
	//Flashlight
	case 8: {
		if (currentRoom->getRoomNumber() == 1 && this->usedFlashlight) {
			this->currentRoom->insertEmpty(11, 1, 3);
			this->usedFlashlight = false;
			std::cout << "\nYou use the flashlight to investigate the room.\n"
				<< "As you scan the room you notice an opening in corner\n"
				<< "that looks large enough to fit through.\n"
				<< "Press enter to continue...";
			std::cin.get();
		}
		else {
			std::cout << "\nYou use the flashlight to investigate the room.\n"
				<< "Nothing out of the ordinary observed.\n"
				<< "Press enter to continue...";
			std::cin.get();
		}

		break;
	}
	//Key E
	case 9: {
		//first check if next to item
		if (this->nextToItem) {
			//to use key, check if currently next to door
			int doorNumber = this->checkDoor();
			switch (doorNumber) {
				//if next to main door, call openFinalDoor method if player has all three keys
			case 0: {
				if (this->allKeys) {
					this->openFinalDoor();
				}
				else {
					std::cout << "You do not have all three keys to open this door.\n"
						<< "Press enter to continue...";
					std::cin.get();
				}
				break;
			}
			case 5: {
				//key does not unlock door
				std::cout << "Key does not unlock this door.\n"
					<< "Press enter to continue...";
				std::cin.get();
				break;
			}
			case 10: {
				//key 9 will unlock door 10
				this->currentRoom->getBoard()[5][1]->setWalkOn(true);
				this->currentRoom->getItemList()[0]->setDoorOpen(true);
				std::cout << "Door unlocked!\n"
					<< "Press enter to continue...";
				std::cin.get();
				break;
			}
			case -1: {
				//not next to door
				std::cout << "You are not next to a door to unlock\n"
					<< "Press enter to continue...";
				std::cin.get();
				break;
			}
			}
		}
		else {
			std::cout << "You are not next to a door to unlock\n"
				<< "Press enter to continue...";
			std::cin.get();
		}
		break;
	}
	//Closet door
	case 10: {
		itemToUse->investigateItem();
		break;
	}
	//Screwdriver
	case 11: {
		if (currentRoom->getRoomNumber() == 1
			&& currentRoom->getPersonRow() == 3
			&& currentRoom->getPersonCol() == 1) {
			this->currentRoom->insertEmpty(3, 0, 1);
			std::cout << "Screwdrive used to open vent cover.\n"
				<< "Press enter to continue...";
			std::cin.get();
		}
		else {
			std::cout << "Nothing to use the screwdriver on.\n"
				<< "Press enter to continue...";
			std::cin.get();
		}
		break;
	}
	//Key S
	case 12: {
		//first check if next to item
		if (this->nextToItem) {
			//to use key, check if currently next to door
			int doorNumber = this->checkDoor();
			switch (doorNumber) {
				//if next to main door call openFinalDoor method
			case 0: {
				this->openFinalDoor();
				break;
			}
			case 5: {
				//key does not unlock door
				std::cout << "Key does not unlock this door.\n"
					<< "Press enter to continue...";
				std::cin.get();
				break;
			}
			case 10: {
				//key does not unlock door
				std::cout << "Key does not unlock this door.\n"
					<< "Press enter to continue...";
				std::cin.get();
				break;
			}
			case -1: {
				//not next to door
				std::cout << "You are not next to a door to unlock\n"
					<< "Press enter to continue...";
				std::cin.get();
				break;
			}
			}
		}
		else {
			std::cout << "You are not next to a door to unlock\n"
				<< "Press enter to continue...";
			std::cin.get();
		}
		break;
	}
	//Toolbox
	case 13: {
		std::cout << "You open a toolbox\n";
		if (!itemToUse->getItemList().empty()) {
			std::string chooseToolPrompt = "Items in toolbox:";
			std::vector<std::string> toolOptions;
			for (size_t i = 0; i < itemToUse->getItemList().size(); i++) {
				toolOptions.push_back(itemToUse->getItemList()[i]->getName());
			}
			int toolChoice = menu(toolOptions, toolOptions.size(), chooseToolPrompt);
			std::string chooseItemPrompt = "\nChoose option and press enter:";
			std::string menu1 = "Pickup " + itemToUse->getItemList()[toolChoice - 1]->getName();
			std::string menu2 = "Ignore item";
			std::vector<std::string> menuOptions = { menu1, menu2 };
			int menuChoice = menu(menuOptions, menuOptions.size(), chooseItemPrompt);
			switch (menuChoice) {
			case 1: {
				itemToUse->getItemList()[toolChoice - 1]->investigateItem();
				std::cout << std::endl << itemToUse->getItemList()[toolChoice - 1]->getName() << " picked up.\nPress enter to continue...";

				//add item to player inventory
				this->player->addItem(itemToUse->getItemList()[toolChoice - 1]);
				//remove item from extraItems vector
				itemToUse->getItemList().erase(itemToUse->getItemList().begin() + (toolChoice - 1));

				std::cin.get();
				break;
			}
			case 2: {
				break;
			}
			}

		}
		break;
	}
	}
}

void Game::dropItem(Item* itemSelection) {
	int personRow = this->currentRoom->getPersonRow();
	int personCol = this->currentRoom->getPersonCol();
	SpaceUnit* currentUnit = this->currentRoom->getBoard()[personRow][personCol];
	//first check if person is on a space that already contains an item 
	if (!currentUnit->getItemOccupied()) {
		//find index of item in player's itemList
		auto playerItems = this->player->getItemList();
		auto thisItem = std::find(playerItems.begin(), playerItems.end(), itemSelection);
		auto itemIndex = std::distance(playerItems.begin(), thisItem);
		//insert item space
		currentRoom->insertItem(personRow, personCol, itemSelection);
		//set player location
		currentRoom->setPersonOccupied(personRow, personCol);
		//delete item from player itemList
		this->player->getItemList().erase(this->player->getItemList().begin() + itemIndex);
		//set itemDropped condition to true
		this->itemDropped = true;
		std::cout << "Item dropped.\n"
			<< "Press enter to continue...";
		std::cin.get();
	}
	else {
		std::cout << "The space you're on is occupied so you cannot drop this item.\n"
			<< "Press enter to continue...";
		std::cin.get();
	}
}


//checkDoor method to determine if player is next to door to use key
int Game::checkDoor() {
	SpaceUnit* itemUnit = currentRoom->getBoard()[this->itemRow][this->itemCol];
	int currentItemKey = itemUnit->getItem()->getItemKey();
	//if one of the three doors, return door number
	if (currentItemKey == 0 || currentItemKey == 5 || currentItemKey == 10) {
		return currentItemKey;
	}
	else {
		return -1;
	}
}

void Game::openFinalDoor() {
	if (!this->currentRoom->getItemList()[0]->getDoorOpen()) {
		int keyOrder[3];
		//prompt user to select the three keys to determine which keyhole for each key
		std::string key1 = "Key C";
		std::string key2 = "Key E";
		std::string key3 = "Key S";
		std::vector<std::string> keyOptions = { key1, key2, key3 };
		for (size_t i = 0; i < 3; i++) {
			std::string keyMenuPrompt = "Choose key to place in keyhole #" + std::to_string(i + 1) + ":";
			int keyChoice = menu(keyOptions, keyOptions.size(), keyMenuPrompt);
			keyOrder[i] = keyChoice;
			keyOptions.erase(keyOptions.begin() + (keyChoice - 1));
		}
		if (keyOrder[0] == 2 && keyOrder[1] == 2 && keyOrder[2] == 1) {
			this->currentRoom->getBoard()[10][5]->setWalkOn(true);
			this->currentRoom->getItemList()[0]->setDoorOpen(true);
			std::cout << "\nDoor unlocked!\n" 
				"Press enter to continue...";
			std::cin.get();
		}
		else {
			std::cout << "\nKeys were inserted into door, but door handle didn't budge.\n"
				"Press enter to continue...";
			std::cin.get();
		}
	}
	else {
		std::cout << "Door already open!\n"
			"Press enter to continue...";
		std::cin.get();
	}


}

//open all doors method for testing purposes
void Game::openAllDoors() {
	//hallway door
	allRooms[0]->getBoard()[10][5]->setWalkOn(true);
	allRooms[0]->getItemList()[0]->setDoorOpen(true);
	//hallway door
	allRooms[0]->getBoard()[7][10]->setWalkOn(true);
	allRooms[0]->getItemList()[5]->setDoorOpen(true);
	//closet door
	allRooms[2]->getBoard()[5][1]->setWalkOn(true);
	allRooms[2]->getItemList()[0]->setDoorOpen(true);
	//vent
	allRooms[0]->insertEmpty(3, 0, 1);
	//tunnel
	allRooms[0]->insertEmpty(11, 1, 3);
}

//setter method to set current space player occupies 
void Game::setCurrentRoom(Space* currentRoom) {
	this->currentRoom = currentRoom;
}

void Game::resetGame() {
	//delete dynamic memory
	for (Space* space : this->allRooms) {
		delete space;
	}

	//reset game conditions
	this->usedFlashlight = true;
	this->allKeys = false;
	this->nextToItem = false;
	this->reachVent = false;
	this->itemDropped = false;
	this->puzzlePickup = false;
	this->winGame = false;
	this->nightstandPrompt = false;
}

//https://stackoverflow.com/questions/7469139/what-is-equivalent-to-getch-getche-in-linux
char Game::getchar() {
	char buf=0;
	#ifdef __unix__ 
	struct termios old={0};
	fflush(stdout);
	if(tcgetattr(0, &old)<0)
		perror("tcsetattr()");
	old.c_lflag&=~ICANON;
	old.c_lflag&=~ECHO;
	old.c_cc[VMIN]=1;
	old.c_cc[VTIME]=0;
	if(tcsetattr(0, TCSANOW, &old)<0)
		perror("tcsetattr ICANON");
	if(read(0,&buf,1)<0)
		perror("read()");
	old.c_lflag|=ICANON;
	old.c_lflag|=ECHO;
	if(tcsetattr(0, TCSADRAIN, &old)<0)
		perror ("tcsetattr ~ICANON");
	#endif
	return buf;
}

void Game::checkAllKeys() {
	bool key1 = false;
	bool key2 = false;
	bool key3 = false;
	for (size_t i = 0; i < player->getItemList().size(); i++) {
		if (player->getItemList()[i]->getItemKey() == 3) {
			key1 = true;
		}
		if (player->getItemList()[i]->getItemKey() == 9) {
			key2 = true;
		}
		if (player->getItemList()[i]->getItemKey() == 12) {
			key3 = true;
		}

		if (key1 && key2 && key3) {
			this->allKeys = true;
		}
		else {
			this->allKeys = false;
		}
	}
}

Game::~Game() {
	//delete dynamic memory
	for (Space* space : this->allRooms) {
		delete space;
	}
}