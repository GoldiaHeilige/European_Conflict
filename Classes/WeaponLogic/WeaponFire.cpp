#include "WeaponFire.h"
#include "BulletLogic/Bullet.h"
#include "Audio/AudioManager.h"

void WeaponFire::fireBullet(cocos2d::Node* characterNode, const cocos2d::Vec2& direction, const WeaponStat& weaponStat, AmmoManager& ammoManager) {
    BulletType* bulletType = createBulletType(weaponStat._bulletType);
    if (!bulletType) {
        CCLOG("Invalid bullet type: %s", weaponStat._bulletType.c_str());
        return;
    }

    Bullet* bullet = Bullet::create(static_cast<Entity*>(characterNode), weaponStat._bulletSprite, bulletType, weaponStat._atk);
    if (!bullet) {
        delete bulletType;
        return;
    }

    Vec2 spawnPosition = calculateSpawnPosition(characterNode, direction);
    float angle = calculateBulletRotation(direction);

    bullet->setPosition(spawnPosition);
    bullet->setRotation(-angle + 90);
    bullet->fire(direction, weaponStat._bulletVelocity);
    bullet->setName("Hero Bullet");

    characterNode->getParent()->addChild(bullet);
    /*AudioManager::getInstance()->playSFX(weaponStat._fireSFX);*/

}

cocos2d::Vec2 WeaponFire::calculateSpawnPosition(cocos2d::Node* characterNode, const cocos2d::Vec2& direction) {
    Vec2 spawnOffset = direction * 20;
    return characterNode->getPosition() + spawnOffset;
}

float WeaponFire::calculateBulletRotation(const cocos2d::Vec2& direction) {
    return CC_RADIANS_TO_DEGREES(atan2(direction.y, direction.x));
}

BulletType* WeaponFire::createBulletType(const std::string& typeName) {
    if (typeName == "Kinetic") {
        return new KineticBulletType();
    }
    return nullptr;
}