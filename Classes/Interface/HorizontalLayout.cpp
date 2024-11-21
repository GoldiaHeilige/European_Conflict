#include "HorizontalLayout.h"

HorizontalLayout::HorizontalLayout()
    : _spacing(10) // Mặc định khoảng cách giữa các đối tượng con là 10
{
}

HorizontalLayout::~HorizontalLayout() {}

void HorizontalLayout::addChild(cocos2d::Node* child)
{
    Node::addChild(child);
    updateLayout();
}

void HorizontalLayout::updateLayout()
{
    float xOffset = 0;
    for (auto& child : getChildren())
    {
        // Đặt vị trí của đối tượng con
        child->setPosition(xOffset + child->getContentSize().width / 2, 0);
        xOffset += child->getContentSize().width + _spacing;
    }
}
