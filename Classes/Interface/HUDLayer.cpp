#include "HUDLayer.h"

HUDLayer::HUDLayer()
    : _ammoLabel(nullptr), _totalAmmoLabel(nullptr),
    _currentAmmo(0), _totalAmmo(0) {}

HUDLayer::~HUDLayer() {}

HUDLayer* HUDLayer::create()
{
    HUDLayer* ret = new HUDLayer();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        delete ret;
        return nullptr;
    }
}

bool HUDLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();

    _ammoLabel = Label::createWithSystemFont("Ammo: 0", "Arial", 24);
    _ammoLabel->setPosition(visibleOrigin.x + visibleSize.width - 150, visibleOrigin.y + 50);
    this->addChild(_ammoLabel);

    _totalAmmoLabel = Label::createWithSystemFont("Total Ammo: 0", "Arial", 24);
    _totalAmmoLabel->setPosition(visibleOrigin.x + visibleSize.width - 150, visibleOrigin.y + 20);
    this->addChild(_totalAmmoLabel);

    auto listener = EventListenerCustom::create("update_ammo_display", [this](EventCustom* event) {
        updateAmmoDisplay();
        });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void HUDLayer::updateAmmoDisplay()
{
    _currentAmmo = WeaponCtrl::getInstance()->getCurrentAmmo();
    _totalAmmo = WeaponCtrl::getInstance()->getTotalAmmo();

    _ammoLabel->setString("Ammo: " + std::to_string(_currentAmmo));
    _totalAmmoLabel->setString("Total Ammo: " + std::to_string(_totalAmmo));
}