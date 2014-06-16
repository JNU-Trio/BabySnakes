#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__
#include "cocos2d.h"

class GameOverLayer : public cocos2d::CCLayerColor {
public:
    bool init();
    CREATE_FUNC(GameOverLayer);
	void StartNewGameCallback(CCObject* pSender);
	void StartNextCallback(CCObject* pSender);
	void ReturnHomeCallback(CCObject* pSender);
	void ExitGameCallback(CCObject* pSender);
	static cocos2d::CCScene *getScene(int, bool);

	static char *m_bgImage;
	static int m_nextScene;
	static int m_curScene;
};

#endif
