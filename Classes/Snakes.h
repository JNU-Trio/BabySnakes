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
	virtual void eatFood(cocos2d::CCLayer *, SnakeLocation, SnakeImgFilename)=0;

	// �ߵĳ�ʼ��
	virtual bool initialize(cocos2d::CCLayer *, SnakeLocation, SnakeImgFilename)=0;

	// �ߵ�λ����Ϣ
	SnakeLocation m_snake;

	// ����ߵ�sprite����
	cocos2d::CCSprite *m_shead, *m_stail;
	std::vector<cocos2d::CCSprite *> m_sbody;
};

// �̳г����ߵļ���
class SimpleSnake : public Snake
{
	bool moveTo(Location);
	void eatFood(cocos2d::CCLayer *, SnakeLocation, SnakeImgFilename);
	bool initialize(cocos2d::CCLayer *, SnakeLocation, SnakeImgFilename);
};

class Control
{
public:
	virtual Location nextMove(std::vector<SnakeLocation>) = 0;
};

class AIControl : public Control
{
	Location nextMove(std::vector<SnakeLocation>);
};

class HumanControl : public Control
{
	Location nextMove(std::vector<SnakeLocation>);
};

class Food
{
public:
	Location m_locate;
	bool generate();
	cocos2d::CCNode *food;
};

#endif // __SNAKES_H_