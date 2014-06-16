#ifndef __EFFECT_H__
#define __EFFECT_H__

#include "cocos2d.h"
#include <vector>

#include "MapAttribute.h"

class FoodEffect {
public:
	virtual void addScore(int){};
	virtual void reduceScore(int){};
	virtual void disappear(int){};
	virtual void beLonger(int){};
	virtual void beShorter(int){};
	virtual void addSpeed(int){};
};

#endif // __EFFECT_H__