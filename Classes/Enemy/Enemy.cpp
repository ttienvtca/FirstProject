#include "Enemy.h"
#include "Utilities/AnimationUtils.h"
#include "DefineBitmask.h"

Enemy* Enemy::create(EntityInfo* info)
{
	auto newObject = new Enemy();
	if (newObject != nullptr && newObject->init(info))
	{
		newObject->autorelease();
		return newObject;
	}

	CC_SAFE_DELETE(newObject);
	return nullptr;
}

bool Enemy::init(EntityInfo* info)
{
	if (!Entity::init(info))
	{
		log("Init Enemy failed!");
		return false;
	}

	_model = Sprite::createWithSpriteFrameName(_info->_entityName + "-idle (1)");
	this->addChild(_model);

	auto body = PhysicsBody::createEdgeBox(_model->getContentSize(), PhysicsMaterial(1, 0, 1), 1.0f);
	body->setCategoryBitmask(DefineBitmask::Enemy);
	body->setCollisionBitmask(DefineBitmask::Character);
	body->setContactTestBitmask(DefineBitmask::Character);
	this->setPhysicsBody(body);

	return true;
}

void Enemy::takeDamage(Entity* attacker)
{
	int dame = attacker->getEntityStat()->_atk;
	log("take dame: %d", dame);
	_healthCtrl->setCurrentHealth(_healthCtrl->getCurrentHealth() - dame);
}

bool Enemy::loadAnimations()
{
	Entity::loadAnimations();

	std::vector<std::string> aniNames;
	aniNames.push_back(_info->_entityName + "-idle");
	aniNames.push_back(_info->_entityName + "-run");
	aniNames.push_back(_info->_entityName + "-attack");

	for (auto name : aniNames)
	{
		AnimationUtils::loadSpriteFrameCache("Enemy/", name);
		AnimationUtils::createAnimation(name, 1.0f);
	}

	return true;
}

void Enemy::onDie()
{
	log("die");
	// add effects....
	this->removeFromParentAndCleanup(true);
}

void Enemy::onEnter()
{
	Node::onEnter();

	// health
	_healthCtrl = HealthController::create(_entityStat->_hp, "fill.png");
	_healthCtrl->setOnDie(CC_CALLBACK_0(Enemy::onDie, this));
	_healthCtrl->setPosition(Vec2(-_healthCtrl->getContentSize().width / 2
		, _model->getContentSize().height));
	this->addChild(_healthCtrl);
}
