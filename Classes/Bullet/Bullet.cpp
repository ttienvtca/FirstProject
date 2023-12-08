#include "Bullet.h"
#include "DefineBitmask.h"
#include "IDamageable.h"

Bullet* Bullet::create(std::string bulletName)
{
	auto newObject = new Bullet();
	if (newObject != nullptr && newObject->init(bulletName))
	{
		newObject->autorelease();
		return newObject;
	}

	CC_SAFE_DELETE(newObject);
	return nullptr;
}

bool Bullet::init(std::string bulletName)
{
	if (!Node::init())
	{
		log("init Bullet failed!");
		return false;
	}

	_model = Sprite::create("Bullet/" + bulletName + ".png");
	this->addChild(_model);


	auto body = PhysicsBody::createEdgeBox(_model->getContentSize(), PhysicsMaterial(1, 0, 1), 1.0f);
	body->setCategoryBitmask(DefineBitmask::Bullet);
	body->setCollisionBitmask(DefineBitmask::Character | DefineBitmask::Enemy | DefineBitmask::Wall);
	body->setContactTestBitmask(DefineBitmask::Character | DefineBitmask::Enemy | DefineBitmask::Wall);
	this->setPhysicsBody(body);


	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = CC_CALLBACK_1(Bullet::callbackOnContactBegin, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

bool Bullet::callbackOnContactBegin(PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	auto target = (nodeA == this) ? (nodeB) : (nodeA);

	auto damageable = dynamic_cast<IDamageable*>(target);
	if (damageable != nullptr)
	{
		damageable->takeDamage(_owner);
	}

	this->removeFromParentAndCleanup(true);

	return false;
}
