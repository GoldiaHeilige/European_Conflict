#ifndef __EXPLOSIVE_PROJECTILE_H__
#define __EXPLOSIVE_PROJECTILE_H__

#include "BulletLogic/Bullet.h"
#include "cocos2d.h"
#include "EntityManager/IDamageable.h"
#include "AnimManager/AnimationUtils.h"  

class ExplosiveProjectile : public Bullet
{
public:
    static ExplosiveProjectile* create(Entity* entity, const std::string& bulletSprite);

    void onHit(IDamageable* target) override;
    void onHitNonDamageable() override;

private:
    float _damageRadius;  // Radius of explosion
    float _explosiveDamage;  // Damage dealt by explosion
    void applyExplosionDamage(const cocos2d::Vec2& explosionCenter);

    int _impactSFXID;
};

#endif // __EXPLOSIVE_PROJECTILE_H__
