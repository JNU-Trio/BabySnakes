#include "Snakes.h"
#include "MapAttribute.h"

USING_NS_CC;

Location SimpleSnake::moveTo()
{
	Location ret;
	return ret;
}

void SimpleSnake::eatFood()
{
}

bool SimpleSnake::initialize(CCLayer *father_layer)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSize contentSize;

	// 初始化蛇的head,tail,body的位置
	m_head.x = 8;
	m_head.y = 5;
	m_tail.x = 6;
	m_tail.y = 5;
	Location tmp;
	tmp.x = 7;
	tmp.y = 5;
	m_body.push_back(tmp);

	// head创建sprite
	m_shead = CCSprite::create("snakes/snakehead1.png");
	contentSize = m_shead->getContentSize();
	m_shead->setScaleX(visibleSize.width/MAP_WIDTH/contentSize.width);
	m_shead->setScaleY(visibleSize.height/MAP_HEIGHT/contentSize.height);
	m_shead->setPosition(LocToPos(m_head));
	father_layer->addChild(m_shead);

	// tail创建sprite
	m_stail = CCSprite::create("snakes/snaketail1.png");
	contentSize = m_stail->getContentSize();
	m_stail->setScaleX(visibleSize.width/MAP_WIDTH/contentSize.width);
	m_stail->setScaleY(visibleSize.height/MAP_HEIGHT/contentSize.height);
	m_stail->setPosition(LocToPos(m_tail));
	father_layer->addChild(m_stail);

	//  body创建sprite
	CCSprite *stmp = CCSprite::create("snakes/snakebody1.png");
	m_sbody.push_back(stmp);
	for(int i=0; i<m_sbody.size(); i++)
	{
		contentSize = m_sbody[i]->getContentSize();
		m_sbody[i]->setScaleX(visibleSize.width/MAP_WIDTH/contentSize.width);
		m_sbody[i]->setScaleY(visibleSize.height/MAP_HEIGHT/contentSize.height);
		m_sbody[i]->setPosition(LocToPos(m_body[i]));
		father_layer->addChild(m_sbody[i]);
	}

	return true;
}