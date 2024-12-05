#ifndef __MEDICAL_LOGIC_H__
#define __MEDICAL_LOGIC_H__

#include "cocos2d.h"
#include <string>

class MedicalStat;
class Character;

class MedicalLogic {
public:
    MedicalLogic();  
    ~MedicalLogic(); 

    void useMedicalItem(const std::string& itemName, Character* character);

private:
    void applyHealing(MedicalStat* stat, Character* character);

    void applyDamageReduction(MedicalStat* stat, Character* character);
};

#endif // __MEDICAL_LOGIC_H__
