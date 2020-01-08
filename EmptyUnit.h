/*********************************************************************
* EmptyUnit class is an derived SpaceUnit class. This class represents
* a blank space in a room that the player can walk on if accessible.
* EmptyUnit objects are also used to create custom boards for each
* room.
**********************************************************************/
#ifndef EMPTYUNIT_H
#define EMPTYUNIT_H
#include "SpaceUnit.h"
class EmptyUnit : public SpaceUnit {
private:
	static const char unitChar = ' ';
	static const bool walkOn = true;
public:
	EmptyUnit();
	EmptyUnit(int transferRoom);
	~EmptyUnit() {}
	Item* getItem() { return nullptr; }
};
#endif // !EMPTYUNIT_H
