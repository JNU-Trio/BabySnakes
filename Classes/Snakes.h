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
	virtual bool moveTo(Location)=0;

	// 蛇吃食物
	virtual void eatFood(cocos2d::CCLayer *)=0;

	// 蛇的初始化
	virtual bool initialize(cocos2d::CCLayer *, SnakeLocation, SnakeImgFilename)=0;

	// 蛇的位置信息
	SnakeLocation m_snake;

	// 组成蛇的sprite集合
	cocos2d::CCSprite *m_shead, *m_stail;
	std::vector<cocos2d::CCSprite *> m_sbody;

	// 组成蛇的图片
	SnakeImgFilename m_snakeImage;
};

// 继承抽象蛇的简单蛇
class SimpleSnake : public Snake
{
	bool moveTo(Location);
	void eatFood(cocos2d::CCLayer *);
	bool initialize(cocos2d::CCLayer *, SnakeLocation, SnakeImgFilename);
};

class Control
{
public:
	virtual Location nextMove(SnakeLocation) = 0;
};

class AIControl : public Control
{
	Location nextMove(SnakeLocation);
};

class HumanControl : public Control
{
	Location nextMove(SnakeLocation);
};

class Food
{
public:
	Location m_locate;
	bool generate();
	cocos2d::CCNode *m_food;
};

class Barrier
{
public:
	std::vector<Location> m_locate;
	std::vector<cocos2d::CCSprite *> m_images;
	char *imgFilename;
	bool init(cocos2d::CCLayer *, const std::vector<Location> &, char *);
};

#endif // __SNAKES_H_