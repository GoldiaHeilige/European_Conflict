#ifndef __INVENTORY_MANAGER_H__
#define __INVENTORY_MANAGER_H__

#include "cocos2d.h"
#include "InventoryUI.h"
#include "EntityManager/PlayerLogic/Character.h"

USING_NS_CC;

class InventoryManager : public Node {
public:
    static InventoryManager* getInstance();
    void toggleInventory();

private:
    InventoryManager();
    bool init();
    void updateInventoryPosition(Character* character);

private:
    bool _isInventoryOpen = false;
    InventoryUI* _inventoryUI = nullptr;

    static InventoryManager* _instance;
};

#endif // __INVENTORY_MANAGER_H__