#include "FightScene.h"
#include "StartScene.h"
#include "GameOverScene.h"
#include "InfoLayer.h"
#include "Snakes.h"

#include <vector>

USING_NS_CC;

CCScene* FightScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// ��ӱ���
	FightScene *bglayer = FightScene::create();
	scene->addChild(bglayer, m_bglayer_zOrder, m_bglayer_tag);

	//��ӼƷֲ�
	InfoLayer *infolayer = InfoLayer::create();
	scene->addChild(infolayer,3,3);


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

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSize contentSize;

	// ��ʼ����ͼ
	VirtualMap::init();

	// ����ǽ
	std::vector<Location> batmp;
	for(int i=1; i<=VirtualMap::MAP_WIDTH; i++)
	{
		Location p;
		p.x = i;
		p.y = 1;
		batmp.push_back(p);
		p.x = i;
		p.y = VirtualMap::MAP_HEIGHT;
		batmp.push_back(p);
	}

	for(int i=2; i<VirtualMap::MAP_HEIGHT; i++)
	{
		Location p;
		p.x = 1;
		p.y = i;
		batmp.push_back(p);
		p.x = VirtualMap::MAP_WIDTH;
		p.y = i;
		batmp.push_back(p);
	}
	m_walls.init(this,batmp,"barriers/wall.png");

	isStop = false;
	CCMenuItemImage *StopGameItem = CCMenuItemImage::create("buttons/pause.png", "buttons/pause.png");
	CCMenuItemImage *StartGameItem = CCMenuItemImage::create("buttons/play.png", "buttons/play.png");
	CCMenuItemToggle *StopOrStartItem = CCMenuItemToggle::createWithTarget(this,menu_selector(SnakesPlay::StopGameCallback), StopGameItem,StartGameItem, NULL);  
	StopOrStartItem->setEnabled(true);
	StopOrStartItem->setScale(0.5);

	//StopOrStartItem->setPosition(ccp(, 1));

	CCMenu* itemToggleMenu = CCMenu::create(StopOrStartItem, NULL);  
	itemToggleMenu->setPosition(ccp(visibleSize.width-20, 20));  
	this->addChild(itemToggleMenu, 1);  

	GameOver *gameover = GameOver::create();
	this->addChild(gameover, 4,4);

	// �����ϰ���
	batmp.clear();
	for(int i=5; i<=8; i++)
	{
		Location p;
		p.x = i;
		p.y = 4;
		batmp.push_back(p);
	}

	for(int i=14; i<=17; i++)
	{
		Location p;
		p.x = i;
		p.y = 8;
		batmp.push_back(p);
	}
	Location p;
	p.x = 17;
	p.y = 7;
	batmp.push_back(p);
	m_barriers.init(this,batmp,"barriers/barrier.png");

	// ����food
	curfood.m_food = CCSprite::create("foods/shit.png");
	contentSize = curfood.m_food->getContentSize();
	curfood.m_food->setScaleX(visibleSize.width/VirtualMap::MAP_WIDTH/contentSize.width);
	curfood.m_food->setScaleY(visibleSize.height/VirtualMap::MAP_HEIGHT/contentSize.height);
	curfood.m_food->setPosition(VirtualMap::LocToPos(curfood.m_locate));
	this->addChild(curfood.m_food);
	curfood.m_locate.x = 3;
	curfood.m_locate.y = 3;
	curfood.generate();

	// �����߶���
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
	curSnake.head.direction = Location::TURN_RIGHT;
	curSnake.tail.x = 6;
	curSnake.tail.y = 5;
	curSnake.tail.direction = Location::TURN_RIGHT;
	Location tmp;
	tmp.x = 7;
	tmp.y = 5;
	tmp.direction = Location::TURN_RIGHT;
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
	curSnake.head.direction = Location::TURN_LEFT;
	curSnake.tail.x = 17;
	curSnake.tail.y = 5;
	curSnake.tail.direction = Location::TURN_LEFT;
	tmp.x = 16;
	tmp.y = 5;
	tmp.direction = Location::TURN_LEFT;
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
	this->schedule(schedule_selector(SnakesPlay::scheUpdate),0.3); 

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
		CCDirector::sharedDirector()->replaceScene(GameOverScene::scene());

	}

	for(int i=0; i<m_snakes.size(); i++)
	{
		if (m_snakes[i]->m_snake.head == curfood.m_locate)
		{
			m_snakes[i]->eatFood(this);
			curfood.generate();
		}
	}

	std::vector<Control *> ctrls;
	ctrls.push_back(new HumanControl());
	ctrls.push_back(new AIControl());

	for(int i=0; i<ctrls.size(); i++)
	{
		Location nextLoc = ctrls[i]->nextMove(m_snakes[i]->m_snake);
		m_snakes[i]->moveTo(nextLoc);
	}
}

bool SnakesPlay::checkGame()
{
	for(int i=0; i<m_snakes.size(); i++)
	{
		for(int j=0; j<m_snakes[i]->m_snake.body.size(); j++)
		{
			Location p = m_snakes[i]->m_snake.body[j];
			VirtualMap::map[p.x][p.y] = VirtualMap::earthSnakeTag;
		}
		Location p = m_snakes[i]->m_snake.tail;
		VirtualMap::map[p.x][p.y] = VirtualMap::earthSnakeTag;
	}

	for(int i=0; i<m_snakes.size(); i++)
	{
		Location p = m_snakes[i]->m_snake.head;
		if (VirtualMap::map[p.x][p.y] != VirtualMap::emptyTag
			&& VirtualMap::map[p.x][p.y] != VirtualMap::foodTag)
			return false;
	}
	if (m_snakes[0]->m_snake.head == m_snakes[1]->m_snake.head)
		return false;

	for(int i=0; i<m_snakes.size(); i++)
	{
		Location p = m_snakes[i]->m_snake.head;
		VirtualMap::map[p.x][p.y] = VirtualMap::earthSnakeTag;
	}

	Location p = VirtualMap::foodLocate;
	VirtualMap::map[p.x][p.y] = VirtualMap::foodTag;

	return true;


	/*SnakeLocation earthS = m_snakes[0]->m_snake, marsS = m_snakes[1]->m_snake;
	for(int i=0; i<m_snakes.size(); i++)
	for(int j=0; j<=m_walls.m_locate.size(); j++)
	if (m_walls.m_locate[i] == m_snakes[i]->m_snake.head)
	return false;
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
	return false;*/
	return true;
}

void SnakesPlay::StopGameCallback(CCObject* pSender){
	if(!isStop){
		CCDirector::sharedDirector()->pause();
		isStop = true;
	}
	else{
		CCDirector::sharedDirector()->resume();
		isStop = false;
	}
}

bool GameOver::init(){
	if(!CCLayer::init())
	{
		return false;
	}
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	// ��ӱ���ͼƬ
	CCSprite* pSprite = CCSprite::create("backgrounds/gameover.png");

	// ���ñ���λ��
	pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	// ����ͼƬ����
	CCSize bgimgSize = pSprite->getContentSize();
	pSprite->setScaleX(visibleSize.width/bgimgSize.width);
	pSprite->setScaleY(visibleSize.height/bgimgSize.height);
	//pSprite->setScale(0.5);

	// ������sprite��Ϊ�ӽ����뱾layer
	this->addChild(pSprite, 0);

	CCMenuItemImage *newGameItem = CCMenuItemImage::create("buttons/playbutton.png", "buttons/pausebutton.png",this,menu_selector(GameOver::StartNewGameCallback));
	newGameItem->setScale(0.1);
	newGameItem->setPosition(ccp(visibleSize.width / 3,visibleSize.height / 2 - 20));
	newGameItem->setEnabled(true);

	CCMenuItemImage *exitGameItem = CCMenuItemImage::create("buttons/playbutton.png", "buttons/pausebutton.png",this,menu_selector(GameOver::ExitGameCallback));
	exitGameItem->setScale(0.1);
	exitGameItem->setPosition(ccp(visibleSize.width*2 / 3,visibleSize.height / 2 - 20));
	exitGameItem->setEnabled(true);

	CCMenu* mainmenu = CCMenu::create(newGameItem,exitGameItem,NULL);
	mainmenu->setPosition(ccp(0,0));
	this->addChild(mainmenu,1,3);
	this->setVisible(false);
}

void GameOver::StartNewGameCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(FightScene::scene());
}

void GameOver::ExitGameCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();
}