#ifndef __SNAKES_H_
#define __SNAKES_H_

#include "cocos2d.h"
#include "MapAttribute.h"
#include <vector>

struct SnakeImgFilename
{
	char *head,*body,*tail;
};

// ������
class Snake
{
public:
	// ��������һ��λ��
	virtual bool moveTo(Location)=0;

	// �߳�ʳ��
	virtual void eatFood(cocos2d::CCLayer *)=0;

	// �ߵĳ�ʼ��
	virtual bool initialize(cocos2d::CCLayer *, SnakeLocation, SnakeImgFilename)=0;

	// �ߵ�λ����Ϣ
	SnakeLocation m_snake;

	// ����ߵ�sprite����
	cocos2d::CCSprite *m_shead, *m_stail;
	std::vector<cocos2d::CCSprite *> m_sbody;

	// ����ߵ�ͼƬ
	SnakeImgFilename m_snakeImage;
};

// �̳г����ߵļ���
class SimpleSnake : public Snake
{
	bool moveTo(Location);
	void eatFood(cocos2d::CCLayer *);
	bool initialize(cocos2d::CCLayer *, SnakeLocation, SnakeImgFilename);
};

class Control
{
public:
	virtual Location nextMove(SnakeLocation) = 0;
};

class AIControl : public Control
{
	Location nextMove(SnakeLocation);
};

class HumanControl : public Control
{
	Location nextMove(SnakeLocation);
};

class Food
{
public:
	Location m_locate;
	bool generate();
	cocos2d::CCNode *m_food;
};

class Barrier
{
public:
	std::vector<Location> m_locate;
	std::vector<cocos2d::CCSprite *> m_images;
	char *imgFilename;
	bool init(cocos2d::CCLayer *, const std::vector<Location> &, char *);
};

#endif // __SNAKES_H_