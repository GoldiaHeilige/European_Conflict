#include "Bullet.h"
#include <typeinfo>  

Bullet* Bullet::create(Entity* entity, const std::string& bulletSprite, BulletType* bulletType, float damage) {
    auto newObj = new Bullet();
    if (newObj && newObj->init(entity, bulletSprite, bulletType, damage)) {
        newObj->autorelease();
        return newObj;
    }
    CC_SAFE_DELETE(newObj);
    return nullptr;
}

bool Bullet::init(Entity* entity, const std::string& bulletSprite, BulletType* bulletType, float damage) {
    if (!Node::init()) {
        return false;
    }

    _entity = entity;
    _bulletType = bulletType;
    _damage = damage;

    std::string bulletSpritePath = "Bullet/" + bulletSprite + ".png";
    _model = Sprite::create(bulletSpritePath);

    if (!_model) {
        CCLOG("Error: Could not load bullet sprite from path: %s", bulletSpritePath.c_str());
        return false;
    }

    this->addChild(_model);

    // Tạo vật lý cho đạn
    auto body = PhysicsBody::createCircle(_model->getContentSize().width / 3.9);
    body->setContactTestBitmask(1);
    this->setPhysicsBody(body);

    // Lắng nghe va chạm
    auto physicListener = EventListenerPhysicsContact::create();
    physicListener->onContactBegin = CC_CALLBACK_1(Bullet::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(physicListener, this);

    // Xóa đạn sau 10 giây
    this->scheduleOnce([this](float) {
        this->removeFromParentAndCleanup(true);
        }, 10.0f, "remove_bullet_after_10_seconds");

    return true;
}

void Bullet::fire(const Vec2& direction, float velocity) {
    getPhysicsBody()->setVelocity(direction * velocity);
}

bool Bullet::onContactBegin(PhysicsContact& contact) {
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

    auto bullet = (nodeA == this) ? nodeA : (nodeB == this) ? nodeB : nullptr;
    auto target = (nodeA == this) ? nodeB : nodeA;

    if (bullet && target && _bulletType) {
        // Gọi logic va chạm của loại đạn, truyền sát thương
        _bulletType->onHit(this, target, _damage);
        this->removeFromParentAndCleanup(true);
    }
    return true;
}