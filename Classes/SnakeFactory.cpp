#include "cocos2d.h"

#include "SnakeFactory.h"
#include "SpriteFactory.h"

USING_NS_CC;

SimpleSnake *SnakeFactory::createSimpleSnake(cocos2d::CCNode *father_layer, const int type)
{
	// create snakes
    SimpleSnake *snake = new SimpleSnake();
	SpriteFactory *factory = new PlaySpriteFactory();

    // initial the images of the snake need
	snake->m_snakeImage = getSnakeImg(type);
	const SnakeImgFilename &snakeImg = snake->m_snakeImage;

    // initial the location of head, tail and body
	snake->m_snake = getSnakeLoc(type);
	const SnakeLocation &snakeLoc = snake->m_snake;

    // create sprite of head
	snake->m_shead = factory->getSprite(snakeImg.head,snakeLoc.head);
	father_layer->addChild(snake->m_shead);

	// create sprite of tail
	snake->m_stail = factory->getSprite(snakeImg.tail,snakeLoc.tail);
	father_layer->addChild(snake->m_stail);

	//  create sprites of body
	for(int i=0; i<snakeLoc.body.size(); i++) {
		CCSprite *stmp = factory->getSprite(snakeImg.body,snakeLoc.body[i]);
		snake->m_sbody.push_back(stmp);
		father_layer->addChild(snake->m_sbody[i]);
	}

	snake->father = father_layer;
	snake->m_score = 0;

	if (type == 1)
		snake->m_tag = VirtualMap::earthSnakeTag;
	else
		snake->m_tag = VirtualMap::marsSnakeTag;

	snake->updateVirtualMap();

	return snake;
}

SnakeImgFilename SnakeFactory::getSnakeImg(int type)
{
	SnakeImgFilename curImage;
	if (type == 1)
	{
		curImage.head = "snakes/snakehead1-1.png";
		curImage.body = "snakes/snakebody1-1.png";
		curImage.tail = "snakes/snaketail1-1.png";
	}
	else if (type == 2)
	{
		curImage.head = "snakes/snakehead1-2.png";
		curImage.body = "snakes/snakebody1-2.png";
		curImage.tail = "snakes/snaketail1-2.png";
	}
	return curImage;
}

SnakeLocation SnakeFactory::getSnakeLoc(int type)
{
	SnakeLocation curSnake;
	if (type == 1)
	{
		// initial virtual state of earth snake
		curSnake.head.x = 8;
		curSnake.head.y = 5;
		curSnake.head.direction = Location::TURN_RIGHT;
		curSnake.tail.x = 6;
		curSnake.tail.y = 5;
		curSnake.tail.direction = Location::TURN_RIGHT;
		Location tmp;
		tmp.x = 7;
		tmp.y = 5;
		tmp.direction = Location::TURN_RIGHT;
		curSnake.body.push_back(tmp);
	}
	else if (2 == type)
	{
		// initial virtual state of mars snake
		curSnake.head.x = 15;
		curSnake.head.y = 5;
		curSnake.head.direction = Location::TURN_LEFT;
		curSnake.tail.x = 17;
		curSnake.tail.y = 5;
		curSnake.tail.direction = Location::TURN_LEFT;
		Location tmp;
		tmp.x = 16;
		tmp.y = 5;
		tmp.direction = Location::TURN_LEFT;
		curSnake.body.clear(); // clear contents
		curSnake.body.push_back(tmp);
	}

	return curSnake;
}