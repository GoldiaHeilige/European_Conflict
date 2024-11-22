#include "BulletType.h"
#include "EntityManager/IDamageable.h"

BulletType::BulletType(const std::string& name)
    : _name(name) {}

void BulletType::onHit(cocos2d::Node* bullet, cocos2d::Node* target, float damage) {
}

void KineticBulletType::onHit(cocos2d::Node* bullet, cocos2d::Node* target, float damage) {
    if (auto damageable = dynamic_cast<IDamageable*>(target)) {
        damageable->takeDame(damage);
    }
}