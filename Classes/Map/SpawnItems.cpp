#include "SpawnItems.h"

using namespace cocos2d;

SpawnItems::SpawnItems(Node* parentNode) : _parentNode(parentNode) {}

void SpawnItems::spawnMedicalFromTiled(TMXTiledMap* map) {
    auto objectItemLayer = map->getObjectGroup("Item Spawn");
    if (!objectItemLayer) {
        CCLOG("Error: 'Item Spawn' layer not found in the TMX map.");
        return;
    }

    auto _objectsItem = objectItemLayer->getObjects();

    if (_objectsItem.empty()) {
        CCLOG("No objects found in the object layer 'Item Spawn'.");
        return;
    }

    for (auto& obj : _objectsItem) {
        auto objectInfo = obj.asValueMap();
        std::string itemName = objectInfo["name"].asString();
        float x = objectInfo["x"].asFloat();
        float y = objectInfo["y"].asFloat();

        MedicalStat* stat = nullptr;
        if (MedicalType::getInstance()->getMedicalStatByName(itemName, stat)) {
            auto itemSprite = Sprite::create(stat->_icon);
            if (itemSprite != nullptr) {
                itemSprite->setPosition(Vec2(x, y));
                itemSprite->setName(itemName);
                _parentNode->addChild(itemSprite);
            }
        }
    }
}
