#ifndef __INFOLAYER_H_
#define __INFOLAYER_H_

#include "cocos2d.h"

class InfoLayer : public cocos2d::CCLayer
{
	public:
	virtual bool init();
	CREATE_FUNC(InfoLayer);
};

#endif // __INFOLAYER_H_