#include "BulletManager.h"
#include "WeaponLogic/WeaponCtrl.h"
#include "WeaponLogic/WeaponType.h"
#include "BulletTypes/KineticProjectile.h"

BulletManager::BulletManager()
{
    schedule([this](float dt) { update(dt); }, "bullet_manager_update_key");
}

BulletManager::~BulletManager()
{
    for (auto& bullet : _bullets) {
        bullet->removeFromParentAndCleanup(true);
    }
    _bullets.clear();
}

Bullet* BulletManager::createBullet(Entity* entity)
{
    std::string bulletType = WeaponCtrl::getInstance()->getCurrentWeaponStat()._bulletType;

    if (bulletType == "Kinetic") {
        return KineticProjectile::create(entity);
    }
    // Add more bullet types as needed (e.g., Explosive)

    return nullptr; // Return nullptr if no matching bullet type is found
}

void BulletManager::addBullet(Bullet* bullet)
{
    if (bullet) {
        _bullets.push_back(bullet);
        this->addChild(bullet);
    }
}

void BulletManager::update(float dt)
{
    // Update bullets here, if necessary (e.g., movement, checking if out of bounds, etc.)
    for (auto& bullet : _bullets) {
        // You can add additional logic for bullet management here
    }
}
