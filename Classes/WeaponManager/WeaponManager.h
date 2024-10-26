﻿#ifndef __WEAPON_MANAGER_H__
#define __WEAPON_MANAGER_H__

#include "cocos2d.h"
#include "EntityManager/EntityStat.h"
#include "UILayer/UIManager.h"
#include "Audio/AudioManager.h"
#include "WeaponManager/Bullet.h"

using namespace cocos2d;

class WeaponManager {
public:
    enum class WeaponType {
        PISTOL,
        ASSAULT_RIFLE,
        MACHINE_GUN,
        GRENADE_LAUNCHER
    };

    WeaponManager();
    static WeaponManager* getInstance();
    WeaponType getCurrentWeapon();

    void setCurrentWeapon(WeaponType weaponType);
    EntityStat* getCurrentWeaponStats();
    void shoot(Node* characterNode, Vec2 direction);
    void reload();

private:
    WeaponType _currentWeapon = WeaponType::PISTOL;
    EntityStat* _currentWeaponStats = nullptr; // Initialize pointer to nullptr
    void initializeWeapons();

    static WeaponManager* _instance;
};

#endif // __WEAPON_MANAGER_H__