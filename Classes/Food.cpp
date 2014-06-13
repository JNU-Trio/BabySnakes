#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "Food.h"

USING_NS_CC;

bool Food::hitFood(Location loc) {
	for(int i=0; i<m_locate.size(); i++)
		if (loc == m_locate[i])
			return true;
	return false;
}

bool SimpleFood::generate() {
	std::vector<Location> locs;
	for(int i=1; i<=VirtualMap::MAP_WIDTH; i++)
		for(int j=1; j<=VirtualMap::MAP_HEIGHT; j++)
			if (VirtualMap::map[i][j] == VirtualMap::emptyTag)
			{
				Location tmp(i,j);
				locs.push_back(tmp);
			}

	cc_timeval psv;  
	CCTime::gettimeofdayCocos2d( &psv, NULL );
	unsigned int tsrans = psv.tv_sec * 1000 + psv.tv_usec / 1000 + rand();
	srand(tsrans);
	int x = CCRANDOM_0_1()*1000;
	x = x % locs.size();

	VirtualMap::changeTag(locs[x], VirtualMap::foodTag);
	m_locate[0] = locs[x];
	m_sprite[0]->setPosition(VirtualMap::LocToPos(locs[x]));

	return true;
}

void SimpleFood::eatFood(FoodEffect *foodEffect, Location loc) {
	foodEffect->addScore(scoreNum);
	foodEffect->beLonger(1);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("eatfood-sound.wav");
	generate();
}

void SimpleFood::updateVirtualMap() {
	for(int i=0; i<m_locate.size(); i++)
		VirtualMap::changeTag(m_locate[i],m_tag);
}

bool SimpleFood::hitFood(Location loc) {
	return Food::hitFood(loc);
}