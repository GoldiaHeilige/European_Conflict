#ifndef __PICKUP_ITEM_LOGIC_H__
#define __PICKUP_ITEM_LOGIC_H__

#include "cocos2d.h"
#include "EntityManager/PlayerLogic/Character.h"
#include "Items/Medical/MedicalStat.h"

class PickupItemLogic {
public:
    static PickupItemLogic* getInstance();
    void setupPickupListener(cocos2d::Node* sceneRoot, Character* character);

private:
    PickupItemLogic();
    ~PickupItemLogic();

    cocos2d::EventListenerPhysicsContact* _contactListener;
    Character* _character;
};

#endif // __PICKUP_ITEM_LOGIC_H__
