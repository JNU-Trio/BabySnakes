#ifndef __BARRIER_H__
#define __BARRIER_H__

#include "cocos2d.h"
#include <vector>

#include "MapAttribute.h"

class Barrier : cocos2d::CCObject {
public:
	std::vector<Location> m_wallLoc;
	std::vector<cocos2d::CCSprite *> m_wall;
	char *m_wallImg;

	std::vector<Location> m_barrierLoc;
	std::vector<cocos2d::CCSprite *> m_barrier;
	char *m_barrierImg;

	int m_tag;

	void updateVirtualMap();
};

#endif // __BARRIER_H__