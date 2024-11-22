#include "KineticProjectile.h"
#include "WeaponLogic/WeaponCtrl.h"
#include "EntityManager/Enemy.h"

KineticProjectile* KineticProjectile::create(Entity* entity)
{
    KineticProjectile* newProjectile = new KineticProjectile();
    if (newProjectile && newProjectile->init(entity, "")) {
        newProjectile->_dmg = WeaponCtrl::getInstance()->getCurrentWeaponStat()._atk;
        newProjectile->autorelease();
        return newProjectile;
    }

    CC_SAFE_DELETE(newProjectile);
    return nullptr;
}

void KineticProjectile::onHit(PhysicsContact& contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    auto bullet = (nodeA == this) ? nodeA : (nodeB == this) ? nodeB : nullptr;
    auto target = (nodeA == this) ? nodeB : nodeA;

    if (bullet && target) {
        if (auto damageable = dynamic_cast<IDamageable*>(target)) {
            damageable->takeDame(_dmg);
        }

        this->removeFromParentAndCleanup(true);
    }
}
