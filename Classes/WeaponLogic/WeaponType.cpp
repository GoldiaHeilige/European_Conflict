#include "WeaponType.h"
#include "cocos2d.h"
#include "json/document.h"

WeaponType::WeaponType()
{
    initializeWeaponTypes();
}

void WeaponType::initializeWeaponTypes() {
    // Load JSON from a file (example file path)
    std::string jsonFilePath = "weapon_data.json";
    cocos2d::FileUtils* fileUtils = cocos2d::FileUtils::getInstance();
    std::string jsonData = fileUtils->getStringFromFile(jsonFilePath);

    if (jsonData.empty()) {
        CCLOG("Error: JSON file could not be loaded!");
        return;
    }

    rapidjson::Document doc;
    doc.Parse<0>(jsonData.c_str());

    if (doc.HasParseError()) {
        CCLOG("Error: JSON parse error at offset %u", doc.GetErrorOffset());
        return;
    }

    if (doc.IsArray()) {
        for (rapidjson::SizeType i = 0; i < doc.Size(); i++) {
            const rapidjson::Value& weapon = doc[i];
            if (weapon.HasMember("weaponID") && weapon["weaponID"].IsInt()) {
                int weaponID = weapon["weaponID"].GetInt();
                WeaponStat weaponStat;

                weaponStat._weaponID = weaponID;
                weaponStat._weaponName = weapon["weaponName"].GetString();
                weaponStat._category = weapon["category"].GetString();
                weaponStat._bulletType = weapon["bulletType"].GetString();
                weaponStat._fireSFX = weapon["fireSFX"].GetString();
                weaponStat._reloadSFX = weapon["reloadSFX"].GetString();
                weaponStat._bulletSprite = weapon["bulletSprite"].GetString();
                weaponStat._atk = weapon["atk"].GetDouble();
                weaponStat._critChance = weapon["critChance"].GetDouble();
                weaponStat._critDmg = weapon["critDmg"].GetDouble();
                weaponStat._piercingChance = weapon["piercingChance"].GetDouble();
                weaponStat._armorDmg = weapon["armorDmg"].GetDouble();
                weaponStat._totalAmmoMax = weapon["totalAmmoMax"].GetInt();
                weaponStat._weaponMag = weapon["weaponMag"].GetInt();
                weaponStat._bulletVelocity = weapon["bulletVelocity"].GetDouble();
                weaponStat._ammoType = weapon["ammoType"].GetInt();
                weaponStat._reloadTime = weapon["reloadTime"].GetDouble();

                _weaponStats[weaponID] = weaponStat;
            }
            else {
                CCLOG("Warning: Missing weaponID in weapon data entry.");
            }
        }
    }
    else {
        CCLOG("Error: Expected JSON array for weapon data.");
    }
}

WeaponStat WeaponType::getWeaponStatByID(int weaponID)
{
    return _weaponStats.count(weaponID) ? _weaponStats[weaponID] : WeaponStat();
}
