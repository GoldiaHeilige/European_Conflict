#ifndef __WEAPON_CTRL_H__
#define __WEAPON_CTRL_H__

#include "WeaponType.h"
#include "AmmoManager.h"
#include "WeaponStat.h"
#include "WeaponReload.h"
#include "cocos2d.h"
#include <unordered_map>

class WeaponCtrl {
public:
    static WeaponCtrl* getInstance();

    void setCurrentWeapon(int weaponID);
    void fireBullet(cocos2d::Node* characterNode, const cocos2d::Vec2& direction);
    void reload(cocos2d::Node* scene);

    int getCurrentAmmo() const { return _ammoManager.getCurrentAmmo(); }
    int getTotalAmmo() const { return _ammoManager.getTotalAmmo(); }

    WeaponStat getCurrentWeaponStat() const;
    AmmoManager& getAmmoManager() { return _ammoManager; }

private:
    WeaponCtrl();
    ~WeaponCtrl();

    static WeaponCtrl* _instance;

    int _currentWeaponID;
    WeaponStat _currentWeaponStat;
    WeaponType _weaponType;
    AmmoManager _ammoManager;

    std::unique_ptr<WeaponReload> _weaponReload;

    std::unordered_map<int, int> _ammoCache;
    std::unordered_map<int, int> _totalAmmoCache;
};

#endif // __WEAPON_CTRL_H__