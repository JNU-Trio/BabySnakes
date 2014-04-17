#include "MapAttribute.h"
#include "cocos2d.h"

cocos2d::CCPoint LocToPos(Location loc)
{
	cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();
	cocos2d::CCPoint origin = cocos2d::CCDirector::sharedDirector()->getVisibleOrigin();
	cocos2d::CCPoint ret;
	ret.x = origin.x + (visibleSize.width/MAP_WIDTH*loc.x + visibleSize.width/MAP_WIDTH*(loc.x-1)) / 2;
	ret.y = origin.y + (visibleSize.height/MAP_HEIGHT*loc.y + visibleSize.height/MAP_HEIGHT*(loc.y-1)) / 2;
	return ret;
}