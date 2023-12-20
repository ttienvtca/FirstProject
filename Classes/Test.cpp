#include "Test.h"
#include "ui/CocosGUI.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "ui/CocosGUI.h"
#include "HelloWorldScene.h"

#include "Entity/EntityDAL.h"

bool Test::init()
{
	if (!Scene::init())
	{
		log("Init Test failed!");
		return false;
	}

	std::vector<std::string> maps;
	maps.push_back("map1");
	maps.push_back("map2");

	float x = Director::getInstance()->getVisibleSize().width / 2;

	for (int i = 0; i < maps.size(); ++i)
	{
		auto button = ui::Button::create("button.png");
		button->setTitleText("Level " + std::to_string(i + 1));
		button->setTitleFontSize(button->getTitleFontSize() * 2);
		button->setPositionX(x);
		button->setPositionY(100 + 100 * i);

		button->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
			{
				if (type == ui::Widget::TouchEventType::ENDED)
				{
					auto gameScene = HelloWorld::create(maps[i]);
					Director::getInstance()->replaceScene(gameScene);
				}
			});

		this->addChild(button, 1);
	}

	return true;
}
