#include "FoodFactory.h"
#include "SpriteFactory.h"

Food *SimpleFoodFactory::createFood(cocos2d::CCNode *fatherLayer) {
	SpriteFactory *spritefactory = new PlaySpriteFactory();
	char *img = getImg();
	Location loc = getLoc();
	SimpleFood *food = new SimpleFood();

	food->m_locate.push_back(loc);
	food->m_sprite.push_back(spritefactory->getSprite(img,loc));
	fatherLayer->addChild(food->m_sprite[0]);

	food->m_tag = VirtualMap::foodTag;

	food->updateVirtualMap();

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