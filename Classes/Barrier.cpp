#include "cocos2d.h"
#include <vector>

#include "Barrier.h"
#include "MapAttribute.h"

USING_NS_CC;

void Barrier::updateVirtualMap() {
	for(int i=0; i<m_wallLoc.size(); i++) {
		VirtualMap::changeTag(m_wallLoc[i],m_tag);
	}

	for(int i=0; i<m_barrierLoc.size(); i++) {
		VirtualMap::changeTag(m_barrierLoc[i],m_tag);
	}
}