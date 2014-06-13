#include "Control.h"

Location HumanControl::nextMove(SnakeLocation p) {
	Location ret = p.head;
    switch(VirtualMap::DIRECTION)
    {
	case 0: ret.x--;ret.direction =Location::TURN_LEFT; break;
	case 1: ret.y++;ret.direction =Location::TURN_UP; break;
	case 2: ret.x++;ret.direction =Location::TURN_RIGHT; break;
	case 3: ret.y--;ret.direction =Location::TURN_DOWN; break;
	}

	return ret;
}

Location AIControl::nextMove(SnakeLocation p) {
	int dir[4][2] = {-1,0,1,0,0,-1,0,1};
	Location ret = p.head;
	Location fp;
	for(int i=1; i<=VirtualMap::MAP_WIDTH; i++)
		for(int j=1; j<=VirtualMap::MAP_HEIGHT; j++)
			if (VirtualMap::map[i][j] == VirtualMap::foodTag) {
				Location tmp(i,j);
				fp = tmp;
			}
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