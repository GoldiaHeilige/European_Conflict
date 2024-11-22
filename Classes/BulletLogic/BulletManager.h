#ifndef __BULLET_MANAGER_H__
#define __BULLET_MANAGER_H__

#include "cocos2d.h"
#include "Bullet.h"
#include "BulletTypes/KineticProjectile.h"

using namespace cocos2d;

class BulletManager : public Node
{
public:
    BulletManager();
    ~BulletManager();

    // Create a bullet based on the current weapon's bullet type
    Bullet* createBullet(Entity* entity);

    void addBullet(Bullet* bullet);
    void update(float dt);

private:
    std::vector<Bullet*> _bullets;
};

#endif // __BULLET_MANAGER_H__
