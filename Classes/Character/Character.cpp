#include "Character.h"
#include "Utilities/AnimationUtils.h"

Character* Character::create(EntityInfo* info)
{
	auto newObject = new Character();
	if (newObject != nullptr && newObject->init(info))
	{
		newObject->autorelease();
		return newObject;
	}

	CC_SAFE_DELETE(newObject);
	return nullptr;
}

bool Character::init(EntityInfo* info)
{
	if (!Entity::init(info))
	{
		log("Init Character failed!");
		return false;
	}

	auto aniIdle = AnimationCache::getInstance()->getAnimation(_info->_entityName + "-idle");
	auto animate = Animate::create(aniIdle);
	_model = Sprite::createWithSpriteFrameName(_info->_entityName + "-idle (1)");
	_model->runAction(RepeatForever::create(animate));
	this->addChild(_model);
	return true;
}

bool Character::loadAnimations()
{
	Entity::loadAnimations();

	std::vector<std::string> aniNames;
	aniNames.push_back(_info->_entityName + "-idle");
	aniNames.push_back(_info->_entityName + "-run");
	aniNames.push_back(_info->_entityName + "-attack");

	for (auto name : aniNames)
	{
		AnimationUtils::loadSpriteFrameCache("Character/", name);
		AnimationUtils::createAnimation(name, 1.0f);
	}

	return true;
}
