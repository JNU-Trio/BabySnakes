#include "StartScene.h"
#include "DescriptionScene.h"

USING_NS_CC;

CCScene* StartScene::scene() {
    CCScene *scene = CCScene::create();
    StartScene *layer = StartScene::create();
    scene->addChild(layer);
    return scene;
}

bool StartScene::init(){
    if(!CCLayer::init()) {
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    // create background image
    CCSprite* pSprite = CCSprite::create("backgrounds/background0.png");

    // set position
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // set scale
    CCSize bgimgSize = pSprite->getContentSize();
    pSprite->setScaleX(visibleSize.width/bgimgSize.width);
    pSprite->setScaleY(visibleSize.height/bgimgSize.height);

    // add bgSprite to bgLayer
    this->addChild(pSprite, 0);

    CCMenuItemImage *startGameItem = CCMenuItemImage::create("buttons/playbut.png", "buttons/playbut.png",this,menu_selector(StartScene::StartGameCallback));
    //startGameItem->setScale(0.1);
    startGameItem->setPosition(ccp(visibleSize.width-190 ,130));
    startGameItem->setEnabled(true);

    CCMenu* mainmenu = CCMenu::create(startGameItem,NULL);
    mainmenu->setPosition(ccp(0,0));
    this->addChild(mainmenu,1,3);
    return true;
}

void StartScene::StartGameCallback(CCObject* pSender) {
	CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(1.0f,
		DescriptionScene::getScene(VirtualMap::SCENE_TYPE_SINGLE), false));
}