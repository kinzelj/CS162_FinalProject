/*********************************************************************
* SpaceUnit class represents each individual board location for each
* room in the game. This class in an abstract class that will be
* inherited by each unique board location.
**********************************************************************/
#include "SpaceUnit.h"
SpaceUnit::SpaceUnit(char unitChar, bool walkOn) :
	unitChar(unitChar),
	walkOn(walkOn)
	{
	this->personOccupied = false;
	this->transferRoom = 0;
	this->winGame = false;
	this->itemOccupied = false;
	}

bool SpaceUnit::checkPerson() {
	if (this->personOccupied) {
		return true;
	}
	else {
		return false;
	}
}

char SpaceUnit::getUnitChar() {
	return this->unitChar;
}
bool SpaceUnit::getWalkOn() {
	return this->walkOn;
}
int SpaceUnit::getTransferRoom() {
	return this->transferRoom;
}
bool SpaceUnit::getWinGame() {
	return this->winGame;
}
bool SpaceUnit::getItemOccupied() {
	return this->itemOccupied;
}

void SpaceUnit::setPersonOccupied(bool status) {
	this->personOccupied = status;
}
void SpaceUnit::setWinGame(bool winStatus) {
	this->winGame = true;
}
void SpaceUnit::setWalkOn(bool walkOnStatus) {
	this->walkOn = walkOnStatus;
}