#ifndef __BULLET_TYPE_H__
#define __BULLET_TYPE_H__

#include "cocos2d.h"
#include <string>

class BulletType {
public:
    BulletType(const std::string& name);

    virtual void onHit(cocos2d::Node* bullet, cocos2d::Node* target, float damage); // Thêm tham số damage
    const std::string& getName() const { return _name; }

protected:
    std::string _name;  // Tên loại đạn
};

class KineticBulletType : public BulletType {
public:
    KineticBulletType() : BulletType("Kinetic") {}
    void onHit(cocos2d::Node* bullet, cocos2d::Node* target, float damage) override;
};

#endif // __BULLET_TYPE_H__
