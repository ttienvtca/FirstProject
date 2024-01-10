#include "GameManager.h"
#include "DesignPattern/Observer.h"
#include "Enemy/Enemy.h"

bool GameManager::init()
{
    if (!Node::init())
        return false;

    Observer::getInstance()->registerEvent("EnemyDie", CC_CALLBACK_1(GameManager::OnEnemyDie, this));
    return true;
}

void GameManager::OnEnemyDie(void* data)
{
    Enemy* enemy = static_cast<Enemy*>(data);
    if (enemy != nullptr)
    {
        _score += enemy->getEntityInfo()->_level;
        log("Score: %d", _score);
    }
}
