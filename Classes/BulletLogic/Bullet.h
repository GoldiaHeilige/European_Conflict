#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#include "EntityManager/Entity.h"
#include "EntityManager/IDamageable.h"

using namespace cocos2d;

class Bullet : public Node
{
public:
    static Bullet* create(Entity* entity, std::string bulletSprite);

    virtual bool init(Entity* entity, const std::string& bulletSprite);
    void fire(Vec2 direction, float velocity);

protected:
    Sprite* _model;
    Entity* _entity;

    bool onContactBegin(PhysicsContact& contact);

    virtual void onHit(IDamageable* target);
    virtual void onHitNonDamageable();
};

#endif // __BULLET_H__