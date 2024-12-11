#include "InventoryManager.h"

InventoryManager* InventoryManager::_instance = nullptr;


InventoryManager* InventoryManager::getInstance() {
    if (_instance == nullptr) {
        _instance = new InventoryManager();
        if (!_instance->init()) {
            CCLOG("Failed to initialize InventoryManager");
            delete _instance;
            _instance = nullptr;
        }
        else {
            _instance->retain();
            CCLOG("InventoryManager initialized successfully");
        }
    }
    return _instance;
}

InventoryManager::InventoryManager() {}

bool InventoryManager::init() {
    if (!Node::init()) {
        return false;
    }

    CCLOG("InventoryManager initialized");

    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addCustomEventListener("TOGGLE_INVENTORY", CC_CALLBACK_0(InventoryManager::toggleInventory, this));
    return true;
}

void InventoryManager::toggleInventory() {
    //CCLOG("InventoryManager::toggleInventory() called");

    auto scene = Director::getInstance()->getRunningScene();
    auto character = dynamic_cast<Character*>(scene->getChildByName("Hero"));

    if (character == nullptr) {
        log("Character not found!");
        return;
    }

    if (_isInventoryOpen) {
        if (_inventoryUI) {
            //log("Closing Inventory UI");
            _inventoryUI->setVisible(false);
        }
    }
    else {
        if (!_inventoryUI) {
            //log("Creating and Opening Inventory UI");
            _inventoryUI = InventoryUI::create();
            _inventoryUI->setName("InventoryUI");
            scene->addChild(_inventoryUI, 100);
        }
        //log("Opening Inventory UI");
        _inventoryUI->setVisible(true);
        updateInventoryPosition(character);
    }

    _isInventoryOpen = !_isInventoryOpen;
}

void InventoryManager::updateInventoryPosition(Character* character) {
    if (!_inventoryUI) return;

    Vec2 characterPosition = character->getPosition();

    Vec2 inventoryPosition = Vec2(characterPosition.x + 100, characterPosition.y);
    _inventoryUI->setPosition(inventoryPosition);
}