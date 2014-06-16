#ifndef __FOOD_FACTORY_H_
#define __FOOD_FACTORY_H_

#include "cocos2d.h"

#include "MapAttribute.h"
#include "Food.h"
#include "Effect.h"

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

class DisappearFoodFactory : public FoodFactory {
public:
	Food *createFood(cocos2d::CCNode *);
	std::vector<char *> getImg();
};

class DiceFoodFactory : public FoodFactory {
public:
	Food *createFood(cocos2d::CCNode *);
	char *getImg();
	Location getLoc();
};

class MultiFoodFactory : public FoodFactory {
	Food *createFood(cocos2d::CCNode *);
	std::vector<char *> getImg();
	std::vector<Location> getLoc();
};

#endif // __FOOD_FACTORY_H_