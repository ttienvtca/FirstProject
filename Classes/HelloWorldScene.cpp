#include "HelloWorldScene.h"
#include "Utilities/AnimationUtils.h"
#include "DemoSingleton.h"
#include "KeyBoardInput.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}
bool HelloWorld::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_character = Character::create(new EntityInfo(1, "ice-cube"));
	_character->setPosition(visibleSize / 2);

	_moveSpeed = 100.0f;
	this->addChild(_character);
	this->scheduleUpdate();
	return true;
}

void HelloWorld::update(float dt)
{
	Vec2 direction = KeyboardInput::getInstance()->getDirection();
	_character->setPosition(_character->getPosition() + direction * _moveSpeed * dt);
}

void HelloWorld::onEnter()
{
	Scene::onEnter();
	if (KeyboardInput::getInstance()->getParent() != nullptr)
		KeyboardInput::getInstance()->removeFromParent();

	this->addChild(KeyboardInput::getInstance());
}
