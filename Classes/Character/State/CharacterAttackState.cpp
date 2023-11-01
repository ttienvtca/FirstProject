#include "CharacterAttackState.h"
#include "StateMachine.h"

void CharacterAttackState::enterState(Entity* owner)
{
    State::enterState(owner);
    log("run state");
    auto ani = AnimationCache::getInstance()
        ->getAnimation(owner->getEntityInfo()->_entityName + "-attack");
    auto animate = RepeatForever::create(Animate::create(ani));
    animate->setTag(StateMachine::AnimationTag);
    owner->getModel()->runAction(animate);
}

std::string CharacterAttackState::updateState()
{
    _elapsedTime += Director::getInstance()->getAnimationInterval();
    if (_elapsedTime >= _timeAttack)
    {
        _elapsedTime = 0;
        return "idle";
    }
	return "attack";
}

void CharacterAttackState::exitState()
{
	State::exitState();
}
