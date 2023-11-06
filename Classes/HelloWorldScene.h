#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Character/Character.h"
#include "Map/GameMap.h"


USING_NS_CC;

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    CREATE_FUNC(HelloWorld);
    
protected:
    Character* _character;
    GameMap* _gameMap;
protected:
    void update(float dt) override;
    void onEnter() override;
};

#endif // __HELLOWORLD_SCENE_H__
