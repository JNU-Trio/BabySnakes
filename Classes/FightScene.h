#ifndef __FIGHT_SCENE_H__
#define __FIGHT_SCENE_H__

#include "cocos2d.h"
#include "MapAttribute.h"
#include "Snakes.h"

#include <vector>
;
class FightScene : public cocos2d::CCScene {
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static FightScene* scene(int);

	// implement the "static node()" method manually
	CREATE_FUNC(FightScene);

	static const int m_playlayer_zOrder = 2;
    static const int m_playlayer_tag = 1;

    static const int m_bglayer_zOrder = 1;
    static const int m_bglayer_tag = 2;

    static const int m_infolayer_zOrder = 3;
    static const int m_infolayer_tag = 3;

    static const int m_overlayer_zOrder = 4;
    static const int m_overlayer_tag = 4;
};

#endif // __FIGHT_SCENE_H__