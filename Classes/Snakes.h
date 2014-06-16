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
	int getScore();
	SnakeLocation getSnakeLoc();
	virtual int count();

	virtual void updateVirtualMap();

	virtual bool moveTo(Location) = 0;
	virtual bool hitOther(SnakeLocation) = 0;
	virtual bool hitBody() = 0;
	virtual bool hitFood(Location) = 0;
	virtual bool hitBarrier(Location) = 0;

	SnakeLocation m_snake;
	SnakeImgFilename m_snakeImage;

	cocos2d::CCSprite *m_shead, *m_stail;
	std::vector<cocos2d::CCSprite *> m_sbody;
    
	cocos2d::CCNode *father;

	int m_score;
	int m_tag;
	int m_updateSpeed;
	int m_timeCounter;

	bool m_victorFlag;
};

// a kind of snake for control by inherit the Snake.class
class SimpleSnake : public Snake {
public:
	bool moveTo(Location);
	void updateVirtualMap();
	int count();

	// food effect
	void addScore(int);
	void reduceScore(int);
	void beLonger(int);
	void beShorter(int);
	void addSpeed(int);
	void disappear(int);

	bool hitOther(SnakeLocation);
	bool hitBody();
	bool hitFood(Location);
	bool hitBarrier(Location);

	bool m_disapFlag;

private:
	void moveAction(SnakeLocation);
	bool comeBack();
};

class BossSnake : public SimpleSnake {
	void beLonger(int);
	void reduceScore(int);
};

#endif // __SNAKES_H_