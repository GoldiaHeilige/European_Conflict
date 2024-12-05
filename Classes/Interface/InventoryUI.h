#ifndef __INVENTORY_UI_H__
#define __INVENTORY_UI_H__

#include "cocos2d.h"

class InventoryUI : public cocos2d::Node {
public:
    static InventoryUI* create();
    bool init() override;

    void createInventory(int rows, int cols, float slotSize, float spacing);
    void addSlot(int row, int col, float slotSize, float spacing, float startX, float startY);

private:
    cocos2d::Sprite* _background;
    cocos2d::Node* _backgroundNode;
};

#endif // __INVENTORY_UI_H__
