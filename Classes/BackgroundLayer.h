#ifndef __BACKGROUND_LAYER_H__
#define __BACKGROUND_LAYER_H__

#include "cocos2d.h"
#include "Snakes.h"

#include <vector>
;
class DoubleBackground : public cocos2d::CCLayer {
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// implement the "static node()" method manually
	CREATE_FUNC(DoubleBackground);
};

#endif // __BACKGROUND_LAYER_H__
