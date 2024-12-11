#ifndef __INVENTORY_SLOT_UI_H__
#define __INVENTORY_SLOT_UI_H__

#include "cocos2d.h"

class InventorySlotUI : public cocos2d::Node {
public:
    static InventorySlotUI* create();
    bool init() override;
    void setSlotIcon(const std::string& iconPath);

private:
    cocos2d::Sprite* _slotBackground;
    cocos2d::Sprite* _slotIcon;  
};

#endif // __INVENTORY_SLOT_UI_H__
