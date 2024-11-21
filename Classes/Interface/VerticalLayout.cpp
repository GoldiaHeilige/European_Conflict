#include "VerticalLayout.h"

VerticalLayout::VerticalLayout()
    : _spacing(10) // Mặc định khoảng cách giữa các đối tượng con là 10
{
}

VerticalLayout::~VerticalLayout() {}

void VerticalLayout::addChild(cocos2d::Node* child)
{
    Node::addChild(child);
    updateLayout();
}

void VerticalLayout::updateLayout()
{
    float yOffset = 0;
    for (auto& child : getChildren())
    {
        // Đặt vị trí của đối tượng con
        child->setPosition(0, yOffset - child->getContentSize().height / 2);
        yOffset -= child->getContentSize().height + _spacing;
    }
}
