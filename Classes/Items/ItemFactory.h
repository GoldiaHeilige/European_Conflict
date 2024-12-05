#ifndef __ITEM_FACTORY_H__
#define __ITEM_FACTORY_H__

#include "cocos2d.h"
#include "Medical/MedicalType.h"
#include "Medical/MedicalStat.h"
#include "BaseItemStat.h"

class ItemFactory {
public:
    static BaseItemStat* createItem(const std::string& itemName);
};

#endif // __ITEM_FACTORY_H__
