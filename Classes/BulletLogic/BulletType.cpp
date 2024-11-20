#include "BulletType.h"
#include "EntityManager/IDamageable.h"

BulletType::BulletType(const std::string& name)
    : _name(name) {}

void BulletType::onHit(cocos2d::Node* bullet, cocos2d::Node* target, float damage) {
    // Default behavior: không làm gì
}

void KineticBulletType::onHit(cocos2d::Node* bullet, cocos2d::Node* target, float damage) {
    // Nếu đối tượng target có thể bị gây sát thương
    if (auto damageable = dynamic_cast<IDamageable*>(target)) {
        damageable->takeDame(damage); // Sử dụng damage được truyền từ vũ khí
    }
}
