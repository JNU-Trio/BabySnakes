#include "Snakes.h"
#include "MapAttribute.h"
#include <vector>

USING_NS_CC;

bool SimpleSnake::moveTo(Location nextLoc)
{
	int bodysize = m_snake.body.size();
	VirtualMap::map[m_snake.tail.x][m_snake.tail.y] = VirtualMap::emptyTag;
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
	m_shead->setRotation(m_snake.head.direction);
	for(int i=0; i<bodysize; i++)
	{
		m_sbody[i]->runAction(bodyaction[i]);
	}
	m_stail->runAction(tailaction);
	m_stail->setRotation(m_snake.tail.direction);
	return true;
}

void SimpleSnake::eatFood(CCLayer *father_layer)
{

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSize contentSize;

	m_snake.body.push_back(m_snake.tail);

	CCSprite *stmp = CCSprite::create(m_snakeImage.body); 
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

	// 初始化图片文件路径
	m_snakeImage = snakeImg;

	// 初始化蛇的head,tail,body的位置
	m_snake = virtualSnakeLoc;

	// head创建sprite
	m_shead = CCSprite::create(snakeImg.head);
	contentSize = m_shead->getContentSize();
	m_shead->setScaleX(visibleSize.width/VirtualMap::MAP_WIDTH/contentSize.width);
	m_shead->setScaleY(visibleSize.height/VirtualMap::MAP_HEIGHT/contentSize.height);
	m_shead->setPosition(VirtualMap::LocToPos(m_snake.head));
	m_shead->setRotation(m_snake.head.direction);
	/*
	switch(m_snake.head.direction){
	case Location::TURN_UP: m_shead->setRotation(90);break;
	case Location::TURN_LEFT:m_shead->setRotation(180);break;
	case Location::TURN_DOWN:m_shead->setRotation(270);break;
	}
	*/
	father_layer->addChild(m_shead);

	// tail创建sprite
	m_stail = CCSprite::create(snakeImg.tail);
	contentSize = m_stail->getContentSize();
	m_stail->setScaleX(visibleSize.width/VirtualMap::MAP_WIDTH/contentSize.width);
	m_stail->setScaleY(visibleSize.height/VirtualMap::MAP_HEIGHT/contentSize.height);
	m_stail->setPosition(VirtualMap::LocToPos(m_snake.tail));
	m_stail->setRotation(m_snake.tail.direction);
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


Location HumanControl::nextMove(SnakeLocation p)
{
	Location ret = p.head;
	switch(VirtualMap::DIRECTION)
	{
	case 0: ret.x--;ret.direction =Location::TURN_LEFT; break;
	case 1: ret.y++;ret.direction =Location::TURN_UP; break;
	case 2: ret.x++;ret.direction =Location::TURN_RIGHT; break;
	case 3: ret.y--;ret.direction =Location::TURN_DOWN; break;
	}

	return ret;
}

Location AIControl::nextMove(SnakeLocation p)
{
	int dir[4][2] = {-1,0,1,0,0,-1,0,1};
	Location ret = p.head;
	Location fp = VirtualMap::foodLocate;
	int m = 0;
	int a = ret.x + dir[0][0];
	int b = ret.y + dir[0][1];
	int msum = a-fp.x < 0 ? fp.x-a:a-fp.x;
	msum += (b-fp.y < 0 ? fp.y-b:b-fp.y);
	int i;
	for(i=0; i<4; i++)
	{
		ret = p.head;
		int nx = ret.x+dir[i][0], ny = ret.y+dir[i][1];
		if ((VirtualMap::map[nx][ny] == VirtualMap::emptyTag
			|| VirtualMap::map[nx][ny] == VirtualMap::foodTag))
		{
			m = i;
			break;
		}
	}

	for(i = m+1; i<4; i++)
	{
		ret = p.head;
		int nx = ret.x+dir[i][0], ny = ret.y+dir[i][1];
		if ((VirtualMap::map[nx][ny] == VirtualMap::emptyTag
			|| VirtualMap::map[nx][ny] == VirtualMap::foodTag)
			&& (nx-fp.x<0?fp.x-nx:nx-fp.x)+(ny-fp.y<0?fp.y-ny:ny-fp.y) < msum)
			m = i;
	}
	m %= 4;
	ret.x += dir[m][0];
	ret.y += dir[m][1];
	if(dir[m][0]!=0){
		if(dir[m][0]==1)
			ret.direction = Location::TURN_RIGHT;
		else
			ret.direction = Location::TURN_LEFT;
	}
	else if(dir[m][0]==0){
		if(dir[m][1]==1)
			ret.direction = Location::TURN_UP;
		else
			ret.direction = Location::TURN_DOWN;
	}

	
	return ret;

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
}

bool Food::generate()
{
	int x,y;
	loop:
	cc_timeval psv;  
	CCTime::gettimeofdayCocos2d( &psv, NULL );
	unsigned int tsrans = psv.tv_sec * 1000 + psv.tv_usec / 1000 + rand();
	srand(tsrans);
	x = CCRANDOM_0_1()*100;
	x = x % (VirtualMap::MAP_WIDTH - 2) + 2;

	CCTime::gettimeofdayCocos2d( &psv, NULL );
	tsrans = psv.tv_sec * 1000 + psv.tv_usec / 1000 + rand();
	srand(tsrans);
	y = CCRANDOM_0_1()*100;
	y = y % (VirtualMap::MAP_HEIGHT - 2) + 2;

	m_locate.x = x;
	m_locate.y = y;
	if (VirtualMap::map[x][y] != VirtualMap::emptyTag)
		goto loop;
	Location preLoc = VirtualMap::foodLocate;
	VirtualMap::foodLocate = m_locate;

	VirtualMap::map[x][y] = VirtualMap::foodTag;
	if (1<=preLoc.x && preLoc.x<=VirtualMap::MAP_WIDTH
		&& 1<=preLoc.y && preLoc.y<=VirtualMap::MAP_HEIGHT)
		VirtualMap::map[preLoc.x][preLoc.y] = VirtualMap::emptyTag;

	m_food->setPosition(VirtualMap::LocToPos(m_locate));

	return true;
}


bool Barrier::init(CCLayer *father_layer, const std::vector<Location> &bloc , char *filename)
{
	imgFilename = filename;
	for(int i=0; i<bloc.size(); i++)
	{
		m_locate.push_back(bloc[i]);

		CCSprite *pt = CCSprite::create(filename);
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
		CCSize contentSize = pt->getContentSize();
		pt->setScaleX(visibleSize.width/VirtualMap::MAP_WIDTH/contentSize.width);
		pt->setScaleY(visibleSize.height/VirtualMap::MAP_HEIGHT/contentSize.height);
		pt->setPosition(VirtualMap::LocToPos(m_locate[i]));

		father_layer->addChild(pt);
	}

	for(int i=0; i<m_locate.size(); i++)
	{
		VirtualMap::map[m_locate[i].x][m_locate[i].y] = VirtualMap::barrierTag;
	}

	return true;
}