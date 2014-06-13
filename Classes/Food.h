#ifndef __FOOD_H__
#define __FOOD_H__

#include "cocos2d.h"
#include <vector>

#include "Effect.h"
#include "MapAttribute.h"

class Food {
public :
	virtual bool generate() = 0;
	virtual void eatFood(FoodEffect *, Location) = 0;
	virtual void updateVirtualMap() = 0;
	virtual bool hitFood(Location);
	std::vector<Location> m_locate;
	std::vector<cocos2d::CCSprite *> m_sprite;
	int m_tag;
};

class SimpleFood : public Food {
public :
	bool generate();
	void eatFood(FoodEffect *, Location);
	void updateVirtualMap();
	bool hitFood(Location);

protected :
	const static int scoreNum = 2;
};

#endif // __FOOD_H__