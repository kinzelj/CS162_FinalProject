/*********************************************************************
* SpaceUnit class represents each individual board location for each 
* room in the game. This class in an abstract class that will be 
* inherited by each unique board location. 
**********************************************************************/
#ifndef SPACEUNIT_H
#define SPACEUNIT_H
#include "Item.h"
class SpaceUnit {
protected:
	char unitChar;
	bool walkOn;
	bool personOccupied;
	bool itemOccupied;
	int transferRoom;
	bool winGame;
public:
	SpaceUnit(char unitChar, bool walkOn);
	virtual ~SpaceUnit() {}
	char getUnitChar();
	bool getWalkOn();
	bool checkPerson();
	void setPersonOccupied(bool);
	int getTransferRoom();
	void setWinGame(bool);
	bool getWinGame();
	bool getItemOccupied();
	virtual Item* getItem() { return nullptr; }
	void setWalkOn(bool);
};
#endif // !SPACEUNIT_H
