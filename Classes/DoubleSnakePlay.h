#ifndef __DOUBLESNAKE_PLAY_H_
#define __DOUBLESNAKE_PLAY_H_

#include "SnakesPlay.h"
#include "cocos2d.h"

class DoubleSnakePlay : public SnakesPlay {
public:
	virtual bool init();
	virtual void judge();
	virtual void scheUpdate(float);
	CREATE_FUNC(DoubleSnakePlay);
};

#endif // __DOUBLESNAKE_PLAY_H_