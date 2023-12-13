#include "Test.h"
#include "ui/CocosGUI.h"
#include "json/rapidjson.h"
#include "json/document.h"

#include "Entity/EntityDAL.h"

bool Test::init()
{
    if (!Scene::init())
    {
        log("Init Test failed!");
        return false;
    }

    EntityDAL* entityDAL = new EntityDAL("character");

    EntityStat* stat = entityDAL->getEntityStat(0);
    EntityStat* stat1 = entityDAL->getEntityStat(2);
    EntityStat* stat2 = entityDAL->getEntityStat(5);
    EntityStat* stat3 = entityDAL->getEntityStat(6);

    return true;
}
