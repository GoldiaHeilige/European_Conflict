#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#include "BulletType.h"
#include "EntityManager/Enemy.h"

using namespace cocos2d;

class Bullet : public Node {
public:
    static Bullet* create(Entity* entity, const std::string& bulletSprite, BulletType* bulletType, float damage);
    bool init(Entity* entity, const std::string& bulletSprite, BulletType* bulletType, float damage);

    void fire(const Vec2& direction, float velocity);

private:
    bool onContactBegin(PhysicsContact& contact);

    BulletType* _bulletType;
    Sprite* _model;
    Entity* _entity;         
    float _damage;          
};

#endif // __BULLET_H__
