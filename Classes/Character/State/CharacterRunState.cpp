#include "CharacterRunState.h"
#include "StateMachine/StateMachine.h"
#include "KeyBoardInput.h"

void CharacterRunState::enterState(Entity* owner)
{
	State::enterState(owner);
	auto ani = AnimationCache::getInstance()
		->getAnimation(_owner->getEntityInfo()->_entityName + "-run");
	auto animate = RepeatForever::create(Animate::create(ani));
	animate->setTag(StateMachine::AnimationTag);
	_owner->getModel()->runAction(animate);
}

std::string CharacterRunState::updateState()
{
	auto keyboard = KeyboardInput::getInstance();
	// update
	Vec2 direction = keyboard->getDirection();
	float dt = Director::getInstance()->getAnimationInterval();
	Vec2 nextPostion = _owner->getPosition() + direction * _owner->getEntityStat()->_moveSpeed * dt;

	_owner->setPosition(nextPostion);

	if (direction.x != 0)
		_owner->getModel()->setFlippedX(direction.x < 0);

	// 
	if (keyboard->getKey(EventKeyboard::KeyCode::KEY_SPACE))
	{
		return "attack";
	}

	if (keyboard->getDirection() == Vec2::ZERO)
	{
		return "idle";
	}
	return "run";
}

void CharacterRunState::exitState()
{
	State::exitState();
}
