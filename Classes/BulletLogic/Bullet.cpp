#include "Bullet.h"
#include "EntityManager/IDamageable.h"
#include "PhysicsCategory.h"
#include <typeinfo>

Bullet* Bullet::create(Entity* entity, std::string bulletSprite)
{
    Bullet* newObj = new Bullet();
    if (newObj != nullptr && newObj->init(entity, bulletSprite)) {
        newObj->autorelease();
        return newObj;
    }
    CC_SAFE_DELETE(newObj);
    return nullptr;
}

bool Bullet::init(Entity* entity, const std::string& bulletSprite)
{
    if (!Node::init()) {
        return false;
    }

    _entity = entity;

    std::string bulletSpritePath = "Bullet/" + bulletSprite + ".png";
    _model = Sprite::create(bulletSpritePath);

    if (!_model) {
        CCLOG("Error: Could not load bullet sprite from path: %s", bulletSpritePath.c_str());
        return false;
    }

    auto body = PhysicsBody::createCircle(_model->getContentSize().width / 3.9);
    body->setCategoryBitmask(PhysicsCategory::BULLET);
    body->setContactTestBitmask(PhysicsCategory::ENEMY | PhysicsCategory::STATIC_OBJECT | PhysicsCategory::PLAYER);
    body->setCollisionBitmask(PhysicsCategory::ENEMY | PhysicsCategory::STATIC_OBJECT | PhysicsCategory::PLAYER);
    this->setPhysicsBody(body);

    auto physicListener = EventListenerPhysicsContact::create();
    physicListener->onContactBegin = CC_CALLBACK_1(Bullet::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(physicListener, this);

    this->scheduleOnce([this](float) {
        this->removeFromParentAndCleanup(true);
        }, 10.0f, "remove_bullet_after_10_seconds");

    this->addChild(_model);
    return true;
}

void Bullet::fire(cocos2d::Vec2 direction, float velocity)
{
    getPhysicsBody()->setVelocity(direction * velocity);
}

bool Bullet::onContactBegin(cocos2d::PhysicsContact& contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    auto bullet = (nodeA == this) ? nodeA : (nodeB == this) ? nodeB : nullptr;
    auto target = (nodeA == this) ? nodeB : nodeA;

    if (bullet && target) {

        if (auto damageable = dynamic_cast<IDamageable*>(target)) {
            CCLOG("Target is damageable!");
            onHit(damageable); // Call onHit, which can be overridden by subclasses
        }
        else {
            CCLOG("Target is not damageable.");
            onHitNonDamageable();
        }

        this->removeFromParentAndCleanup(true); 
    }

    //if (nodeA && nodeB) {
    //    int categoryA = contact.getShapeA()->getBody()->getCategoryBitmask();
    //    int categoryB = contact.getShapeB()->getBody()->getCategoryBitmask();

    //    // Ví dụ: Kiểm tra va chạm giữa đạn và Enemy
    //    if (categoryA == PhysicsCategory::ENEMY || categoryB == PhysicsCategory::ENEMY) {
    //        CCLOG("Bullet hit an enemy");
    //        // Xử lý va chạm
    //    }

    //    // Kiểm tra va chạm giữa đạn và Static Object
    //    if (categoryA == PhysicsCategory::STATIC_OBJECT || categoryB == PhysicsCategory::STATIC_OBJECT) {
    //        CCLOG("Bullet hit a static object");
    //        // Xử lý va chạm
    //    }

    //    // Kiểm tra va chạm giữa đạn và Player
    //    if (categoryA == PhysicsCategory::PLAYER || categoryB == PhysicsCategory::PLAYER) {
    //        CCLOG("Bullet hit the player");
    //        // Xử lý va chạm
    //    }
    //}

    return true;
}

void Bullet::onHit(IDamageable* target) {
    // Default behavior does nothing, but can be overridden by subclasses
    CCLOG("Default onHit: Bullet hit target, but no effect in base class.");
}

void Bullet::onHitNonDamageable() {
    // Phương thức này có thể được override trong các lớp con nếu cần
    CCLOG("Base Bullet: Hit non-damageable target, no action in base class.");
}