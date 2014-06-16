#include "cocos2d.h"

#include "FoodFactory.h"
#include "SpriteFactory.h"

USING_NS_CC;

Food *SimpleFoodFactory::createFood(cocos2d::CCNode *fatherLayer) {
	SpriteFactory *spritefactory = new PlaySpriteFactory();
	char *img = getImg();
	Location loc = getLoc();
	SimpleFood *food = new SimpleFood();
	food->m_locate.push_back(loc);
	food->m_sprite.push_back(spritefactory->getSprite(img,loc));
	fatherLayer->addChild(food->m_sprite[0]);

	food->father = fatherLayer;
	food->m_tag = VirtualMap::foodTag;
	food->updateVirtualMap();

	delete spritefactory;

	return food;
}

char *SimpleFoodFactory::getImg() {
	return "foods/shit1.png";
}

Location SimpleFoodFactory::getLoc()
{
	Location ret;
	ret.x = 3;
	ret.y = 3;
	return ret;
}

///////////////////////DisappearFoodFactory//////////////////////////////

Food *DisappearFoodFactory::createFood(cocos2d::CCNode *fatherLayer) {
	DisappearFood *food = new DisappearFood();
	food->m_images = getImg();
	food->father = fatherLayer;
	food->m_tag = VirtualMap::foodTag;
	food->updateVirtualMap();

	food->m_sprite.push_back(CCSprite::create());

	return food;
}

std::vector<char *> DisappearFoodFactory::getImg() {
	std::vector<char *> ret;
	char *tmp = "foods/shit3.png";
	ret.push_back(tmp);
	tmp = "foods/shit3-2.png";
	ret.push_back(tmp);
	return ret;
}

/////////////////////DiceFoodFactory////////////////////////////

Food *DiceFoodFactory::createFood(cocos2d::CCNode *fatherLayer) {
	SpriteFactory *spritefactory = new PlaySpriteFactory();
	char *img = getImg();
	Location loc = getLoc();
	DiceFood *food = new DiceFood();
	
	food->m_image = img;
	food->m_locate.push_back(loc);
	food->m_sprite.push_back(CCSprite::create());

	food->father = fatherLayer;
	food->m_tag = VirtualMap::foodTag;
	food->updateVirtualMap();

	food->m_number = 0;
	food->m_gone = false;
	food->m_show = CCSprite::create();
	return food;
}

char *DiceFoodFactory::getImg() {
	return "foods/shit2.png";
}

Location DiceFoodFactory::getLoc()
{
	Location ret;
	ret.x = 3;
	ret.y = 3;
	return ret;
}


//////////////////////MultiFoodFactory//////////////////////////////

Food *MultiFoodFactory::createFood(cocos2d::CCNode *fatherLayer) {

	SpriteFactory *spritefactory = new PlaySpriteFactory();
	std::vector<char *>img = getImg();
	std::vector<Location> loc = getLoc();
	MultiFood *food = new MultiFood();
	food->m_locate = loc;
	food->m_sprite.push_back(spritefactory->getSprite(img[0],loc[0]));
	fatherLayer->addChild(food->m_sprite[0]);

	for(int i=1; i<loc.size(); i++) {
		food->m_sprite.push_back(spritefactory->getSprite(img[1],loc[i]));
		fatherLayer->addChild(food->m_sprite[i]);
	}
	food->father = fatherLayer;
	food->m_tag = VirtualMap::foodTag;
	food->updateVirtualMap();

	delete spritefactory;

	return food;
}

std::vector<char *> MultiFoodFactory::getImg() {
	std::vector<char *> ret;
	char *tmp = "foods/shit6.png";
	ret.push_back(tmp);
	tmp = "foods/shit6-2.png";
	ret.push_back(tmp);
	return ret;
}

std::vector<Location> MultiFoodFactory::getLoc()
{
	std::vector<Location> ret;
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
	int c = locs.size()/7;
	for(int i=0; i<7; i++) {
		int tt = VirtualMap::getRandom(c);
		ret.push_back(locs[i*c+tt]);
	}
	return ret;
}