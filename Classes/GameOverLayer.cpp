#include "GameOverLayer.h"
#include "FightScene.h"
#include "StartScene.h"
#include "DescriptionScene.h"

USING_NS_CC;

char *GameOverLayer::m_bgImage;
int GameOverLayer::m_nextScene;
int GameOverLayer::m_curScene;

bool GameOverLayer::init() {
	if (!CCLayerColor::initWithColor(ccc4(0,0,0,150))) {
		return false;
	}
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	// create background sprite
	CCSprite* pSprite = CCSprite::create(m_bgImage);

	pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	CCSize bgimgSize = pSprite->getContentSize();
	pSprite->setScaleX(visibleSize.width/bgimgSize.width);
	pSprite->setScaleY(visibleSize.height/bgimgSize.height);

	this->addChild(pSprite, 0);

	// create buttons
	CCMenuItemImage *newGameItem = CCMenuItemImage::create("buttons/restart.png", "buttons/restart.png",this,menu_selector(GameOverLayer::StartNewGameCallback));
	newGameItem->setPosition(ccp(visibleSize.width - 165,222));
	newGameItem->setEnabled(true);

	CCMenuItemImage *nextItem = CCMenuItemImage::create("buttons/next.png", "buttons/next.png",this,menu_selector(GameOverLayer::StartNextCallback));
	nextItem->setPosition(ccp(visibleSize.width - 165,177));
	nextItem->setEnabled(true);

	CCMenuItemImage *homeItem = CCMenuItemImage::create("buttons/return.png", "buttons/return.png",this,menu_selector(GameOverLayer::ReturnHomeCallback));
	homeItem->setPosition(ccp(visibleSize.width - 165,137));
	homeItem->setEnabled(true);

	CCMenuItemImage *exitGameItem = CCMenuItemImage::create("buttons/exit.png", "buttons/exit.png",this,menu_selector(GameOverLayer::ExitGameCallback));
	exitGameItem->setPosition(ccp(visibleSize.width-165,80));
	exitGameItem->setEnabled(true);

	CCMenu* mainmenu = CCMenu::create(newGameItem,nextItem,exitGameItem,homeItem,NULL);
	mainmenu->setPosition(ccp(0,0));
	this->addChild(mainmenu,1,3);

	return true;
}

void GameOverLayer::StartNewGameCallback(CCObject* pSender) {
	CCDirector::sharedDirector()->popScene();
	CCDirector::sharedDirector()->replaceScene(FightScene::scene(m_curScene));
}

void GameOverLayer::StartNextCallback(CCObject* pSender) {
	CCDirector::sharedDirector()->popScene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(1.0f,
		DescriptionScene::getScene(m_nextScene), false));
}

void GameOverLayer::ExitGameCallback(CCObject* pSender) {
	CCDirector::sharedDirector()->end();
}

void GameOverLayer::ReturnHomeCallback(CCObject* pSender) {
	CCDirector::sharedDirector()->popScene();
	CCDirector::sharedDirector()->replaceScene(StartScene::scene());
}

CCScene *GameOverLayer::getScene(int cur, bool win) {
	m_curScene = cur;

	switch(m_curScene)
	{
	case VirtualMap::SCENE_TYPE_SINGLE :
		if (win)
			m_bgImage = "backgrouds/win1.png";
		else
			m_bgImage = "backgrounds/lose1.png";
		m_nextScene = VirtualMap::SCENE_TYPE_DOUBLE;

		break;
	case VirtualMap::SCENE_TYPE_DOUBLE :
		if (win)
			m_bgImage = "backgrounds/win2.png";
		else
			m_bgImage = "backgrounds/lose2.png";
		m_nextScene = VirtualMap::SCENE_TYPE_DISAPPEAR;

		break;
	case VirtualMap::SCENE_TYPE_DISAPPEAR :
		if (win)
			m_bgImage = "backgrounds/win3.png";
		else
			m_bgImage = "backgrounds/lose3.png";
		m_nextScene = VirtualMap::SCENE_TYPE_DICE;

		break;
	case VirtualMap::SCENE_TYPE_ZHA :
		if (win)
			m_bgImage = "backgrounds/win4.png";
		else
			m_bgImage = "backgrounds/lose4.png";
		m_nextScene = VirtualMap::SCENE_TYPE_DICE;

		break;
	case VirtualMap::SCENE_TYPE_DICE :
		if (win)
			m_bgImage = "backgrounds/win5.png";
		else
			m_bgImage = "backgrounds/lose5.png";
		m_nextScene = VirtualMap::SCENE_TYPE_BOSS;

		break;

	case VirtualMap::SCENE_TYPE_BOSS :
		if (win)
			m_bgImage = "backgrounds/win6.png";
		else
			m_bgImage = "backgrounds/lose6.png";
		m_nextScene = VirtualMap::SCENE_TYPE_SINGLE;

		break;
	}

	CCScene *scene = CCScene::create();
	scene->addChild(create());
	return scene;
}
