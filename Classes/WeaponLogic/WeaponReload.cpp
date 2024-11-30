#include "WeaponReload.h"

const int RELOAD_ACTION_TAG = 1001;

WeaponReload::WeaponReload(AmmoManager& ammoManager, const WeaponStat& weaponStat)
    : _ammoManager(ammoManager), _weaponStat(weaponStat), _isReloading(false), _reloadSFXID(-1) {}

void WeaponReload::startReload(cocos2d::Node* scene) {
    if (_isReloading || _ammoManager.getCurrentAmmo() == _ammoManager.getMaxMagCapacity()) {
        return;
    }

    _isReloading = true;
    CCLOG("Reloading...");

    /*_reloadSFXID = AudioManager::getInstance()->playSFX(_weaponStat._reloadSFX);*/

    float reloadTime = _weaponStat._reloadTime;

    auto delay = cocos2d::DelayTime::create(reloadTime);
    auto reloadComplete = cocos2d::CallFunc::create([this]() {
        int maxReload = _ammoManager.getMaxMagCapacity() - _ammoManager.getCurrentAmmo();
        int reloaded = _ammoManager.reload(maxReload);
        _isReloading = false;

        AudioManager::getInstance()->stopSFX(_reloadSFXID);
        CCLOG("Reloaded %d bullets.", reloaded);
        });

    auto reloadSequence = cocos2d::Sequence::create(delay, reloadComplete, nullptr);
    reloadSequence->setTag(RELOAD_ACTION_TAG);

    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("update_ammo_display");

    scene->stopActionByTag(RELOAD_ACTION_TAG);
    scene->runAction(reloadSequence);
}

void WeaponReload::cancelReload(cocos2d::Node* scene) {
    if (_isReloading) {
        _isReloading = false;
        CCLOG("Reload canceled.");
        scene->stopActionByTag(RELOAD_ACTION_TAG);
        AudioManager::getInstance()->stopSFX(_reloadSFXID);
    }
}