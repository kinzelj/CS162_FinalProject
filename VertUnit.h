/*********************************************************************
* VertUnit class is an derived SpaceUnit class. This object represents
* each board space that is occupied by the '|' character.
**********************************************************************/
#ifndef VERTUNIT_H
#define VERTUNIT_H
#include "SpaceUnit.h"
class VertUnit : public SpaceUnit {
private:
	static const char unitChar = '|';
	static const bool walkOn = false;
public:
	VertUnit();
	~VertUnit() {}
	Item* getItem() { return nullptr; }
};
#endif // !VERTUNIT_H
