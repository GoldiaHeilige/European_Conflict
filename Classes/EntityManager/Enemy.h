#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <random>
#include <cmath>
#include <cstdlib>
#include "Entity.h"
#include "IDamageable.h"
#include "AnimManager/AnimationUtils.h"

class Enemy : public Entity, public IDamageable
{
public:
    static Enemy* create(EntityInfo* info, EntityStat* entityStat);
    virtual bool init(EntityInfo* info, EntityStat* entityStat);
    void takeDame(int dame) override;

private:
    void die();
    void update(float dt);

    bool _isMoving = false; // Flag to check if the enemy is moving
    float _movementTimer = 0.0f; // Timer to track movement time
    float _nextMovementTime = 5.0f; // Random movement time (initially set to 5 seconds)
    Vec2 _targetPosition; // The target position to move towards
    Vec2 _targetDirection; // The direction vector to move in
};

#endif // !__ENEMY_H__