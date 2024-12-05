#ifndef __PLAYER_STATS_MANAGER_H__
#define __PLAYER_STATS_MANAGER_H__

#include "EntityManager/EntityStat.h"

class PlayerStatsManager
{
public:
    static PlayerStatsManager* getInstance();

    void initializePlayerStats();
    void updatePlayerStats(float hp, float speed, float armor);
    EntityStat* getPlayerStats();

private:
    PlayerStatsManager();
    ~PlayerStatsManager();

    EntityStat* _playerStats;
};

#endif // __PLAYER_STATS_MANAGER_H__
