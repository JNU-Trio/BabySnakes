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

CCSprite *BgSpriteFactory::getSprite(char *bgimg, Location tmp) {
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    // create background sprite
    CCSprite* pSprite = CCSprite::create(bgimg);
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    CCSize bgimgSize = pSprite->getContentSize();
    pSprite->setScaleX(visibleSize.width/bgimgSize.width);
    pSprite->setScaleY(visibleSize.height/bgimgSize.height);

	return pSprite;
}