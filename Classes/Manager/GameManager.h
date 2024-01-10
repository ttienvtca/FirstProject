#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "cocos2d.h"
USING_NS_CC;

class GameManager : public Node
{
public:
	bool init() override;

	CREATE_FUNC(GameManager);
private:
	int _score = 0;
	void OnEnemyDie(void* data);
};

#endif // !__GAME_MANAGER_H__
