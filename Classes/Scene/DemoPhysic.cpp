#include "DemoPhysic.h"
#include "Ball.h"
#include "DefineBitmask.h"

bool DemoPhysic::init()
{
	if (!Scene::initWithPhysics())
	{
		log("Init DemoPhysic failed!");
		return false;
	}
	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	this->getPhysicsWorld()->setGravity(Vec2(0, -500));

	auto edgeBox = Node::create();
	auto edgeBody = PhysicsBody::createEdgeBox(Director::getInstance()->getVisibleSize(), 
		PhysicsMaterial(1, 1, 1), 30);
	edgeBody->setCategoryBitmask(DefineBitmask::Wall);
	edgeBody->setCollisionBitmask(DefineBitmask::BALL);
	edgeBody->setContactTestBitmask(DefineBitmask::BALL | DefineBitmask::Wall);


	edgeBox->setPhysicsBody(edgeBody);
	edgeBox->setPosition(Director::getInstance()->getVisibleSize() / 2);

	_character = Ball::create();
	_character->setPosition(Director::getInstance()->getWinSize() / 2);

	auto listener = EventListenerMouse::create();
	listener->onMouseDown = CC_CALLBACK_1(DemoPhysic::onMouseDown, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	this->addChild(_character);
	this->addChild(edgeBox);

	return true;
}

void DemoPhysic::onMouseDown(EventMouse* event)
{
	_character->getPhysicsBody()->applyForce(Vec2(0, 1) * 3000);
}
