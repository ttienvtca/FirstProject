#include "HelloWorldScene.h"
#include "Utilities/AnimationUtils.h"
#include "DemoSingleton.h"
#include "KeyBoardInput.h"
#include "ui/CocosGUI.h"
#include "Camera/CameraFlow.h"
#include "audio/include/AudioEngine.h"

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

	this->getPhysicsWorld()->setGravity(Vec2(0, -98.0f));
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	ui::ScrollView* scrollView = ui::ScrollView::create();
	scrollView->setContentSize(Size(200, 200));
	scrollView->setBackGroundImage("bg.jpg", ui::Widget::TextureResType::LOCAL);
	scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
	scrollView->setScrollBarEnabled(false);
	scrollView->setBounceEnabled(true);

	//this->addChild(scrollView, 3);

	EntityStat* characterStat = new EntityStat();
	characterStat->_moveSpeed = 200.0f;

	_character = Character::create(new EntityInfo(1, "character"));
	_character->setEntityStat(characterStat);

	/*TMXTiledMap* map = TMXTiledMap::create("Maps/map1.tmx");

	this->addChild(map);

	TMXObjectGroup* objGroup = map->getObjectGroup("SpawnPoint");
	ValueMap charPoint = objGroup->getObject("CharacterSpawnPoint");

	Vec2 position;
	position.x = charPoint["x"].asFloat();
	position.y = charPoint["y"].asFloat();
	_character->setPosition(position);

	this->getDefaultCamera()->setPosition(position);*/


	_gameMap = GameMap::create("/Maps/map1.tmx");

	TMXObjectGroup* objGroup = _gameMap->getObjectGroup("SpawnPoint");
	ValueMap charPoint = objGroup->getObject("CharacterSpawnPoint");

	Vec2 position;
	position.x = charPoint["x"].asFloat();
	position.y = charPoint["y"].asFloat();

	_character->setPosition(position);

	KeyboardInput::getInstance()->addKey(EventKeyboard::KeyCode::KEY_SPACE);

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
	//Rect boundingBox = { 640,360,320,560 };
	CameraFollow* cam = CameraFollow::create(_character, boundingBox);
	this->addChild(cam);

	this->addChild(KeyboardInput::getInstance());
}
