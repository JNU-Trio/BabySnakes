#include "cocos2d.h"
#include <vector>

#include "BarrierFactory.h"
#include "SpriteFactory.h"
#include "MapAttribute.h"

Barrier *BarrierFactory::createBarrier(cocos2d::CCNode *fatherLayer, const int type) {
	SpriteFactory *factory = new PlaySpriteFactory();
	
	Barrier *barrier = new Barrier();

	barrier->m_wallLoc = getWallsLoc(type);
	barrier->m_wallImg = getWallsImg(type);
	for(int i=0; i<barrier->m_wallLoc.size(); i++) {
		barrier->m_wall.push_back(factory->getSprite(barrier->m_wallImg,barrier->m_wallLoc[i]));
		fatherLayer->addChild(barrier->m_wall[i]);
	}

	barrier->m_barrierLoc = getBarrierLoc(type);
	barrier->m_barrierImg = getBarrierImg(type);
	for(int i=0; i<barrier->m_barrierLoc.size(); i++) {
		barrier->m_barrier.push_back(factory->getSprite(barrier->m_barrierImg,barrier->m_barrierLoc[i]));
		fatherLayer->addChild(barrier->m_barrier[i]);
	}

	barrier->m_tag = VirtualMap::barrierTag;

	barrier->updateVirtualMap();

	return barrier;
}
std::vector<Location> BarrierFactory::getWallsLoc(const int type) {
	// create the begin locations of barriers and walls
    std::vector<Location> batmp;
    for(int i=1; i<=VirtualMap::MAP_WIDTH; i++) {
        Location p;
        p.x = i;
        p.y = 1;
        batmp.push_back(p);
        p.x = i;
        p.y = VirtualMap::MAP_HEIGHT;
        batmp.push_back(p);
    }

    for(int i=2; i<VirtualMap::MAP_HEIGHT; i++) {
        Location p;
        p.x = 1;
        p.y = i;
        batmp.push_back(p);
        p.x = VirtualMap::MAP_WIDTH;
        p.y = i;
        batmp.push_back(p);
    }

	return batmp;
}

std::vector<Location> BarrierFactory::getBarrierLoc(const int type) {
	std::vector<Location> batmp;
    for(int i=5; i<=8; i++) {
        Location p;
        p.x = i;
        p.y = 4;
        batmp.push_back(p);
    }

    for(int i=14; i<=17; i++) {
        Location p;
        p.x = i;
        p.y = 8;
        batmp.push_back(p);
    }
    Location p;
	p.x = 17;
	p.y = 7;
	batmp.push_back(p);
	return batmp;
}

char *BarrierFactory::getWallsImg(const int type) {
	char *img;
	switch(type)
	{
	case 1: img = "barriers/wall1.png"; break;
	}
	return img;
}

char *BarrierFactory::getBarrierImg(const int type) {
	char *img;
	switch(type)
	{
	case 1: img = "barriers/barrier1.png"; break;
	}
	return img;
}