#ifndef __AMMO_MANAGER_H__
#define __AMMO_MANAGER_H__

#include "cocos2d.h"
#include "WeaponStat.h"

class AmmoManager
{
public:
    AmmoManager();

    void initializeAmmo(const WeaponStat& weaponStat);
    void updateAmmo(int ammoUsed);
    int reload(int maxReload); // Returns amount reloaded

    int getCurrentAmmo() const { return _currentAmmo; }
    int getTotalAmmo() const { return _currentTotalAmmo; }
    int getMaxMagCapacity() const { return _maxMagCapacity; }

    void setMaxMagCapacity(int capacity) { _maxMagCapacity = capacity; }
    void setCurrentAmmo(int ammo) { _currentAmmo = ammo; }
    void setTotalAmmo(int totalAmmo) { _currentTotalAmmo = totalAmmo; }

private:
    int _currentAmmo;
    int _currentTotalAmmo;
    int _maxMagCapacity;
};

#endif // __AMMO_MANAGER_H__
