#include "HelloWorldScene.h"
#include "Utilities/AnimationUtils.h"
#include "DemoSingleton.h"
#include "KeyBoardInput.h"
#include "ui/CocosGUI.h"
#include "Camera/CameraFlow.h"
#include "audio/include/AudioEngine.h"
#include "Enemy/Enemy.h"
#include "Bullet/Bullet.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

bool HelloWorld::init()
{
	if (!Scene::initWithPhysics())
	{
		return false;
	}

	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	this->getPhysicsWorld()->setGravity(Vec2(0, -98.0f));
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	EntityStat* characterStat = new EntityStat();
	characterStat->_moveSpeed = 200.0f;
	characterStat->_attack = 10;

	// Character
	_character = Character::create(new EntityInfo(1, "character"));
	_character->setEntityStat(characterStat);

	// Enemy
	auto enemy = Enemy::create(new EntityInfo(1, "ice-cube"));
	enemy->setPosition(Director::getInstance()->getVisibleSize() / 2);

	EntityStat* enemyStat = new EntityStat();
	enemyStat->_moveSpeed = 200.0f;
	enemyStat->_attack = 10;
	enemyStat->_health = 50;

	enemy->setEntityStat(enemyStat);

	this->addChild(enemy, 1);

	// Map
	_gameMap = GameMap::create("/Maps/map1.tmx");
	_gameMap->setTag(99);

	TMXObjectGroup* objGroup = _gameMap->getObjectGroup("SpawnPoint");
	ValueMap charPoint = objGroup->getObject("CharacterSpawnPoint");

	Vec2 position;
	position.x = charPoint["x"].asFloat();
	position.y = charPoint["y"].asFloat();

	_character->setPosition(position);
	KeyboardInput::getInstance()->addKey(EventKeyboard::KeyCode::KEY_SPACE);


	auto listener = EventListenerMouse::create();
	listener->onMouseDown = CC_CALLBACK_1(HelloWorld::onMouseDown, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

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
	this->addChild(cam);

	this->addChild(KeyboardInput::getInstance());
}

void HelloWorld::onMouseDown(EventMouse* event)
{
	Vec2 direction = event->getLocationInView() - _character->getPosition();
	direction.normalize();
	auto bullet = Bullet::create("1");

	bullet->setPosition(_character->getPosition());
	bullet->getPhysicsBody()->setVelocity(direction * 300);
	bullet->setOwner(_character);

	this->addChild(bullet, 1);
}
