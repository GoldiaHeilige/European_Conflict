#ifndef __ENEMY_TYPE_H__
#define __ENEMY_TYPE_H__

#include <unordered_map>
#include <string>
#include "EntityStat.h"
#include "EntityInfo.h"

class EnemyType {
public:
    // Truy cập instance singleton
    static EnemyType* getInstance();

    // Tải dữ liệu từ file JSON
    void loadEnemyDataFromJSON(const std::string& filePath);

    // Lấy thông tin enemy dựa trên tên
    bool getEnemyData(const std::string& enemyName, EntityInfo*& info, EntityStat*& stat);

private:
    // Constructor private (singleton)
    EnemyType();

    // Destructor
    ~EnemyType();

    // Instance singleton
    static EnemyType* _instance;

    // Cấu trúc lưu dữ liệu kẻ địch
    struct EnemyData {
        EntityInfo info;
        EntityStat stat;
    };

    // Map để lưu trữ dữ liệu enemy
    std::unordered_map<std::string, EnemyData> _enemyDataMap;
};

#endif // __ENEMY_TYPE_H__
