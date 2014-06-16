#include "Snakes.h"
#include "MapAttribute.h"
#include "SpriteFactory.h"
#include <vector>

USING_NS_CC;

int Snake::getScore() {
	return  m_score;
}

SnakeLocation Snake::getSnakeLoc() {
	return m_snake;
}

int Snake::count() {
	m_timeCounter = (m_timeCounter + 1) % m_updateSpeed;
	return m_timeCounter;
}

void Snake::updateVirtualMap() {
	VirtualMap::changeTag(m_snake.head,m_tag);
	VirtualMap::changeTag(m_snake.tail,m_tag);
	for(int i=0; i<m_snake.body.size(); i++)
		VirtualMap::changeTag(m_snake.body[i],m_tag);
}

////////////////////SimpleSnake//////////////////////////
bool SimpleSnake::moveTo(Location nextLoc) {
	if (m_disapFlag)
		return true;
	VirtualMap::changeTag(nextLoc,m_tag);
	VirtualMap::changeTag(m_snake.tail, VirtualMap::emptyTag);

	int bodysize = m_snake.body.size();
	m_snake.tail = m_snake.body[bodysize-1];
    for(int i=bodysize-1; i>0; i--) {
		m_snake.body[i] = m_snake.body[i-1];
	}
	m_snake.body[0] = m_snake.head;
	m_snake.head = nextLoc;
	
	moveAction(m_snake);

	return true;
}

void SimpleSnake::updateVirtualMap() {
	Snake::updateVirtualMap();
}

bool SimpleSnake::comeBack() {
	int length = m_snake.body.size() + 2;
	std::vector<Location> locs = VirtualMap::getNewLoc(length);
	m_snake.head = locs[locs.size()-1];
	m_snake.tail = locs[0];
	int bodysize = m_snake.body.size();
	for(int i=0; i<bodysize; i++)
		m_snake.body[i] = locs[bodysize-i];

	m_shead->setPosition(VirtualMap::LocToPos(m_snake.head));
	m_shead->setRotation(m_snake.head.direction);
	m_stail->setPosition(VirtualMap::LocToPos(m_snake.tail));
	m_stail->setRotation(m_snake.tail.direction);
	for(int i=0; i<m_snake.body.size(); i++) {
		m_sbody[i]->setPosition(VirtualMap::LocToPos(m_snake.body[i]));
		m_sbody[i]->setRotation(m_snake.body[i].direction);
	}

	VirtualMap::DIRECTION = 1;
	m_updateSpeed = 5;

	return true;
}

int SimpleSnake::count() {
	int tmp = Snake::count();
	if (0 == tmp && m_disapFlag) {
		comeBack();
		m_disapFlag = false;
	}

	return tmp;
}

void SimpleSnake::moveAction(SnakeLocation aimLoc) {
	float speed = 0.5*m_updateSpeed*VirtualMap::MIN_SPEED;
	//create action
	CCActionInterval* headaction = CCMoveTo::create(speed,VirtualMap::LocToPos(m_snake.head));
	
	std::vector<CCActionInterval*> bodyaction;
	int bodysize = aimLoc.body.size();
    for(int i=0; i<bodysize; i++) {
		bodyaction.push_back(CCMoveTo::create(speed,VirtualMap::LocToPos(m_snake.body[i])));
	}

	CCActionInterval* tailaction = CCMoveTo::create(speed,VirtualMap::LocToPos(m_snake.tail));

	// run action
	m_shead->runAction(headaction);
	m_shead->setRotation(m_snake.head.direction);
    for(int i=0; i<bodysize; i++) {
		m_sbody[i]->runAction(bodyaction[i]);
		m_sbody[i]->setRotation(m_snake.body[i].direction);
	}
	m_stail->runAction(tailaction);
	m_stail->setRotation(m_snake.tail.direction);
}

//////SimpleSnake FoodEffect implemention/////////
void SimpleSnake::addScore(int score) {
	m_score += score;
}

void SimpleSnake::reduceScore(int score) {
	m_score -= score;
}

void SimpleSnake::beLonger(int length) {
	SpriteFactory *factory = new PlaySpriteFactory();
	while (length--) {
		m_snake.body.push_back(m_snake.tail);
		CCSprite *stmp = factory->getSprite(m_snakeImage.body,m_snake.tail);
		m_sbody.push_back(stmp);
		father->addChild(stmp);
	}
	delete factory;
}

void SimpleSnake::beShorter(int length) {
	for(int i=0; i<length && m_snake.body.size() > 1; i++) {
		int size = m_snake.body.size();
		Location cur = m_snake.body[size-1];
		
		VirtualMap::changeTag(m_snake.tail,VirtualMap::emptyTag);
		m_snake.tail = cur;
		father->removeChild(m_sbody[m_sbody.size()-1],true);
		m_sbody.pop_back();
		m_snake.body.pop_back();

		m_stail->setPosition(VirtualMap::LocToPos(m_snake.tail));
		m_stail->setRotation(m_snake.tail.direction);
	}
}

void SimpleSnake::addSpeed(int length) {
	m_updateSpeed += length;
	if (m_updateSpeed <= 0)
		m_updateSpeed = 1;
}

void SimpleSnake::disappear(int time) {
	m_disapFlag = true;

	Location gone;
	gone.x = 30;
	gone.y = 30;

	VirtualMap::changeTag(m_snake.head,VirtualMap::emptyTag);
	VirtualMap::changeTag(m_snake.tail,VirtualMap::emptyTag);
	for(int i=0; i<m_snake.body.size(); i++)
		VirtualMap::changeTag(m_snake.body[i],VirtualMap::emptyTag);

	m_snake.head = gone;
	gone.x++;
	gone.y++;
	m_shead->setPosition(VirtualMap::LocToPos(gone));
	m_snake.tail = gone;
	gone.x++;
	gone.y++;
	m_stail->setPosition(VirtualMap::LocToPos(gone));
	for(int i=0; i<m_snake.body.size(); i++) {
		m_sbody[i]->setPosition(VirtualMap::LocToPos(gone));
		m_snake.body[i] = gone;
		gone.x++;
		gone.y++;
	}

	addSpeed(time);
}

////////////////////////////////////////////
bool SimpleSnake::hitOther(SnakeLocation loc) {
	if (m_snake.head == loc.head)
		return true;
	if (m_snake.head == loc.tail)
		return true;
	for(int i=0; i<loc.body.size(); i++)
		if (m_snake.head == loc.body[i])
			return true;
	return false;
}
bool SimpleSnake::hitBody() {
	if (m_snake.head == m_snake.tail)
		return true;
	for(int i=0; i<m_snake.body.size(); i++)
		if (m_snake.head == m_snake.body[i])
			return true;
	return false;
}
bool SimpleSnake::hitFood(Location loc) {
	if (m_snake.head == loc)
		return true;
	else
		return false;
}
bool SimpleSnake::hitBarrier(Location loc) {
	if (m_snake.head == loc)
		return true;
	else
		return false;
}

/////////////BossSnake///////////////////
void BossSnake::beLonger(int l) {}

void BossSnake::reduceScore(int score) {
}