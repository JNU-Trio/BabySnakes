#ifndef __SNAKES_H_
#define __SNAKES_H_

#include "cocos2d.h"
#include "MapAttribute.h"
#include <vector>

// 抽象蛇
class Snake
{
public:
	// 蛇移向下一个位置
	virtual Location moveTo()=0;

	// 蛇吃食物
	virtual void eatFood()=0;

	// 蛇的初始化
	virtual bool initialize(cocos2d::CCLayer *)=0;

protected:

	// 蛇的位置信息
	Location m_head, m_tail;
	std::vector<Location> m_body;

	// 组成蛇的sprite集合
	cocos2d::CCSprite *m_shead, *m_stail;
	std::vector<cocos2d::CCSprite *> m_sbody;
};

// 继承抽象蛇的简单蛇
class SimpleSnake : public Snake
{
	Location moveTo();
	void eatFood();
	bool initialize(cocos2d::CCLayer *);
};

#endif // __SNAKES_H_