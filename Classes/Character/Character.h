#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "Entity/Entity.h"

class Character : public Entity
{
public:
	static Character* create(EntityInfo* info);

	bool init(EntityInfo* info) override;

protected:
	bool loadAnimations() override;
};

#endif // !__CHARACTER_H__
