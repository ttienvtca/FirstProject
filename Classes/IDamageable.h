#ifndef __I_DAMAGEABLE_H__

#include "Entity/Entity.h"

class IDamageable
{
public:
	virtual void takeDamage(Entity* attacker) {}
};

#endif // !__I_DAMAGEABLE_H__
