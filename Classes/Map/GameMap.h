#ifndef __GAME_MAP_H__
#define __GAME_MAP_H__

#include "cocos2d.h"

USING_NS_CC;

class GameMap : TMXTiledMap
{
public:
	static const std::string Collidable;

	static const int MetaRed = 0;
	static const int MetaGreen = 1;

	int getMetaAtPos(const Vec2& position);
	Point convertPosTileMap(Vec2 objectPos);
};

#endif // !__GAME_MAP_H__
