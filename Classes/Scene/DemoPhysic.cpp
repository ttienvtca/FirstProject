#include "DemoPhysic.h"

bool DemoPhysic::init()
{
	if (!Scene::initWithPhysics())
	{
		log("Init DemoPhysic failed!");
		return false;
	}

	//this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	_character = Sprite::create("HelloWorld.png");
	_character->setPosition(Director::getInstance()->getWinSize() / 2);
	this->addChild(_character);
	auto listener = EventListenerMouse::create();
	listener->onMouseDown = CC_CALLBACK_1(DemoPhysic::onMouseDown, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

void DemoPhysic::onMouseDown(EventMouse* event)
{
	Vec2 mousePos = event->getLocationInView();
	float speed = 300;
	Vec2 direction = mousePos - _character->getPosition();
	direction.normalize();
	
	// create bullet
	auto bullet = Sprite::create("1.png");
	bullet->setPosition(_character->getPosition());

	auto body = PhysicsBody::createCircle(bullet->getContentSize().width / 2, PhysicsMaterial(1, 0, 1));
	bullet->setPhysicsBody(body);
	bullet->getPhysicsBody()->setGravityEnable(false);
	bullet->getPhysicsBody()->setVelocity(direction * speed);

	float angle = Vec2::angle(Vec2::ANCHOR_BOTTOM_RIGHT, direction);
	if (direction.y > 0)
		angle = -angle;
	bullet->setRotation(CC_RADIANS_TO_DEGREES(angle));
	this->addChild(bullet);
}
