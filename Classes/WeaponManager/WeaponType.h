#ifndef __WEAPON_TYPE_H__
#define __WEAPON_TYPE_H__

#include <unordered_map>
#include <string>
#include "WeaponStat.h"

class WeaponType {
public:
    WeaponType();

    bool loadWeaponTypesFromJSON(const std::string& filePath);
    WeaponStat getWeaponStatByID(int weaponID) const;

private:
    std::unordered_map<int, WeaponStat> _weaponStats;
};

#endif // __WEAPON_TYPE_H__
