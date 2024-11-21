#include "BulletType.h"
#include "EntityManager/IDamageable.h"

BulletType::BulletType(const std::string& name)
    : _name(name) {}

void BulletType::onHit(cocos2d::Node* bullet, cocos2d::Node* target, float damage) {
}

void KineticBulletType::onHit(cocos2d::Node* bullet, cocos2d::Node* target, float damage) {
    if (auto damageable = dynamic_cast<IDamageable*>(target)) {
        float finalDamage = damage;

        if (auto enemy = dynamic_cast<Enemy*>(target)) {
            auto entityStat = enemy->getEntityStat(); 
            auto weaponStat = enemy->getWeaponStat(); 

            if (entityStat._armor > 0) {
                if (rand() % 100 < std::min(weaponStat->_piercingChance, 100.0f)) { 
                    finalDamage = damage;  
                    CCLOG("Armor piercing successful: Damage remains at original: %.2f", finalDamage);
                }
                else {
                    finalDamage -= weaponStat->_armorDmg;
                    finalDamage = std::max(finalDamage, 0.0f);  
                    CCLOG("Hit armor: Final damage after armor reduction: %.2f", finalDamage);
                }
            }
        }

        // Kiểm tra chí mạng (Crit)
        if (auto enemy = dynamic_cast<Enemy*>(target)) {
            auto weaponStat = enemy->getWeaponStat();  
            if (rand() % 100 < weaponStat->_critChance) {
                finalDamage *= weaponStat->_critDmg;
                CCLOG("Critical hit! Final damage: %.2f", finalDamage); 
            }
            else {
                CCLOG("No critical hit. Damage: %.2f", finalDamage); 
            }
        }

        damageable->takeDame(finalDamage);
        CCLOG("Final damage dealt: %.2f", finalDamage);  
    }
}
