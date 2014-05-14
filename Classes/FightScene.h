#ifndef __FIGHT_SCENE_H__
#define __FIGHT_SCENE_H__

#include "cocos2d.h"
#include "MapAttribute.h"
#include "Snakes.h"

#include <vector>

class FightScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(FightScene);

private:
	static const int m_playlayer_zOrder = 2;
	static const int m_bglayer_zOrder = 1;
	static const int m_playlayer_tag = 1;
	static const int m_bglayer_tag = 2;
};

class SnakesPlay : public cocos2d::CCLayer
{
public:
	virtual bool init();
	CREATE_FUNC(SnakesPlay);

	//重写触屏回调函数
	virtual bool ccTouchBegan(cocos2d::CCTouch* , cocos2d::CCEvent*);
	virtual void ccTouchMoved(cocos2d::CCTouch* , cocos2d::CCEvent*);
	virtual void ccTouchEnded(cocos2d::CCTouch* , cocos2d::CCEvent*);

	void StopGameCallback(CCObject* pSender);
	void scheUpdate(float);
	bool checkGame();
	Food curfood;
	Barrier m_walls;
	Barrier m_barriers;

private:
	bool m_disFlag;
	std::vector<Snake *> m_snakes;
	bool isStop;
};

class GameOver: public cocos2d::CCLayer
{
public:
	virtual bool init();
	CREATE_FUNC(GameOver);
	void StartNewGameCallback(CCObject* pSender);
	void ReturnHomeCallback(CCObject* pSender);
	void ExitGameCallback(CCObject* pSender);

};
#endif // __FIGHT_SCENE_H__
