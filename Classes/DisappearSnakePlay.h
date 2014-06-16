#ifndef __DISAPPEARSNAKE_PLAY_H_
#define __DISAPPEARSNAKE_PLAY_H_

#include "SnakesPlay.h"

class DisappearSnakePlay : public SnakesPlay {
public:
	virtual bool init();
	virtual void judge();
	virtual void scheUpdate(float);
	CREATE_FUNC(DisappearSnakePlay);
};

#endif // __DISAPPEARSNAKE_PLAY_H_