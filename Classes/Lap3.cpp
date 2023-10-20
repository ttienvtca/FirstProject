#include "lap3.h"

USING_NS_CC;
Animation* lap3::creatAnimation(std::string name, int numFrame, float duration)
{
    Animation* animation = Animation::create();
    animation->setDelayPerUnit(duration);
    for (int i = 1; i < numFrame; i++)
    {
        std::string frameName = name + "(" + std::to_string(i) + ")";
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
        animation->addSpriteFrame(frame);
    }
    return animation;
}
