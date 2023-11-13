#include "Ball.h"
#include "DefineBitmask.h"

bool Ball::init()
{
	if (!Sprite::initWithFile("CloseNormal.png"))
	{
		return false;
	}

	this->_count = 5;
	auto body = PhysicsBody::createCircle(_contentSize.width / 2,
		PhysicsMaterial(1, 1, 1));

	body->setCategoryBitmask(DefineBitmask::BALL);
	body->setCollisionBitmask(DefineBitmask::Wall);
	body->setContactTestBitmask(DefineBitmask::Wall);
	body->setMass(0.1f);

	this->setPhysicsBody(body);

	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = CC_CALLBACK_1(Ball::callbackOnContactBegin, this);
	listener->onContactPreSolve = CC_CALLBACK_1(Ball::callbackOnContactPreSolve, this);
	listener->onContactPostSolve = CC_CALLBACK_1(Ball::callbackOnContactPostSolve, this);
	listener->onContactSeparate = CC_CALLBACK_1(Ball::onContactSeparate, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	this->setPhysicsBody(body);
	return true;
}

bool Ball::callbackOnContactBegin(PhysicsContact& contact)
{
	log("Begin");
	--_count;
	if (_count < 0)
	{
		log("lose");
	}
	return true;
}

bool Ball::callbackOnContactPreSolve(PhysicsContact& contact)
{
	log("Pre");
	getPhysicsBody()->applyForce(Vec2(0, 1) * 20000);
	return true;
}

bool Ball::callbackOnContactPostSolve(PhysicsContact& contact)
{
	log("Post");
	return true;
}

bool Ball::onContactSeparate(PhysicsContact& contact)
{
	log("Separate");
	return true;
}
