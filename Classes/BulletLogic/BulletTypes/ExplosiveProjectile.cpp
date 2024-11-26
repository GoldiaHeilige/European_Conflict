#include "ExplosiveProjectile.h"
#include "WeaponLogic/WeaponCtrl.h"
#include "cocos2d.h"
#include "AnimManager/AnimationUtils.h"  

USING_NS_CC;

ExplosiveProjectile* ExplosiveProjectile::create(Entity* entity, const std::string& bulletSprite)
{
    ExplosiveProjectile* newProjectile = new ExplosiveProjectile();
    if (newProjectile && newProjectile->init(entity, bulletSprite)) {
        newProjectile->_explosiveDamage = WeaponCtrl::getInstance()->getCurrentWeaponStat()._atk;
        newProjectile->_damageRadius = 100.0f;  // Adjust Radius Damage here
        newProjectile->autorelease();
        return newProjectile;
    }

    CC_SAFE_DELETE(newProjectile);
    return nullptr;
}

void ExplosiveProjectile::onHit(IDamageable* target)
{
    CCLOG("Explosive projectile hit the target!");
    if (target) {
        /*_impactSFXID = AudioManager::getInstance()->playSFX("explode_rocket4.ogg");*/

        AnimationUtils::loadSpriteFrameCache("Effects/Weapon Effect/", "LauncherExplosion");
        auto explodeAnim = AnimationUtils::createAnimation("LauncherExplosion", 1.2f);
        auto animateExplode = Animate::create(explodeAnim.first);

        auto explodeSprite = Sprite::createWithSpriteFrameName("./LauncherExplosion (1)");
        Vec2 projectilePos = this->getPosition();
        explodeSprite->setPosition(projectilePos);
        explodeSprite->setScale(2.0);

        this->getParent()->addChild(explodeSprite, 200);

        explodeSprite->runAction(Sequence::create(animateExplode, CallFunc::create([explodeSprite]() {
            explodeSprite->removeFromParentAndCleanup(true);
            }), nullptr));

        applyExplosionDamage(this->getPosition());

    }
}

void ExplosiveProjectile::applyExplosionDamage(const Vec2& explosionCenter)
{
    _explosiveDamage = WeaponCtrl::getInstance()->getCurrentWeaponStat()._atk;

    auto scene = Director::getInstance()->getRunningScene();
    auto entities = scene->getChildren();

    for (auto& entity : entities) {
        if (auto damageableEntity = dynamic_cast<IDamageable*>(entity)) {
            float distance = explosionCenter.distance(entity->getPosition());
            if (distance <= _damageRadius) {

                damageableEntity->takeDame(_explosiveDamage);
                CCLOG("Entity in radius took %f damage!", _explosiveDamage);
            }
        }
    }
}


void ExplosiveProjectile::onHitNonDamageable() {
    CCLOG("Explosive projectile hit a non-damageable object!");
    /*_impactSFXID = AudioManager::getInstance()->playSFX("explode_rocket4.ogg");*/

    AnimationUtils::loadSpriteFrameCache("Effects/Weapon Effect/", "LauncherExplosion");
    auto explodeAnim = AnimationUtils::createAnimation("LauncherExplosion", 1.2f);
    auto animateExplode = Animate::create(explodeAnim.first);

    auto explodeSprite = Sprite::createWithSpriteFrameName("./LauncherExplosion (1)");
    Vec2 worldPosition = this->getParent()->convertToWorldSpace(this->getPosition());
    explodeSprite->setScale(2.0);
    explodeSprite->setPosition(worldPosition);

    auto scene = Director::getInstance()->getRunningScene();
    scene->addChild(explodeSprite, 200);

    explodeSprite->runAction(Sequence::create(animateExplode, CallFunc::create([explodeSprite]() {
        explodeSprite->removeFromParentAndCleanup(true);
        }), nullptr));

    applyExplosionDamage(worldPosition);
}