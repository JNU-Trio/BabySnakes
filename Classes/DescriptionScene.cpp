#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "DescriptionScene.h"
#include "FightScene.h"

USING_NS_CC;

char *DescriptionScene::m_bgImage;
int DescriptionScene::m_nextScene;

CCScene* DescriptionScene::scene() {
    CCScene *scene = CCScene::create();
    DescriptionScene *layer = DescriptionScene::create();
    scene->addChild(layer);
    return scene;
}

bool DescriptionScene::init() {
	// super init first
    if ( !CCLayer::init() ) {
        return false;
    }

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    // create background sprite
    CCSprite* pSprite = CCSprite::create(m_bgImage);
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    CCSize bgimgSize = pSprite->getContentSize();
    pSprite->setScaleX(visibleSize.width/bgimgSize.width);
    pSprite->setScaleY(visibleSize.height/bgimgSize.height);

    this->addChild(pSprite, 0);

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    this->setTouchEnabled(true);
	this->scheduleOnce(schedule_selector(DescriptionScene::changeToNext), 10.0f);

	return true;
}

CCScene* DescriptionScene::getScene(int next) {
	switch(next)
	{
	case VirtualMap::SCENE_TYPE_SINGLE : m_bgImage = "backgrounds/description1.png" ; break;
	case VirtualMap::SCENE_TYPE_DOUBLE : m_bgImage = "backgrounds/description2.png" ; break;
	case VirtualMap::SCENE_TYPE_DISAPPEAR : m_bgImage = "backgrounds/description3.png" ; break;
	case VirtualMap::SCENE_TYPE_ZHA : m_bgImage = "backgrounds/description4.png" ; break;
	case VirtualMap::SCENE_TYPE_DICE : m_bgImage = "backgrounds/description5.png" ; break;
	case VirtualMap::SCENE_TYPE_BOSS : m_bgImage = "backgrounds/description6.png" ; break;
	}
	m_nextScene = next;
	return scene();
}

void DescriptionScene::changeToNext(float time) {
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.1f,
		FightScene::scene(m_nextScene)));
}

// rewrite touch method
bool DescriptionScene::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* pevent) {
	this->changeToNext(0);
    return true;
}