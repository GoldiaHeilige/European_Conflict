#ifndef __HORIZONTAL_LAYOUT_H__
#define __HORIZONTAL_LAYOUT_H__

#include "cocos2d.h"

class HorizontalLayout : public cocos2d::Node
{
public:
    HorizontalLayout();
    virtual ~HorizontalLayout();

    // Thêm một đối tượng con vào layout
    void addChild(cocos2d::Node* child) override;

    // Cập nhật vị trí các đối tượng con theo chiều ngang
    void updateLayout();

protected:
    // Khoảng cách giữa các đối tượng con
    float _spacing;
};

#endif // __HORIZONTAL_LAYOUT_H__
