#include "MedicalLogic.h"
#include "MedicalType.h"
#include "EntityManager/PlayerLogic/PlayerStatsManager.h"
#include "EntityManager/PlayerLogic/Character.h"
#include "cocos2d.h"

using namespace cocos2d;

MedicalLogic::MedicalLogic() {}

MedicalLogic::~MedicalLogic() {}

void MedicalLogic::useMedicalItem(const std::string& itemName, Character* character) {
    MedicalStat* stat = nullptr;

    if (MedicalType::getInstance()->getMedicalStatByName(itemName, stat)) {
        if (stat->_effectType == "heal") {
            applyHealing(stat, character);
        }
        else if (stat->_effectType == "reduce_damage") {
            applyDamageReduction(stat, character);
        }

        EventCustom event("MedicalItemUsed");
        event.setUserData(stat);
        Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
    }
}

void MedicalLogic::applyHealing(MedicalStat* stat, Character* character) {
    if (!character) return;

    EntityStat* charStat = character->getStat();
    if (charStat) {
        charStat->_hp += stat->_healAmount;
        CCLOG("Healed %s by %d HP. New HP: %f", character->getName().c_str(), stat->_healAmount, charStat->_hp);
    }
}

void MedicalLogic::applyDamageReduction(MedicalStat* stat, Character* character) {
    if (character) {
        character->getStat()->_armor += 10.0f;  // Giả lập giảm sát thương
        CCLOG("Damage reduction applied, new armor: %f", character->getStat()->_armor);
    }
}