#include "GameOverScene.h"
#include "FightScene.h"
#include "StartScene.h"
USING_NS_CC;

CCScene* GameOverScene::scene() {
	CCScene *scene = CCScene::create();

	GameOverScene *layer = GameOverScene::create();

	scene->addChild(layer);

	return scene;
}

bool GameOverScene::init(){
    if(!CCLayer::init()) {
		return false;
	}
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    // create background sprite
	CCSprite* pSprite = CCSprite::create("backgrounds/gameover.png");

	pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	CCSize bgimgSize = pSprite->getContentSize();
	pSprite->setScaleX(visibleSize.width/bgimgSize.width);
	pSprite->setScaleY(visibleSize.height/bgimgSize.height);

	this->addChild(pSprite, 0);

    // create buttons
    CCMenuItemImage *newGameItem = CCMenuItemImage::create("buttons/restart.png", "buttons/restart.png",this,menu_selector(GameOverScene::StartNewGameCallback));
	newGameItem->setPosition(ccp(visibleSize.width - 165,192));
	newGameItem->setEnabled(true);

	CCMenuItemImage *homeItem = CCMenuItemImage::create("buttons/return.png", "buttons/return.png",this,menu_selector(GameOverScene::ReturnHomeCallback));
	homeItem->setPosition(ccp(visibleSize.width - 165,137));
	homeItem->setEnabled(true);

	CCMenuItemImage *exitGameItem = CCMenuItemImage::create("buttons/exit.png", "buttons/exit.png",this,menu_selector(GameOverScene::ExitGameCallback));
	exitGameItem->setPosition(ccp(visibleSize.width-165,80));
	exitGameItem->setEnabled(true);

	CCMenu* mainmenu = CCMenu::create(newGameItem,exitGameItem,homeItem,NULL);
	mainmenu->setPosition(ccp(0,0));
	this->addChild(mainmenu,1,3);

    return true;
}

void GameOverScene::StartNewGameCallback(CCObject* pSender) {
	CCDirector::sharedDirector()->replaceScene(FightScene::scene());
}

void GameOverScene::ExitGameCallback(CCObject* pSender) {
	CCDirector::sharedDirector()->end();
}

void GameOverScene::ReturnHomeCallback(CCObject* pSender) {
    CCDirector::sharedDirector()->replaceScene(StartScene::scene());
}
