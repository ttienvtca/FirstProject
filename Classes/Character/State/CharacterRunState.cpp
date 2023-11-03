#include "CharacterRunState.h"
#include "StateMachine.h"
#include "KeyBoardInput.h"

void CharacterRunState::enterState(Entity* owner)
{
	State::enterState(owner);
	log("run state");
	auto ani = AnimationCache::getInstance()
		->getAnimation(owner->getEntityInfo()->_entityName + "-run");
	auto animate = RepeatForever::create(Animate::create(ani));
	animate->setTag(StateMachine::AnimationTag);
	owner->getModel()->runAction(animate);
}

std::string CharacterRunState::updateState()
{
	Vec2 direction = KeyboardInput::getInstance()->getDirection();
	Vec2 nextPosition = _owner->getPosition() + direction * 200 * Director::getInstance()->getAnimationInterval();
	_owner->setPosition(nextPosition);

	if (direction.x != 0)
		_owner->getModel()->setFlippedX(!(direction.x > 0));

	auto keyboard = KeyboardInput::getInstance();
	if (keyboard->getKey(EventKeyboard::KeyCode::KEY_SPACE))
	{
		return "attack";
	}
	if (direction == Vec2::ZERO)
	{
		return "idle";
	}

	return "run";
}

void CharacterRunState::exitState()
{
	State::exitState();
}
