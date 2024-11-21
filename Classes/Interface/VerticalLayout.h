#ifndef __VERTICAL_LAYOUT_H__
#define __VERTICAL_LAYOUT_H__

#include "cocos2d.h"

class VerticalLayout : public cocos2d::Node
{
public:
    VerticalLayout();
    virtual ~VerticalLayout();

    // Thêm một đối tượng con vào layout
    void addChild(cocos2d::Node* child) override;

    // Cập nhật vị trí các đối tượng con theo chiều dọc
    void updateLayout();

protected:
    // Khoảng cách giữa các đối tượng con
    float _spacing;
};

#endif // __VERTICAL_LAYOUT_H__
