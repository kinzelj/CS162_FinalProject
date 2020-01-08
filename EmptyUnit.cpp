/*********************************************************************
* EmptyUnit class is an derived SpaceUnit class. This class represents
* a blank space in a room that the player can walk on if accessible.
* EmptyUnit objects are also used to create custom boards for each
* room.
**********************************************************************/
#include "EmptyUnit.h"
EmptyUnit::EmptyUnit() : SpaceUnit(unitChar, walkOn) {
}

EmptyUnit::EmptyUnit(int transferRoom) : SpaceUnit (unitChar, walkOn) {
	this->transferRoom = transferRoom;
}
