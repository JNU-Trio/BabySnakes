#ifndef __SNAKES_H_
#define __SNAKES_H_

#include "cocos2d.h"
#include "MapAttribute.h"
#include <vector>

struct SnakeImgFilename {
	char *head,*body,*tail;
};

// Abstract class of Snakes
class Snake {
public:
    // virtual method of snake move to next location
	virtual bool moveTo(Location)=0;

    // virtual method of snake eat food
	virtual void eatFood(cocos2d::CCLayer *)=0;

    // initialize the display of snake on the Layer
	virtual bool initialize(cocos2d::CCLayer *, SnakeLocation, SnakeImgFilename)=0;

    // record the virtual location of this snake
	SnakeLocation m_snake;

    // record the sprite of head, body and tail
	cocos2d::CCSprite *m_shead, *m_stail;
	std::vector<cocos2d::CCSprite *> m_sbody;

    // record the snake's images file path
	SnakeImgFilename m_snakeImage;
};

// a kind of snake for control by inherit the Snake.class
class SimpleSnake : public Snake {
	bool moveTo(Location);
	void eatFood(cocos2d::CCLayer *);
	bool initialize(cocos2d::CCLayer *, SnakeLocation, SnakeImgFilename);
};

// abstract class for giving the next move
class Control {
public:
	virtual Location nextMove(SnakeLocation) = 0;
};

// control by AI(writting algorithm yourself)
class AIControl : public Control {
	Location nextMove(SnakeLocation);
};

// control by player
class HumanControl : public Control {
	Location nextMove(SnakeLocation);
};

class Food {
public:
	Location m_locate;
	bool generate();
	cocos2d::CCNode *m_food;
};

class Barrier {
public:
	std::vector<Location> m_locate;
	std::vector<cocos2d::CCSprite *> m_images;
	char *imgFilename;
	bool init(cocos2d::CCLayer *, const std::vector<Location> &, char *);
};

#endif // __SNAKES_H_
