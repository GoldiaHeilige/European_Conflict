#include "WeaponCtrl.h"
#include "WeaponFire.h"

WeaponCtrl* WeaponCtrl::_instance = nullptr;

WeaponCtrl* WeaponCtrl::getInstance() {
    if (_instance == nullptr) {
        _instance = new WeaponCtrl();
    }
    return _instance;
}

WeaponCtrl::WeaponCtrl()
    : _currentWeaponID(0) {}

WeaponCtrl::~WeaponCtrl() {}

WeaponStat WeaponCtrl::getCurrentWeaponStat() const {
    return _currentWeaponStat;
}

void WeaponCtrl::setCurrentWeapon(int weaponID) {
    auto scene = cocos2d::Director::getInstance()->getRunningScene();

    if (_weaponType.getWeaponStatByID(weaponID)._weaponID == 0) {
        CCLOG("Invalid Weapon ID: %d", weaponID);
        return;
    }

    if (_weaponReload && _weaponReload->isReloading()) {
        if (_currentWeaponID == weaponID) {
            CCLOG("You are already using this weapon. Reloading will continue.");
            return;
        }
        CCLOG("Canceling reload before switching weapons.");
        _weaponReload->cancelReload(scene);
    }

    if (_currentWeaponID > 0) {  // Chỉ cache nếu đã có vũ khí trước đó
        _ammoCache[_currentWeaponID] = _ammoManager.getCurrentAmmo();
        _totalAmmoCache[_currentWeaponID] = _ammoManager.getTotalAmmo();
    }

    _currentWeaponID = weaponID;
    _currentWeaponStat = _weaponType.getWeaponStatByID(weaponID);

    if (_ammoCache.find(weaponID) != _ammoCache.end()) {
        _ammoManager.setCurrentAmmo(_ammoCache[weaponID]);
        _ammoManager.setTotalAmmo(_totalAmmoCache[weaponID]);
    }
    else {
        _ammoManager.initializeAmmo(_currentWeaponStat);
    }

    _ammoManager.setMaxMagCapacity(_currentWeaponStat._weaponMag);

    _weaponReload = std::make_unique<WeaponReload>(_ammoManager, _currentWeaponStat);

    CCLOG("Weapon switched to ID: %d", weaponID);
    CCLOG("Current Ammo: %d / %d", _ammoManager.getCurrentAmmo(), _ammoManager.getTotalAmmo());
}

void WeaponCtrl::fireBullet(cocos2d::Node* characterNode, const cocos2d::Vec2& direction) {

    if (_currentWeaponID == 0 || _currentWeaponStat._weaponID == 0) {
        CCLOG("Error: Attempted to fire an invalid weapon (ID = %d).", _currentWeaponID);
        return;
    }

    if (_weaponReload->isReloading()) {
        CCLOG("Cannot fire while reloading.");
        return;
    }

    if (_ammoManager.getCurrentAmmo() > 0) {
        WeaponFire::fireBullet(characterNode, direction, _currentWeaponStat, _ammoManager);
        _ammoManager.updateAmmo(1);
    }
    else {
        CCLOG("No ammo left in magazine. Unable to fire.");
    }
}

void WeaponCtrl::reload(cocos2d::Node* scene) {
    _weaponReload->startReload(scene);
}