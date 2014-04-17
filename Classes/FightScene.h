#ifndef __FIGHT_SCENE_H__
#define __FIGHT_SCENE_H__

#include "cocos2d.h"
#include "MapAttribute.h"
#include "Snakes.h"

#include <vector>

class FightScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(FightScene);

private:
	static const int m_playlayer_zOrder = 2;
	static const int m_bglayer_zOrder = 1;
	static const int m_playlayer_tag = 1;
	static const int m_bglayer_tag = 2;
};

class SnakesPlay : public cocos2d::CCLayer
{
public:
	virtual bool init();
	CREATE_FUNC(SnakesPlay);

private:
	std::vector<Snake *> m_snakes;
};

#endif // __FIGHT_SCENE_H__
