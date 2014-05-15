#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__
#include "cocos2d.h"

class GameOverScene : public cocos2d::CCLayer
{
public:
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(GameOverScene);
	void StartNewGameCallback(CCObject* pSender);
	void ReturnHomeCallback(CCObject* pSender);
	void ExitGameCallback(CCObject* pSender);
};

#endif