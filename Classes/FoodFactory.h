#ifndef __FOOD_FACTORY_H_
#define __FOOD_FACTORY_H_

#include "cocos2d.h"

#include "MapAttribute.h"
#include "Food.h"

class FoodFactory {
public:
	virtual Food *createFood(cocos2d::CCNode *) = 0;
};

class SimpleFoodFactory : public FoodFactory {
public:
	Food *createFood(cocos2d::CCNode *);
	char *getImg();
	Location getLoc();
};

#endif // __FOOD_FACTORY_H_