#ifndef __MAP_ATTRIBUTE_H_
#define __MAP_ATTRIBUTE_H_

#include "cocos2d.h"

struct Location
{
	int x,y;
};

const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 12;

extern cocos2d::CCPoint LocToPos(Location);

#endif // __MAP_ATTRIBUTE_H_