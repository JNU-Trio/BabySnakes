#ifndef __MAP_ATTRIBUTE_H_
#define __MAP_ATTRIBUTE_H_

#include "cocos2d.h"

struct Location
{
	int x,y;
	bool operator==(const Location &src)
	{
		if (x == src.x && y == src.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

struct SnakeLocation
{
	Location head,tail;
	std::vector<Location> body;
};

class VirtualMap
{
public:
	static const int MAP_WIDTH = 20;
	static const int MAP_HEIGHT = 12;
	static float SPEED;

	static int DIRECTION;

	static Location foodLocate;

	static cocos2d::CCPoint LocToPos(Location);
};

#endif // __MAP_ATTRIBUTE_H_