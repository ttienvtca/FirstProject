#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity/Entity.h"
#include "IDamageable.h"

class Enemy : public Entity, public IDamageable
{
public:
	static Enemy* create(EntityInfo* info);
	virtual bool init(EntityInfo* info) override;

	void takeDamage(Entity* attacker) override;
protected:
	bool loadAnimations() override;
};

#endif // !__ENEMY_H__
