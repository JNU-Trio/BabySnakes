#ifndef __FOOD_H__
#define __FOOD_H__

#include "cocos2d.h"
#include <vector>

#include "Effect.h"
#include "Control.h"
#include "MapAttribute.h"

class Food : public Control {
public :
	virtual bool generate() = 0;
	virtual void eatFood(FoodEffect *, Location) = 0;
	virtual void updateVirtualMap() = 0;
	virtual bool hitFood(Location);
	virtual Location nextMove(SnakeLocation){Location ret;return ret;};
	std::vector<Location> m_locate;
	std::vector<cocos2d::CCSprite *> m_sprite;
	cocos2d::CCNode *father;
	FoodEffect *m_foodEffect;
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

class DisappearFood : public Food {
public:
	bool generate();
	void eatFood(FoodEffect *, Location);
	void updateVirtualMap();
	bool hitFood(Location);

	std::vector<int> m_type;
	std::vector<char *> m_images;
};

class DiceFood : public Food {
public:
	bool generate();
	void eatFood(FoodEffect *, Location);
	void updateVirtualMap();
	bool hitFood(Location);

	int m_number;

	cocos2d::CCSprite *m_show;
	char *m_image;
	bool m_gone;

private:
	int m_time;
};

class MultiFood : public Food {
public:
	bool generate();
	void eatFood(FoodEffect *, Location);
	void updateVirtualMap();
	bool hitFood(Location);

	Location nextMove(SnakeLocation);

	std::vector<char *> m_images;
};

#endif // __FOOD_H__