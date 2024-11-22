#include "KineticProjectile.h"
#include "WeaponLogic/WeaponCtrl.h"
#include "EntityManager/Enemy.h"

KineticProjectile* KineticProjectile::create(Entity* entity, const std::string& bulletSprite)
{
    KineticProjectile* newProjectile = new KineticProjectile();
    if (newProjectile && newProjectile->init(entity, bulletSprite)) {
        newProjectile->_dmg = WeaponCtrl::getInstance()->getCurrentWeaponStat()._atk;
        newProjectile->autorelease();
        return newProjectile;
    }

    CC_SAFE_DELETE(newProjectile);
    return nullptr;
}

void KineticProjectile::onHit(IDamageable* target)
{
    CCLOG("Kinetic projectile hit the target! Damage: %f", _dmg);
    if (target) {
        target->takeDame(_dmg);  
    }
}