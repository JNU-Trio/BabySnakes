#ifndef __SINGLESNAKE_PLAY_H_
#define __SINGLESNAKE_PLAY_H_

#include "SnakesPlay.h"
class SingleSnakePlay : public SnakesPlay {
public:
	virtual bool init();
	virtual void judge();
	virtual void scheUpdate(float);
	CREATE_FUNC(SingleSnakePlay);
};

#endif // __SINGLESNAKE_PLAY_H_