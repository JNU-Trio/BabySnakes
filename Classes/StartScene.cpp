#include "StartScene.h"

USING_NS_CC;

CCScene* StartScene::scene()
{
    CCScene *scene = CCScene::create();
    
    StartScene *layer = StartScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool StartScene::init(){
	if(!CCLayer::init())
	{
		return false;
	}
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    // 添加背景图片
    CCSprite* pSprite = CCSprite::create("backgrounds/background0.png");

    // 设置背景位置
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	// 背景图片缩放
	CCSize bgimgSize = pSprite->getContentSize();
	pSprite->setScaleX(visibleSize.width/bgimgSize.width);
	pSprite->setScaleY(visibleSize.height/bgimgSize.height);

    // 将背景sprite作为子结点加入本layer
    this->addChild(pSprite, 0);

	CCMenuItemImage *startGameItem = CCMenuItemImage::create("buttons/playbut.png", "buttons/playbut.png",this,menu_selector(StartScene::StartGameCallback));
    //startGameItem->setScale(0.1);
    startGameItem->setPosition(ccp(visibleSize.width-190 ,130));
    startGameItem->setEnabled(true);

	CCMenu* mainmenu = CCMenu::create(startGameItem,NULL);
    mainmenu->setPosition(ccp(0,0));
    this->addChild(mainmenu,1,3);
}

void StartScene::StartGameCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(FightScene::scene());
}