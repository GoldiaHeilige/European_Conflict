#include "SpawnItems.h"
#include "PhysicsCategory.h"

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
        std::string itemType = objectInfo["type"].asString();
        float x = objectInfo["x"].asFloat();
        float y = objectInfo["y"].asFloat();

        if (itemType == "Medical") { 
            MedicalStat* stat = nullptr;
            if (MedicalType::getInstance()->getMedicalStatByName(itemName, stat)) {
                auto itemSprite = Sprite::create(stat->_icon);
                if (itemSprite != nullptr) {
                    itemSprite->setPosition(Vec2(x, y));
                    itemSprite->setName(itemName);

                    auto physicsBody = PhysicsBody::createBox(itemSprite->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
                    physicsBody->setDynamic(false);
                    physicsBody->setCategoryBitmask(PhysicsCategory::ITEM);               
                    physicsBody->setContactTestBitmask(PhysicsCategory::PLAYER);     
                    physicsBody->setCollisionBitmask(PhysicsCategory::NONE);
                    itemSprite->addComponent(physicsBody);

                    _parentNode->addChild(itemSprite);
                }
            }
        }
    }
}