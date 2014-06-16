#ifndef __DESCRIPTION_SCENE_H_
#define __DESCRIPTION_SCENE_H_

#include "cocos2d.h"

class DescriptionScene : public cocos2d::CCLayer {
public:
	virtual bool init();
	CREATE_FUNC(DescriptionScene);

	static cocos2d::CCScene* scene();
	static cocos2d::CCScene* getScene(int);

	static char *m_bgImage;
	static int m_nextScene;

	void changeToNext(float);
	// implement touch event
	bool ccTouchBegan(cocos2d::CCTouch* , cocos2d::CCEvent*);
	void ccTouchMoved(cocos2d::CCTouch* , cocos2d::CCEvent*){};
	void ccTouchEnded(cocos2d::CCTouch* , cocos2d::CCEvent*){};
};

#endif // __DESCRIPTION_SCENE_H_