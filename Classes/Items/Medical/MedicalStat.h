#ifndef __MEDICAL_STAT_H__
#define __MEDICAL_STAT_H__

#include "Items/BaseItemStat.h"

struct MedicalStat : public BaseItemStat {
    int _healAmount;         
    float _useTime;         
    float _cooldown;         
    std::string _effectType;  
};

#endif // __MEDICAL_STAT_H__
