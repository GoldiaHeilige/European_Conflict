﻿#ifndef __HUD_LAYER_H__
#define __HUD_LAYER_H__

#include "cocos2d.h"
#include "WeaponLogic/WeaponCtrl.h"  

USING_NS_CC;

class HUDLayer : public Layer
{
public:
    HUDLayer();
    ~HUDLayer();

    static HUDLayer* create();
    virtual bool init();

    void updateAmmoDisplay();
    void updateHUDPosition(Vec2 playerPosition);
    void updateWithPlayerPosition(Vec2 playerPosition);

private:
    Label* _ammoLabel;
    Label* _totalAmmoLabel;

    int _currentAmmo;
    int _totalAmmo;
};

#endif // __HUD_LAYER_H__