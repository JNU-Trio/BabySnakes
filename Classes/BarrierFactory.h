#ifndef __BARRIER_FACTORY_H_
#define __BARRIER_FACTORY_H_

#include "cocos2d.h"
#include <vector>

#include "MapAttribute.h"
#include "Barrier.h"

class BarrierFactory
{
public:
	const static int BARRIER_TYPE_SINGLE = 1;
	const static int BARRIER_TYPE_DOUBLE = 2;
	const static int BARRIER_TYPE_DISAPPEAR = 3;
	const static int BARRIER_TYPE_ZHA = 4;
	const static int BARRIER_TYPE_DICE = 5;
	const static int BARRIER_TYPE_BOSS = 6;

	Barrier * createBarrier(cocos2d::CCNode *, const int);
	std::vector<Location> getWallsLoc(const int);
	std::vector<Location> getBarrierLoc(const int);
	char *getWallsImg(const int);
	char *getBarrierImg(const int);
};

#endif // __BARRIER_FACTORY_H_

