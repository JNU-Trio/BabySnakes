#include "FightScene.h"

USING_NS_CC;

CCScene* FightScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();

	// 添加背景
    FightScene *bglayer = FightScene::create();
	scene->addChild(bglayer, m_bglayer_zOrder, m_bglayer_tag);

	// 添加蛇的运动层
	SnakesPlay *playlayer = SnakesPlay::create();
	scene->addChild(playlayer, m_playlayer_zOrder, m_playlayer_tag);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool FightScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    // 添加背景图片
    CCSprite* pSprite = CCSprite::create("backgrounds/HelloWorld.png");

    // 设置背景位置
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	// 背景图片缩放
	CCSize bgimgSize = pSprite->getContentSize();
	pSprite->setScaleX(visibleSize.width/bgimgSize.width);
	pSprite->setScaleY(visibleSize.height/bgimgSize.height);

    // 将背景sprite作为子结点加入本layer
    this->addChild(pSprite, 0);
    
    return true;
}

bool SnakesPlay::init()
{
	if (!CCLayer::init())
		return false;

	Snake *snake = new SimpleSnake();
	m_snakes.push_back(snake);

	for(std::vector<Snake *>::iterator iter = m_snakes.begin(); iter != m_snakes.end(); iter++)
	{
		Snake *tsnake = *iter;
		tsnake->initialize(this);
	}

	return true;
}
