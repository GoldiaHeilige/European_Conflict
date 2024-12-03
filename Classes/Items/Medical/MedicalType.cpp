#include "MedicalType.h"
#include "cocos2d.h"
#include "json/document.h"

using namespace cocos2d;
using namespace rapidjson;

MedicalType* MedicalType::_instance = nullptr;

MedicalType* MedicalType::getInstance() {
    if (!_instance) {
        _instance = new MedicalType();
        _instance->loadMedicalDataFromJSON("Items/Medical/medical_data.json");
    }
    return _instance;
}

MedicalType::MedicalType() {}

MedicalType::~MedicalType() {}

void MedicalType::loadMedicalDataFromJSON(const std::string& filePath) {
    std::string fileData = FileUtils::getInstance()->getStringFromFile(filePath);
    if (fileData.empty()) {
        CCLOG("Failed to load medical data from %s", filePath.c_str());
        return;
    }

    Document document;
    document.Parse(fileData.c_str());

    if (document.HasParseError() || !document.IsArray()) {
        CCLOG("Invalid JSON format in %s", filePath.c_str());
        return;
    }

    for (auto& medicalItem : document.GetArray()) {
        if (medicalItem.IsObject() && medicalItem.HasMember("name") && medicalItem["name"].IsString()) {
            MedicalStat stat;
            stat._id = medicalItem["id"].GetString();
            stat._name = medicalItem["name"].GetString(); // Dùng để spawn từ Tiled
            stat._description = medicalItem["description"].GetString();
            stat._healAmount = medicalItem["heal_amount"].GetInt();
            stat._stackSize = medicalItem["stack_size"].GetInt();
            stat._weight = medicalItem["weight"].GetFloat();
            stat._icon = medicalItem["icon"].GetString();
            stat._useTime = medicalItem["use_time"].GetFloat();
            stat._cooldown = medicalItem["cooldown"].GetFloat();
            stat._effectType = medicalItem["effect_type"].GetString();

            _medicalStats[stat._name] = stat;
            CCLOG("Loaded medical item: %s", stat._name.c_str());
        }
    }
}

bool MedicalType::getMedicalStatByName(const std::string& name, MedicalStat*& stat) {
    auto it = _medicalStats.find(name);
    if (it != _medicalStats.end()) {
        stat = &it->second;
        return true;
    }
    return false;
}
