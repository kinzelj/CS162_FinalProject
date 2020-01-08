/*********************************************************************
* HorizUnit class is an derived SpaceUnit class. This object represents
* each board space that is occupied by the '-' character.
**********************************************************************/
#ifndef HORIZUNIT_H
#define HORIZUNIT_H
#include "SpaceUnit.h"
class HorizUnit : public SpaceUnit {
private:
	static const char unitChar = '-';
	static const bool walkOn = false;
public:
	HorizUnit();
	~HorizUnit() {}
	Item* getItem() { return nullptr; }
};
#endif // !HORIZUNIT_H

