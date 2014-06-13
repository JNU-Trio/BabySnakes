#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__
#include "cocos2d.h"

class GameOverLayer : public cocos2d::CCLayerColor {
public:
    bool init();
    CREATE_FUNC(GameOverLayer);
	void StartNewGameCallback(CCObject* pSender);
	void ReturnHomeCallback(CCObject* pSender);
	void ExitGameCallback(CCObject* pSender);

    cocos2d::CCLabelTTF *getLabel();

private :
    cocos2d::CCLabelTTF *m_label;
};

#endif
