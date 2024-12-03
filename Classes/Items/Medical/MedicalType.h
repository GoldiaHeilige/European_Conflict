#ifndef __MEDICAL_TYPE_H__
#define __MEDICAL_TYPE_H__

#include <unordered_map>
#include <string>
#include "MedicalStat.h"
#include "cocos2d.h"
#include "json/document.h"

class MedicalType {
public:
    static MedicalType* getInstance(); // Singleton Pattern

    void loadMedicalDataFromJSON(const std::string& filePath);
    bool getMedicalStatByName(const std::string& name, MedicalStat*& stat);

private:
    MedicalType();  // Constructor
    ~MedicalType(); // Destructor

    static MedicalType* _instance;
    std::unordered_map<std::string, MedicalStat> _medicalStats; 
};

#endif // __MEDICAL_TYPE_H__
