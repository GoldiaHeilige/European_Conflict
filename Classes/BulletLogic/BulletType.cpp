#include "BulletType.h"
#include "EntityManager/IDamageable.h"

BulletType::BulletType(const std::string& name)
    : _name(name) {}

void BulletType::onHit(cocos2d::Node* bullet, cocos2d::Node* target, float damage) {
}

void KineticBulletType::onHit(cocos2d::Node* bullet, cocos2d::Node* target, float damage) {
    if (auto damageable = dynamic_cast<IDamageable*>(target)) {
        float finalDamage = damage;

        // Kiểm tra xuyên giáp
        if (auto enemy = dynamic_cast<Enemy*>(target)) {
            // Lấy thông tin stat và weapon stat của enemy
            auto entityStat = enemy->getEntityStat();  // Đảm bảo lấy đúng EntityStat
            auto weaponStat = enemy->getWeaponStat();  // Đảm bảo lấy đúng WeaponStat

            // Kiểm tra nếu Enemy có giáp
            if (entityStat._armor > 0) {
                // Xác định tỷ lệ xuyên giáp
                if (rand() % 100 < std::min(weaponStat->_piercingChance, 100.0f)) {  // Giới hạn piercingChance <= 100
                    finalDamage = damage;  // Xuyên giáp thành công, dùng sát thương gốc
                    CCLOG("Armor piercing successful: Damage remains at original: %.2f", finalDamage);
                }
                else {
                    finalDamage -= weaponStat->_armorDmg;
                    finalDamage = std::max(finalDamage, 0.0f);  // Đảm bảo sát thương không bị âm
                    CCLOG("Hit armor: Final damage after armor reduction: %.2f", finalDamage);
                }
            }
        }

        // Kiểm tra chí mạng (Crit)
        if (auto enemy = dynamic_cast<Enemy*>(target)) {
            auto weaponStat = enemy->getWeaponStat();  // Lấy lại weaponStat từ enemy
            if (rand() % 100 < weaponStat->_critChance) {
                finalDamage *= weaponStat->_critDmg;
                CCLOG("Critical hit! Final damage: %.2f", finalDamage); // Chí mạng thành công
            }
            else {
                CCLOG("No critical hit. Damage: %.2f", finalDamage); // Không có chí mạng
            }
        }

        // Gây sát thương lên Entity
        damageable->takeDame(finalDamage);
        CCLOG("Final damage dealt: %.2f", finalDamage);  // Gây sát thương
    }
}
