#ifndef __SNAKES_H_
#define __SNAKES_H_

#include "cocos2d.h"
#include "MapAttribute.h"
#include <vector>

// ������
class Snake
{
public:
	// ��������һ��λ��
	virtual Location moveTo()=0;

	// �߳�ʳ��
	virtual void eatFood()=0;

	// �ߵĳ�ʼ��
	virtual bool initialize(cocos2d::CCLayer *)=0;

protected:

	// �ߵ�λ����Ϣ
	Location m_head, m_tail;
	std::vector<Location> m_body;

	// ����ߵ�sprite����
	cocos2d::CCSprite *m_shead, *m_stail;
	std::vector<cocos2d::CCSprite *> m_sbody;
};

// �̳г����ߵļ���
class SimpleSnake : public Snake
{
	Location moveTo();
	void eatFood();
	bool initialize(cocos2d::CCLayer *);
};

#endif // __SNAKES_H_