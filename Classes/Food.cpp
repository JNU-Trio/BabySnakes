#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "Food.h"
#include "SpriteFactory.h"

USING_NS_CC;

bool Food::hitFood(Location loc) {
	for(int i=0; i<m_locate.size(); i++)
		if (loc == m_locate[i])
			return true;
	return false;
}

/////////////////////////SimpleFood//////////////////////////////////
bool SimpleFood::generate() {
	std::vector<Location> locs;
	for(int i=1; i<=VirtualMap::MAP_WIDTH; i++) {
		for(int j=1; j<=VirtualMap::MAP_HEIGHT; j++) {
			if (VirtualMap::map[i][j] == VirtualMap::emptyTag) {
				Location tmp;
				tmp.x = i;
				tmp.y = j;
				tmp.direction = Location::TURN_RIGHT;
				locs.push_back(tmp);
			}
		}
	}

	int x = VirtualMap::getRandom(locs.size());
	VirtualMap::changeTag(locs[x], VirtualMap::foodTag);
	m_locate[0] = locs[x];
	m_sprite[0]->setPosition(VirtualMap::LocToPos(locs[x]));

	return true;
}

void SimpleFood::eatFood(FoodEffect *effect, Location loc) {
	m_foodEffect = effect;
	m_foodEffect->addScore(scoreNum);
	m_foodEffect->beLonger(1);
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


/////////////////////////DisappearFood//////////////////////////////////
bool DisappearFood::generate() {
	std::vector<Location> locs;
	for(int i=1; i<=VirtualMap::MAP_WIDTH; i++) {
		for(int j=1; j<=VirtualMap::MAP_HEIGHT; j++) {
			if (VirtualMap::map[i][j] == VirtualMap::emptyTag) {
				Location tmp;
				tmp.x = i;
				tmp.y = j;
				tmp.direction = Location::TURN_RIGHT;
				locs.push_back(tmp);
			}
		}
	}

	int x = VirtualMap::getRandom(locs.size());
	VirtualMap::changeTag(locs[x], VirtualMap::foodTag);
	m_locate.clear();
	m_locate.push_back(locs[x]);
	m_type.clear();
	int tmp = VirtualMap::getRandom(6);
	if (tmp == 0)
		tmp = 1;
	else
		tmp = 0;
	m_type.push_back(tmp);
	
	father->removeChild(m_sprite[0]);
	SpriteFactory *factory = new PlaySpriteFactory();
	m_sprite[0] = factory->getSprite(m_images[m_type[0]],locs[x]);
	father->addChild(m_sprite[0]);
	delete factory;
	return true;
}

void DisappearFood::eatFood(FoodEffect *effect, Location loc) {
	m_foodEffect = effect;

	if (m_type[0] == 0) {
		effect->addScore(2);
		effect->beLonger(1);
	} else {
		effect->addScore(8);
		effect->beShorter(2);
		effect->disappear(100);
	}
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("eatfood-sound.wav");
	generate();
}

void DisappearFood::updateVirtualMap() {
	for(int i=0; i<m_locate.size(); i++)
		VirtualMap::changeTag(m_locate[i],m_tag);
}

bool DisappearFood::hitFood(Location loc) {
	return Food::hitFood(loc);
}

//////////////////DiceFood//////////////////////////////////
bool DiceFood::generate() {
	father->removeChild(m_show);
	std::vector<Location> locs;
	for(int i=1; i<=VirtualMap::MAP_WIDTH; i++)
		for(int j=1; j<=VirtualMap::MAP_HEIGHT; j++)
			if (VirtualMap::map[i][j] == VirtualMap::emptyTag)
			{
				Location tmp;
				tmp.x = i;
				tmp.y = j;
				tmp.direction = Location::TURN_RIGHT;
				locs.push_back(tmp);
			}
	
	int x = VirtualMap::getRandom(locs.size());

	VirtualMap::changeTag(locs[x], VirtualMap::foodTag);
	m_locate[0] = locs[x];
	SpriteFactory *spritefactory = new PlaySpriteFactory();
	
	m_sprite[0] = spritefactory->getSprite(m_image,m_locate[0]);
	m_sprite[0]->setPosition(VirtualMap::LocToPos(locs[x]));
	father->addChild(m_sprite[0]);
	delete spritefactory;
	return true;
}

void DiceFood::eatFood(FoodEffect *effect, Location loc) {
	father->removeChild(m_sprite[0]);
	m_foodEffect = effect;
	int m_number = VirtualMap::getRandom(6);
	m_number++;

	CCAnimation *animation = CCAnimation::create();  
	for (int i = 0; i < 6; i++) {
		char szImageFileName[128] = {0};  
		sprintf(szImageFileName, "tools/%d.png", i+1);  
		animation->addSpriteFrameWithFileName(szImageFileName);    
	}  
	// dice will run 10 round then stop
	animation->setDelayPerUnit(VirtualMap::MIN_SPEED*10 / 6.0f); // 这个动画包含6帧，将会持续2.0秒.   
	animation->setRestoreOriginalFrame(true); 

	CCAnimate *action = CCAnimate::create(animation);
	
	char filename[50] = {0};  
	sprintf(filename, "tools/%d.png", m_number);  
	m_show = CCSprite::create(filename);
	
	Location tmp;
	tmp.x = 11;
	tmp.y = 10;
	tmp.direction = Location::TURN_RIGHT;

	m_show->setPosition(VirtualMap::LocToPos(tmp));
	father->addChild(m_show);
	m_show->runAction(action);  // 运行精灵对象
	switch(m_number)
	{
	case 1:
		{
			m_foodEffect->addScore(10);
			m_foodEffect->beLonger(1);
		};
		break;
	case 2:
		{
			m_foodEffect->beLonger(3);
		};
		break;
	case 3:
		{
			m_foodEffect->addScore(-5);
		};
		break;
	case 4:
		{
			m_foodEffect->addSpeed(1);
		};
		break;
	case 5:
		{
			m_foodEffect->beShorter(3);
		};
		break;
	case 6:
		{
			m_foodEffect->addSpeed(-1);
		};
		break;
	}
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("eatfood-sound.wav");
	//father->removeChild(sprite,true);
	m_gone = true;
	m_time = 40; // after 40 round it food will show again
}

void DiceFood::updateVirtualMap() {
	for(int i=0; i<m_locate.size(); i++)
		VirtualMap::changeTag(m_locate[i],m_tag);
}

bool DiceFood::hitFood(Location loc) {
	if (m_gone) {
		if (!m_time) {
			m_gone = false;
			generate();
		}
		m_time--;
		return false;
	}
	return Food::hitFood(loc);
}


/////////////////////////MultiFood//////////////////////////////////
bool MultiFood::generate() {
	std::vector<Location> locs;
	for(int i=1; i<=VirtualMap::MAP_WIDTH; i++) {
		for(int j=1; j<=VirtualMap::MAP_HEIGHT; j++) {
			if (VirtualMap::map[i][j] == VirtualMap::emptyTag) {
				Location tmp;
				tmp.x = i;
				tmp.y = j;
				tmp.direction = Location::TURN_RIGHT;
				locs.push_back(tmp);
			}
		}
	}

	int x = VirtualMap::getRandom(locs.size());
	VirtualMap::changeTag(locs[x], VirtualMap::foodTag);
	m_locate[0] = locs[x];
	m_sprite[0]->setPosition(VirtualMap::LocToPos(locs[x]));
	return true;
}

void MultiFood::eatFood(FoodEffect *effect, Location loc) {
	m_foodEffect = effect;
	for(int i=0; i<m_locate.size(); i++) {
		if (m_locate[i] == loc) {
			if (0 == i) {
				effect->addScore(2);
				effect->beLonger(1);
			} else {
				effect->reduceScore(2);
				m_locate.erase(m_locate.begin()+i);
				father->removeChild(m_sprite[i]);
				m_sprite.erase(m_sprite.begin()+i);
			}
			break;
		}
	}
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("eatfood-sound.wav");

	generate();
}

void MultiFood::updateVirtualMap() {
	for(int i=0; i<m_locate.size(); i++)
		VirtualMap::changeTag(m_locate[i],m_tag);
}

bool MultiFood::hitFood(Location loc) {
	return Food::hitFood(loc);
}

Location MultiFood::nextMove(SnakeLocation p) {
	int dir[4][2] = {-1,0,1,0,0,-1,0,1};
	Location ret = p.head;
	Location fp = m_locate[0];
	int m = 0;
	int a = ret.x + dir[0][0];
	int b = ret.y + dir[0][1];
	int msum = a-fp.x < 0 ? fp.x-a:a-fp.x;
	msum += (b-fp.y < 0 ? fp.y-b:b-fp.y);
	int i;
    for(i=0; i<4; i++) {
		ret = p.head;
		int nx = ret.x+dir[i][0], ny = ret.y+dir[i][1];
		if ((VirtualMap::map[nx][ny] == VirtualMap::emptyTag
            || VirtualMap::map[nx][ny] == VirtualMap::foodTag))
        {
			m = i;
			break;
		}
	}

    for(i = m+1; i<4; i++) {
		ret = p.head;
		int nx = ret.x+dir[i][0], ny = ret.y+dir[i][1];
		if ((VirtualMap::map[nx][ny] == VirtualMap::emptyTag
			|| VirtualMap::map[nx][ny] == VirtualMap::foodTag)
			&& (nx-fp.x<0?fp.x-nx:nx-fp.x)+(ny-fp.y<0?fp.y-ny:ny-fp.y) < msum)
			m = i;
	}
	m %= 4;
	ret.x += dir[m][0];
	ret.y += dir[m][1];
	if(dir[m][0]!=0){
		if(dir[m][0]==1)
			ret.direction = Location::TURN_RIGHT;
		else
			ret.direction = Location::TURN_LEFT;
	}
	else if(dir[m][0]==0){
		if(dir[m][1]==1)
			ret.direction = Location::TURN_UP;
		else
			ret.direction = Location::TURN_DOWN;
	}

	return ret;
}