#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include <vector>

#include "BackgroundLayer.h"

USING_NS_CC;

bool DoubleBackground::init() {
    // super init first
    if ( !CCLayer::init() ) {
        return false;
    }

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    // create background sprite
    CCSprite* pSprite = CCSprite::create("backgrounds/background1.png");
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    CCSize bgimgSize = pSprite->getContentSize();
    pSprite->setScaleX(visibleSize.width/bgimgSize.width);
    pSprite->setScaleY(visibleSize.height/bgimgSize.height);

    this->addChild(pSprite, 0);

    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background-music.mp3", true);

    return true;
}
