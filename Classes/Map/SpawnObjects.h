#ifndef __SPAWN_OBJECTS_H__
#define __SPAWN_OBJECTS_H__

#include "cocos2d.h"
#include "AnimManager/AnimationUtils.h"
#include "EntityManager/EnemyType.h"
#include "EntityManager/Enemy.h"

class SpawnObjects {
public:
    SpawnObjects(cocos2d::Node* parentNode); 
    // Vehicle
    void spawnCarsFromTiled(cocos2d::TMXTiledMap* map);

    // Building & Elements
    void spawn_Building_Industrial_Normal(cocos2d::TMXTiledMap* map);
    void spawn_Building_Industrial_Broken(cocos2d::TMXTiledMap* map);
    void spawn_Industrial_Elements_Broken(cocos2d::TMXTiledMap* map);

    // Static Decoration
    void spawnFiresFromTiled(cocos2d::TMXTiledMap* map);

    // Entity
    void spawnEnemiesFromTiled(cocos2d::TMXTiledMap* map);

private:
    cocos2d::Node* _parentNode; 
};

#endif // __SPAWN_OBJECTS_H__
