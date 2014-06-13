#include "GameOverLayer.h"
#include "FightScene.h"
#include "StartScene.h"

USING_NS_CC;

bool GameOverLayer::init(){
    if (!CCLayerColor::initWithColor(ccc4(255,255,255,150))) {
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    // create information
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    m_label = CCLabelTTF::create("","Artial", 32);
    m_label->setColor( ccc3(0, 0, 0) );
    m_label->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(m_label);

    // create background sprite
    CCSprite* pSprite = CCSprite::create("backgrounds/gameover.png");

    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    CCSize bgimgSize = pSprite->getContentSize();
    pSprite->setScaleX(visibleSize.width/bgimgSize.width);
    pSprite->setScaleY(visibleSize.height/bgimgSize.height);

    this->addChild(pSprite, 0);

    // create buttons
    CCMenuItemImage *newGameItem = CCMenuItemImage::create("buttons/restart.png", "buttons/restart.png",this,menu_selector(GameOverLayer::StartNewGameCallback));
    newGameItem->setPosition(ccp(visibleSize.width - 165,192));
    newGameItem->setEnabled(true);

    CCMenuItemImage *homeItem = CCMenuItemImage::create("buttons/return.png", "buttons/return.png",this,menu_selector(GameOverLayer::ReturnHomeCallback));
    homeItem->setPosition(ccp(visibleSize.width - 165,137));
    homeItem->setEnabled(true);

    CCMenuItemImage *exitGameItem = CCMenuItemImage::create("buttons/exit.png", "buttons/exit.png",this,menu_selector(GameOverLayer::ExitGameCallback));
    exitGameItem->setPosition(ccp(visibleSize.width-165,80));
    exitGameItem->setEnabled(true);

    CCMenu* mainmenu = CCMenu::create(newGameItem,exitGameItem,homeItem,NULL);
    mainmenu->setPosition(ccp(0,0));
    this->addChild(mainmenu,1,3);

    return true;
}

void GameOverLayer::StartNewGameCallback(CCObject* pSender) {
    CCDirector::sharedDirector()->replaceScene(FightScene::scene(1));
    CCDirector::sharedDirector()->resume();
}

void GameOverLayer::ExitGameCallback(CCObject* pSender) {
    CCDirector::sharedDirector()->end();
}

void GameOverLayer::ReturnHomeCallback(CCObject* pSender) {
    CCDirector::sharedDirector()->replaceScene(StartScene::scene());
    CCDirector::sharedDirector()->resume();
}

CCLabelTTF * GameOverLayer::getLabel() {
    return m_label;
}
