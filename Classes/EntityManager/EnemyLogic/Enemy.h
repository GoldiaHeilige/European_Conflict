#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <random>
#include <cmath>
#include <cstdlib>
#include "EntityManager/Entity.h"
#include "EntityManager/IDamageable.h"
#include "AnimManager/AnimationUtils.h"

class Enemy : public Entity, public IDamageable
{
public:
    static Enemy* create(EntityInfo* info, EntityStat* entityStat);
    virtual bool init(EntityInfo* info, EntityStat* entityStat);
    void takeDame(float dame) override;

    ~Enemy();
private:
    void die(); 
};

#endif // !__ENEMY_H__