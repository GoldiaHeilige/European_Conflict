#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#include "EntityManager/Enemy.h"
#include "EntityManager/IDamageable.h"
#include "WeaponCtrl.h"

using namespace cocos2d;

class Bullet : public Node
{
public:
    static Bullet* create(Entity* entity, std::string bulletName);
    virtual bool init(Entity* entity, std::string bulletName);

    void fire(Vec2 direction, float velocity);
private:
    int _dmg;
protected:
    Sprite* _model;
    Entity* _entity;
    bool onContactBegin(PhysicsContact& contact);
};

#endif // !__BULLET_H__
