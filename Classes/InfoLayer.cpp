#include "InfoLayer.h"
#include "cocos2d.h"

USING_NS_CC;

bool InfoLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	CCLabelTTF *yourScore = CCLabelTTF::create("Score","fonts/Marker Felt.ttf", 40);
	yourScore->setPosition(ccp(100, visibleSize.height-50));
	this->addChild(yourScore);


	return true;
}

