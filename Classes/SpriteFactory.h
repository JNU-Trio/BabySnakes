#ifndef __SPRITEFACTORY_H_
#define __SPRITEFACTORY_H_

#include "cocos2d.h"

#include "MapAttribute.h"

class SpriteFactory {
public:
    virtual cocos2d::CCSprite* getSprite(char *, Location) = 0;
};

class PlaySpriteFactory : public SpriteFactory {
public:
    cocos2d::CCSprite* getSprite(char *, Location);
};

class BgSpriteFactory : public SpriteFactory {
public:
    cocos2d::CCSprite* getSprite(char *, Location);
};

#endif // __SPRITEFACTORY_H
