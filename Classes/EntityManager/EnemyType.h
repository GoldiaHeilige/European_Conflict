#ifndef __ENEMY_TYPE_H__
#define __ENEMY_TYPE_H__

#include <unordered_map>
#include <string>
#include "EntityStat.h"
#include "EntityInfo.h"

class EnemyType {
public:
    static EnemyType* getInstance();

    // Loads predefined enemy configurations
    void preloadEnemyData();

    // Retrieves enemy stats and info based on name
    bool getEnemyData(const std::string& enemyName, EntityInfo*& info, EntityStat*& stat);

private:
    EnemyType() { preloadEnemyData(); }
    static EnemyType* _instance;

    struct EnemyData {
        EntityInfo info;
        EntityStat stat;
    };

    // Map to store enemy configurations with enemy name as the key
    std::unordered_map<std::string, EnemyData> _enemyDataMap;
};

#endif // __ENEMY_TYPE_H__
