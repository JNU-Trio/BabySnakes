#include "Snakes.h"
#include "MapAttribute.h"
#include <vector>

USING_NS_CC;

bool SimpleSnake::moveTo(Location nextLoc)
{
	int bodysize = m_snake.body.size();
	m_snake.tail = m_snake.body[bodysize-1];
	for(int i=bodysize-1; i>0; i--)
	{
		m_snake.body[i] = m_snake.body[i-1];
	}
	m_snake.body[0] = m_snake.head;
	m_snake.head = nextLoc;

	CCActionInterval* headaction = CCMoveTo::create(VirtualMap::SPEED,VirtualMap::LocToPos(m_snake.head));
	std::vector<CCActionInterval*> bodyaction;
	for(int i=0; i<bodysize; i++)
	{
		bodyaction.push_back(CCMoveTo::create(VirtualMap::SPEED,VirtualMap::LocToPos(m_snake.body[i])));
	}
	CCActionInterval* tailaction = CCMoveTo::create(VirtualMap::SPEED,VirtualMap::LocToPos(m_snake.tail));
	
	
	m_shead->runAction(headaction);
	for(int i=0; i<bodysize; i++)
	{
		m_sbody[i]->runAction(bodyaction[i]);
	}
	m_stail->runAction(tailaction);
	return true;
}

void SimpleSnake::eatFood(CCLayer *father_layer, SnakeLocation pre_loc, SnakeImgFilename snakeImg)
{

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSize contentSize;

	Location loc = m_snake.tail;
	m_snake.body.push_back(loc);
	m_snake.tail = pre_loc.tail;

	CCSprite *stmp = CCSprite::create(snakeImg.body); 
	m_sbody.push_back(stmp);

	int i = m_sbody.size() - 1;
		contentSize = m_sbody[i]->getContentSize();
		m_sbody[i]->setScaleX(visibleSize.width/VirtualMap::MAP_WIDTH/contentSize.width);
		m_sbody[i]->setScaleY(visibleSize.height/VirtualMap::MAP_HEIGHT/contentSize.height);
		m_sbody[i]->setPosition(VirtualMap::LocToPos(m_snake.body[i]));
		father_layer->addChild(m_sbody[i]);


}

bool SimpleSnake::initialize(CCLayer *father_layer, SnakeLocation virtualSnakeLoc, SnakeImgFilename snakeImg)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSize contentSize;

	// 初始化蛇的head,tail,body的位置
	m_snake = virtualSnakeLoc;

	// head创建sprite
	m_shead = CCSprite::create(snakeImg.head);
	contentSize = m_shead->getContentSize();
	m_shead->setScaleX(visibleSize.width/VirtualMap::MAP_WIDTH/contentSize.width);
	m_shead->setScaleY(visibleSize.height/VirtualMap::MAP_HEIGHT/contentSize.height);
	m_shead->setPosition(VirtualMap::LocToPos(m_snake.head));
	father_layer->addChild(m_shead);

	// tail创建sprite
	m_stail = CCSprite::create(snakeImg.tail);
	contentSize = m_stail->getContentSize();
	m_stail->setScaleX(visibleSize.width/VirtualMap::MAP_WIDTH/contentSize.width);
	m_stail->setScaleY(visibleSize.height/VirtualMap::MAP_HEIGHT/contentSize.height);
	m_stail->setPosition(VirtualMap::LocToPos(m_snake.tail));
	father_layer->addChild(m_stail);

	//  body创建sprite
	CCSprite *stmp = CCSprite::create(snakeImg.body);
	m_sbody.push_back(stmp);
	for(int i=0; i<m_sbody.size(); i++)
	{
		contentSize = m_sbody[i]->getContentSize();
		m_sbody[i]->setScaleX(visibleSize.width/VirtualMap::MAP_WIDTH/contentSize.width);
		m_sbody[i]->setScaleY(visibleSize.height/VirtualMap::MAP_HEIGHT/contentSize.height);
		m_sbody[i]->setPosition(VirtualMap::LocToPos(m_snake.body[i]));
		father_layer->addChild(m_sbody[i]);
	}

	return true;
}


Location HumanControl::nextMove(std::vector<SnakeLocation> tmp)
{
	Location ret = tmp[0].head;
	switch(VirtualMap::DIRECTION)
	{
	case 0: ret.x--; break;
	case 1: ret.y++; break;
	case 2: ret.x++; break;
	case 3: ret.y--; break;
	}
	return ret;
}

Location AIControl::nextMove(std::vector<SnakeLocation> snakes)
{
	Location ret = snakes[1].head;
	if (VirtualMap::foodLocate.x - ret.x < 0)
		ret.x--;
	else if (VirtualMap::foodLocate.x - ret.x > 0)
		ret.x++;
	else if (VirtualMap::foodLocate.y - ret.y < 0)
		ret.y--;
	else
		ret.y++;
	/*
	int sum = 0;
	while (true)
	{
		ret = snakes[1].head;
		sum ++;
		if (sum > 1000)
			break;
		int x,y;
		cc_timeval psv;  
		CCTime::gettimeofdayCocos2d( &psv, NULL );
		unsigned int tsrans = psv.tv_sec * 1000 + psv.tv_usec / 1000 + rand();
		srand(tsrans);
		x = CCRANDOM_0_1()*100;
		x = x % 4;
		switch(x)
		{
		case 0: ret.x++; break;
		case 1: ret.y++; break;
		case 2: ret.x--; break;
		case 3: ret.y--; break;
		}
		bool flag = true;
		for(int i=0; i<snakes.size(); i++)
		{
			if (snakes[i].head.x == ret.x || snakes[i].head.y == ret.y)
			{
				flag = false;
				break;
			}
			else if (snakes[i].tail.x == ret.x || snakes[i].tail.y == ret.y)
			{
				flag = false;
				break;
			}
			else
			{
				for(int j=0; j<snakes[i].body.size(); j++)
				{
					if (snakes[i].body[j].x == ret.x || snakes[i].body[j].y == ret.y)
					{
						flag = false;
						break;
					}
				}
				if (!flag)
				{
					break;
				}
			}
		}
		if (flag)
			break;
	}*/

	return ret;
}

bool Food::generate()
{
	int x,y;
	cc_timeval psv;  
	CCTime::gettimeofdayCocos2d( &psv, NULL );
	unsigned int tsrans = psv.tv_sec * 1000 + psv.tv_usec / 1000 + rand();
	srand(tsrans);
	x = CCRANDOM_0_1()*100;
	x = x % VirtualMap::MAP_WIDTH + 1;

	CCTime::gettimeofdayCocos2d( &psv, NULL );
	tsrans = psv.tv_sec * 1000 + psv.tv_usec / 1000 + rand();
	srand(tsrans);
	y = CCRANDOM_0_1()*100;
	y = y % VirtualMap::MAP_HEIGHT + 1;

	m_locate.x = x;
	m_locate.y = y;

	VirtualMap::foodLocate = m_locate;

	return true;
}