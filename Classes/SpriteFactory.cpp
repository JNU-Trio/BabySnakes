#include "cocos2d.h"

#include "SpriteFactory.h"
#include "MapAttribute.h"

USING_NS_CC;

CCSprite* PlaySpriteFactory::getSprite(char *imgpath, Location loc)
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    CCSprite *ret = CCSprite::create(imgpath);
    CCSize contentSize = ret->getContentSize();

    ret->setScaleX(visibleSize.width/VirtualMap::MAP_WIDTH/contentSize.width);
    ret->setScaleY(visibleSize.height/VirtualMap::MAP_HEIGHT/contentSize.height);
	ret->setPosition(VirtualMap::LocToPos(loc));
	ret->setRotation(loc.direction);
    return ret;
}
