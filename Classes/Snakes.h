#ifndef __SNAKES_H_
#define __SNAKES_H_

#include "cocos2d.h"
#include "MapAttribute.h"
#include <vector>

struct SnakeImgFilename
{
	char *head,*body,*tail;
};

// 抽象蛇
class Snake
{
public:
	// 蛇移向下一个位置
	virtual bool moveTo(SnakeLocation)=0;

	// 蛇吃食物
	virtual void eatFood(cocos2d::CCLayer *, SnakeLocation, SnakeImgFilename)=0;

	// 蛇的初始化
	virtual bool initialize(cocos2d::CCLayer *, SnakeLocation, SnakeImgFilename)=0;

	// 蛇的位置信息
	SnakeLocation m_snake;

	// 组成蛇的sprite集合
	cocos2d::CCSprite *m_shead, *m_stail;
	std::vector<cocos2d::CCSprite *> m_sbody;
};

// 继承抽象蛇的简单蛇
class SimpleSnake : public Snake
{
	bool moveTo(SnakeLocation);
	void eatFood(cocos2d::CCLayer *, SnakeLocation, SnakeImgFilename);
	bool initialize(cocos2d::CCLayer *, SnakeLocation, SnakeImgFilename);
};

class Control
{
public:
	virtual SnakeLocation nextMove(SnakeLocation) = 0;
};

class AIControl : public Control
{
	SnakeLocation nextMove(SnakeLocation);
};

class HumanControl : public Control
{
	SnakeLocation nextMove(SnakeLocation);
};

class Food
{
public:
	Location m_locate;
	bool generate();
	cocos2d::CCNode *food;
};

#endif // __SNAKES_H_