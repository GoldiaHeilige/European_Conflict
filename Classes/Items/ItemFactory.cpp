#include "ItemFactory.h"

BaseItemStat* ItemFactory::createItem(const std::string& itemName) {
    MedicalStat* medicalStat = nullptr;

    // Kiểm tra nếu item là loại medical
    if (MedicalType::getInstance()->getMedicalStatByName(itemName, medicalStat)) {
        return new MedicalStat(*medicalStat);
    }

    // Có thể mở rộng thêm các loại vật phẩm khác như vũ khí, đạn dược
    // WeaponStat* weaponStat = nullptr;
    // if (WeaponType::getInstance()->getWeaponStatByName(itemName, weaponStat)) {
    //     return new WeaponStat(*weaponStat);
    // }

    CCLOG("ItemFactory: Item %s not found!", itemName.c_str());
    return nullptr;
}
