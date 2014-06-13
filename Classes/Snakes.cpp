#include "Snakes.h"
#include "MapAttribute.h"
#include "SpriteFactory.h"
#include <vector>

USING_NS_CC;

bool Snake::moveTo(Location nextLoc) {
	int bodysize = m_snake.body.size();
	VirtualMap::map[m_snake.tail.x][m_snake.tail.y] = VirtualMap::emptyTag;
	m_snake.tail = m_snake.body[bodysize-1];
    for(int i=bodysize-1; i>0; i--) {
		m_snake.body[i] = m_snake.body[i-1];
	}
	m_snake.body[0] = m_snake.head;
	m_snake.head = nextLoc;

	VirtualMap::map[m_snake.head.x][m_snake.head.y] = m_tag;

	CCActionInterval* headaction = CCMoveTo::create(VirtualMap::SPEED,VirtualMap::LocToPos(m_snake.head));
	std::vector<CCActionInterval*> bodyaction;
    for(int i=0; i<bodysize; i++) {
        m_sbody[i]->setRotation(m_snake.body[i].direction);
		bodyaction.push_back(CCMoveTo::create(VirtualMap::SPEED,VirtualMap::LocToPos(m_snake.body[i])));
	}

	CCActionInterval* tailaction = CCMoveTo::create(VirtualMap::SPEED,VirtualMap::LocToPos(m_snake.tail));

	m_shead->runAction(headaction);
	m_shead->setRotation(m_snake.head.direction);
    for(int i=0; i<bodysize; i++) {
		m_sbody[i]->runAction(bodyaction[i]);
	}
	m_stail->runAction(tailaction);
	m_stail->setRotation(m_snake.tail.direction);
	return true;
}

int Snake::getScore() {
	return  m_score;
}

void Snake::updateVirtualMap() {
	VirtualMap::changeTag(m_snake.head,m_tag);
	VirtualMap::changeTag(m_snake.tail,m_tag);
	for(int i=0; i<m_snake.body.size(); i++)
		VirtualMap::changeTag(m_snake.body[i],m_tag);
}

bool Snake::hitOther(Location loc) {
	if (m_tag != VirtualMap::map[loc.x][loc.y] &&
		VirtualMap::barrierTag != VirtualMap::map[loc.x][loc.y] &&
		VirtualMap::emptyTag != VirtualMap::map[loc.x][loc.y] &&
		VirtualMap::foodTag != VirtualMap::map[loc.x][loc.y])
		return true;
	else
		return false;
}
bool Snake::hitBody(Location loc) {
	if (m_tag == VirtualMap::map[loc.x][loc.y])
		return true;
	else
		return false;
}
bool Snake::hitFood(Location loc) {
	if (VirtualMap::foodTag == VirtualMap::map[loc.x][loc.y])
		return true;
	else
		return false;
}
bool Snake::hitBarrier(Location loc) {
	if (VirtualMap::barrierTag == VirtualMap::map[loc.x][loc.y])
		return true;
	else
		return false;
}

bool SimpleSnake::moveTo(Location nextLoc) {
	Snake::moveTo(nextLoc);
	return true;
}

void SimpleSnake::updateVirtualMap() {
	Snake::updateVirtualMap();
}

void SimpleSnake::addScore(int score) {
	m_score += score;
}

void SimpleSnake::disappear() {
}

void SimpleSnake::beLonger(int length) {
	while (length--) {
		m_snake.body.push_back(m_snake.tail);

		SpriteFactory *factory = new PlaySpriteFactory();
		int i = m_sbody.size() - 1;
		CCSprite *stmp = factory->getSprite(m_snakeImage.body,m_snake.body[i]);
		m_sbody.push_back(stmp);
		father->addChild(stmp);
	}
}

void SimpleSnake::beShorter(int length) {
	for(int i=0; i<length; i++) {
		int size = m_snake.body.size();
		Location cur = m_snake.body[size-1];
		
		VirtualMap::map[m_snake.tail.x][m_snake.tail.y] = VirtualMap::emptyTag;
		m_snake.tail = cur;
		m_sbody.pop_back();
		m_snake.body.pop_back();

		m_stail->setPosition(VirtualMap::LocToPos(m_snake.tail));
		m_stail->setRotation(m_snake.tail.direction);
	}
}
