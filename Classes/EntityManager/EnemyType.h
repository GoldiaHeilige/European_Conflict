#ifndef __ENEMY_TYPE_H__
#define __ENEMY_TYPE_H__

#include <unordered_map>
#include <string>
#include "EntityStat.h"
#include "EntityInfo.h"

class EnemyType {
public:
    static EnemyType* getInstance();

    void loadEnemyDataFromJSON(const std::string& filePath);

    bool getEnemyData(const std::string& enemyName, EntityInfo*& info, EntityStat*& stat);

private:
    EnemyType();
    ~EnemyType();

    static EnemyType* _instance;

    struct EnemyData {
        EntityInfo info;
        EntityStat stat;
    };

    std::unordered_map<std::string, EnemyData> _enemyDataMap;
};

#endif // __ENEMY_TYPE_H__
