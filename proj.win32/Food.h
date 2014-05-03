#ifndef __FOOD_H_
#define __FOOD_H_

#include "cocos2d.h"
#include "MapAttribute.h"

/****����ʳ��**********/
class Food{

public:
	/******����ʳ�� *******/
	virtual bool Generate(cocos2d::CCLayer *) = 0;

	/******��ȡʳ��λ��*******/
	virtual Location GetLocation() = 0;

protected:
	/*********ʳ��λ����Ϣ***********/
	Location f_location;

	/**********ʳ�ﾫ��***********/
	cocos2d::CCSprite *f_pictrue;

};

    /******��ʳ��*******/
class SimpleFood : public Food{


	bool Generate(cocos2d::CCLayer *);
	Location GetLocation();

};
#endif