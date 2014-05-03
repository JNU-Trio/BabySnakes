#ifndef __FOOD_H_
#define __FOOD_H_

#include "cocos2d.h"
#include "MapAttribute.h"

/****抽象食物**********/
class Food{

public:
	/******生成食物 *******/
	virtual bool Generate(cocos2d::CCLayer *) = 0;

	/******获取食物位置*******/
	virtual Location GetLocation() = 0;

protected:
	/*********食物位置信息***********/
	Location f_location;

	/**********食物精灵***********/
	cocos2d::CCSprite *f_pictrue;

};

    /******简单食物*******/
class SimpleFood : public Food{


	bool Generate(cocos2d::CCLayer *);
	Location GetLocation();

};
#endif