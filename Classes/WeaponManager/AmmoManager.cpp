#include "AmmoManager.h"

AmmoManager::AmmoManager()
    : _currentAmmo(0), _currentTotalAmmo(0), _maxMagCapacity(0) {}

void AmmoManager::initializeAmmo(const WeaponStat& weaponStat)
{
    _currentTotalAmmo = weaponStat._totalAmmoMax;
    _maxMagCapacity = weaponStat._weaponMag;
    _currentAmmo = _maxMagCapacity;
    CCLOG("Initialized ammo: Current Ammo = %d, Total Ammo = %d, Mag Capacity = %d",
        _currentAmmo, _currentTotalAmmo, _maxMagCapacity);
}

void AmmoManager::updateAmmo(int ammoUsed)
{
    _currentAmmo = std::max(0, _currentAmmo - ammoUsed);
    CCLOG("Ammo updated: Current Ammo = %d, Total Ammo = %d", _currentAmmo, _currentTotalAmmo);
}

int AmmoManager::reload(int maxReload)
{
    int reloadAmount = std::min(_currentTotalAmmo, maxReload);
    _currentAmmo += reloadAmount;
    _currentTotalAmmo -= reloadAmount;
    CCLOG("Weapon reloaded: New Ammo = %d, Remaining Total Ammo = %d", _currentAmmo, _currentTotalAmmo);
    return reloadAmount;
}