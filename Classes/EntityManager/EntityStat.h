#ifndef __ENTITY_STAT_H__
#define __ENTITY_STAT_H__

#include <string>

class EntityStat
{
public:
    // Character stats
    std::string _hitSFX;   // Play SFX when bullet hit an Entity
    std::string _dieSFX;   // Play die SFX when entity is dead

    float _hp;  // Health Point of an Entity
    float _spd; // Speed of an Entity
    float _armor; // Armor of an Entity
};

#endif // __ENTITY_STAT_H__
