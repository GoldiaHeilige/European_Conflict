#include "KineticProjectile.h"
#include "WeaponLogic/WeaponCtrl.h"
#include "EntityManager/Enemy.h"
#include <vector>
#include <cstdlib>

KineticProjectile* KineticProjectile::create(Entity* entity, const std::string& bulletSprite)
{
    KineticProjectile* newProjectile = new KineticProjectile();
    if (newProjectile && newProjectile->init(entity, bulletSprite)) {
        newProjectile->_dmg = WeaponCtrl::getInstance()->getCurrentWeaponStat()._atk;
        newProjectile->autorelease();
        return newProjectile;
    }

    CC_SAFE_DELETE(newProjectile);
    return nullptr;
}

void KineticProjectile::onHit(IDamageable* target)
{
    CCLOG("Kinetic projectile hit the target! Damage: %f", _dmg);

    // Tạo danh sách các file âm thanh cho va chạm với Entity
    std::vector<std::string> hitEntitySounds = {
        "hit_zombie1.ogg"
        "hit_zombie2.ogg",
        "hit_zombie3.ogg",
        "hit_zombie4.ogg"
    };

    std::string selectedSFX;

    if (target) {
        int randomIndex = rand() % hitEntitySounds.size(); 
        selectedSFX = hitEntitySounds[randomIndex];
        /*_impactSFXID = AudioManager::getInstance()->playSFX(selectedSFX);*/

        target->takeDame(_dmg); 
    }
}

void KineticProjectile::onHitNonDamageable() {
    std::vector<std::string> hitSpriteSounds = {
        "ricochet1.ogg",
        "ricochet2.ogg",
        "ricochet3.ogg"
    };

    int index = rand() % hitSpriteSounds.size();  
    std::string soundFile = hitSpriteSounds[index];
    /*_impactSFXID = AudioManager::getInstance()->playSFX(soundFile);*/
}