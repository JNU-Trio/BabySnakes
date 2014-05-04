#include "MapAttribute.h"
#include "cocos2d.h"
#include <vector>

int VirtualMap::DIRECTION = 0;
float VirtualMap::SPEED = 0.15;
Location VirtualMap::foodLocate;

cocos2d::CCPoint VirtualMap::LocToPos(Location loc)
{
	cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();
	cocos2d::CCPoint origin = cocos2d::CCDirector::sharedDirector()->getVisibleOrigin();
	cocos2d::CCPoint ret;
	ret.x = origin.x + (visibleSize.width/VirtualMap::MAP_WIDTH*loc.x + visibleSize.width/VirtualMap::MAP_WIDTH*(loc.x-1)) / 2;
	ret.y = origin.y + (visibleSize.height/VirtualMap::MAP_HEIGHT*loc.y + visibleSize.height/VirtualMap::MAP_HEIGHT*(loc.y-1)) / 2;
	return ret;
}