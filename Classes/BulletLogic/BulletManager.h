#ifndef __BULLET_MANAGER_H__
#define __BULLET_MANAGER_H__

#include "cocos2d.h"
#include "Bullet.h"
#include "BulletTypes/KineticProjectile.h"
#include "BulletTypes/ExplosiveProjectile.h"

using namespace cocos2d;

class BulletManager : public Node
{
public:
    BulletManager();
    ~BulletManager();

    static BulletManager* getInstance();

    Bullet* createBullet(Entity* entity, const std::string& bulletSprite);

    void addBullet(Bullet* bullet);
    void update(float dt);

private:
    std::vector<Bullet*> _bullets;

    static BulletManager* _instance;
};

#endif // __BULLET_MANAGER_H__
