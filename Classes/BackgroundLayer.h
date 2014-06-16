#ifndef __BACKGROUND_LAYER_H__
#define __BACKGROUND_LAYER_H__

#include "cocos2d.h"
#include <vector>

#include "Snakes.h"

class SingleBackground : public cocos2d::CCLayer {
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// implement the "static node()" method manually
	CREATE_FUNC(SingleBackground);
};

class DoubleBackground : public cocos2d::CCLayer {
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// implement the "static node()" method manually
	CREATE_FUNC(DoubleBackground);
};

class DisappearBackground : public cocos2d::CCLayer {
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// implement the "static node()" method manually
	CREATE_FUNC(DisappearBackground);
};

class DiceBackground : public cocos2d::CCLayer {
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// implement the "static node()" method manually
	CREATE_FUNC(DiceBackground);
};

class BossBackground : public cocos2d::CCLayer {
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// implement the "static node()" method manually
	CREATE_FUNC(BossBackground);
};

#endif // __BACKGROUND_LAYER_H__
