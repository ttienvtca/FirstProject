#include "DemoJson.h"
#include "json/rapidjson.h"
#include "json/document.h"



bool DemoJson::init()
{
    if (!Scene::init())
    {
        return false;
    }

    rapidjson::Document docs;

    std::string dataContent = FileUtils::getInstance()->getStringFromFile("test-data.json");
    docs.Parse(dataContent.c_str());

    int coin = docs["coin"].GetInt();
    std::string charName = docs["characterSelectName"].GetString();
    float speed = docs["speed"].GetFloat();

    return true;
}
