#include "InventoryUI.h"
#include "InventorySlotUI.h"

USING_NS_CC;

InventoryUI* InventoryUI::create() {
    InventoryUI* ret = new (std::nothrow) InventoryUI();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool InventoryUI::init() {
    if (!Node::init()) return false;

    int numRows = 5;
    int numCols = 5;
    float slotSize = 64.0f;
    float slotSpacing = 10.0f;

    float width = numCols * slotSize + (numCols - 1) * slotSpacing;
    float height = numRows * slotSize + (numRows - 1) * slotSpacing;

    _backgroundNode = Node::create();
    this->addChild(_backgroundNode);

    _background = Sprite::create("UI/UIAtlasFramesTEST1.png");
    if (!_background) {
        CCLOG("Failed to load background image.");
        return false;
    }


    _background->setContentSize(Size(width, height));
    _background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _backgroundNode->addChild(_background);

    float totalWidth = numCols * slotSize + (numCols - 1) * slotSpacing;
    float totalHeight = numRows * slotSize + (numRows - 1) * slotSpacing;

    float marginFactor = 1.25f;
    _background->setContentSize(Size(totalWidth * marginFactor, totalHeight * marginFactor));

    _backgroundNode->setPosition(Vec2(0, 20));

    createInventory(numRows, numCols, slotSize, slotSpacing);

    return true;
}

void InventoryUI::createInventory(int rows, int cols, float slotSize, float spacing) {
    Size bgSize = _background->getContentSize();
    float startX = (bgSize.width - (cols * slotSize + (cols - 1) * spacing)) / 2;
    float startY = (bgSize.height - (rows * slotSize + (rows - 1) * spacing)) / 2;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            addSlot(i, j, slotSize, spacing, startX, startY);
        }
    }
}

void InventoryUI::addSlot(int row, int col, float slotSize, float spacing, float startX, float startY) {
    auto slot = InventorySlotUI::create();

    float x = startX + col * (slotSize + spacing) + slotSize / 2;
    float y = startY + row * (slotSize + spacing) + slotSize / 2;

    slot->setPosition(Vec2(x, y));

    _background->addChild(slot);
}