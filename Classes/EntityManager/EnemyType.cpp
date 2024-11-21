#include "EnemyType.h"
#include "cocos2d.h"
#include "json/document.h"
#include "json/filereadstream.h"

using namespace cocos2d;
using namespace rapidjson;

EnemyType* EnemyType::_instance = nullptr;

EnemyType* EnemyType::getInstance() {
    if (!_instance) {
        _instance = new EnemyType();
    }
    return _instance;
}

EnemyType::EnemyType() {
    loadEnemyDataFromJSON("Entity/Enemy/enemy_data.json");
}

EnemyType::~EnemyType() {}

void EnemyType::loadEnemyDataFromJSON(const std::string& filePath) {

    std::string fileData = FileUtils::getInstance()->getStringFromFile(filePath);
    if (fileData.empty()) {
        CCLOG("Failed to load enemy data from %s", filePath.c_str());
        return;
    }

    Document document;
    document.Parse(fileData.c_str());

    if (document.HasParseError() || !document.IsObject()) {
        CCLOG("Invalid JSON format in %s", filePath.c_str());
        return;
    }

    if (document.HasMember("enemies") && document["enemies"].IsArray()) {
        const auto& enemies = document["enemies"];
        for (auto& enemy : enemies.GetArray()) {
            if (enemy.IsObject()) {
                EnemyData enemyData;
                enemyData.info._type = enemy["type"].GetString();
                enemyData.info._name = enemy["name"].GetString();
                enemyData.stat._spd = enemy["spd"].GetFloat();
                enemyData.stat._hp = enemy["hp"].GetFloat();
                enemyData.stat._armor = enemy["armor"].GetFloat();

                _enemyDataMap[enemyData.info._name] = enemyData;
                CCLOG("Loaded enemy: %s", enemyData.info._name.c_str());
            }
        }
    }
    else {
        CCLOG("No enemies found in %s", filePath.c_str());
    }
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
