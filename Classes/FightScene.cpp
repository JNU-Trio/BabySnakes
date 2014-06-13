#include "SimpleAudioEngine.h"
#include <vector>

#include "FightScene.h"
#include "InfoLayer.h"
#include "SnakesPlay.h"
#include "BackgroundLayer.h"

USING_NS_CC;

FightScene* FightScene::scene(int type) {
    // 'scene' is an autorelease object
    FightScene *scene = FightScene::create();

    // add background
    CCLayer *bglayer;
	switch(type)
	{
	case 1:bglayer = DoubleBackground::create(); break;
	}
    scene->addChild(bglayer, m_bglayer_zOrder, m_bglayer_tag);

    // add infomation layer
    InfoLayer *infolayer = InfoLayer::create();
    scene->addChild(infolayer,m_infolayer_zOrder, m_infolayer_tag);

    // add play layer
    SnakesPlay *playlayer;
	switch(type)
	{
	case 1:playlayer = DoubleSnakePlay::create(); break;
	}
    scene->addChild(playlayer, m_playlayer_zOrder, m_playlayer_tag);

    // return the scene
    return scene;
}
