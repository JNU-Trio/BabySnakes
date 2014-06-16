#ifndef __INFOLAYER_H_
#define __INFOLAYER_H_

#include "cocos2d.h"
#include <vector>

class InfoLayer : public cocos2d::CCLayer {
public:
	virtual bool init();
	CREATE_FUNC(InfoLayer);
    void scheUpdate(float);

private:
    std::vector<cocos2d::CCLabelTTF *>snakeScore;
};

#endif // __INFOLAYER_H_