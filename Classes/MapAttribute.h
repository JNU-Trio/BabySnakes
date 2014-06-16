#ifndef __MAP_ATTRIBUTE_H_
#define __MAP_ATTRIBUTE_H_

#include "cocos2d.h"

struct Location {
	Location():x(0),y(0),direction(0){};

	int direction;
	int x,y;
    bool operator==(const Location &src) {
        if (x == src.x && y == src.y) {
			return true;
		}
        else {
			return false;
		}
	}
	static const int TURN_LEFT = 180;
	static const int TURN_RIGHT = 0;
	static const int TURN_UP = 270;
	static const int TURN_DOWN = 90;
};

struct SnakeLocation {
	Location head,tail;
	std::vector<Location> body;
};

class VirtualMap {
public:
	static const int MAP_WIDTH = 20;
	static const int MAP_HEIGHT = 12;
	static float MIN_SPEED;

    static int DIRECTION;

	static int map[100][100];

	static const int emptyTag = 0;
	static const int foodTag = 1;
	static const int earthSnakeTag = 2;
	static const int marsSnakeTag = 3;
	static const int barrierTag = 4;

	static const int SCENE_TYPE_SINGLE = 1;
	static const int SCENE_TYPE_DOUBLE = 2;
	static const int SCENE_TYPE_DISAPPEAR = 3;
	static const int SCENE_TYPE_ZHA = 4;
	static const int SCENE_TYPE_DICE = 5;
	static const int SCENE_TYPE_BOSS = 6;

	static cocos2d::CCPoint LocToPos(Location);
	static int getRandom(int);
	static std::vector<Location> getNewLoc(int length);

	static bool init();

	static void changeTag(Location,int);

    static std::vector<int> m_CurScore;

private:
	static std::vector<Location> path;
	static bool dfs(Location,int);
	static int dir[4][2];
	static int aimLength;
};

#endif // __MAP_ATTRIBUTE_H_