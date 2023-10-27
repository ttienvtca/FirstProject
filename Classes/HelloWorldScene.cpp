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

	_moveSpeed = 100.0f;
	this->addChild(_character, 1);
	this->scheduleUpdate();

	/*TMXTiledMap* map = TMXTiledMap::create("Maps/map1.tmx");

	this->addChild(map);

	TMXObjectGroup* objGroup = map->getObjectGroup("SpawnPoint");
	ValueMap charPoint = objGroup->getObject("CharacterSpawnPoint");

	Vec2 position;
	position.x = charPoint["x"].asFloat();
	position.y = charPoint["y"].asFloat();
	_character->setPosition(position);

	this->getDefaultCamera()->setPosition(position);*/


	TMXTiledMap* map = TMXTiledMap::create("/Maps/Demo/map-demo.tmx");
	this->addChild(map);

	TMXObjectGroup* objGroup = map->getObjectGroup("SpawnPoint");
	ValueMap charPoint = objGroup->getObject("CharacterSpawnPoint");

	Vec2 position;
	position.x = charPoint["x"].asFloat();
	position.y = charPoint["y"].asFloat();

	_character->setPosition(position);


	return true;
}

void HelloWorld::update(float dt)
{
	Vec2 direction = KeyboardInput::getInstance()->getDirection();
	_character->setPosition(_character->getPosition() + direction * _moveSpeed * dt);

	Camera* defaultCam = this->getDefaultCamera();
	defaultCam->setPosition(_character->getPosition());
}

void HelloWorld::onEnter()
{
	Scene::onEnter();
	if (KeyboardInput::getInstance()->getParent() != nullptr)
		KeyboardInput::getInstance()->removeFromParent();

	this->addChild(KeyboardInput::getInstance());
}
