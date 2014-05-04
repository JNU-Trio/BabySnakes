#include "FightScene.h"
#include "Snakes.h"

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
    CCSprite* pSprite = CCSprite::create("backgrounds/background1.png");

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

	curfood.generate();

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSize contentSize;

	// ����food
	curfood.food = CCSprite::create("foods/shit.png");
	contentSize = curfood.food->getContentSize();
	curfood.food->setScaleX(visibleSize.width/VirtualMap::MAP_WIDTH/contentSize.width);
	curfood.food->setScaleY(visibleSize.height/VirtualMap::MAP_HEIGHT/contentSize.height);
	curfood.food->setPosition(VirtualMap::LocToPos(curfood.m_locate));
	this->addChild(curfood.food);

	Snake *snake = new SimpleSnake();
	m_snakes.push_back(snake);
	snake = new SimpleSnake();
	m_snakes.push_back(snake);

	SnakeLocation curSnake;
	std::vector<SnakeLocation> virtualSnakes;

	SnakeImgFilename curImage;
	std::vector<SnakeImgFilename> snakeImages;
	

	// ����������λ��
	curSnake.head.x = 8;
	curSnake.head.y = 5;
	curSnake.tail.x = 6;
	curSnake.tail.y = 5;
	Location tmp;
	tmp.x = 7;
	tmp.y = 5;
	curSnake.body.push_back(tmp);
	virtualSnakes.push_back(curSnake);

	// ������ͼƬ
	curImage.head = "snakes/snakehead1.png";
	curImage.body = "snakes/snakebody1.png";
	curImage.tail = "snakes/snaketail1.png";
	snakeImages.push_back(curImage);

	// ����������λ��
	curSnake.head.x = 15;
	curSnake.head.y = 5;
	curSnake.tail.x = 17;
	curSnake.tail.y = 5;
	tmp.x = 16;
	tmp.y = 5;
	curSnake.body.clear(); // ע��Ҫ���
	curSnake.body.push_back(tmp);
	virtualSnakes.push_back(curSnake);

	// ������ͼƬ
	curImage.head = "snakes/snakehead2.png";
	curImage.body = "snakes/snakebody2.png";
	curImage.tail = "snakes/snaketail2.png";
	snakeImages.push_back(curImage);

	for(int i=0; i < m_snakes.size(); i++)
	{
		m_snakes[i]->initialize(this,virtualSnakes[i],snakeImages[i]);
	}

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	this->setTouchEnabled(true);
	this->schedule(schedule_selector(SnakesPlay::scheUpdate),0.2);

	return true;
}

//��д�����ص�����
bool SnakesPlay::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* pevent)
{
	m_disFlag = false;
	return true;
}

void SnakesPlay::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* pevent)
{
	if (!m_disFlag)
	{
		CCPoint startpos = touch->getStartLocation();
		CCPoint curpos = touch->getLocation();
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		if (ccpDistance(startpos,curpos) > visibleSize.height/8)
		{
			CCPoint judge = ccpSub(ccpRotateByAngle(ccpMidpoint(curpos,startpos), startpos, CC_DEGREES_TO_RADIANS(45)),startpos);
			if (judge.x > 0)
			{
				if (judge.y > 0) // ����
				{
					VirtualMap::DIRECTION = 2;
				}
				else // ����
				{
					VirtualMap::DIRECTION = 3;
				}
			}
			else
			{
				if (judge.y > 0) // ����
				{
					VirtualMap::DIRECTION = 1;
				}
				else // ����
				{
					VirtualMap::DIRECTION = 0;
				}
			}
			m_disFlag = true;
		}
	}
}

void SnakesPlay::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* pevent)
{
}

void SnakesPlay::scheUpdate(float time)
{
	if (!checkGame())
	{
		CCDirector::sharedDirector()->end();
	}

	SnakeImgFilename curImage;
	std::vector<SnakeImgFilename> snakeImages;
	
	curImage.head = "snakes/snakehead1.png";
	curImage.body = "snakes/snakebody1.png";
	curImage.tail = "snakes/snaketail1.png";
	snakeImages.push_back(curImage);

	curImage.head = "snakes/snakehead2.png";
	curImage.body = "snakes/snakebody2.png";
	curImage.tail = "snakes/snaketail2.png";
	snakeImages.push_back(curImage);




	std::vector<SnakeLocation> locs;
	for(int i=0; i<m_snakes.size(); i++)
		locs.push_back(m_snakes[i]->m_snake);

	SnakeLocation earthS = m_snakes[0]->m_snake, marsS = m_snakes[1]->m_snake;
	if (earthS.head == curfood.m_locate)
	{	
		m_snakes[0]->eatFood(this, locs[0],snakeImages[0]);
		curfood.generate();
		curfood.food->setPosition(VirtualMap::LocToPos(curfood.m_locate));
	}
	else if (marsS.head == curfood.m_locate)
	{
		m_snakes[1]->eatFood(this,locs[1],snakeImages[1]);
		curfood.generate();
		curfood.food->setPosition(VirtualMap::LocToPos(curfood.m_locate));
	}

	std::vector<Control *> ctrls;
	ctrls.push_back(new HumanControl());
	ctrls.push_back(new AIControl());

	


	for(int i=0; i<ctrls.size(); i++)
	{
		Location nextLoc = ctrls[i]->nextMove(locs);
		CCLOG("x:%d y:%d\n",nextLoc.x,nextLoc.y);
		m_snakes[i]->moveTo(nextLoc);
	}
}

bool SnakesPlay::checkGame()
{
	SnakeLocation earthS = m_snakes[0]->m_snake, marsS = m_snakes[1]->m_snake;
	if (earthS.head.x > VirtualMap::MAP_WIDTH || earthS.head.x < 0
		|| earthS.head.y > VirtualMap::MAP_HEIGHT || earthS.head.y < 0
		|| marsS.head.x > VirtualMap::MAP_WIDTH || marsS.head.x < 0
		|| marsS.head.y > VirtualMap::MAP_HEIGHT || marsS.head.y < 0)
	{
		return false;
	}
	if (earthS.head == marsS.head)
		return false;
	if (earthS.head == marsS.tail)
		return false;
	for(int i=0; i<marsS.body.size(); i++)
		if (earthS.head == marsS.body[i])
			return false;

	if (marsS.head == earthS.tail)
		return false;
	for(int i=0; i<earthS.body.size(); i++)
		if (marsS.head == earthS.body[i])
			return false;
	return true;
}