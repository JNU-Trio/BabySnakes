#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "SingleSnakePlay.h"
#include "BarrierFactory.h"
#include "FoodFactory.h"
#include "SnakeFactory.h"
#include "GameOverLayer.h"

USING_NS_CC;

bool SingleSnakePlay::init() {
    if (!SnakesPlay::init())
        return false;

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    // init the map
    VirtualMap::init();

	BarrierFactory barrierfactory;
	m_barrier = barrierfactory.createBarrier(this,BarrierFactory::BARRIER_TYPE_SINGLE);

    // generate food
    FoodFactory *foodfactory = new SimpleFoodFactory();
	m_food = foodfactory->createFood(this);
    m_food->generate();

    // create snakes
	SnakeFactory snakefactory;
	Snake *snake = snakefactory.createSimpleSnake(this,SnakeFactory::SNAKEIMG_TYPE_WHITE,1);
    m_snakes.push_back(snake);

	// create control
	m_controls.push_back(new HumanControl());

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

    this->schedule(schedule_selector(SingleSnakePlay::scheUpdate),m_updateTime);

    return true;
}

void SingleSnakePlay::judge() {
	bool flag = true;
	for(int i=0; i<m_snakes.size(); i++) {
		if (!m_snakes[i]->m_victorFlag) {
			flag = false;
			break;
		}
	}
	if (m_snakes[0]->getScore() >= 20)
		flag = false;
	if (flag) {
		for(int i=0; i<m_snakes.size(); i++) {
			if (m_food->hitFood(m_snakes[i]->getSnakeLoc().head)) {
				m_food->eatFood(m_snakes[i], m_snakes[i]->getSnakeLoc().head);
				VirtualMap::m_CurScore[i] += 2;
			}
		}
	}
	else {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		CCScene *gameover;
		if (m_snakes[0]->m_victorFlag) {
			gameover = GameOverLayer::getScene(VirtualMap::SCENE_TYPE_SINGLE,true);
		} else {
			gameover = GameOverLayer::getScene(VirtualMap::SCENE_TYPE_SINGLE, false);
		}
		CCDirector::sharedDirector()->pushScene(gameover);
	}
}

void SingleSnakePlay::scheUpdate(float time) {
	
    for(int i=0; i<m_snakes.size(); i++) {
		m_snakes[i]->m_victorFlag = true;
		if (m_snakes[i]->count())
			continue;
		Location nextLoc = m_controls[i]->nextMove(m_snakes[i]->getSnakeLoc());
		m_snakes[i]->moveTo(nextLoc);
    }
	checkGame();
	judge();
}
