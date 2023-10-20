#include "Test.h"

bool Test::init()
{
    if (!Sprite::init())
    {
        log("Init Test failed!");
        return false;
    }

    _horizontalLayout = HorizontalLayout::create();

    return true;
}

void Test::addChild(Node* child)
{
    Sprite::addChild(child);
    _horizontalLayout->alignment();
}
