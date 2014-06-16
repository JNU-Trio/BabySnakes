#ifndef __BOSSSNAKE_PLAY_H_
#define __BOSSSNAKE_PLAY_H_

#include "SnakesPlay.h"
#include "cocos2d.h"

class BossSnakePlay : public SnakesPlay {
public:
	virtual bool init();
	virtual void judge();
	virtual void scheUpdate(float);
	CREATE_FUNC(BossSnakePlay);
};

#endif // __BOSSSNAKE_PLAY_H_