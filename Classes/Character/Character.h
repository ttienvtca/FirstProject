#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "Entity/Entity.h"
#include "StateMachine.h"
#include "State/CharacterAttackState.h"
#include "State/CharacterIdleState.h"
#include "State/CharacterRunState.h"

class Character : public Entity
{
public:
	static Character* create(EntityInfo* info);

	bool init(EntityInfo* info) override;

protected:
	bool loadAnimations() override;
	StateMachine* _stateMachine;
};

#endif // !__CHARACTER_H__
