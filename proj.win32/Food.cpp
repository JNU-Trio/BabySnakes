#include "Food.h"
#include "MapAttribute.h"
#include "Snakes.h"

USING_NS_CC;

bool SimpleFood ::Generate(CCLayer *father_layer){
	/****************��ȡ�����ߵ�λ����Ϣ*****************/
	Snake *m_Snake = father_layer->getChildByTag("NUM_1");
	Snake *AI_Snake = father_layer->getChildByTag("NUM_2");

	do
	{
		/****************��ȡ���λ��*****************/
		cc_timeval psv;  
		CCTime::gettimeofdayCocos2d( &psv, NULL );
		unsigned int tsrans = psv.tv_sec * 1000 + psv.tv_usec / 1000 + rand();
		srand(tsrans);
		f_location.x = CCRANDOM_0_1()*100;
		f_location.x = f_location.x % MAP_WIDTH + 1;

		CCTime::gettimeofdayCocos2d( &psv, NULL );
		tsrans = psv.tv_sec * 1000 + psv.tv_usec / 1000 + rand();
		srand(tsrans);
		f_location.y = CCRANDOM_0_1()*100;
		f_location.y = f_location.y % MAP_HEIGHT + 1;
		

		/*************�ж�ʳ���Ƿ��߷�����ײ*************/
		if((f_location.x != m_Snake->m_head.x)&&(f_location.y != m_Snake->m_head.y))
		{
			for(int i = 0 ;);
		
		}
	

		
	}while(true);

	/************��ʾʳ��ͼƬ�Լ�λ��***********/
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	f_pictrue = CCSprite::create("food_pic_URL");
	CCSize contentSize = f_pictrue->getContentSize();
	f_pictrue->setScaleX(visibleSize.width/MAP_WIDTH/contentSize.width);
	f_pictrue->setScaleY(visibleSize.height/MAP_HEIGHT/contentSize.height);
	f_pictrue->setPosition(LocToPos(f_location));
	father_layer->addChild(f_pictrue);


	return true;
}

Location SimpleFood ::GetLocation(){
	return f_location;
}