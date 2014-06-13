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

	// set touchdispatcher and schedule method
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    this->setTouchEnabled(true);
    m_updateTime = 0.3;
    this->schedule(schedule_selector(SnakesPlay::scheUpdate),m_updateTime);

    return true;
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

void SnakesPlay::scheUpdate(float time) {/*
	for(int i=1; i<=VirtualMap::MAP_WIDTH; i++)
	{
		char tmp[50];
		for(int j=1; j<=VirtualMap::MAP_HEIGHT; j++)
		{
			tmp[j-1] = VirtualMap::map[i][j] + '0';
		}
		tmp[VirtualMap::MAP_HEIGHT] = 0;
		CCLOG("%s",tmp);
	}
	CCLOG("\n");*/
	std::vector<Location> nextLocs;
    for(int i=0; i<m_snakes.size(); i++) {
		m_snakes[i]->m_victorFlag = true;
		nextLocs.push_back(m_controls[i]->nextMove(m_snakes[i]->m_snake));
    }

	for(int i=0; i<m_snakes.size(); i++) {
		if (m_snakes[i]->hitBarrier(nextLocs[i]))
			m_snakes[i]->m_victorFlag = false;
		else if (m_snakes[i]->hitBody(nextLocs[i]))
			m_snakes[i]->m_victorFlag = false;
		else if (m_snakes[i]->hitOther(nextLocs[i]))
			m_snakes[i]->m_victorFlag = false;
	}

	for(int i=0; i<m_snakes.size(); i++) {
		m_snakes[i]->moveTo(nextLocs[i]);
    }

	judge(nextLocs);
}

void SnakesPlay::StopGameCallback(CCObject* pSender){
    if(!m_stopFlag){
        CCDirector::sharedDirector()->pause();
        m_stopFlag = true;
    }
    else{
        CCDirector::sharedDirector()->resume();
        m_stopFlag = false;
    }
}

bool DoubleSnakePlay::init() {
    if (!SnakesPlay::init())
        return false;

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    // init the map
    VirtualMap::init();

	BarrierFactory barrierfactory;
    m_barrier = barrierfactory.createBarrier(this,1);

    // generate food
    FoodFactory *foodfactory = new SimpleFoodFactory();
	m_food = foodfactory->createFood(this);
    m_food->generate();

    // create snakes
	SnakeFactory snakefactory;
	Snake *snake = snakefactory.createSimpleSnake(this,1);
    m_snakes.push_back(snake);
	snake = snakefactory.createSimpleSnake(this,2);
    m_snakes.push_back(snake);

	// create control
	m_controls.push_back(new HumanControl());
    m_controls.push_back(new AIControl());

    // game control button
    m_stopFlag = false;
    CCMenuItemImage *StopGameItem = CCMenuItemImage::create("buttons/pause.png", "buttons/pause.png");
    CCMenuItemImage *StartGameItem = CCMenuItemImage::create("buttons/play.png", "buttons/play.png");
    CCMenuItemToggle *StopOrStartItem = CCMenuItemToggle::createWithTarget(this,menu_selector(SnakesPlay::StopGameCallback), StopGameItem,StartGameItem, NULL);
    StopOrStartItem->setEnabled(true);
    StopOrStartItem->setScale(0.5);

    CCMenu* itemToggleMenu = CCMenu::create(StopOrStartItem, NULL);
    itemToggleMenu->setPosition(ccp(visibleSize.width-20, 20));
    this->addChild(itemToggleMenu, 1);

    return true;
}

void DoubleSnakePlay::judge(std::vector<Location> locs) {
	bool flag = true;
	for(int i=0; i<m_snakes.size(); i++) {
		if (!m_snakes[i]->m_victorFlag) {
			flag = false;
			break;
		}
	}
	if (flag) {
		for(int i=0; i<m_snakes.size(); i++) {
			if (m_food->hitFood(locs[i])) {
				m_food->eatFood(m_snakes[i], m_snakes[i]->m_snake.head);
				VirtualMap::m_CurScore[i] += 2;
			}
		}
	}
	else {
		CCDirector::sharedDirector()->pause();
		GameOverLayer *gameover = GameOverLayer::create();
		if (m_snakes[0]->m_victorFlag)
			gameover->getLabel()->setString("You Win!");
		else
			gameover->getLabel()->setString("You Lose!");
		this->addChild(gameover);
	}
}
