#ifndef __KINETIC_PROJECTILE_H__
#define __KINETIC_PROJECTILE_H__

#include "BulletLogic/Bullet.h"
#include "cocos2d.h"
#include "EntityManager/IDamageable.h"

class KineticProjectile : public Bullet
{
public:
    static KineticProjectile* create(Entity* entity, const std::string& bulletSprite);

    void onHit(IDamageable* target) override;

private:
    float _dmg;
};

#endif // __KINETIC_PROJECTILE_H__