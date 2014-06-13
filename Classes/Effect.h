#ifndef __EFFECT_H__
#define __EFFECT_H__

#include "cocos2d.h"
#include <vector>

#include "MapAttribute.h"

class FoodEffect {
public:
	virtual void addScore(int) = 0;
	virtual void disappear() = 0;
	virtual void beLonger(int) = 0;
	virtual void beShorter(int) = 0;
};

#endif // __EFFECT_H__