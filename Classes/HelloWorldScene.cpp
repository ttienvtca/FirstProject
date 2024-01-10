#include "HelloWorldScene.h"
#include "Utilities/AnimationUtils.h"
#include "DemoSingleton.h"
#include "KeyBoardInput.h"
#include "ui/CocosGUI.h"
#include "Camera/CameraFlow.h"
#include "audio/include/AudioEngine.h"
#include "Enemy/Enemy.h"
#include "Bullet/Bullet.h"
#include "Manager/GameManager.h"

USING_NS_CC;

Scene* HelloWorld::create(std::string mapName)
{
	auto newObject = new HelloWorld();
	if (newObject != nullptr && newObject->init(mapName))
	{
		newObject->autorelease();
		return newObject;
	}

	CC_SAFE_DELETE(newObject);
	return nullptr;
}

bool HelloWorld::init(std::string mapName)
{
	if (!Scene::initWithPhysics())
	{
		return false;
	}

	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	this->getPhysicsWorld()->setGravity(Vec2(0, -98.0f));
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	// Map
	_gameMap = GameMap::create(mapName);
	_gameMap->setTag(99);


	// Enemy
	TMXObjectGroup* enemySpawnPoint = _gameMap->getObjectGroup("EnemySpawnPoint");
	auto enemies = enemySpawnPoint->getObjects();

	for (auto enemyInfo : enemies)
	{
		ValueMap entityInfo = enemyInfo.asValueMap();
		std::string name = entityInfo["name"].asString();
		int lv = entityInfo["level"].asInt();
		auto info = new EntityInfo(lv, name);

		Vec2 position;
		position.x = entityInfo["x"].asFloat();
		position.y = entityInfo["y"].asFloat();

		auto enemy = Enemy::create(info);
		enemy->setPosition(position);

		this->addChild(enemy, 3);
	}
	/*auto enemy = Enemy::create(new EntityInfo(2, "ice-cube"));
	enemy->setPosition(Director::getInstance()->getVisibleSize() / 2);

	this->addChild(enemy, 1);*/

	// Character
	TMXObjectGroup* spawnPoint = _gameMap->getObjectGroup("SpawnPoint");
	ValueMap charPoint = spawnPoint->getObject("CharacterSpawnPoint");
	_character = Character::create(new EntityInfo(1, "character"));

	Vec2 position;
	position.x = charPoint["x"].asFloat();
	position.y = charPoint["y"].asFloat();

	_character->setPosition(position);
	KeyboardInput::getInstance()->addKey(EventKeyboard::KeyCode::KEY_SPACE);

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode key, Event* event) {
		if (key == EventKeyboard::KeyCode::KEY_TAB)
		{
			log("character level up");
			_character->setLevel(_character->getEntityInfo()->_level + 1);
		}
	};

	auto listener = EventListenerMouse::create();
	listener->onMouseDown = CC_CALLBACK_1(HelloWorld::onMouseDown, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	this->addChild(_gameMap);
	this->addChild(_character, 1);
	this->scheduleUpdate();
	return true;
}

void HelloWorld::update(float dt)
{

}

void HelloWorld::onEnter()
{
	Scene::onEnter();
	if (KeyboardInput::getInstance()->getParent() != nullptr)
		KeyboardInput::getInstance()->removeFromParent();
	Size size = Director::getInstance()->getOpenGLView()->getFrameSize();
	auto mapSize = _gameMap->getContentSize();
	Rect boundingBox = { size.width / 2,size.height / 2,mapSize.width - size.width / 2 - size.width / 2,mapSize.height - size.height / 2 - size.height / 2 };
	CameraFollow* cam = CameraFollow::create(_character, boundingBox);


	this->addChild(GameManager::create());

	this->addChild(cam);
	this->addChild(KeyboardInput::getInstance());
}

void HelloWorld::onMouseDown(EventMouse* event)
{
	Vec2 camPos = Camera::getDefaultCamera()->getPosition();
	Vec2 visibleSize = Director::getInstance()->getVisibleSize();

	Vec2 mousPos = camPos - visibleSize / 2 + event->getLocationInView();

	Vec2 direction = mousPos - _character->getPosition();
	direction.normalize();
	auto bullet = Bullet::create("1");

	bullet->setPosition(_character->getPosition());
	bullet->getPhysicsBody()->setVelocity(direction * 300);
	bullet->setOwner(_character);

	this->addChild(bullet, 1);
}
