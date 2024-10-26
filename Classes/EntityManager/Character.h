#ifndef __CHARACTER_H__
#define	__CHARACTER_H__

#include "Entity.h"
#include "IDamageable.h"

#include "AnimManager/AnimationUtils.h"
#include "MenuManager/MainMenuScene.h"

#include "WeaponManager/WeaponManager.h"
#include "WeaponManager/Bullet.h"

class Character : public Entity
{
public:
    static Character* create(EntityInfo* info, EntityStat* entityStat);

    bool init(EntityInfo* info, EntityStat* entityStat);

    void move(Vec2 direction);
    void rotateBody(float angle);
    void takeDame(int dame);

    void shoot(Vec2 direction);
    void attack();
    void switchWeapon(WeaponManager::WeaponType newWeaponType);

private:
    void die();
    void onEnter();
    void update(float dt);
    EntityStat* _stat;
    WeaponManager _weaponManager;
};

#endif // !__CHARACTER_H__