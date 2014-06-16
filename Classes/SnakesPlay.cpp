#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include <vector>

#include "SnakesPlay.h"
#include "FightScene.h"
#include "StartScene.h"
#include "GameOverLayer.h"
#include "InfoLayer.h"
#include "Snakes.h"
#include "Food.h"
#include "Barrier.h"
#include "SpriteFactory.h"
#include "SnakeFactory.h"
#include "BarrierFactory.h"
#include "FoodFactory.h"
#include "Control.h"

USING_NS_CC;

bool SnakesPlay::init() {
    if (!CCLayer::init())
        return false;

	m_updateTime = VirtualMap::MIN_SPEED;

	// set touchdispatcher and schedule method
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    this->setTouchEnabled(true);

    return true;
}

void SnakesPlay::checkGame() {
	for(int i=0; i<m_snakes.size(); i++) {
		if (m_barrier->hitBarrier(m_snakes[i]->getSnakeLoc().head))
			m_snakes[i]->m_victorFlag = false;
		else if (m_snakes[i]->hitBody())
			m_snakes[i]->m_victorFlag = false;
		for(int j=0; j<m_snakes.size(); j++)
			if (i != j && m_snakes[i]->hitOther(m_snakes[j]->getSnakeLoc()))
				m_snakes[i]->m_victorFlag = false;
	}
}

// rewrite touch method
bool SnakesPlay::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* pevent) {
    m_disFlag = false;
    return true;
}

void SnakesPlay::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* pevent) {
    if (!m_disFlag) {
        CCPoint startpos = touch->getStartLocation();
        CCPoint curpos = touch->getLocation();
        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        if (ccpDistance(startpos,curpos) > visibleSize.height/8) {
            CCPoint judge = ccpSub(ccpRotateByAngle(ccpMidpoint(curpos,startpos), startpos, CC_DEGREES_TO_RADIANS(45)),startpos);
            if (judge.x > 0) {
                if (judge.y > 0) { // right
                    VirtualMap::DIRECTION = 2;
                }
                else { // down
                    VirtualMap::DIRECTION = 3;
                }
            }
            else {
                if (judge.y > 0) { // up
                    VirtualMap::DIRECTION = 1;
                }
                else { // left
                    VirtualMap::DIRECTION = 0;
                }
            }
            m_disFlag = true;
        }
    }
}

void SnakesPlay::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* pevent) {
}

void SnakesPlay::StopGameCallback(CCObject* pSender){
    if(!m_stopFlag){
        CCDirector::sharedDirector()->pause();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
        m_stopFlag = true;
    }
    else{
        CCDirector::sharedDirector()->resume();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
        m_stopFlag = false;
    }
}