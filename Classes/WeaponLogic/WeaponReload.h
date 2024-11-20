#ifndef __WEAPON_RELOAD_H__
#define __WEAPON_RELOAD_H__

#include "cocos2d.h"
#include "Audio/AudioManager.h"
#include "AmmoManager.h"
#include "WeaponStat.h"

class WeaponReload {
public:
    WeaponReload(AmmoManager& ammoManager, const WeaponStat& weaponStat);

    void startReload(cocos2d::Node* scene);
    void cancelReload(cocos2d::Node* scene);
    bool isReloading() const { return _isReloading; }

private:
    AmmoManager& _ammoManager;
    const WeaponStat& _weaponStat;

    bool _isReloading;
    int _reloadSFXID;
};

#endif // __WEAPON_RELOAD_H__
