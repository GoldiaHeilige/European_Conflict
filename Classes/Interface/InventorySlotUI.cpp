#include "InventorySlotUI.h"

USING_NS_CC;

InventorySlotUI* InventorySlotUI::create() {
    InventorySlotUI* ret = new (std::nothrow) InventorySlotUI();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool InventorySlotUI::init() {
    if (!Node::init()) return false;

    _slotBackground = Sprite::create("UI/InventoryUIAtlasTEST1.png");
    _slotBackground->setContentSize(Size(64.0f, 64.0f));
    _slotBackground->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    this->addChild(_slotBackground);

    return true;
}

void InventorySlotUI::setSlotIcon(const std::string& iconPath) {
    if (!_slotIcon) {
        _slotIcon = Sprite::create(iconPath);
        _slotIcon->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        this->addChild(_slotIcon);
    }
    else {
        _slotIcon->setTexture(iconPath);
    }
}
