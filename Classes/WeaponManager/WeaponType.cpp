#include "WeaponType.h"
#include "cocos2d.h"
#include "json/document.h" 
#include "json/filereadstream.h"
#include <fstream>

WeaponType::WeaponType() {}

bool WeaponType::loadWeaponTypesFromJSON(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        CCLOG("Failed to open JSON file: %s", filePath.c_str());
        return false;
    }

    std::string jsonString((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    rapidjson::Document document;
    document.Parse(jsonString.c_str());

    if (document.HasParseError()) {
        CCLOG("Error parsing JSON file: %s", filePath.c_str());
        CCLOG("Parse error at offset %u: %s", document.GetErrorOffset(), document.GetParseError());
        return false;
    }

    if (!document.HasMember("weapons") || !document["weapons"].IsArray()) {
        CCLOG("Invalid JSON format: Missing 'weapons' array");
        return false;
    }

    for (const auto& weapon : document["weapons"].GetArray()) {
        WeaponStat stat;

        stat._weaponID = weapon["weaponID"].GetInt();
        stat._weaponName = weapon["weaponName"].GetString();
        stat._category = weapon["category"].GetString();
        stat._fireSFX = weapon["fireSFX"].GetString();
        stat._reloadSFX = weapon["reloadSFX"].GetString();
        stat._bulletSprite = weapon["bulletSprite"].GetString();
        stat._gunChamber = weapon["gunChamber"].GetString();
        stat._atk = weapon["atk"].GetFloat();
        stat._critChance = weapon["critChance"].GetFloat();
        stat._critDmg = weapon["critDmg"].GetFloat();
        stat._piercingChance = weapon["piercingChance"].GetFloat();
        stat._armorDmg = weapon["armorDmg"].GetFloat();
        stat._totalAmmoMax = weapon["totalAmmoMax"].GetInt();
        stat._weaponMag = weapon["weaponMag"].GetInt();
        stat._bulletVelocity = weapon["bulletVelocity"].GetFloat();
        stat._ammoType = weapon["ammoType"].GetFloat();
        stat._reloadTime = weapon["reloadTime"].GetFloat();

        _weaponStats[stat._weaponID] = stat;
    }

    CCLOG("Loaded %zu weapons from JSON", _weaponStats.size());
    return true;
}

WeaponStat WeaponType::getWeaponStatByID(int weaponID) const {
    return _weaponStats.count(weaponID) ? _weaponStats.at(weaponID) : WeaponStat();
}
