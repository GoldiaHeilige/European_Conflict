#include "BulletManager.h"
#include "WeaponLogic/WeaponCtrl.h"
#include "WeaponLogic/WeaponType.h"

BulletManager* BulletManager::_instance = nullptr;

BulletManager* BulletManager::getInstance()
{
    if (_instance == nullptr) {
        _instance = new BulletManager();
        _instance->retain(); 
    }
    return _instance;
}

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

Bullet* BulletManager::createBullet(Entity* entity, const std::string& bulletSprite)
{
    std::string bulletType = WeaponCtrl::getInstance()->getCurrentWeaponStat()._bulletType;
    if (bulletType == "Kinetic") {
        return KineticProjectile::create(entity, bulletSprite);
    }

    return nullptr;
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
        // Add additional logic for bullet management here
    }
}
