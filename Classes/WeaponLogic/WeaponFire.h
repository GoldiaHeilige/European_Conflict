#ifndef __WEAPON_FIRE_H__
#define __WEAPON_FIRE_H__

#include "WeaponStat.h"
#include "AmmoManager.h"
#include "cocos2d.h"

class WeaponFire
{
public:
    static void fireBullet(cocos2d::Node* characterNode, const cocos2d::Vec2& direction, const WeaponStat& weaponStat, AmmoManager& ammoManager);

private:
    static cocos2d::Vec2 calculateSpawnPosition(cocos2d::Node* characterNode, const cocos2d::Vec2& direction);
    static float calculateBulletRotation(const cocos2d::Vec2& direction);
};

#endif // __WEAPON_FIRE_H__