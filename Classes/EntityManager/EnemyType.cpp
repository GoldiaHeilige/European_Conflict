#include "EnemyType.h"

EnemyType* EnemyType::_instance = nullptr;

EnemyType* EnemyType::getInstance() {
    if (!_instance) {
        _instance = new EnemyType();
    }
    return _instance;
}

void EnemyType::preloadEnemyData() {
    EnemyData enemy1;
    enemy1.info._type = "Enemy";
    enemy1.info._name = "Enemy4_Rifle";
    enemy1.stat._spd = 10;
    enemy1.stat._hp = 100;
    _enemyDataMap["Enemy4_Rifle"] = enemy1;
   
    EnemyData enemy2;
    enemy2.info._type = "Enemy";
    enemy2.info._name = "Enemy3_Rifle";
    enemy2.stat._spd = 10;
    enemy2.stat._hp = 150;
    _enemyDataMap["Enemy3_Rifle"] = enemy2;
}

bool EnemyType::getEnemyData(const std::string& enemyName, EntityInfo*& info, EntityStat*& stat) {
    auto it = _enemyDataMap.find(enemyName);
    if (it != _enemyDataMap.end()) {
        info = &it->second.info;
        stat = &it->second.stat;
        return true;
    }
    return false;
}
