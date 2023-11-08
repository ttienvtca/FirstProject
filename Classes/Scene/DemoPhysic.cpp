#include "DemoPhysic.h"

bool DemoPhysic::init()
{
	if (!Scene::initWithPhysics())
	{
		log("Init DemoPhysic failed!");
		return false;
	}

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
	Vec2 mousPos = event->getLocationInView();
	float speed = 300;
	Vec2 direction = mousPos - _character->getPosition();
	direction.normalize();
	
	// create bullet
	auto bullet = Sprite::create("1.png");
	bullet->setPosition(_character->getPosition());

	auto body = PhysicsBody::createCircle(bullet->getContentSize().width / 2, PhysicsMaterial(1, 0, 1));
	bullet->setPhysicsBody(body);
	bullet->getPhysicsBody()->setGravityEnable(false);
	bullet->getPhysicsBody()->setVelocity(direction * speed);

	this->addChild(bullet);
}
