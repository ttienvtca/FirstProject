#ifndef __GAME_MAP_H__
#define __GAME_MAP_H__

#include "cocos2d.h"

USING_NS_CC;

class GameMap : TMXTiledMap
{
public:
	int getMetaAtPos(const Vec2& position);
	Point convertPosTileMap(Vec2 objectPos);
};

#endif // !__GAME_MAP_H__
