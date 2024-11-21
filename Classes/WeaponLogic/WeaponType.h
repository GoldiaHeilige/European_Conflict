#ifndef __WEAPON_TYPE_H__
#define __WEAPON_TYPE_H__

#include <unordered_map>
#include <string>
#include "WeaponStat.h"
#include "cocos2d.h"
#include "json/document.h"  // Add rapidjson for JSON parsing (if necessary)

// Forward declaration to avoid circular dependency issues (if needed)
class WeaponStat;

class WeaponType
{
public:
    // Constructor: Initializes the weapon types by loading from a JSON file
    WeaponType();

    // Initializes weapon stats by reading from a JSON file
    void initializeWeaponTypes();

    // Retrieves weapon stats by weapon ID
    WeaponStat getWeaponStatByID(int weaponID);

private:
    // A map to store weapon statistics by weapon ID
    std::unordered_map<int, WeaponStat> _weaponStats;
};

#endif // __WEAPON_TYPE_H__
