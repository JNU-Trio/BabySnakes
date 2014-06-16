#ifndef __SNAKES_PLAY_H__
#define __SNAKES_PLAY_H__

#include "cocos2d.h"
#include <vector>

#include "MapAttribute.h"
#include "Snakes.h"
#include "Food.h"
#include "Barrier.h"
#include "Control.h"

class SnakesPlay : public cocos2d::CCLayer {
public:
	virtual bool init();
	virtual void checkGame();
	virtual void judge() = 0;
	virtual void scheUpdate(float) = 0;
    // implement touch event
	bool ccTouchBegan(cocos2d::CCTouch* , cocos2d::CCEvent*);
	void ccTouchMoved(cocos2d::CCTouch* , cocos2d::CCEvent*);
	void ccTouchEnded(cocos2d::CCTouch* , cocos2d::CCEvent*);

    // implement stop button
	void StopGameCallback(CCObject* pSender);
	
	Food *m_food;
	Barrier *m_barrier;

protected:
	bool m_disFlag;
    bool m_stopFlag;
    float m_updateTime;
    std::vector<Snake *> m_snakes;
	std::vector<Control *> m_controls;
};

#endif // __SNAKES_PLAY_H__
