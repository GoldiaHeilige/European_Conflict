#ifndef __WEAPON_STAT_H__
#define __WEAPON_STAT_H__

#include <string>

class WeaponStat
{
public:
    int _weaponID;                // ID của vũ khí
    std::string _weaponName;      // Tên vũ khí
    std::string _category;        // Loại vũ khí
    std::string _bulletType;      // Loại đạn của vũ khí (eg. đạn nổ, cháy,....)
    std::string _fireSFX;       // Âm thanh khi bắn
    std::string _reloadSFX;     // Âm thanh thay đạn
    std::string _bulletSprite;    // Sprite của đạn
    std::string _gunSprite;    // Sprite súng chưa có sprite súng nên thêm sau
    std::string _gunChamber;    // SFX đổi súng

    float _atk;                   // Sát thương của vũ khí (e.g., 10.5 damage)
    float _critChance;            // Tỉ lệ sát thương chí mạng (e.g., 25.5% crit chance)
    float _critDmg;               // Dmg sát thương chí mạng (e.g., 2.0x damage)
    float _piercingChance;        // Tỉ lệ xuyên giáp và gây trực tiếp damage = _atk
    float _armorDmg;             // Dmg sát thương cho áo giáp
    int _totalAmmoMax;            // Số đạn tối đa
    int _weaponMag;               // Số đạn trong mỗi băng đạn
    float _bulletVelocity;        // Tốc độ bắn của đạn (e.g., 300.5)
    float _ammoType;              // Cỡ đạn (9mm, 45mm, 5.56mm, 7.62mm, ...
    float _reloadTime;           // Thời gian thay đạn

    WeaponStat()
        : _weaponID(0), _atk(0), _critChance(0), _critDmg(0), _piercingChance(0), 
        _armorDmg(0), _totalAmmoMax(0), _weaponMag(0),
        _bulletVelocity(0), _ammoType(0), _reloadTime(0) {}
};  

#endif // __WEAPON_STAT_H__
