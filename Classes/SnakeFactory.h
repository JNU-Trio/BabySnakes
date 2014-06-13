#ifndef __SNAKE_FACTORY_H_
#define __SNAKE_FACTORY_H_

#include "cocos2d.h"

#include "Snakes.h"

class SnakeFactory
{
public:
	SimpleSnake *createSimpleSnake(cocos2d::CCNode *, const int type);
	SnakeImgFilename getSnakeImg(int);
	SnakeLocation getSnakeLoc(int);
};

#endif // __SNAKE_FACTORY_H_

