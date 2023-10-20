#ifndef __lap3__
#define __lap3__

#include "cocos2d.h"

class lap3 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    cocos2d::Animation* creatAnimation(std::string name, int numFrame, float duration);
    // implement the "static create()" method manually
    CREATE_FUNC(lap3);
};

#endif // __HELLOWORLD_SCENE_H__
