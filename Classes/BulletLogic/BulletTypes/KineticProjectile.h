#ifndef __KINETIC_PROJECTILE_H__
#define __KINETIC_PROJECTILE_H__

#include "BulletLogic/Bullet.h"
#include "cocos2d.h"
#include "EntityManager/IDamageable.h"

class KineticProjectile : public Bullet
{
public:
    static KineticProjectile* create(Entity* entity);

    // Handle what happens when the bullet hits something
    void onHit(PhysicsContact& contact);

private:
    int _dmg; // Damage for kinetic bullet
};

#endif // __KINETIC_PROJECTILE_H__
