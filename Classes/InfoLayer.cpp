#include "InfoLayer.h"
#include "cocos2d.h"
#include "MapAttribute.h"
#include <vector>

USING_NS_CC;

bool InfoLayer::init() {
    if ( !CCLayer::init() ) {
        return false;
    }

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    std::vector<int> & m_CurScore = VirtualMap::m_CurScore;
    m_CurScore.clear();

    m_CurScore.push_back(0);
    char initstr[50];
    sprintf(initstr,"Earth: %d",m_CurScore[0]);
    snakeScore.push_back(CCLabelTTF::create(initstr,"fonts/Marker Felt.ttf", 40));
    snakeScore[0]->setPosition(ccp(100, visibleSize.height-50));
    this->addChild(snakeScore[0]);

    m_CurScore.push_back(0);
    sprintf(initstr,"Mars: %d",m_CurScore[1]);
    snakeScore.push_back(CCLabelTTF::create(initstr,"fonts/Marker Felt.ttf", 40));
    snakeScore[1]->setPosition(ccp(600, visibleSize.height-50));
    this->addChild(snakeScore[1]);

    this->schedule(schedule_selector(InfoLayer::scheUpdate),0.3);

    return true;
}

// refresh ths score each time
void InfoLayer::scheUpdate(float time) {
    std::vector<int> &m_CurScore = VirtualMap::m_CurScore;
    for(int i=0; i<VirtualMap::m_CurScore.size(); i++) {
        char curStr[50];
        if (i == 0)
            sprintf(curStr,"Earth: %d",m_CurScore[i]);
        else
            sprintf(curStr,"Mars: %d",m_CurScore[i]);
        snakeScore[i]->setString(curStr);
    }
}
