#ifndef __DICESNAKE_PLAY_H_
#define __DICESNAKE_PLAY_H_

#include "cocos2d.h"

#include "SnakesPlay.h"

class DiceSnakePlay : public SnakesPlay {
public:
	virtual bool init();
	virtual void judge();
	virtual void scheUpdate(float);
	CREATE_FUNC(DiceSnakePlay);
};

#endif // __DICESNAKE_PLAY_H_