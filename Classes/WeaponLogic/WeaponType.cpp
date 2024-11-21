#include "WeaponType.h"

WeaponType::WeaponType()
{
    initializeWeaponTypes();
}

void WeaponType::initializeWeaponTypes()
{
    WeaponStat pistol1;
    pistol1._weaponID = 001;
    pistol1._weaponName = "Glock 17";
    pistol1._category = "Handgun";
    pistol1._bulletType = "Kinetic";
    pistol1._fireSFX = "Revolver1.ogg";
    pistol1._reloadSFX = "reload_pistol.ogg";
    pistol1._bulletSprite = "pistol1";
    pistol1._gunChamber = "reload_pistolChamber.ogg";
    pistol1._atk = 10.0;
    pistol1._critChance = 20.0;
    pistol1._critDmg = 20.0;
    pistol1._piercingChance = 20;
    pistol1._armorDmg = 20;
    pistol1._totalAmmoMax = 50;
    pistol1._weaponMag = 12;
    pistol1._bulletVelocity = 400.0;
    pistol1._ammoType = 9;
    pistol1._reloadTime = 2.5;

    WeaponStat smg1;
    smg1._weaponID = 002;
    smg1._weaponName = "Mp9";
    smg1._category = "Submachine Gun";
    smg1._bulletType = "Kinetic";
    smg1._fireSFX = "SMGsingleShot1.ogg";
    smg1._reloadSFX = "reload_smg.ogg";
    smg1._bulletSprite = "ar1";
    smg1._atk = 20.0;
    smg1._critChance = 100.0;
    smg1._critDmg = 50.0;
    smg1._piercingChance = 100.0;
    smg1._armorDmg = 30.0;
    smg1._totalAmmoMax = 100;
    smg1._weaponMag = 30;
    smg1._bulletVelocity = 450.0;
    smg1._ammoType = 45;
    smg1._reloadTime = 3.0;

    WeaponStat ar1;
    ar1._weaponID = 003;
    ar1._weaponName = "M4A1";
    ar1._category = "Assault Rifle";
    ar1._fireSFX = "Revolver1.ogg";
    ar1._bulletSprite = "m4a1bullet";
    ar1._atk = 30;
    ar1._totalAmmoMax = 180;
    ar1._weaponMag = 30;
    ar1._ammoType = 5.56;

    WeaponStat launcher1;
    launcher1._weaponID = 004;
    launcher1._weaponName = "RPG-7";
    launcher1._category = "Anti-Tank Launcher";
    /*launcher1._bulletType = "High Explosive";*/
    launcher1._bulletType = "Kinetic";
    launcher1._fireSFX = "fire_rocket.ogg";
    launcher1._reloadSFX = "reload_RPG.ogg";
    launcher1._bulletSprite = "launcher1";
    launcher1._gunChamber = "reload_RPGLoad.ogg";
    launcher1._atk = 150.0;
    launcher1._critChance = 80.0;
    launcher1._critDmg = 300.0;
    launcher1._piercingChance = 100;
    launcher1._armorDmg = 200;
    launcher1._totalAmmoMax = 10;
    launcher1._weaponMag = 1;
    launcher1._bulletVelocity = 350.0;
    launcher1._ammoType = 40;
    launcher1._reloadTime = 4.5;

    _weaponStats[pistol1._weaponID] = pistol1;
    _weaponStats[smg1._weaponID] = smg1;
    _weaponStats[ar1._weaponID] = ar1;
    _weaponStats[launcher1._weaponID] = launcher1;
}

WeaponStat WeaponType::getWeaponStatByID(int weaponID)
{
    return _weaponStats.count(weaponID) ? _weaponStats[weaponID] : WeaponStat();
}