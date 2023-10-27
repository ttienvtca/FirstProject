#include "GameMap.h"

int GameMap::getMetaAtPos(const Vec2& position)
{
	Point posTile = convertPosTileMap(position);
	int result = 0;
	int tileGid = this->getLayer("Meta")->getTileGIDAt(posTile);
	if (tileGid != 0)
	{
		Value temp = this->getPropertiesForGID(tileGid);
		if (!temp.isNull())
		{
			ValueMap properties = temp.asValueMap();
			auto properName = properties.find("Collidable");
			auto properValue = properties.at("Collidable").asInt();
			if (properName != properties.end() && properValue == 0)
			{
				result = 0;
			}
			else if (properName != properties.end() && properValue == 1)
			{
				result = 1;
			}
		}
	}

	return result;
}

Point GameMap::convertPosTileMap(Vec2 objectPos)
{
	int x = objectPos.x / _tileSize.width;
	int y = (this->getContentSize().height - objectPos.y) / _tileSize.height;
	return Point(x, y);
}