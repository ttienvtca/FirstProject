#ifndef __BALL_H__
#define __BALL_H__

#include "cocos2d.h"

USING_NS_CC;

class Ball : public Sprite
{
public:
	bool init();

	CREATE_FUNC(Ball);

private:
	bool callbackOnContactBegin(PhysicsContact& contact);
	bool callbackOnContactPreSolve(PhysicsContact& contact);
	bool callbackOnContactPostSolve(PhysicsContact& contact);
	bool onContactSeparate(PhysicsContact& contact);

private:
	int _count;
};

#endif // !__BALL_H__
