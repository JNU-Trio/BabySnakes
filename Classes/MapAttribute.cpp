#include "MapAttribute.h"
#include "cocos2d.h"
#include <vector>

USING_NS_CC;
using namespace std;

int VirtualMap::DIRECTION = 0;
float VirtualMap::MIN_SPEED = 0.05;
int VirtualMap::map[100][100];
vector<int> VirtualMap::m_CurScore;
vector<Location> VirtualMap::path;

CCPoint VirtualMap::LocToPos(Location loc) {
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCPoint ret;
	ret.x = origin.x + (visibleSize.width/VirtualMap::MAP_WIDTH*loc.x + visibleSize.width/VirtualMap::MAP_WIDTH*(loc.x-1)) / 2;
	ret.y = origin.y + (visibleSize.height/VirtualMap::MAP_HEIGHT*loc.y + visibleSize.height/VirtualMap::MAP_HEIGHT*(loc.y-1)) / 2;
	return ret;
}

int VirtualMap::getRandom(int limit) {
	cc_timeval psv;  
	CCTime::gettimeofdayCocos2d( &psv, NULL );
	unsigned int tsrans = psv.tv_sec * 1000 + psv.tv_usec / 1000 + rand();
	srand(tsrans);
	int MOD = 1;
	int tmplimit = limit;
	while (tmplimit)
	{
		MOD *= 10;
		tmplimit /= 10;
	}
	int x = CCRANDOM_0_1()*MOD;
	x = x % limit;
	return x;
}

int VirtualMap::dir[4][2] = {-1,0,0,-1,1,0,0,1};

bool VirtualMap::dfs(Location p, int depth) {
	path.push_back(p);
	changeTag(p,earthSnakeTag);
	if (depth == aimLength)
		return true;
	for(int i=3; i>=0; i--) {
		Location next = p;
		next.x += dir[i][0];
		next.y += dir[i][1];
		switch(i)
		{
		case 0: next.direction = Location::TURN_LEFT; break;
		case 1: next.direction = Location::TURN_DOWN; break;
		case 2: next.direction = Location::TURN_RIGHT; break;
		case 3: next.direction = Location::TURN_UP; break;
		}
		if (1<=next.x && next.x<=MAP_WIDTH && 1<=next.y && next.y<=MAP_HEIGHT
			&& map[next.x][next.y] == emptyTag) {
				if (dfs(next,depth+1))
					return true;
		}
	}

	changeTag(p,emptyTag);
	path.pop_back();
	return false;
}

int VirtualMap::aimLength;

vector<Location> VirtualMap::getNewLoc(int length) {
	aimLength = length;
	path.clear();
	Location start;
	bool flag = false;
	for(int i=2; i<MAP_WIDTH; i++) {
		for(int j=2; j<MAP_HEIGHT; j++) {
			start.x = i;
			start.y = j;
			start.direction = Location::TURN_RIGHT;
			if (map[i][j] == emptyTag && dfs(start, 1)) {
				flag = true;
				break;
			}
		}
		if (flag)
			break;
	}
	return path;
}

bool VirtualMap::init() {
	for(int i=1; i<=MAP_WIDTH; i++)
		for(int j=1; j<=MAP_HEIGHT; j++)
            map[i][j] = emptyTag;
    DIRECTION = 2;
	return true;
}

void VirtualMap::changeTag(Location aims, int Tag) {
	map[aims.x][aims.y] = Tag;
}
