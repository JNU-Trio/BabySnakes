#include "FightScene.h"

USING_NS_CC;

CCScene* FightScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();

	// ��ӱ���
    FightScene *bglayer = FightScene::create();
	scene->addChild(bglayer, m_bglayer_zOrder, m_bglayer_tag);

	// ����ߵ��˶���
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

    // ��ӱ���ͼƬ
    CCSprite* pSprite = CCSprite::create("backgrounds/HelloWorld.png");

    // ���ñ���λ��
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	// ����ͼƬ����
	CCSize bgimgSize = pSprite->getContentSize();
	pSprite->setScaleX(visibleSize.width/bgimgSize.width);
	pSprite->setScaleY(visibleSize.height/bgimgSize.height);

    // ������sprite��Ϊ�ӽ����뱾layer
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
