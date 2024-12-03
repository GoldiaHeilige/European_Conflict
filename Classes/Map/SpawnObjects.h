#ifndef __SPAWN_OBJECTS_H__
#define __SPAWN_OBJECTS_H__

#include "cocos2d.h"
#include "AnimManager/AnimationUtils.h"
#include "EntityManager/EnemyLogic/EnemyType.h"
#include "EntityManager/EnemyLogic/Enemy.h"

class SpawnObjects {
public:
    SpawnObjects(cocos2d::Node* parentNode); 
    // Vehicle
    void spawn_Civil_Normal_Cars_1(cocos2d::TMXTiledMap* map);
    void spawn_Civil_Normal_Cars_2(cocos2d::TMXTiledMap* map);

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
