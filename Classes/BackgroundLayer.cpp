#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include <vector>

#include "BackgroundLayer.h"
#include "SpriteFactory.h"

USING_NS_CC;

bool SingleBackground::init() {
    // super init first
    if ( !CCLayer::init() ) {
        return false;
    }
	SpriteFactory *factory = new BgSpriteFactory();
	Location tmp;
    this->addChild(factory->getSprite("backgrounds/background1.png",tmp), 0);

    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background-music.mp3", true);

    return true;
}

bool DoubleBackground::init() {
    // super init first
    if ( !CCLayer::init() ) {
        return false;
    }

    SpriteFactory *factory = new BgSpriteFactory();
	Location tmp;
    this->addChild(factory->getSprite("backgrounds/background2.png",tmp), 0);

    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background-music.mp3", true);

    return true;
}

bool DisappearBackground::init() {
    // super init first
    if ( !CCLayer::init() ) {
        return false;
    }

    SpriteFactory *factory = new BgSpriteFactory();
	Location tmp;
    this->addChild(factory->getSprite("backgrounds/background3.png",tmp), 0);

    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background-music.mp3", true);

    return true;
}

bool DiceBackground::init() {
    // super init first
    if ( !CCLayer::init() ) {
        return false;
    }

    SpriteFactory *factory = new BgSpriteFactory();
	Location tmp;
    this->addChild(factory->getSprite("backgrounds/background1.png",tmp), 0);

    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background-music.mp3", true);

    return true;
}

bool BossBackground::init() {
    // super init first
    if ( !CCLayer::init() ) {
        return false;
    }

    SpriteFactory *factory = new BgSpriteFactory();
	Location tmp;
    this->addChild(factory->getSprite("backgrounds/background6.png",tmp), 0);

    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background-music.mp3", true);

    return true;
}
