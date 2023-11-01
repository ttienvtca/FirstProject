#include "StateMachine.h"

StateMachine* StateMachine::create(Entity* entity)
{
    auto newObject = new StateMachine();
    if (newObject != nullptr && newObject->init(entity))
    {
        newObject->autorelease();
        return newObject;
    }

    CC_SAFE_DELETE(newObject);
    return nullptr;
}

bool StateMachine::init(Entity* entity)
{
    if (!Node::init())
    {
        log("Init StateMachine failed!");
        return false;
    }

    this->_entityTarget = entity;
    /*_entityTarget->getModel()->stopActionByTag(StateMachine::AnimationTag);

    auto ani = AnimationCache::getInstance()
        ->getAnimation(_entityTarget->getEntityInfo()->_entityName + "-idle");
    auto animate = RepeatForever::create(Animate::create(ani));
    animate->setTag(StateMachine::AnimationTag);
    _entityTarget->getModel()->runAction(animate);*/
    this->scheduleUpdate();
	return true;
}

void StateMachine::addState(State* state, std::string stateName)
{
    if (_states.find(stateName) != _states.end())
    {
        return;
    }
    _states.insert({ stateName, state });
}

void StateMachine::update(float dt)
{
    std::string updateState = _states[_currentState]->updateState();
    if (updateState != _currentState)
    {
        _states[_currentState]->exitState();
        _currentState = updateState;
        _states[_currentState]->enterState(_entityTarget);
    }
}

void StateMachine::onEnter()
{
    Node::onEnter();
    _currentState = "idle";
    _states[_currentState]->enterState(_entityTarget);
}
