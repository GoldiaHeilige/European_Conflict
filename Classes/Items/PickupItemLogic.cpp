#include "PickupItemLogic.h"
#include "Map/Spawn Node/SpawnItems.h"
#include "PhysicsCategory.h"

USING_NS_CC;

PickupItemLogic* PickupItemLogic::getInstance() {
    static PickupItemLogic instance;
    return &instance;
}

PickupItemLogic::PickupItemLogic() : _contactListener(nullptr), _character(nullptr) {}

PickupItemLogic::~PickupItemLogic() {
    if (_contactListener) {
        Director::getInstance()->getEventDispatcher()->removeEventListener(_contactListener);
    }
}

void PickupItemLogic::setupPickupListener(Node* sceneRoot, Character* character) {
    _character = character;

    // Tạo listener cho Physics
    _contactListener = EventListenerPhysicsContact::create();
    _contactListener->onContactBegin = [this](PhysicsContact& contact) {
        auto nodeA = contact.getShapeA()->getBody()->getNode();
        auto nodeB = contact.getShapeB()->getBody()->getNode();

        // Kiểm tra va chạm giữa Player và Item
        if ((nodeA && nodeA->getName() == "Hero" && nodeB && nodeB->getPhysicsBody()->getCategoryBitmask() == PhysicsCategory::ITEM) ||
            (nodeB && nodeB->getName() == "Hero" && nodeA && nodeA->getPhysicsBody()->getCategoryBitmask() == PhysicsCategory::ITEM)) {

            Node* itemNode = (nodeA->getName() == "Hero") ? nodeB : nodeA;
            CCLOG("Item picked up: %s", itemNode->getName().c_str());

            // Xóa vật phẩm khỏi map
            itemNode->removeFromParent();
        }

        return true;
        };

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_contactListener, sceneRoot);
}