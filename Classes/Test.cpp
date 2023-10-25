#include "Test.h"
#include "ui/CocosGUI.h"

bool Test::init()
{
    if (!Sprite::init())
    {
        log("Init Test failed!");
        return false;
    }
    
    auto sprite = Sprite::create();
    ui::ScrollView* scrollView = ui::ScrollView::create();
    scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
    scrollView->setContentSize(Size()); // view
    scrollView->setInnerContainerSize(Size()); // content
    scrollView->setScrollBarEnabled(false);
    scrollView->setBounceEnabled(true);
    scrollView->addChild(sprite);

    return true;
}
