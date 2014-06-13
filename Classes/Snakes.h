#ifndef __SNAKES_H_
#define __SNAKES_H_

#include "cocos2d.h"
#include <vector>

#include "MapAttribute.h"
#include "Effect.h"

struct SnakeImgFilename {
	char *head,*body,*tail;
};

// Abstract class of Snakes
class Snake : public FoodEffect {
public:
	virtual void updateVirtualMap();
	virtual bool moveTo(Location);
	int getScore();
	bool hitOther(Location);
	bool hitBody(Location);
	bool hitFood(Location);
	bool hitBarrier(Location);

	SnakeLocation m_snake;
	SnakeImgFilename m_snakeImage;

	cocos2d::CCSprite *m_shead, *m_stail;
	std::vector<cocos2d::CCSprite *> m_sbody;
    
	cocos2d::CCNode *father;

	int m_score;
	int m_tag;

	bool m_victorFlag;
};

// a kind of snake for control by inherit the Snake.class
class SimpleSnake : public Snake {
public:
	bool moveTo(Location);
	void updateVirtualMap();

	// food effect
	void addScore(int);
	void disappear();
	void beLonger(int);
	void beShorter(int);
};

#endif // __SNAKES_H_
