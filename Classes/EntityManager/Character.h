#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "Entity.h"
#include "IDamageable.h"
#include "AnimManager/AnimationUtils.h"
#include "Menu/MainMenuScene.h"
#include "WeaponLogic/WeaponCtrl.h"

class Character : public Entity
{
public:
    static Character* create(EntityInfo* info, EntityStat* entityStat);
    bool init(EntityInfo* info, EntityStat* entityStat);

    Character(); 
    virtual ~Character();

    void move(Vec2 direction);
    void rotateBody(float angle);
    void takeDame(int dame);
    void shoot(Vec2 direction);

    virtual void onEnter() override;
    virtual void onExit() override;

private:
    void die();
    void update(float dt);

    void updateSpriteBasedOnWeaponCategory(const std::string& category);
    std::string getSpriteFileNameForCategory(const std::string& category);

    EntityStat* _stat;
    cocos2d::Sprite* _model;
};

#endif // __CHARACTER_H__
