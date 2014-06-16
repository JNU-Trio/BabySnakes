#include "SimpleAudioEngine.h"
#include <vector>

#include "FightScene.h"
#include "InfoLayer.h"
#include "SnakesPlay.h"
#include "BackgroundLayer.h"
#include "SingleSnakePlay.h"
#include "DoubleSnakePlay.h"
#include "DisappearSnakePlay.h"
#include "BossSnakePlay.h"
#include "DiceSnakePlay.h"

USING_NS_CC;

FightScene* FightScene::scene(int type) {
    // 'scene' is an autorelease object
    FightScene *scene = FightScene::create();

    // add background
    CCLayer *bglayer;
	switch(type)
	{
	case VirtualMap::SCENE_TYPE_DOUBLE : bglayer = DoubleBackground::create(); break;
	case VirtualMap::SCENE_TYPE_SINGLE : bglayer = SingleBackground::create(); break;
	case VirtualMap::SCENE_TYPE_DISAPPEAR : bglayer = DisappearBackground::create(); break;
	//case VirtualMap::SCENE_TYPE_ZHA : bglayer = ZhaBackground::create(); break;
	case VirtualMap::SCENE_TYPE_DICE : bglayer = DiceBackground::create(); break;
	case VirtualMap::SCENE_TYPE_BOSS : bglayer = BossBackground::create(); break;
	}
	scene->addChild(bglayer, m_bglayer_zOrder, m_bglayer_tag);

    // add infomation layer
    InfoLayer *infolayer = InfoLayer::create();
    scene->addChild(infolayer,m_infolayer_zOrder, m_infolayer_tag);

	// add play layer
	SnakesPlay *playlayer;
	switch(type)
	{
	case VirtualMap::SCENE_TYPE_DOUBLE : playlayer = DoubleSnakePlay::create(); break;
	case VirtualMap::SCENE_TYPE_SINGLE : playlayer = SingleSnakePlay::create(); break;
	case VirtualMap::SCENE_TYPE_DISAPPEAR : playlayer = DisappearSnakePlay::create(); break;
	//case VirtualMap::SCENE_TYPE_ZHA : playlayer = ZhaSnakePlay::create(); break;
	case VirtualMap::SCENE_TYPE_DICE : playlayer = DiceSnakePlay::create(); break;
	case VirtualMap::SCENE_TYPE_BOSS : playlayer = BossSnakePlay::create(); break;
	}
    scene->addChild(playlayer, m_playlayer_zOrder, m_playlayer_tag);

    // return the scene
    return scene;
}