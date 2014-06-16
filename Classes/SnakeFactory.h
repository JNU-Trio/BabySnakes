#ifndef __SNAKE_FACTORY_H_
#define __SNAKE_FACTORY_H_

#include "cocos2d.h"

#include "Snakes.h"

class SnakeFactory
{
public:
	SimpleSnake *createSimpleSnake(cocos2d::CCNode *, const int, const int);
	BossSnake *createBossSnake(cocos2d::CCNode *, const int, const int);
	SnakeImgFilename getSnakeImg(int);
	SnakeLocation getSnakeLoc(int);

	const static int SNAKEIMG_TYPE_WHITE = 1;
	const static int SNAKEIMG_TYPE_GREEN = 2;
	const static int SNAKEIMG_TYPE_FAHAI = 3;
	const static int SNAKEIMG_TYPE_ZHA = 4;
	const static int SNAKEIMG_TYPE_LI = 5;
	const static int SNAKEIMG_TYPE_BOSS = 6;
};

#endif // __SNAKE_FACTORY_H_

