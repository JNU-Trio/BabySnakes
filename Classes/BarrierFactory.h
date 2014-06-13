#ifndef __BARRIER_FACTORY_H_
#define __BARRIER_FACTORY_H_

#include "cocos2d.h"
#include <vector>

#include "MapAttribute.h"
#include "Barrier.h"

class BarrierFactory
{
public:
	Barrier * createBarrier(cocos2d::CCNode *, const int);
	std::vector<Location> getWallsLoc(const int);
	std::vector<Location> getBarrierLoc(const int);
	char *getWallsImg(const int);
	char *getBarrierImg(const int);
};

#endif // __BARRIER_FACTORY_H_

