#ifndef __SPAWN_ITEMS_H__
#define __SPAWN_ITEMS_H__

#include "cocos2d.h"
#include "Items/Medical/MedicalType.h"

class SpawnItems {
public:
    SpawnItems(cocos2d::Node* parentNode);
    void spawnMedicalFromTiled(cocos2d::TMXTiledMap* map);

private:
    cocos2d::Node* _parentNode;
};

#endif // __SPAWN_ITEMS_H__
